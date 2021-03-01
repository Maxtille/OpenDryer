#include <DHT_U.h>
#include <DHT.h>


#define DHTPINH 8 // broche ou l'on a branche le capteurH
#define DHTPINM 9 // broche ou l'on a branche le capteurM
#define DHTPINL 10 // broche ou l'on a branche le capteurL
#define DHTTYPE DHT22
#define LED_OK LED_BUILTIN // broche ou l'on connecte la led qui indique par son clignottement que le programme tourne normalement

DHT dht_h(DHTPINH, DHTTYPE);//déclaration du capteurH
DHT dht_m(DHTPINM, DHTTYPE);//déclaration du capteurM
DHT dht_l(DHTPINL, DHTTYPE);//déclaration du capteurL

void setup() {


  pinMode(DHTPINH, INPUT);
  pinMode(DHTPINM, INPUT);
  pinMode(DHTPINL, INPUT);
  Serial.begin(9600);
  Serial.print("Initialisation");
  dht_h.begin();
  dht_m.begin();
  dht_l.begin();
  Serial.println(" ok");
  pinMode(LED_OK, OUTPUT);
}

void loop() {
  //déclaration et initialisation des variables
  unsigned long StartLoopTime = millis() ;
  float tempH=0 , tempM=0 , tempL=0 , humH=0 , humM=0 , humL=0 ;
  float humMoy=0, tempMoy=0, tempMin=0, tempMax=0, humMin=0, humMax=0;
  
  // La lecture du capteur prend 250ms
  // Les valeurs lues peuvent etre vieilles de jusqu'a 2 secondes (le capteur est lent)
  //mais ici on va se contenter d'une lecture toute les 10 secondes
  humH = dht_h.readHumidity();//on lit l'hygrometrieH
  tempH = dht_h.readTemperature();//on lit la temperatureH en celsius (par defaut)
  humM = dht_m.readHumidity();//on lit l'hygrometrieM
  tempM = dht_m.readTemperature();//on lit la temperatureM en celsius (par defaut)
  humL = dht_l.readHumidity();//on lit l'hygrometrieL
  tempL = dht_l.readTemperature();//on lit la temperatureL en celsius (par defaut)


  //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
  if (isnan(humH) || isnan(tempH)  )
  { Serial.println("Echec à la lecture du capteur Haut!");delay(1000);
    return ;}
  if (isnan(humM) || isnan(tempM)  )
  { Serial.println("Echec à la lecture du capteur Millieu!");delay(1000);
    return ;}
  if (isnan(humL) || isnan(tempL)  )
  { Serial.println("Echec à la lecture du capteur Bas!");delay(1000);
    return ;}


  // Calcul de l'indice de temperature en Celsius
  //float indiceH = dht_h.computeHeatIndex(tempH, humH, false);

  //Calcul des moyennes (et des minimas maximas)
  tempMoy = ( tempH + tempM + tempL ) / 3 ;
  humMoy = ( humH + humM + humL ) / 3 ;

  //évaluation de l'état du système
  
  //maintien à une hygro stable et réglable via un potentiomètre analogique (45-70)
  //et
  //renouvellement automatique de l'air une fois toute les 3h (relais ON pendant 5 min)

  

  //Affichages :
  Serial.print("Température moyenne : ");
  Serial.print(tempMoy);
  Serial.print(" °C, ");
  Serial.print("Humidité moyenne : ") ;
  Serial.print(humMoy);
  Serial.println(" %");

  //Sauvegardes des données et évènnements sur sd


  

 //Timing de la boucle + LED 
  do
  {delay(50);
    digitalWrite(LED_OK, HIGH);
    delay(50);
    digitalWrite(LED_OK, LOW);
  }while(millis()<(StartLoopTime + 9890 ));
  do
  {delay(1);}while(millis()<(StartLoopTime + 10000)) ;

}
