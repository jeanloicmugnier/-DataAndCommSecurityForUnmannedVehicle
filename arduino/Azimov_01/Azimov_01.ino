// =================================================================================================
// Projet AZIMOV
//
// =================================================================================================
//                                      module principal
// =================================================================================================
const String CurrentRelease = "Azimov-V1-R1 a";    // version courante du logiciel
const String CompilationDate = "03/12/2015";          // date de compilation de la version



//#define LCD_DISPLAY true
#define SERIAL_CONSOLE true
#define SERIAL_RADIO true


// =================================================================================================
//                          inclusion des libraries et des fichier headers
// =================================================================================================

#include <SoftwareSerial.h>
#include <Wire.h>
/*
#include <LiquidCrystal.h>
*/

#include <LSM303.h>       // fichier de l'accelerometre-magnetometre LSM 303

#include "Telemetres.h"
#include "MotorShield.h"
#include "Azimov_01.h"

// =================================================================================================
//                                    displayMsg (String myMsg)
// =================================================================================================
void displayMsg (String myMsg) {

  // cette fonction affiche les message en fonction de la definbition de Console, LCD, 3DR, etc ..
  float timeStamp;

  // rajoute un horodatage
  timeStamp = millis() - absoluteTime;
  timeStamp = timeStamp / 1000 ;  // conversion en secondes
  myMsg = String(timeStamp) + "- " + myMsg;

#ifdef SERIAL_CONSOLE
  Serial.println (myMsg);    // affichage sur la console serie de l'IDE
#endif

#ifdef SERIAL_RADIO
  Serial1.println (myMsg);    // affichage sur RX-TX1 : radio 3DR
#endif

}

// =================================================================================================
//                                    calibrateLSM303(void)
// fonction de calibration du LSM 303
// Les valeurs par défaut de +/-32767 pour chacun des axes correspondent a un biais de
// magnétomètre "supposée" de 0.
// La fonction calibrate() pertmet de déterminer les valeurs appropriées pour une utilisation
// particulière.
//
// =================================================================================================
void calibrateLSM303(void) {

  compass.m_min = (LSM303::vector<int16_t>) {
    -32767, -32767, -32767
  };
  compass.m_max = (LSM303::vector<int16_t>) {
    +32767, +32767, +32767
  };
  delay(100);
}

// =================================================================================================
//                                      readHeading(void)
//
//   Sans  argument, la fonction heading() retourne la différence angulaire dans le plan horizontal
//   entre un vecteur par défaut et le Nord, en degrés.
//   Le vecteur par défaut est choisi par la bibliothèque poiunte  le long de la surface du circuit
//   imprimé, dans le sens de la partie supérieure du texte sur la sérigraphie. Il s'agit du l'axe X
//   sur le LSM303D et l'axe Y sur les LSM303DLHC, LSM303DLM et LSM303DLH.
//   Pour utiliser un vecteur différent comme une référence, utilisez heading() avec  un argument
//   vecteur.
//
//   Exemple pour utiliser l' axe Z comme référence :
//        compass.heading ((LSM303::vector<int>) {0, 0, 1}) ;
//
// =================================================================================================
float readHeading(void) {
  float heading = 0.0;

  // boucle de lecture du Cap
  for (int i = 0; i <= 100; i++) {
    compass.read();
    //heading = heading + compass.heading();
    heading = heading + compass.heading((LSM303::vector<int>){1, 0, 0});  // reference = +X axis
    delayMicroseconds(50);
  }
  heading = heading/100;     // calcul de la moyenne arithmetique du Cap
  return heading;
}


