/*
 * Connections:
 *     | esp8266 | nodemcu | rdm6300 | notes                               |
 *     |---------+---------+---------|-------------------------------------|
 *     | GPIO-13 | D7      | TX      | TX level is same 3.3V as esp8266    |
 *     | 5V      | Vin (5V) | VCC    | The rdm6300 must be powered with 5V |
 *     | GND     | GND     | GND     |                                     |
 */
#include <rdm6300.h>

#define RDM6300_RX_PIN 13
#define READ_LED_PIN 16

Rdm6300 rdm6300;

void setup()
{
    Serial.begin(115200); //Higher baudrate for faster reading speed

  pinMode(READ_LED_PIN, OUTPUT);
  digitalWrite(READ_LED_PIN, LOW);

  rdm6300.begin(RDM6300_RX_PIN);

  Serial1.println("\nPlace RFID tag near the RDM6300");
}

void loop()
{
  /* if non-zero tag_id, update() returns true- a new tag is near! */
  if (rdm6300.update())
    Serial.println(rdm6300.get_tag_id(), DEC);

  digitalWrite(READ_LED_PIN, rdm6300.is_tag_near());

  delay(10);
}