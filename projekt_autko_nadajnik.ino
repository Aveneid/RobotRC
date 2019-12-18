#include <RCSwitch.h>
#define joyX A0
#define joyY A1
short int ymap, xmap;
int xValue, yValue;


RCSwitch mySwitch = RCSwitch();
void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(10);

}
 
void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  ymap = map(yValue,0,1023,-9,9);
  xmap = map(xValue,0,1023,-9,9);

  
  if(yValue < 510 and yValue >490){
    ymap = 0;
  }

  if(xValue < 510 and xValue >490){
    xmap = 0;
  }


  //print the values with to plot or view
  //Serial.print(xValue);
  Serial.print(ymap);
  Serial.print("\t");
  Serial.print(xmap);
  Serial.print("\n");


    
    if(xmap < 0){
      xmap=20 - xmap;
    }
    else{
      xmap+=10;
    }

    if(ymap < 0){
      ymap=30 - ymap;
    }
    else{
      ymap+=40;
    }


  Serial.print(ymap);
  Serial.print("\t");
  Serial.print(xmap);
  Serial.print("\n");
  
  mySwitch.send(xmap);
  mySwitch.send(ymap);
}

