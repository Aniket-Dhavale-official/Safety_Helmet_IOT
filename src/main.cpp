#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// LCD
LiquidCrystal lcd(12, 11, 5, 6, 3, 9);

// GSM & GPS
SoftwareSerial gsm(10, 11);
SoftwareSerial gps(4, 5);

// Pins
int irPin = 2;
int mq3Pin = A0;
int relayPin = 7;
int ledPin = 8;

// MPU6050
int16_t ax = 0, ay = 0, az = 0;

// Thresholds
int alcoholThreshold = 250;
int accidentThreshold = 25000;

// GPS data
String latitude = "NA";
String longitude = "NA";
bool gpsAvailable = false;
bool gsmAvailable = false;

// -------- Convert GPS --------
float convertToDecimal(String raw) {
  if (raw.length() < 3) return 0;

  float val = raw.toFloat();
  int degrees = (int)(val / 100);
  float minutes = val - (degrees * 100);
  return degrees + (minutes / 60.0);
}

// -------- Read GPS --------
void readGPS() {
  while (gps.available()) {
    String data = gps.readStringUntil('\n');

    if (data.startsWith("$GPGGA") || data.startsWith("$GPRMC")) {

      int idx1 = data.indexOf(",") + 1;
      int idx2 = data.indexOf(",", idx1);

      idx1 = data.indexOf(",", idx2) + 1;
      idx2 = data.indexOf(",", idx1);
      latitude = data.substring(idx1, idx2);

      idx1 = data.indexOf(",", idx2) + 1;
      idx2 = data.indexOf(",", idx1);
      longitude = data.substring(idx1, idx2);

      gpsAvailable = true;
    }
  }
}

// -------- GSM CHECK --------
void checkGSM() {
  gsm.println("AT");
  delay(500);
  if (gsm.available()) gsmAvailable = true;
}

// -------- SEND SMS --------
void sendSMS(String msg) {
  if (!gsmAvailable) return;

  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+918369711639\"");
  delay(1000);
  gsm.print(msg);
  delay(500);
  gsm.write(26);
  delay(3000);
}

// -------- LCD --------
void lcdPrint(String l1, String l2 = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(l1);
  lcd.setCursor(0, 1);
  lcd.print(l2);
}

// -------- SETUP --------
void setup() {
  pinMode(irPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  gsm.begin(9600);
  gps.begin(9600);

  Wire.begin();

  // MPU6050 init
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  lcd.begin(16, 2);
  lcdPrint("System Init...");
  delay(2000);

  checkGSM();
}

// -------- LOOP --------
void loop() {

  int helmet = digitalRead(irPin);
  int alcohol = analogRead(mq3Pin);

  // -------- MPU READ --------
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  if (Wire.available() == 6) {
    ax = Wire.read() << 8 | Wire.read();
    ay = Wire.read() << 8 | Wire.read();
    az = Wire.read() << 8 | Wire.read();
  } else {
    Serial.println("MPU FAIL");
    delay(200);
    return;
  }

  // -------- GPS --------
  readGPS();

  // -------- FINAL GPS (WITH FALLBACK) --------
float finalLat = 19.160408;   // Datta Meghe College
float finalLon = 72.995558;

  bool validGPS = false;

  if (gpsAvailable && latitude != "NA" && latitude.length() > 5) {
    float lat = convertToDecimal(latitude);
    float lon = convertToDecimal(longitude);

    if (lat != 0 && lon != 0) {
      finalLat = lat;
      finalLon = lon;
      validGPS = true;
    }
  }

  // -------- PRINT GPS --------
  if (validGPS) {
    Serial.print("DETECTED GPS -> ");
  } else {
    Serial.print("GPS -> ");
  }

  Serial.print("Lat: ");
  Serial.print(finalLat, 6);
  Serial.print(" Lon: ");
  Serial.println(finalLon, 6);

  // -------- CONDITIONS --------
  bool accident = (abs(ax) > accidentThreshold || abs(ay) > accidentThreshold);
  bool safeHelmet = (helmet == LOW);
  bool safeAlcohol = (alcohol < alcoholThreshold);

  // -------- LOGIC --------

  if (accident) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);

    lcdPrint("ACCIDENT!");

    String msg = "Accident! ";
    msg += "https://maps.google.com/?q=";
    msg += String(finalLat, 6) + "," + String(finalLon, 6);

    sendSMS(msg);
    Serial.println(msg);

    delay(3000);
  }

  else if (!safeHelmet) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);

    lcdPrint("WEAR HELMET");
    Serial.println("Helmet Missing");
  }

  else if (!safeAlcohol) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);

    lcdPrint("ALCOHOL ALERT");
    Serial.println("Alcohol Detected");
  }

  else {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, HIGH);

    lcdPrint("SAFE TO DRIVE");
    Serial.println("Safe");
  }

  // -------- DEBUG --------
  Serial.print("IR: "); Serial.print(helmet);
  Serial.print(" MQ3: "); Serial.print(alcohol);
  Serial.print(" AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.println(ay);

  delay(500);
}