// =================================================================================================
//                               allignToCapCap(float consigneCap)
//
// float consigneCap : consigne de Cap en degre pour l'alignement
//    s'aligne sur le Cap donne par consigneCap
//    calculer la rotation a faire pour s'aligner avec le Cap
//    faire une rotation moteurs pour s'aligner avec le Cap
// =================================================================================================
void allignToCapCap(float consigneCap) {
  float currentCap = readHeading ();
  int angleRotation = 0;
  int sensRotation = 0;

  displayMsg ("Start ==> Cap Consigne : " + String(consigneCap));
  displayMsg ("Start ==>Cap Actuel   :  " + String(currentCap));

  // calculer la rotation a faire pour s'aligner avec le Cap
  if ((consigneCap + 180) >  currentCap ) {
    angleRotation = consigneCap - currentCap;
    if (angleRotation <= 0) {
      // effectuer une rotation a droite de  angleRotation
      sensRotation = DROITE;
      angleRotation = angleRotation;
    }
    else {
      // effectuer une rotation a gauche de  abds(angleRotation)
      sensRotation = GAUCHE;
      angleRotation = abs(angleRotation);
    }

  }
  else {
    sensRotation = GAUCHE;
    angleRotation = consigneCap + ( 360 - currentCap);
  }

  // boucle de rotation selon les valeurs definies ci-dessus
  if (angleRotation > 20)rotateMotor (speedMotorDesengage , sensRotation, angleRotation);
  else
    for (int i = 0; i <= abs(angleRotation / 10) + 1; i++) {
      rotateMotor (speedMotorDesengage , sensRotation, abs(angleRotation / 10));
    }

  stopFrein ;                               // activation des frein
  currentCap = readHeading ();
  displayMsg ("End ==> Cap Consigne : " + String(consigneCap));
  displayMsg ("End ==> Cap Actuel   :  " + String(currentCap));
  // speedMotor =  currentSpeedMotor;      // initialise l'ancienne vitesse
}

// =================================================================================================
//                                            followCap(float myCap)
//
//  float myCapa : consigne de Cap en degre a suivre
//  agit sur les moteurs pour que la trajectoire respecte le Cap donne en consigne
//    alignement sur le Cap : appel a allignToCapCap(float consigneCap)
//    maintien du Cap
//
// =================================================================================================
void followCap(float myCap) {

  float currentCap = readHeading ();     // lecture du cap actuel

  // allignement sur le Cap donne en consigne
  allignToCapCap(myCap);

  // maitien du Cap

  /*
  if ((myCap + 180) > currentCap ) {

  }

  */
}



// =================================================================================================
//                                    readDistanceSonarAvant(void)
// =================================================================================================
float readDistanceSonarAvant(void) {
  long Lecture_Echo;      // lecture de l'écho sonar frontal
  float distanceTV = 0.0;  // distance calculee par temps de vol
  float distanceAna = 0.0; // distance calculee par lecture analogique
  double voltage = 0;      // voltage (lecture analogique)

  switch ( flagAcquire) {
    case 99:
    case 0:  // init, on lit tous les capteurs dans toutes les directions
      // lecture de la distance a l'obstacle avec le telemetre frontal EZ MaxSonar

      // mode 1 : lecture de la duree en microsecondes (temps de vol)
      Lecture_Echo = pulseIn(EZ_tempsVol, HIGH);
      //5 8 uS per cm for MB1240 XL-MaxSonar Operation Range: 20 cm min (50 cm for accurate)
      distanceTV = Lecture_Echo / 58.0;

      // Mode 2 lecture d'une valeur analogique .49 mV per unit
      /*  travaille sur la plage 0-5 V avec 1024 pas (4.9 milliV par pas)
       *  la fonction analogRead utilise 100 microsec pour faire une lecture
       *  => taux d'echantillonage maxi = 10 000 / sec
       */
      voltage = analogRead(EZ_Analogique) *  0.0049 ;
      distanceAna = voltage / 0.0049 ;  //.49 mV per cm
      DistanceF =  (distanceTV +  distanceAna) / 2;   // moyenne des deux resultats
      if (flagAcquire == 0) break;

    case 1:
      // lecture de la distance a l'obstacle avec le telemetre a droite
      digitalWrite(TrigD, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigD, LOW);
      Lecture_Echo = pulseIn(EchoD, HIGH);
      DistanceD = Lecture_Echo / 58.0;
      if (flagAcquire == 1) break;

    case 2:
      // lecture de la distance a l'obstacle avec le telemetre a gauche
      digitalWrite(TrigG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigG, LOW);
      Lecture_Echo = pulseIn(EchoG, HIGH);
      DistanceG = Lecture_Echo / 58.0;
      if (flagAcquire == 2) break;
  }
  // determination de la distance mini et du cote de l'obstacle
  DistanceMin = min(DistanceF, min(DistanceG, DistanceD));
  if (DistanceMin == DistanceF)  flagObstacleSide = DEVANT;
  else {
    if (DistanceD < DistanceG)  flagObstacleSide = DROITE;
    else flagObstacleSide = GAUCHE;
  }
  /*
  // DEBUG
    displayMsg("Frontal : "+String(DistanceF));
    displayMsg("Droite  : "+String(DistanceD));
    displayMsg("Gauche  : "+String(DistanceG));
    displayMsg("Min     : "+String(DistanceMin));
    displayMsg("Cote    : "+String(flagObstacleSide));
  // end DEBUG
  */
  return DistanceMin;
}

