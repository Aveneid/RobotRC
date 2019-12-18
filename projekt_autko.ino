#include <RCSwitch.h>
#include <String.h>

#define hornHorn 3
#define enableRearWheels 5
#define enableFrontWheels 6
#define rearWheel1 A0
#define rearWheel2 A1
#define frontWheel1 9 
#define frontWheel2 10
#define frontLights 1 
#define backLights 0

int mode = 1; //forward 1 back 2
RCSwitch recreiver = RCSwitch();
void steeringWheel(int data){   
  int direction = data / 10;
  int speed = (data%10)*20;         
  if(direction == 3){             //left
    digitalWrite(frontWheel1,HIGH);
    digitalWrite(frontWheel2,LOW);
  }
  if(direction == 4){             //right
    digitalWrite(frontWheel2,HIGH);
    digitalWrite(frontWheel1,LOW);
  }
  analogWrite(enableFrontWheels,speed); 
}
void mainEngine(int data){   
  int direction = data / 10;              //get direction
  int speed = (data%10) * 25;           //get speed

 // if(mode==1){                  //mode forward
  if(direction==1){     
    Serial.println("for");// forward  
    analogWrite(rearWheel1,255);
    analogWrite(rearWheel2,0);
  }
  /*if(direction==2){               // brakes
    digitalWrite(rearWheel1,LOW);
    digitalWrite(rearWheel2,LOW);
  }  
 } 
  if(mode == 2){*/
  if(direction==2){             
    Serial.println("back");// backward  
    analogWrite(rearWheel1,0);
    analogWrite(rearWheel2,255);
  }/*
  if(direction==2){               // brakes
    digitalWrite(rearWheel1,LOW);
    digitalWrite(rearWheel2,LOW);
  }  
  } */
  
 /* if((mode == 1 && direction == 2) ||( mode == 2 && direction == 2)){
    digitalWrite(backLights,HIGH);      //turn on stop lights
    analogWrite(enableRearWheels,255);    //fast motor stop
  } else {*/
    Serial.println(digitalRead(rearWheel1));
  Serial.println(digitalRead(rearWheel2));
    analogWrite(enableRearWheels,speed);   //0xaa
   Serial.println(analogRead(rearWheel2));/*
    if(digitalRead(backLights) == HIGH) digitalWrite(backLights,LOW);
  }*/
    
}

void toggleLights(){
    digitalWrite(frontLights,!digitalRead(frontLights));
}
void setup(){
  Serial.begin(9600);
  recreiver.enableReceive(0);
  
  pinMode(frontLights,OUTPUT);
  pinMode(enableFrontWheels,OUTPUT);
  pinMode(enableRearWheels,OUTPUT);
  pinMode(frontWheel1,OUTPUT);
  pinMode(frontWheel2,OUTPUT);
  pinMode(rearWheel1,OUTPUT);
  pinMode(rearWheel2,OUTPUT);
  pinMode(backLights,OUTPUT);
  pinMode(frontLights,OUTPUT);
  
  digitalWrite(frontLights,LOW);
  digitalWrite(backLights,LOW);
  digitalWrite(frontWheel2,LOW);
  digitalWrite(frontWheel1,LOW);
  digitalWrite(rearWheel1,LOW);
  digitalWrite(rearWheel2,LOW);
}


void loop(){
  analogWrite(enableFrontWheels,0); 
  analogWrite(enableRearWheels,0); 
  if(recreiver.available()){
    int data = recreiver.getReceivedValue();
    int command = data/10;
    Serial.print(data);Serial.println("");
    if(data == -25464) mainEngine(17);
    if(data == -25470) mainEngine(27);
    if(data == 91){tone(hornHorn,2137,250);tone(hornHorn,2137,250);}
    if(data == 90) toggleLights();
  
    switch(command){
      case 1: case 2: mainEngine(data); break;
      case 3: case 4: steeringWheel(data); break; 
    default: 
  //  digitalWrite(enableRearWheels,LOW);  //free-runnig rear wheels
    break;
  }    
  }
  recreiver.resetAvailable();
}
  








