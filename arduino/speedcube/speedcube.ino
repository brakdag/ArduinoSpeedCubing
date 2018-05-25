/* by brakdag@gmail.com
 *  release in 2018 for arduino software.
 *  Connect pin 12 to red led and 13 to green led, connect 2 pulsators in serie to gnd and pin 11.
 */
#include <Timer.h> 

#define RED_LED 12
#define GREEN_LED 13
#define PULSATOR 11

// States of the program

#define PRESS_TIME 1000  // time to hold sensors before start 

#define PRESIONADO 1
#define SUELTO 0
#define PREPARED 2
#define RUNNING 3
#define FINISH 4
Timer t;

void setup() {
Serial.begin(9600);

pinMode(RED_LED,OUTPUT);
pinMode(GREEN_LED,OUTPUT);
pinMode(PULSATOR,INPUT_PULLUP);

digitalWrite(RED_LED,LOW);
digitalWrite(GREEN_LED,LOW);
}
int pulsador =0;
int estado = SUELTO;
long int tiempo=0;
long int startTime=0;
void loop() {
pulsador = digitalRead(PULSATOR);
if((pulsador == 0) && (estado == SUELTO || estado== RUNNING)){
estado = PRESIONADO;

digitalWrite(RED_LED,HIGH);
tiempo =millis();
  if(startTime!=0) {
    Serial.write("E");
    //Serial.println(tiempo-startTime);
    startTime=0;
}
}
if((pulsador == 1) && (estado == PRESIONADO)){
estado = SUELTO;
digitalWrite(RED_LED,LOW);
digitalWrite(GREEN_LED,LOW);
}
if((millis()-tiempo >PRESS_TIME) && estado == PRESIONADO){
     estado=PREPARED;
     Serial.write("P");
     digitalWrite(GREEN_LED,HIGH);
  }
if((pulsador == 1) && (estado == PREPARED)){
Serial.write("S");
estado = RUNNING;
startTime=millis();
digitalWrite(RED_LED,LOW);
digitalWrite(GREEN_LED,LOW);
}
if((estado == RUNNING)){
t.oscillate(RED_LED,40,LOW);
t.oscillate(GREEN_LED,40,HIGH);
t.update();
}
}
