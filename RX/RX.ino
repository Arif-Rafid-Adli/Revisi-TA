#include <SoftwareSerial.h>
#include <LoRa_E32.h>

SoftwareSerial loraSerial(2, 3);  // Pin RX dan TX untuk komunikasi serial dengan modul EBYTE E32
LoRa_E32 e32ttl(&loraSerial, 5, 6, 7);
const int ledPin = 9;  // Pin untuk LED

void setup() {
  pinMode(ledPin, OUTPUT);  // Set pin LED sebagai output
  Serial.begin(9600);       // Serial monitor
  e32ttl.begin();
  ResponseStructContainer c;
  c = e32ttl.getConfiguration();
  Configuration configuration = *(Configuration*)c.data;
  configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;

  e32ttl.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
  c.close();
  // ---------------------------
  Serial.println();
  Serial.println("Start listening!");
  e32ttl.setMode(MODE_2_POWER_SAVING);

  delay(1000);
  Serial.println("Penerima Siap");
}

void loop() {
  if (loraSerial.available() > 1) {
    String message = loraSerial.readString();  // Membaca pesan dari LoRa
    Serial.println("Pesan diterima: " + message);

    if (message == "ON") {
      digitalWrite(ledPin, HIGH);  // Nyalakan LED
      Serial.println("LED ON.");
    }
    if (message == "OFF") {
      digitalWrite(ledPin, LOW);  // Matikan LED
      Serial.println("LED OFF.");
    }
  }

  delay(200);  // Delay untuk mengurangi penggunaan CPU
}
