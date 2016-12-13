//4Code de calcul et test unitaire
//4.1 Un télémètre avant
setup(){
  byte mode = 1;
  // 1 = lecture digit (temps de vol) 2 = lect analogique (tension)
  double distance;
  double calibration;
  double voltage;
  byte EzDigiPin = 22; // Pin pour lecture digitale (22)
  byte EzAnaPin = 10; // Pin pour lecture analogique (A10)
}
loop(){
  if (mode == 1) // distance determinee par le temps de vol AR de l'onde accoustique
{
long duration = pulseIn(EzDigiPin, HIGH); //Read duration in microSeconds
distance = duration / 58.0; // 58.0 uS per cm for MB1240 XL-MaxSonar
mode = 2; // mode suivant
}
if (mode == 2) // passage en mode 2
{
//lecture d'une valeur analogique .49 mV per unit
voltage = analogRead(EzAnaPin) * 0.0049
distance = voltage / 0.0049 ;
//.49 mV per cm
calibration = 0.0;
}
mode = 1; // retour en mode 1
}
/*
byte mode = 1;
// 1 = lecture digit (temps de vol) 2 = lect analogique (tension)
double distance;
double calibration;
double voltage;
byte EzDigiPin = 22; // Pin pour lecture digitale (22)
byte EzAnaPin = 10; // Pin pour lecture analogique (A10)
Initialisation
RAS
Code de calcul
if (mode == 1) // distance determinee par le temps de vol AR de l'onde accoustique
{
long duration = pulseIn(EzDigiPin, HIGH); //Read duration in microSeconds
distance = duration / 58.0; // 58.0 uS per cm for MB1240 XL-MaxSonar
mode = 2; // mode suivant
}
if (mode == 2) // passage en mode 2
{
//lecture d'une valeur analogique .49 mV per unit
voltage = analogRead(EzAnaPin) * 0.0049
distance = voltage / 0.0049 ;
//.49 mV per cm
calibration = 0.0;
}
mode = 1; // retour en mode 1
4.2 Télémètres latéraux (droite et gauche)
Déclaration
// Définition des broches utilisées pour les telemetres
byte TrigDroite = 17;
byte EchoDroite = 16;
byte TrigGauche = 23;
13byte EchoGauche = 24;
// variables globales
long Lecture_EchoDroite;
// lecture de l'écho sonar lateral Droite
double DistanceDroite;
// distance laterale Droite
long Lecture_EchoGauche;
// lecture de l'écho sonar lateral Gauche
double DistanceGauche;
// distance laterale Gauche
Initialisation
// initialisation du telemetre Droit
pinMode(TrigDroite, OUTPUT);
digitalWrite(TrigDroite, LOW);
pinMode(EchoDroite, INPUT);
// initialisation du telemetre Gauche
pinMode(TrigGauche, OUTPUT);
digitalWrite(TrigGauche, LOW);
pinMode(EchoGauche, INPUT);
Code de calcul
// traitement du prmier telemetre (latteral Droit)
digitalWrite(TrigDroite, HIGH);
delayMicroseconds(10);
digitalWrite(TrigDroite, LOW);
Lecture_EchoDroite = pulseIn(EchoDroite, HIGH);
DistanceDroite = Lecture_EchoDroite / 58.0;
// traitement du second telemetre (lateral Gauche)
digitalWrite(TrigGauche, HIGH);
delayMicroseconds(10);
digitalWrite(TrigGauche, LOW);
Lecture_EchoGauche = pulseIn(EchoGauche, HIGH);
DistanceGauche = Lecture_EchoGauche / 58.0;
4.3 Capteur de pression,
Déclaration
#include <Wire.h> // standart I2c library
#define kpa2atm 0.00986923267 // facteur de conversion KiloPascal vers Atmosphere
byte pressureAnaPin = 9;
// identification I/O analogique sur Mega
14Initialisation
RAS
Code de calcul
// variables
int val;
float pkPa; // pressure in kPa
float pAtm; // pressure in Atm
val = analogRead(pressureAnaPin); // lecture de la pression capteur
pkPa = ((float)val/(float)1023+0.095)/0.009;
// pression en kPa
pAtm = kpa2atm*pkPa;
// conversion en Atm
4.4 Boussole magnétique
Déclaration
#include <Wire.h> // standart I2c library
#define HMC5803L_Address 0x1E // adresse I2C du module MC5803L
// definition des adresses des registres pour les axes X, Y et Z
#define X 3
#define Y 7
#define Z 5
Initialisation
Wire.begin();
Init_HMC5803L();
// initialisation libray I2C (Wire library)
// Initialisation du module HMC5803L
Code de calcul
// lecture de la valeur de chacun des axes de la boussole
HMC5803L_Read(X);
HMC5803L_Read(Y);
HMC5803L_Read(Z);
// temporasation entre deux lectures
delay(200);
Fonctions annexes
//_________________________________________________________________________
// fonction Init_HMC5803L, initialise le module, elle ne doit être exécuté qu'une seule fois
void Init_HMC5803L(void) {
15// initialise le nbr valeur moyenne (averaging) à 8
// et la frequence de mesure (measurement rate) à 15 Hz
Wire.beginTransmission(HMC5803L_Address);
Wire.write(0x00);
Wire.write(0x70);
// initialise le Gain à 5
Wire.write(0x01);
Wire.write(0xA0);
Wire.endTransmission();
}
//______________________________________________________________________
// fonction HMC5803L_Read.Cette fonction doit être appelée pour chacun des 3 axes.
// Elle retourne un résultat sur 16 bits signés
int HMC5803L_Read(byte Axis) {
int Result;
/* Initiate a single measurement 
Wire.beginTransmission(HMC5803L_Address);
Wire.write(0x02);
Wire.write(0x01);
Wire.endTransmission();
delay(6);
/* Move modules the resiger pointer to one of the axis data registers *
Wire.beginTransmission(HMC5803L_Address);
Wire.write(Axis);
Wire.endTransmission();
/* Read the data from registers (there are two 8 bit registers for each axis) *
Wire.requestFrom(HMC5803L_Address, 2);
Result = Wire.read() << 8;
Result |= Wire.read();
return Result;
}
164.5 Détecteurs d'obstacle IR (avant et arrière)
Déclaration
#include <SharpIR.h>
// bibliothèque SHARP
#define irPin A8
#define nbAverage 25
#define deltaMinValue 93
#define model 1080
// 1080 pour le GP2Y0A21Y, 20150 pour le GP2Y0A02Y
#define baudRate 9600
boolean done=false;
// initialisation de la bibliothèsque Sharp
SharpIR sharp(irPin, nbAverage, deltaMinValue, model);
// irPin (def A8) : I/O carte Arduino sur lequel est connecte le port signal du capteur
// nbAverage ( def 25): nombre de lectures consecutives utilisées par la la bibliothèque pour
// le calcul d'une distance moyenne qui est renvoyée
// deltaMinValue(def 93): différence entre deux mesures consécutives pour être considèré
// comme valable
// model: détermine le type de capteur: 1080 pour le GP2Y0A21Y
//
20150 pour le GP2Y0A02Y
//
Initialisation
pinMode (irPin, INPUT);
Code de calcul
unsigned long startTime;
unsigned long mesureTime; // duree de la mesure
int distanceCalcul;
// distance calculee (moyenne sur nbAverage echantillons)
if (done==false){
// pour ne faire qu'une boucle
startTime=millis();
// lecture du temps CPU pour initialser la mesure de duree
distanceCalcul=sharp.distance();
// lecture de la distance à l'obstacle
delay (200);
done=true; // pour ne faire qu'une boucle
}
174.6 Télémesure
Déclaration
#include <SoftwareSerial.h>
int trig = 20;
int echo = 21;
float ttime;
float distance_cm;
Initialisation
pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
delayMicroseconds(10);
pinMode(echo, INPUT);
Serial1.begin(115200);
// tout ce qui est sur Serial1 est émis

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}*/