// =================================================================================================
//                                   readDistanceSonarArriere(void)
// =================================================================================================
float readDistanceSonarArriere(void) {

  long Lecture_Echo;      // lecture de la duree de l'écho sonar arriere

  // lecture de la distance a l'obstacle avec le telemetre arriere
  digitalWrite(TrigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigR, LOW);
  Lecture_Echo = pulseIn(EchoR, HIGH);
  DistanceR = Lecture_Echo / 58.0;
  return DistanceR;
}


// =================================================================================================
//                                             initSonar(void)
// =================================================================================================
int initSonar(void) {
  // initialisation du telemetre frontal (anti-colision)
  pinMode(Trig, OUTPUT);
  digitalWrite(Trig, LOW);
  pinMode(Echo, INPUT);
  // initialisation du telemetre droit (anti-colision)
  pinMode(TrigD, OUTPUT);
  digitalWrite(TrigD, LOW);
  pinMode(EchoD, INPUT);
  // initialisation du telemetre gauche (anti-colision)
  pinMode(TrigG, OUTPUT);
  digitalWrite(TrigG, LOW);
  pinMode(EchoG, INPUT);
  // initialisation du telemetre arriere (anti-colision)
  pinMode(TrigR, OUTPUT);
  digitalWrite(TrigR, LOW);
  pinMode(EchoR, INPUT);

  // lecture de tous les telemetres pour initialiser les variables de distance
  readDistanceSonarAvant();
  readDistanceSonarArriere();
}


// =================================================================================================
//                                           initMotorShiled (void)
//  prepare le shield motor pour l'utilisation
//      configure les broches numeriques des moteur A et B en sorties
//      initialisation des moteur A et B :
//          vitesse = 0 (speedStop)
//          sens de la marche = marche avant (FORWARD)
//          frein relache (OFF)
//
// =================================================================================================
int initMotorShield (void) {

  // configure les broches numeriques du moteur A en sorties
  pinMode (vitesseMotA, OUTPUT);    // Broche vitesseMotA configuree en sortie
  pinMode (freinMotA, OUTPUT);      // Broche freinMotA configuree en sortie
  pinMode (sensMotA, OUTPUT);       // Broche sensMotA configuree en sortie

  // configure les broches numeriques du moteur B en sorties
  pinMode (vitesseMotB, OUTPUT);    // Broche vitesseMotB configuree en sortie
  pinMode (freinMotB, OUTPUT);      // Broche freinMotB configuree en sortie
  pinMode (sensMotB, OUTPUT);       // Broche senMotB configuree en sortie

  // initialisation moteur A
  digitalWrite(vitesseMotA, LOW);   // vitesse 0
  digitalWrite(sensMotA, LOW);      // marche avant
  digitalWrite(freinMotA, LOW);     // frein OFF

  // initialisation moteur B
  digitalWrite(vitesseMotB, LOW);   // vitesse 0
  digitalWrite(sensMotB, LOW);      // marche avant
  digitalWrite(freinMotB, LOW);     // frein OFF
}

// =================================================================================================
//                             cmdMotor (int speedMotor; int sensMotor)
// =================================================================================================
// int speedMotor : vitesse. valeurs = [0..255]
// int sensMotor  : sens de la marche. valeurs = [FORWARD,BACKWARD]
//
// configure les moteurs
//    enlever les frein
//    configurer le sens de marche selon sensMotor (FORWARD ou BACKWARD)
//    mettre a jour flagAction
//    regler la vitesse a la valeur speedMotor
//    sauvegarder la vitesse dans currentSpeedMotor
// =================================================================================================
int cmdMotor (int speedMotor , int sensMotor) {

  // mettre frein OFF
  digitalWrite(freinMotA, LOW);             // frein OFF moteur A
  digitalWrite(freinMotB, LOW);             // frein OFF moteur B

  // configutation du sens de marche
  if (sensMotor == FORWARD) {               // marche avant
    digitalWrite(sensMotA, LOW);            // LOW = avant moteur A
    digitalWrite(sensMotB, LOW);            // LOW = avant moteur B
    flagAction = FORWARD;                   //  mise a jour du flag action = marche avant
  }
  else {                                    // marche arriere
    digitalWrite(sensMotA, HIGH);           // HIGH = arriere moteur A
    digitalWrite(sensMotB, HIGH);           // HIGH = arriere moteur B
    flagAction = BACKWARD;                  //  mise a jour du flag action  = marche arriere
  }
  // configurer la vitesse sur les deux moteurs
  analogWrite(vitesseMotA, speedMotor);     // reglage de la vitesse en analogique via PWM
  analogWrite(vitesseMotB, speedMotor);     // reglage de la vitesse en analogique via PWM
  currentSpeedMotor = speedMotor;           // mise a jour de la vitesse actuelle
}


