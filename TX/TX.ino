#include <SoftwareSerial.h>
#include <LoRa_E32.h>

SoftwareSerial loraSerial(2, 3);  // Pin RX dan TX untuk komunikasi serial dengan modul EBYTE E32
LoRa_E32 e32ttl(&loraSerial, 5, 6, 7);

const int buttonPin = 9;  // Pin untuk button
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Set pin button sebagai input
  Serial.begin(9600);                // Serial monitor
  e32ttl.begin();
  delay(1000);
  Serial.println("Pemancar Siap");
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Membaca status button

  if (buttonState == LOW) {
    ResponseStatus rs = e32ttl.sendMessage("ON");
    Serial.println("Button ditekan");
    Serial.println(rs.getResponseDescription());
  }
  if (buttonState == HIGH) {
    ResponseStatus rs = e32ttl.sendMessage("OFF");
    Serial.println("Button tidak ditekan");
    Serial.println(rs.getResponseDescription());
  }
  delay(100);
}
