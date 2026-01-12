#include <SPI.h>
#include <MFRC522.h>

#define RST 22
#define SDA 21
#define RELAY 4
#define LED_HIJAU 12
#define LED_MERAH 14
#define ALARM 5
#define BUTTON_PIN 34

int buttonState = 1;

MFRC522 mfrc522(SDA, RST);


typedef struct {
  byte data[7]; 
} CardData;

CardData allowedCards[] = {
  {{ 0x33, 0x2E, 0x08, 0x14 }},
  {{ 0x02, 0x1A, 0x1F, 0xD7, 0x04, 0x40, 0x00 }},
  {{ 0x05, 0x8C, 0xFB, 0x7D, 0xB6, 0x51, 0x00 }},
  {{ 0x02, 0xBB, 0xA8, 0x61, 0x20, 0xB0, 0xA0 }},
  {{ 0x04, 0x1E, 0x3B, 0x22, 0x0F, 0x5D, 0x80 }},
  {{ 0x02, 0x1A, 0x1F, 0xD7, 0x04, 0x40, 0x00 }},
  {{ 0x05, 0x81, 0x62, 0x2E, 0x98, 0xD1, 0x00 }},
  {{ 0x02, 0xC3, 0x78, 0xB1, 0x90, 0x99, 0x90 }},
  {{ 0x02, 0xA4, 0xC9, 0x11, 0x50, 0xD5, 0x00 }},
  {{ 0x05, 0x84, 0x36, 0x61, 0x73, 0xA1, 0x00 }},
  {{ 0x05, 0x84, 0xB5, 0xD9, 0x2C, 0xA1, 0x00 }},
  {{ 0x02, 0x7F, 0x98, 0x42, 0x04, 0x40, 0x00 }}

};

int numCards = sizeof(allowedCards) / sizeof(CardData); 

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println("Letakan Kartu Di Sensor");
  pinMode(RELAY, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(ALARM, OUTPUT);
  noTone(ALARM);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    Serial.println("Button pressed");
    digitalWrite(RELAY, HIGH);
    delay(5000);
    digitalWrite(RELAY, LOW);
  } 

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return;

  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  Serial.print("Kode Kartu: ");
  Serial.print("{ ");

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print("0x");
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0"); 
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) {
      Serial.print(", ");
    }
  }
  Serial.print(" }");
  Serial.println();
  bool accessGranted = false;

  // Membandingkan UID kartu dengan setiap token kartu yang diizinkan
  for (int i = 0; i < numCards; i++) {
    bool match = true;
    for (int j = 0; j < mfrc522.uid.size; j++) {
      if (mfrc522.uid.uidByte[j] != allowedCards[i].data[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      accessGranted = true;
      break;
    }
  }

  if (accessGranted) {
    Serial.println("AKSES DITERIMA");
    Serial.println();
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_HIJAU, HIGH);
    delay(5000);
    digitalWrite(RELAY, LOW);
    digitalWrite(LED_HIJAU, LOW);
  } 
  else {
    Serial.println("Akses Ditolak");
    digitalWrite(LED_MERAH, HIGH);
    tone(ALARM, 2000);
    delay(1000);
    noTone(ALARM);
    digitalWrite(LED_MERAH, LOW);
  }
}
