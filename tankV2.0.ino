
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const int enA =10;
const int enB =9;
const int in1 =3;
const int in2 =4;
const int in3 =5;
const int in4=6;
int writeL, writeR;
//1023 is max back
//0 is max front
int leftD,rigthD;
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00002";
void setup() {
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

}
void loop() {

int  arr[2];

if(radio.available()){
  radio.read(&arr, sizeof(arr));
         

       leftD=arr[0];
       rigthD=arr[1];
   
//  Serial.print("leftD");
//       Serial.print(leftD);
//       
//       Serial.println(" rigthD");
//           Serial.print(rigthD);
//                 Serial.println(" ");
}

if(leftD>510){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(enA,HIGH);
writeL= map(leftD,510,1023,0,200);
}else if(leftD<500){
  digitalWrite(enA,HIGH);
 digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
writeL= map(leftD,0,500,200,0);
}else{
writeL=0;
  digitalWrite(enA,LOW);
}


if(rigthD>525){
  digitalWrite(enB,HIGH);
    digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  writeR= map(rigthD,525,1023,0,500);
}else if(rigthD<515){
    digitalWrite(enB,HIGH);
writeR= map(rigthD,0,515,500,0);
    digitalWrite(in4,LOW);
  digitalWrite(in3,HIGH);
}else{
  writeR=0;
    digitalWrite(enB,LOW);
}
//  analogWrite(enB,writeR);
//  analogWrite(enA,writeL);
Serial.print("writeR is ");
Serial.println(writeR);

Serial.print("writeL is ");
Serial.print(writeL);
}
