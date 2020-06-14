/*
 * program untuk membuat keamanan rumah dan kostan 
 * bebasis RFID(radio frekuensi identifier)
 * Ditulis oleh : ScienceofGlory Algorithm Factory
 */
#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN,RST_PIN);

Servo servoini;

const int sudut = 90; // UNTUK MENENTUKAN SUDUT PUTAR SERVO
const int ledPIN1 = 7; // UNTUK LED BERWARNA HIJAU== BERHASIL
const int ledPIN2 = 6;  // UNTUK LED WARNA MERAH== GAGAL
const int pingPin = A0;
int jarak = 0;

void setup() 
{
  Serial.begin(9600); 
  servoini.attach(8);                      
  pinMode(ledPIN1, OUTPUT);
  pinMode(ledPIN2, OUTPUT);
  pinMode(pingPin, INPUT);
  delay(1000);
  SPI.begin();
  rfid.init();
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("HELLO SELAMAT DATANG");
  delay(1000);
  lcd.clear();
}

void loop() 
{ 
  if(rfid.isCard())
  {
    if(rfid.readCardSerial())
    {
       Serial.print(rfid.serNum[0]);
       Serial.print(" ");
       Serial.print(rfid.serNum[1]);
       Serial.print(" ");
       Serial.print(rfid.serNum[2]);
       Serial.print(" ");
       Serial.println(rfid.serNum[3]);
    }
    rfid.halt();
  } 
  if(rfid.serNum[3]==127)
  {
    
    Serial.println("BERHASIL ");
    lcd.setCursor(0, 0);
    lcd.print("BERHASIL");
    lcd.setCursor(0, 1);
    lcd.print("Silahkan Masuk");
    digitalWrite(ledPIN1, HIGH);
    digitalWrite(ledPIN2, LOW);
    delay(1000);

    int sudut = 0;
    for (sudut = 0; sudut <= 180; sudut += 1)
    { 
      servoini.write(sudut);              
      delay(15);                       
    }
    for (sudut = 180; sudut >= 0; sudut -= 1) 
    { 
      servoini.write(sudut);              
      delay(15);                       
    }
  }
  else
  {
    Serial.println("GAGAL ");
    lcd.setCursor(0, 0);
    lcd.print("Yahhhh");
    lcd.setCursor(0, 1);
    lcd.print("GAGAL");
    digitalWrite(ledPIN2, HIGH);
    digitalWrite(ledPIN1, LOW);
    delay(1000);
  }
}
