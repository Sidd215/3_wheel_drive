#include <ps5Controller.h>
int FMpwm=16,FMdir=4,LMpwm=23,LMdir=22,RMpwm=19,RMdir=21;
  float lx=ps5.LStickX();
float ly=ps5.LStickY();
float rx=ps5.RStickX();
float k=lx,t=rx,p=ly;

void setup() {
  Serial.begin(115200);
  ps5.begin("88:03:4C:93:FE:13"); //replace with MAC address of your controller
  
 
    while (ps5.isConnected()==0) {
    Serial.println("Connecting...");
    }
  Serial.println("Ready.");

  pinMode(FMpwm,OUTPUT);
  pinMode(LMpwm,OUTPUT);
  pinMode(RMpwm,OUTPUT);
  pinMode(FMdir,OUTPUT);
  pinMode(LMdir,OUTPUT);
  pinMode(RMdir,OUTPUT);
  delay(1000);
  }
float mapp(float control){
  float z;
  if((-128<=control)&&(control<=-30))
  {
    z=map(control,-30,-128,0,225);
  }
  else if((30<=control)&&(control<=128))
  {
    z=map(control,30,128,0,225);
  }
  else
  z =0;
  return z;
}
 
  void forward(float control){

    float z = mapp(control);
    digitalWrite(FMdir,LOW);
    analogWrite(FMpwm,0);
    digitalWrite(LMdir,HIGH);
    analogWrite(LMpwm,z);
    digitalWrite(RMdir,LOW);
    analogWrite(RMpwm,z);
    Serial.println("IAM IN FORWARD");
    delay(300);
    Serial.printf("Left Stick x at %d\n", ps5.LStickX());
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());
    Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    Serial.printf("Right Stick y at %d\n", ps5.RStickY());

  // analogWrite(k,z);
  }

  void back(float control){
    float z = mapp(control);
    digitalWrite(FMdir,LOW);
    analogWrite(FMpwm,0);
    digitalWrite(LMdir,LOW);
    analogWrite(LMpwm,z);
    digitalWrite(RMdir,HIGH);
    analogWrite(RMpwm,z);
    Serial.println("IAM IN BACK");
    delay(300);
    Serial.printf("Left Stick x at %d\n", ps5.LStickX());
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());  
    Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    Serial.printf("Right Stick y at %d\n", ps5.RStickY());
  }

  void right (float control)
  {     float z = mapp(control);
    digitalWrite(FMdir,HIGH);
    analogWrite(LMpwm,z);
    digitalWrite(RMdir,LOW);
    analogWrite(RMpwm,z);
    digitalWrite(LMdir,LOW);
    analogWrite(LMpwm,z);
        Serial.println("IAM IN RIGHT");
    delay(300);
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());
    Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    Serial.printf("Right Stick y at %d\n", ps5.RStickY());

  }

  void left(float control){
    float z = mapp(control);
    digitalWrite(FMdir,LOW);
    analogWrite(FMpwm,z);
    digitalWrite(RMdir,HIGH);
    analogWrite(RMpwm,z);
    digitalWrite(LMdir,HIGH);
    analogWrite(LMpwm,z);
        Serial.println("IAM IN LEFT");
    delay(300);
    Serial.printf("Left Stick x at %d\n", ps5.LStickX());
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());
    Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    Serial.printf("Right Stick y at %d\n", ps5.RStickY());
  }

void stop(){
    digitalWrite(FMdir,LOW);
    analogWrite(FMpwm,0);
    digitalWrite(RMdir,HIGH);
    analogWrite(RMpwm,0);
    digitalWrite(LMdir,HIGH);
    analogWrite(LMpwm,0);
        Serial.println("IAM IN STOP");
    delay(300);
    Serial.printf("Left Stick x at %d\n", ps5.LStickX());
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());
        Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    Serial.printf("Right Stick y at %d\n", ps5.RStickY());
}

  void Clk(float control){
    float z = mapp(control);
    digitalWrite(FMdir,HIGH);
    analogWrite(FMpwm,z);
    digitalWrite(RMdir,HIGH);
    analogWrite(RMpwm,z);
    digitalWrite(LMdir,HIGH);
    analogWrite(LMpwm,z);
        Serial.println("IAM IN CLOCK");
    delay(300);
    Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    Serial.printf("Right Stick y at %d\n", ps5.RStickY());
    Serial.printf("Left Stick x at %d\n", ps5.LStickX());
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());
  
    }

    void antiClk(float control){
    float z = mapp(control);
    digitalWrite(FMdir,LOW);
    analogWrite(FMpwm,z);
    digitalWrite(RMdir,LOW);
    analogWrite(RMpwm,z);
    digitalWrite(LMdir,LOW);
    analogWrite(LMpwm,z);
        Serial.println("IAM IN ANTICLOCK");
    delay(300);
    Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    Serial.printf("Right Stick y at %d\n", ps5.RStickY());
    Serial.printf("Left Stick x at %d\n", ps5.LStickX());
    Serial.printf("Left Stick y at %d\n", ps5.LStickY());
  }


void loop() {
  lx=ps5.LStickX();
 ly=ps5.LStickY();
 rx=ps5.RStickX();
  
 if (ly < -30) {
    forward(ly);
  } else if (ly > 30) {
    back(ly);
  } else if (lx > 30) {
    right(lx);
  } else if (lx < -30) {
    left(lx);
  } else if (rx < -30) {
    Clk(rx);
  } else if (rx > 30) {
    antiClk(rx);
  } else {
    stop();
  }
}
