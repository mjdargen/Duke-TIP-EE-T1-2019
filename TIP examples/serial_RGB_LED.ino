void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // send an intro:
  Serial.println("Send a command (R,G,B)");
  Serial.println();
}

void loop() {
  // get any incoming bytes:
  if (Serial.available() > 0) {
    int thisChar = Serial.read();

    // say what was sent:
    Serial.print("You sent me: \'");
    Serial.write(thisChar);

    /* write what color LED you want turned on or off
     * R - for red
     * G - for green
     * B - for blue
     */

    // add some space and ask for another byte:
    Serial.println();
    Serial.println("Give me another command:");
    Serial.println();
  }
}
