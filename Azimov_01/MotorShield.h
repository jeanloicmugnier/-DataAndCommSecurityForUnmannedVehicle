// declarations du Motor Schield


// =================================================================================================
//                Définition des broches utilisées par le Motor Schield
// =================================================================================================


// =================================================================================================
//                               constantes des broches E/S pour le motor shield
// =================================================================================================
const int vitesseMotA = 3;            // Constante pour la broche vitesse moteur A
const int sensMotA = 12;              // Constante pour la broche sens moteur A
const int freinMotA = 9;              // Constante pour la broche frein moteur moteur A
const int intensiteMotA = A0;         // intensite du moteur moteur A

const int vitesseMotB = 11;           // Constante pour la broche vitesse moteur B
const int sensMotB = 13;              // Constante pour la broche sens  moteur B
const int freinMotB = 8;              // Constante pour la broche frein  moteur B
const int intensiteMotB = A1;         // intensite du moteur  moteur B

const int speedStop = 0;
const int speedMotorMini = 40;          // valeur PWM de la vitesse minimum (40)
const int speedMotorDesengage = 80;    // valeur PWM de la vitesse de manoeuvre(80)
const int speedMotorMaxi = 255;         // valeur PWM de la vitesse maximum (255)

int currentSpeedMotor = 0;              // valeur PWM de la vitesse courante
int speedMotorConsigne = 0;             // valeur PWM de la vitesse consignee

const float ctPower = 2.92;           // facteur de conversion V/ma pour le calcul consomation moteur
const float maxConsoMoteur = 400.0;   // > 400 mA : le moteur est bloque

float consoMoteurA = 0.0;             // consomation instantanee moteur A
float consoMoteurB = 0.0;             // consomation instantanee moteur B
int STOP = 0;
int FORWARD = 1;                      // sens marche avant
int BACKWARD = 2;                     // sens marche arriere

// definition de la position de l'obstacle
int NoOBST = 99;
int DEVANT = 0;
int DROITE = 1;
int GAUCHE = 2;
int DERRIERE = 3;

