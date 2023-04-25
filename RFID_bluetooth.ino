#include <SPI.h>
#include <MFRC522.h>  
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(4,5);
int LED_HIJAU = 8;

int P1=0;
int P2=0;
int berenti=0;
int x = 0;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);               // Initiate a serial communication
bluetooth.begin(9600);
SPI.begin();   
mfrc522.PCD_Init(); 
pinMode(LED_HIJAU,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Tempelkan E-ktp Anda...");
  Serial.println();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "7A E9 8B AB") //NOMOR KARTU YANG BENER
  {  
    digitalWrite(LED_HIJAU, HIGH);  
    bluetooth.write(1);
    P1=1;
    P2=0;
    delay(1000);  
    digitalWrite(LED_HIJAU, LOW); 
    
  }
  else if (content.substring(1) == "E5 AB 80 45") //NOMOR KARTU YANG BENER
  {  
    bluetooth.write(2);
    digitalWrite(LED_HIJAU, HIGH);  
    P1=1;
    P2=0;
    delay(1000); 
    digitalWrite(LED_HIJAU, LOW);  
  }   

}