// =================================================================================================
//                                             int stopFrein(void)
// cette fonction arrete le mobile avec freinage
//    configure la vitesse des deux moteurs à speedStop
//    active les freins des deux moteurs
//    met a jour flagAction = STOP
//    temporisation de 50 millis secoindes (duree du freinage)
//    relache les freins des deux moteurs
//
// =================================================================================================
int stopFrein(void) {

  // configurer la vitesse
  analogWrite(vitesseMotA, speedStop);     // reglage de la vitesse en analogique via PWM
  analogWrite(vitesseMotB, speedStop);     // reglage de la vitesse en analogique via PWM
  // freinage sur les deux moteur
  digitalWrite(freinMotA, HIGH);           // frein ON
  digitalWrite(freinMotB, HIGH);           // frein ON
  flagAction = STOP;                       //  mise a jour du flag action
  delay(50);                               // temporisation avant de relacher les freins
  // desserer les freins des deux moteurs
  digitalWrite(freinMotA, LOW);           // frein OFF
  digitalWrite(freinMotB, LOW);           // frein OFF
}


// =================================================================================================
//                             int rotateMotor (int speedMotor , int sensRotate)
// =================================================================================================
int rotateMotor (int speedMotor , int sensRotate, int angleRotation) {
  int durationRotate  = 0;                          // duree de la rotation

  //displayMsg(" ==> int rotateMotor (int speedMotor , int sensRotate ");

  // configutation du sens de marche
  if (sensRotate == GAUCHE) {                       // rotation a droite
    digitalWrite(sensMotA, HIGH);                   // sens arriere moteur A
    digitalWrite(sensMotB, LOW);                    // sens  avant moteur B
  }
  else
  {
    digitalWrite(sensMotA, LOW);                    // sens avant moteur A
    digitalWrite(sensMotB, HIGH);                   // sens arriere moteur B
  }
  // configurer la vitesse
  analogWrite(vitesseMotA, speedMotor);             // reglage de la vitesse en analogique via PWM
  analogWrite(vitesseMotB, speedMotor);             // reglage de la vitesse en analogique via PWM

  // calcul de la temporisation (duree de la rotation)
  durationRotate = int(angleRotation * cteAngleDelay ) ;   // cteAngleDelay = 8.88
  //displayMsg(" ==> Rotation de : " + String(angleRotation));
  delay (durationRotate);

  return durationRotate;
}

// =================================================================================================
//                                       desengageObstacle(void)
// =================================================================================================
void desengageObstacle(void) {

  // marche arriere lente valeur = desengageRetroDistance (1000 mS = 10 cm)
  flagAction == BACKWARD;                                               // mise a jour du flag
  cmdMotor (speedMotorMini, BACKWARD);                                  // reculer de desengageRetroDistance (20 cm)
  delay (2000);

  // rotation du cote opose a l'obstacle, angle = desengageRotation
  // l'obstacle est sur les cotes
  if (flagObstacleSide == DROITE)
    rotateMotor (speedMotorDesengage , GAUCHE, desengageRotationLOW );  // obstacle le plus proche a droite = rotation a gauche
  else if (flagObstacleSide == GAUCHE)
    rotateMotor (speedMotorDesengage , DROITE, desengageRotationLOW);  // obstacle le plus proche a gauche = rotation a droite

  // l'obstacle est devant
  if (flagObstacleSide == DEVANT) {
    // tourner du cote ou il a le plus de place
    if (DistanceD < DistanceG)
      rotateMotor (speedMotorDesengage , GAUCHE, desengageRotationHIGH);                              // rotation a droite
    else if (DistanceD > DistanceG)
      rotateMotor (speedMotorDesengage , DROITE, desengageRotationHIGH);                              //  rotation a gauche
    if (DistanceG == DistanceD)
      // choix aleatoire d'un cote pour tourner
      if (random(1, 3) == 1)  rotateMotor (speedMotorDesengage , DROITE, desengageRotationHIGH);      // rotation a droite
      else rotateMotor (speedMotorDesengage , GAUCHE, desengageRotationHIGH);                         // rotation a gauche
  }

  // l'obstacle est derriere
  if (flagObstacleSide == DERRIERE) {
    if (DistanceD < DistanceG) rotateMotor (speedMotorDesengage , GAUCHE, desengageRotationHIGH);  // rotation a droite
    else if (DistanceD >= DistanceG)
      rotateMotor (speedMotorDesengage , DROITE, desengageRotationHIGH);                        //  rotation a gauche
  }
  else {
    // choix aleatoire d'un cote pour tourner
    if (random(1, 3) == 1)  rotateMotor (speedMotorDesengage , DROITE, desengageRotationHIGH);     //  rotation a droite
    else rotateMotor (speedMotorDesengage , GAUCHE, desengageRotationHIGH);                        //  rotation a gauche
  }

  // on repars en avant avec la vitesse normale
  displayMsg ("Retour aux consignes .....");
  flagAction == FORWARD;                                                    // mise a jour du flag
  cmdMotor (speedMotorConsigne, FORWARD);

}

