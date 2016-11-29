
// =================================================================================================
//               definition des plage de la bulle de securite
// =================================================================================================
const int greenFlag = 80;           // navigation libre
const int yellowFlag = 45;          // reduction de la vitesse : obstacle dans le champ
const int redFlag = 20;             // arret : collision imminente  (25 cm mini pour EZ MaxSonar)
const int desengageRotationLOW = 15;   // angle de rotation pour se desengager obstacle lateral = 15;   // angle de rotation pour desengager obstacle lateral
const int desengageRotationHIGH = 45;   // angle de rotation pour desengager obstacle avant ou arriere
const int desengageRetroDistance = 20;  // distance de recul pour de desengager d'un obstacle

const float cteAngleDelay = 8.8888; // cte pour calcul de duree de rotation  6.6650;
int flagAction = STOP ;             // definition d'un flag d'action 0 = arret, 1 = marche avant, 2 = marche arriere
int flagAcquire = 99;               // 0 = lire devant, 1 lire D, 2 lire gauche, 99 lire tous les capteurs
int flagObstacleSide = NoOBST;      // 0 = devant, 1 = Droite, 2 = Gauche,  3 = arriere,  99 pas d'obstacle
int currentSpeed = 0;               // memorisation de la vitesse actuelle
byte pressureAnaPin = 9;

// =================================================================================================
//                                definition d'un compteur de temps
// =================================================================================================
unsigned long absoluteTime = 0;   // reference de temps absolue, initialise par setup
unsigned long refTime = 0;        // reference de temps
unsigned long delayCMD = 0;       // duree de la commande
unsigned long tempoConso =  1000; // delay avant de mesurer le courant (eviter les pics)

// =================================================================================================
//                                definitions pour Serials
// =================================================================================================
const int SERIALCONSOL = 0;
const int SERIALRADIO = 1;


// =================================================================================================
//                       declarations pour l'accelerometre-magnetometre LSM 303
// =================================================================================================
LSM303 compass;
LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = { -32768, -32768, -32768};
