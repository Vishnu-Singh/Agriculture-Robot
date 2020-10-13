/*************************************************************

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "H2ajExldKt1umhBDhToljgeQePp_ojem";
char ssid[] = "Vasnavi";
char pass[] = "1847@Vashnavi";
int m1Clock=D8;
int m1AntiClock=D7;
int m2Clock=D6;
int m2AntiClock=D5;
int m3=D1;
int m4=D3;
int m5=D2;
int m6Clock=D4;
int m6AntiClock=D0;
int count=0;
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(m1Clock,OUTPUT);
  pinMode(m1AntiClock,OUTPUT);
  pinMode(m2Clock,OUTPUT);
  pinMode(m2AntiClock,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
  pinMode(m5,OUTPUT);
  pinMode(m6Clock,OUTPUT);
  pinMode(m6AntiClock,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V8){
  int val=param.asInt();
  if(val){
    Blynk.virtualWrite(V0,"Forward Start");
    digitalWrite(m1Clock,HIGH);
    digitalWrite(m2Clock,HIGH);
  }else{
    Blynk.virtualWrite(V0,"Forward stop");
    digitalWrite(m1Clock,LOW);
    digitalWrite(m2Clock,LOW);
  }
}

BLYNK_WRITE(V7){
  int val=param.asInt();
  if(val){
    digitalWrite(m1AntiClock,HIGH);
    digitalWrite(m2AntiClock,HIGH);
    Blynk.virtualWrite(V0,"Backward Start");
  }else{
    digitalWrite(m1AntiClock,LOW);
    digitalWrite(m2AntiClock,LOW);
    Blynk.virtualWrite(V0,"Backward stop");
  }
}

BLYNK_WRITE(V6){
  int val=param.asInt();
  if(val){
    digitalWrite(m1Clock,HIGH);
    digitalWrite(m2Clock,LOW);
    Blynk.virtualWrite(V0,"Left Start");
  }else{
    digitalWrite(m1Clock,LOW);
    digitalWrite(m2Clock,LOW);
    Blynk.virtualWrite(V0,"Left stop");
  }
}

BLYNK_WRITE(V5){
  int val=param.asInt();
  if(val){
    digitalWrite(m1Clock,LOW);
    digitalWrite(m2Clock,HIGH);
    Blynk.virtualWrite(V0,"Right Start");
  }else{
    digitalWrite(m2Clock,LOW);
    Blynk.virtualWrite(V0,"Right stop");
  }
}

BLYNK_WRITE(V4){
  int val=param.asInt();
  if(val){
    digitalWrite(m3,HIGH);
    Blynk.virtualWrite(V0,"Sedding");
  }else{
    digitalWrite(m3,LOW);
    Blynk.virtualWrite(V0,"........");
  }
}

BLYNK_WRITE(V3){
  int val=param.asInt();
  if(val){
    digitalWrite(m4,HIGH);
    Blynk.virtualWrite(V0,"Cultivating");
  }else{
    digitalWrite(m4,LOW);
    Blynk.virtualWrite(V0,"........");
  }
}

BLYNK_WRITE(V1){
  int val=param.asInt();
  if(val){
    digitalWrite(m5,HIGH);
    delay(100);
    digitalWrite(m5,LOW);
    Blynk.virtualWrite(V0,"Harvester");
  }else{
    digitalWrite(m5,LOW);
    Blynk.virtualWrite(V0,"Backward stop");
  }
}

BLYNK_WRITE(V2){
  int val=param.asInt();
  if(val){
    harvest(200);
    count++;
    if(count==1){
      harvest(200);
      count=0;
    }
    Blynk.virtualWrite(V0,"Harvesting");
  }else{
   // digitalWrite(m6AntiClock,LOW);
    Blynk.virtualWrite(V0,"......");
  }
}

void harvest(int t){
    digitalWrite(m6Clock,HIGH);
    delay(t);
    digitalWrite(m6Clock,LOW);
    delay(2000);
    digitalWrite(m6AntiClock,HIGH);
    delay(t);
    digitalWrite(m6AntiClock,LOW);
    
}
