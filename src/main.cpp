#include <Arduino.h>

int irPin = 2;
int mq3Pin = A0;

int ledPin = 8;
int buzzerPin = 9;
int relayPin = 7;

int threshold = 350;

void setup()
{
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int helmet = digitalRead(irPin);
  int alcohol = analogRead(mq3Pin);

  Serial.print("IR: ");
  Serial.print(helmet);
  Serial.print(" | MQ3: ");
  Serial.println(alcohol);

  if (helmet == LOW && alcohol < threshold)
  {
    // SAFE
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    // UNSAFE
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, LOW);
  }

  delay(500);
}