// =================================================================================================
//                                           detecteObstacle(void)
// =================================================================================================
void detecteObstacle(void) {

boolean OnDEBUG = true;   // afichage des informations detaillé pour mise au point

  if (flagAction == FORWARD) {
    readDistanceSonarAvant();             // lecture des telemetres avant
    displayMsg("DEBUG : detecteObstacle() => flagAction == FORWARD");
    if (DistanceMin >= greenFlag) { }
    else {
      if (DistanceMin >= redFlag) {
        if (currentSpeedMotor > speedMotorDesengage) {
          if (OnDEBUG) displayMsg("Zone Jaune. D min : " + String(DistanceF) + " Reduction vitesse");
          cmdMotor (speedMotorDesengage, FORWARD);  // reduire la vitesse a la vitesse de manoeuvre
        }
      }
      else if (DistanceMin < redFlag) {
        if (OnDEBUG) displayMsg("Zone rouge. D min : " + String(DistanceF) + "Arret des moteurs");
        stopFrein();
        desengageObstacle();            // desengager l'obstacle
      }
    }
  }       // end flagAction == FORWARD
  else if (flagAction == BACKWARD) {
    // gestion des obstacle en marche arriere
    readDistanceSonarArriere();    // lecture du telemetre arriere
  }

  // affichage de la distance min et du cote DEBUG
  if (OnDEBUG) displayMsg ("Dist : " + String(DistanceMin) + " Cote (0=F, 1=D, 2=G, 3=R.) : " + String( flagObstacleSide));
}


// =================================================================================================
//                         int initSerials (int myPort , long baudRate)
// int myPort : ID du port a utiliser. valeurs 0=Serial, 1=Serial1, etc.
// long baudRate : vitesse du port à configuer. valeurs = [300 .. 250000]. defaut = 115000
// =================================================================================================
int initSerials (int myPort , long baudRate) {

  // initilisation de la ligne serie pour la console
  if (myPort == SERIALCONSOL) Serial.begin(baudRate);
  // initilisation de la ligne serie telemetrie radio 3DR
  if (myPort == SERIALRADIO) Serial1.begin(baudRate);
}


// =================================================================================================
//                                                    setup(void)
// fonction d'initialisation
//      initialisation des lignes series utilisees parametre = vitesse
//      initialisation des telemetres
//      initialisation d ela carte Shield Motor
//      initialisation accelerometre-magnetometre :
//          initialiser le liaison Wire
//          initialisation du compas LSM 303
//          configuratiuon des valeurs par defaut du compas LSM 303
//          appel a la fonction de calibration du compas LSM 303
//      initialisation du compteur de temps
//          definition de absoluteTime
//
// =================================================================================================
void setup(void) {

#ifdef SERIAL_CONSOLE
  initSerials(SERIALCONSOL, 115200);       // initilisation de la ligne serie pour la console
#endif

#ifdef  SERIAL_RADIO
  initSerials(SERIALRADIO, 115200);       // initilisation de la ligne serie RX1 TX1 pour la liaison 3DR
#endif

  // initSerials(SERIALCONSOL, 115200);                        // initialisation des lignes series utilisees
  displayMsg ("Programme AZIMOV : initialisation ...");
  displayMsg ("Current Release: " + CurrentRelease);        // version de logiciel
  displayMsg ("Compliation du : " + CompilationDate);       // date de compilation
  displayMsg (" ");

  displayMsg ("Initialisation Serials .....");

  /*
    LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // initialisatuion de la library LCD
  */

  displayMsg ("Initialisation des telemetres .....");
  initSonar();                                            // initialisation de telemetres accoustiques
  displayMsg ("Initialisation de l'electronique moteurs .....");
  initMotorShield ();                                     // initialise le motorschield

  // initialisation accelerometre-magnetometre
  Wire.begin();
  displayMsg ("Calibration accelerometre et magnetometre .....");
  compass.init();
  compass.enableDefault();
  calibrateLSM303();

  // initialisation du compteur de temps
  displayMsg ("Initialisation des timers .....");
  absoluteTime = millis();    // initialisation du temps 0 absolu
  displayMsg (" ");
  displayMsg ("AZIMOV : Initialisation terminee ...... ");
  displayMsg (" ");
}

