void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  /* 
   *  Send an intro notifying the user that you are ready.
   *  Send a prompt about what commands the program is looking for.
   */
  Serial.println("Hi, welcome to the program!");
  Serial.println();
}

void loop() {
  // get any incoming bytes:
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();

    // say what was sent:
    // sample of how you would send something back
    Serial.print("You sent me: ");
    Serial.write(receivedChar);
    Serial.println();

    /* 
     *  Here is where you will put your code.
     */

    /* 
     *  after your processing in the loop is done
     *  send another message notifying the user 
     *  that you are ready for the next command
     */
    Serial.println("Give me another command:");
  }
}
