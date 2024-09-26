#define pinLedR   10
#define BEFORE_1ST_ENTRANCE 13
#define ENTRANCE 14
#define EXIT 15

// defines pins numbers
const int trigPin = 12;
const int echoPin = 11;
// defines variables
long duration;
int distance,cState,En_cnt=0,Ex_cnt=0;
unsigned long exit_time=0,c_Time=0,hefresh_time=2000;

float maxLenInMicroSec=100 * 2 / 0.034; // max time we wait for responses. this calculation is for 46 cm
void setup() {
  
   pinMode(pinLedR,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
 //אתחול מצב
  cState=BEFORE_1ST_ENTRANCE;
  digitalWrite(pinLedR,LOW);
 
 
}


void loop() {
     sendTrig();
     duration = pulseIn(echoPin, HIGH,maxLenInMicroSec);
  // Calculating the distance
  distance= duration*0.034/2;
  setState();
  switch (cState) 
  {
case BEFORE_1ST_ENTRANCE:
if(Ex_cnt==2)
{

  c_Time=millis();
  if(c_Time-exit_time>=hefresh_time)
  {
    digitalWrite(pinLedR,LOW);
    
  
    Ex_cnt=0;
    En_cnt=0;
  }
}
 Serial.println("lifneyyy knisaaaa 1");

break;


 case ENTRANCE:
     
  if(En_cnt==0)
{
  En_cnt=1;
digitalWrite(pinLedR,HIGH);

}
if(Ex_cnt==1&&En_cnt==1)
{
En_cnt=2;  
}
else if(En_cnt==2&&Ex_cnt==2)
{
  En_cnt=1;
}
 Serial.println("knisaaaaa");
  break;

  case EXIT:
  
  if(En_cnt==1)
  {
    Ex_cnt=1;
  }
  if(En_cnt==2&&Ex_cnt==1)
  {
    Ex_cnt=2;
     exit_time= millis();
  }
  
Serial.println("exitttttt");
  break;

  
  }
  
  

}

void sendTrig(){

    // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void setState()
{
if((En_cnt==0||Ex_cnt==2&&En_cnt==2)&&(distance>30))
{
  cState=BEFORE_1ST_ENTRANCE;
 
}
  if(distance>4&&distance<20)
  {
    cState=ENTRANCE;
   
  }
 if((distance>30)&&(En_cnt==2&&Ex_cnt==1||En_cnt==1))
  {
    cState=EXIT;
    
  }



}