// =================================================================================================
//                                                 loop(void)
// boucle principale
//    attend un message sur le serial configuré (Console (Serial) ou telemetrie radio 3DR (Serial1)
//       gere le code action reçu
//    gestion du changement d'etat de flagAcquire
//    sauvergarde la vitesse programmee dans speedMotorConsigne
//    lecture de tous les telemetres avant
//    appel de la fonction detecteObstacle()
//
// =================================================================================================
void loop(void) {
  float myCap = 0.0;
  int randNumber = 0;

  if (Serial1.available() > 0) {
    int inByte = Serial1.read();
    switch (inByte) {

      // =================================== CMD de tests =================================
      case '1' :   // test des capteurs sonar
        readDistanceSonarAvant();
        readDistanceSonarArriere();
        displayMsg ("Distance avant   :" + String(DistanceF) + " cm");
        displayMsg ("Distance droite  :" + String(DistanceD) + " cm");
        displayMsg ("Distance gauche  :" + String(DistanceG) + " cm");
        displayMsg ("Distance arriere :" + String(DistanceR) + " cm");
        break;

      case '2' :   // test des moteurs
        displayMsg ("Test des moteurs");
        for (int i = speedMotorMini; i < speedMotorMaxi; i = i + 10) {
          displayMsg ("Vitesse = " + String(i));
          cmdMotor (i, FORWARD);
          delay(1000);
        }
        cmdMotor (0 , FORWARD);
        break;

      case '3' :   // test du magnetometre
        displayMsg ("Test accelerometre-magnetometre");
        myCap = readHeading ();
        delay(200);
        displayMsg("Cap = " + String(myCap));
        break;

      case '4' :  // test du suivi de Cap
        displayMsg ("Test suivi de Cap 310");
        followCap(310);    // suivre le cap 310
        stopFrein();
        break;

      case '5' :  // test de rotation
        displayMsg ("Test de rotation : 90 Droite");
        myCap = readHeading ();
        displayMsg("Cap = " + String(myCap));
        rotateMotor (speedMotorDesengage, DROITE, 90);
        stopFrein();
        delay(200);
        myCap = readHeading ();
        displayMsg("Cap = " + String(myCap)); break;

      // ========================================== fin CMD de tests =================================

      case 'a' :  // marche avant
        displayMsg ("Marche avant.....");
        cmdMotor (150, FORWARD);
        break;

      case 'r' :  // marche arriere
        displayMsg ("Marche arriere .....");
        cmdMotor (150, BACKWARD);
        break;

      case 's' :  // stop
        displayMsg ("Arret des Moteurs .....");
        stopFrein();
        break;

      case 'd' :  // virage 90 degres a droite
        displayMsg ("90 deg droite.....");
        rotateMotor (speedMotorDesengage, DROITE, 90);
        stopFrein();
        break;

      case 'g' :  // virage 90 degres a gauchee
        displayMsg ("90 deg gauche.....");
        rotateMotor (speedMotorDesengage, GAUCHE, 90);
        stopFrein();
        break;
        
      default:
        displayMsg ("Sequence non reconue : " + String(inByte));

    } // end switch
  }  // end read serial1

  
    // gestion du changement d'etat de flagAcquire ====================================================
    switch (flagAcquire) {
      case 0:
      case 1: flagAcquire++;
        break;
      //case 99:aa
      case 2: flagAcquire = 0;
        break;
    }
  

  speedMotorConsigne = currentSpeedMotor;   // sauvegarde de la vitesse courante
  flagAcquire = 99;                         // lire tous les capteurs avant
  readDistanceSonarAvant();
  detecteObstacle();                        // evitement d'obstacles

  delay(20);   // temporisation 20 mS
}

