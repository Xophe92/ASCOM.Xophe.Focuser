#include <String.h>
// set pin numbers:

const int a1 = 2;     
const int a2 =  3;
const int b1 =  4;
const int b2 =  5;

int position = 5000;
int setPoint = 5000;
byte   incomingByte;
String command;



void setup() {
  // initialize pins
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  
  setMotorStates();
  Serial.begin(9600);

}

void loop(){
  delay(10);
  int movement = setPoint-position;
  if (movement!=0)
    {
    position += (movement/abs(movement)); 
    setMotorStates();
  
    //Serial.println("Position :  " + String(position) + " setPoint : " + String(setPoint)  + " mouvement : " + String(movement));
    }

  if (Serial.available() > 0) {
  command = Serial.readStringUntil(char(10));
  treatCommand();
  }
}

void setMotorStates(){
  int states[] = {B1000, B1010, B0010, B0110, B0100, B0101, B0001, B1001};
  int state = states[((position<0)?8:0) + position%8];
  digitalWrite(a1, state>>3);
  digitalWrite(a2, (state>>2) & 1); 
  digitalWrite(b1, (state>>1) & 1);   
  digitalWrite(b2, state & 1);   
}

void treatCommand(){
  if (command.substring(0,1) == "s") //setPoint
    setPoint = command.substring(1).toInt();     
  if (command.substring(0,1) == "m") //isMoving
    Serial.println(((position!=setPoint)?"1":"0"));
  if (command.substring(0,1) == "p") //isMoving
    Serial.println(String(position));



  // je ne connais aucune autre commande !
}

