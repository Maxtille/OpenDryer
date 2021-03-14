/*------------------------------------------------------------------------*\
|                              OPEN DRYER                                  |
|              an arduino project to optimize drying process               |
|           Copyright (C) 2021 maxtille, more detail at the foot           |
\*------------------------------------------------------------------------*/


//MEN AT WORK

#include <DHT_U.h>
#include <DHT.h>


#define DHTPINH 8 // broche ou l'on a branche le capteurH
#define DHTPINM 9 // broche ou l'on a branche le capteurM
#define DHTPINL 10 // broche ou l'on a branche le capteurL
#define DHTTYPE DHT22
#define LED_RENEW 12 //broche ou l'on connecte la led qui indique le renouvellement automatique
#define LED_OK LED_BUILTIN // broche ou l'on connecte la led qui indique par son clignottement que le programme tourne normalement
#define RELAY 1   // broche ou l'on a branche le relais et la led qui indique l'état du relais

DHT dht_h(DHTPINH, DHTTYPE);//déclaration du capteurH
DHT dht_m(DHTPINM, DHTTYPE);//déclaration du capteurM
DHT dht_l(DHTPINL, DHTTYPE);//déclaration du capteurL

void setup() {


  pinMode(DHTPINH, INPUT);
  pinMode(DHTPINM, INPUT);
  pinMode(DHTPINL, INPUT);
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
  Serial.print("Initialisation");
  dht_h.begin();
  dht_m.begin();
  dht_l.begin();
  Serial.println(" ok");
  pinMode(LED_OK, OUTPUT);
}

unsigned int loopCount =0;    //compteur du nombre de fois que loop a été executé
bool isRenewing = false;      //true = cycle de renouvellement automatique en cours
float humSet =0;              //humidité cible

void loop() {
  //déclaration et initialisation des variables
  unsigned long StartLoopTime = millis() ;
  float tempH=0 , tempM=0 , tempL=0 , humH=0 , humM=0 , humL=0 ;
  float humMoy=0, tempMoy=0 ;
  
  // La lecture du capteur prend 250ms
  // Les valeurs lues peuvent etre vieilles de jusqu'a 2 secondes (le capteur est lent)
  //mais ici on va se contenter d'une lecture toute les 10 secondes
  humH = dht_h.readHumidity();              //on lit l'hygrometrieH
  tempH = dht_h.readTemperature();          //on lit la temperatureH en celsius (par defaut)
  humM = dht_m.readHumidity();              //on lit l'hygrometrieM
  tempM = dht_m.readTemperature();          //on lit la temperatureM en celsius (par defaut)
  humL = dht_l.readHumidity();              //on lit l'hygrometrieL
  tempL = dht_l.readTemperature();          //on lit la temperatureL en celsius (par defaut)


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
  

  //Calcul des moyennes
  tempMoy = ( tempH + tempM + tempL ) / 3 ;
  humMoy = ( humH + humM + humL ) / 3 ;


  //évaluation de l'état du système
  switch (loopCount)
  {
    case 1080 : //après 1080 loop il devrait s'etre passé 3h
    {//renouvellement automatique de l'air une fois toute les 3h (relais ON pendant 5 min)
      digitalWrite(RELAY, HIGH);
      isRenewing = true;
      loopCount =0;
      break;
    }
    case 30 : //si renouvellement, stop
    {
      if(isRenewing)
        digitalWrite(RELAY, LOW);
      isRenewing = false;
      break;
    }
    default:
    {//maintien à une hygro stable et réglable via un potentiomètre analogique (45-70)
       if(humMoy > (humSet+2.5))
       {
        digitalWrite(RELAY, HIGH);
       }
       else if(humMoy < (humSet-1))
       {
        digitalWrite(RELAY,LOW);
       }
    }
  }
  
  //Affichages :
  Serial.print("Température moyenne : ");
  Serial.print(tempMoy);
  Serial.print(" °C, ");
  Serial.print("Humidité moyenne : ") ;
  Serial.print(humMoy);
  Serial.println(" %");
  if(isRenewing)
    digitalWrite(LED_RENEW,HIGH);
  else
    digitalWrite(LED_RENEW,LOW);
  

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
  loopCount ++;

}



/*------------------------------------------------------------------------------*\
  Copyright (C) 2021 maxtille, maxtille@gmail.com
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
\*------------------------------------------------------------------------------*/
