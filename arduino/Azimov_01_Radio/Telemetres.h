// declarations des telemetres


// =================================================================================================
//                D�finition des broches utilis�es pour les telemetres
// =================================================================================================


const int Trig = 43;     // sonar avant EZ MaxSonar
const int Echo = 42;
const int TrigD = 45;    // sonar droit HC SR04
const int EchoD = 44;
const int TrigG = 47;    // sonar gauche HC SR04
const int EchoG = 46;
const int TrigR = 49;    // sonar gauche HC SR04
const int EchoR = 48;
const int EZ_tempsVol =  22;   // sonar avant, calcul par temps de vol (numerique)
const int EZ_Analogique = A10;        // sonar avant, port analogique

// definition de svariable pour les calculs de distances
float DistanceF = 0;          // distance frontale
float DistanceD = 0;          // distance a roite
float DistanceG = 0;          // distance a gauche
float DistanceR = 0;          // distance arriere
float DistanceMin = 0;        // distance minimale d'un obstacle


