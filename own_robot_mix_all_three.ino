
#include<Servo.h>
Servo s;
int pos=0;
#define enable1 1
#define enable2 2

int Motor1speed=128;
int Motor2speed=128;

int motor1a=8;
int motor1b=9;
int motor2b=10;
int motor2a=11;

int trigpin=7;
int echopin=6;

long duration;
int distance;

#define LEFT A0
#define RIGHT A3
void setup() {
  // put your setup code here, to run once:
s.attach(13);
for(pos=90;pos<=180;pos++)
{
  s.write(pos);
  delay(15);
}
for(pos=180;pos>=0;pos--)
{
  s.write(pos);
  delay(15);
}
for(pos=0;pos<=90;pos++)
{
  s.write(pos);
  delay(15);
}
pinMode(enable1,OUTPUT);
pinMode(enable2,OUTPUT);

pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
pinMode(7,OUTPUT);//trigpin
pinMode(6,INPUT);//echopin

pinMode(RIGHT,INPUT);//ir sensor
pinMode(LEFT,INPUT);

//Serial.begin(9600);//for serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
//we will declare which pin goes when hight and low
digitalWrite(trigpin,LOW);
delay(2);
digitalWrite(trigpin,HIGH);
delay(10);
digitalWrite(trigpin,LOW);

duration = pulseIn(echopin,HIGH);//this reads the pin which high or low 
distance = (duration*0.034/2);

int Rightval=digitalRead(RIGHT);
int Leftval=digitalRead(LEFT);

//for forward
if((Rightval == 0) && (Leftval==0) &&(distance>=0 && distance<=30))//distance in cm
{
digitalWrite(motor1a,HIGH);
digitalWrite(motor1b,LOW);
digitalWrite(motor2a,HIGH);
digitalWrite(motor2b,LOW);//for fast turn

analogWrite(enable1,Motor1speed);
analogWrite(enable2,Motor2speed);
//delay(2000);
}
// detects object at right so gives low signal that is 0
else if((Rightval==0) && (Leftval==1))
{
digitalWrite(motor1a,LOW);
digitalWrite(motor1b,HIGH);
digitalWrite(motor2a,HIGH);
digitalWrite(motor2b,LOW);//for fast turn//
delay(15);
analogWrite(enable1,Motor1speed);
analogWrite(enable2,Motor2speed);
//delay(2000);
}
// detects object at left so gives low signal that is 0
else if((Rightval==1) && (Leftval==0))
{
digitalWrite(motor1a,HIGH);
digitalWrite(motor1b,LOW);
digitalWrite(motor2a,HIGH);//
digitalWrite(motor2b,HIGH);
delay(15);

analogWrite(enable1,Motor1speed);
analogWrite(enable2,Motor2speed);
//delay(2000);
}
//stop
else if((Rightval==1) && (Leftval==1))
{
digitalWrite(motor1a,LOW);
digitalWrite(motor1b,LOW);
digitalWrite(motor2a,LOW);
digitalWrite(motor2b,LOW);
//`delay(2000);
}
/*else if(distance>1 && distance<=5)//safety so that robot dont hit the object
{
digitalWrite(motor1a,LOW);
digitalWrite(motor1b,LOW);
digitalWrite(motor2a,LOW);
digitalWrite(motor2b,LOW);  
}*/
}
