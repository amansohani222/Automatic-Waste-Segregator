#include <Servo.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
const int rs = 49, en = 45, d4 = 35, d5 = 33, d6 = 31, d7 = 29;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
Servo servo;
int angle = 10;

void setup() {
   pinMode(5, INPUT);
  servo.attach(8);
  servo.write(angle);
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  int lcdVDD = 53;
  pinMode(lcdVDD, OUTPUT);
  digitalWrite(lcdVDD, HIGH);

  int lcdV0 = 51;
  pinMode(lcdV0, OUTPUT);
  digitalWrite(lcdV0, LOW);

  int lcdRW = 47;
  pinMode(lcdRW, OUTPUT);
  digitalWrite(lcdRW, LOW);
  
   lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello Welcome");
  lcd.setCursor(0,1);
  lcd.print("to My home");
 /* * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 1
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) */
}

int B=0;
void loop() 
{ 
  int detect = digitalRead(5);// read obstacle status and store it into "detect"
  if(detect == LOW){
   B=1;
   Serial.println("Obastacle on the way"); 
  }
  if(B==1){
   amanMoisture(B); }
   
  B=0;
  sensors_event_t event;
  dht.humidity().getEvent(&event);  
  float P = event.relative_humidity;   
  Serial.print(F("Humidity: "));
  Serial.print(P);
  Serial.println(F("%"));
  delay(1000);
}

void amanMoisture(int B)
{   sensors_event_t eventf;
    dht.humidity().getEvent(&eventf);   
    float Hf = eventf.relative_humidity;
    Serial.print(F("Humidity first: "));
    Serial.print(Hf);
    Serial.println(F("%"));
    delay(8000);
    sensors_event_t eventfake;
    dht.humidity().getEvent(&eventfake);   
    float Hfake = eventfake.relative_humidity;   
    Serial.print(F("Humidity Fake: "));
    Serial.print(Hfake);
    Serial.println(F("%"));
    delay(2000);
    sensors_event_t eventl;
    dht.humidity().getEvent(&eventl);   
    float Hl = eventl.relative_humidity;   
    Serial.print(F("Humidity last: "));
    Serial.print(Hl);
    Serial.println(F("%"));
    amanMotor(Hf, Hl);
}

void amanMotor(float Hf, float Hl)
{  if(Hl>Hf+3)
   { lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("WET");
     for(angle = 90; angle > 0; angle--)  
     { servo.write(angle);               
       delay(15); } 
     delay(200);
     for(angle = 0; angle < 90; angle++)    
     { servo.write(angle);           
       delay(15 ); } 
     delay(200);      
   }
   else
   { lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("WET");
     for(angle = 90; angle < 180; angle++)  
     { servo.write(angle);               
       delay(15); } 
     delay(200);
     for(angle = 180; angle > 90; angle--)    
     { servo.write(angle);           
       delay(15); } 
     delay(200); 
    }
}
