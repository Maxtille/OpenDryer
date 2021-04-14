# OpenDryer
## an Open Source Arduino code to dry stuff in a semi controlled environment


### Purpose of the project
- Powering on and off the extraction of the room in function of the choosen relative humidity vs relative humidity of the room
- Automaticaly and rapidly renewing the room air every 3 hours
- Activating for 1 min every 30 min or so a fan which will ensure uniform distribution of new air
- Saveing data for a graph of HR, Temp, and  extraction cycle on a microSD card

### What you need

- Arduino UNO 
- Dual Relay shield 
- 4x LED 
- 3x DHT22 sensors
- SDCard shield
- 


### Pin list

- DIG0
- DIG1
- DIG2  : LED Everything is ok (not the LED_BUILTIN)
- DIG3  : LED + Relay 1, air extractor
- DIG4  : LED + Relay 2, Oscillating fan
- DIG5  : LED Renewing cycle 
- DIG6 
- DIG7  : Sensor 1
- DIG8  : Sensor 2
- DIG9  : Sensor 3
- DIG10 : SD CS
- DIG11 : SD MOSI
- DIG12 : SD MISO
- DIG13 : SD SCK
- AN0   : Analog potentiometer 
- AN1
- AN2
- AN3
- AN4
- AN5
- AN6
- AN7


### Setup Recommandations 
- Air extractor effective debit in m³/h should be more than 20x room volume in m³
- Oscillating fan should be aimed to the intake or a wall but not directly to the stuff you want tor dry
- Different sensors should be dispatched accross different position in the room, even at different height, next to your drying stuff
- Intake air is supposed to be a bit dryer than your target RH, and at ideal temperature
