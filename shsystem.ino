#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

#define Trigpin 9
#define Echopin 10
const int button_pin = 8;

float bottle_height = 23.0; //Intake logic
float radius_bottle = 3.5;
float water_volume = 850.0;
bool buttonstate = HIGH;
bool last_reading = HIGH;
unsigned long last_bounced = 0;
unsigned long bounce_delay = 50;
long duration;
float distance;
float water_remaining;
float water_intake;


const int led_remainder = 12;
const int buzzer_remainder = 11;
unsigned long last_time_drank = 0;
unsigned long interval = 0;
void setup() {
  pinMode(led_remainder,OUTPUT);
  pinMode(buzzer_remainder,OUTPUT);
  pinMode(Trigpin,OUTPUT);
  pinMode(Echopin,INPUT);
  Serial.begin(600);
  pinMode(button_pin,INPUT_PULLUP);
  dht.begin();  // put your setup code here, to run once:

}

void loop() {
  float temp = dht.readTemperature();
  Serial.println("\ntemperature is");
  Serial.print(temp);
  if(temp < 0.0)
  {
    interval = 30 * 1000;
    Serial.println("the temperature is in negative degrees\n");
  }
  else if(temp > 0.0 && temp < 20.0)
  {
    interval = 12 * 1000;
  }
  else if(temp > 20.0 && temp < 32.0)
  {
    interval = 8 * 1000;
  
  }
  else
  {
    interval = 5 * 1000;
  }

  if((millis() - last_time_drank) >= interval)
  {
    digitalWrite(led_remainder,HIGH);
    digitalWrite(buzzer_remainder,HIGH);
    Serial.println("\nwater thaagu bey !!\n");
    digitalWrite(led_remainder,LOW);
    digitalWrite(buzzer_remainder,LOW);
    last_time_drank = millis();
  }
  // put your main code here, to run repeatedly:
  
 bool reading = digitalRead(button_pin);
 if(reading != last_reading)
 {
  last_bounced = millis();
 }

if((millis() - last_bounced) >= bounce_delay)   // looking for the stability of the button
 {
  if(reading != buttonstate)
  {
    buttonstate =  reading;
    if(buttonstate == LOW)
    {
      digitalWrite(Trigpin,LOW);
      delayMicroseconds(2);
      digitalWrite(Trigpin,HIGH);
      delayMicroseconds(10);
      digitalWrite(Trigpin,LOW);
      delayMicroseconds(2);

      duration = pulseIn(Echopin,HIGH);
      distance = (duration * 0.0343) / 2;
      float water_level = bottle_height - distance;
      float volume_remain_in_bottle = 3.14*radius_bottle*radius_bottle*water_level;
      water_intake = water_volume - volume_remain_in_bottle;

      Serial.println("\nintake is:");
      Serial.print(water_intake);
    

    }
  }
  
 }
 last_reading = reading;
}