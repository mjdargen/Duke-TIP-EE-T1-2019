#include "pitches.h"

int buttonPin = 2;
int speakerPin = 8;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  // put your setup code here, to run once:

  pinMode(buttonPin, INPUT);
  pinMode(speakerPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  bool switch_state;
  
  switch_state = digitalRead(buttonPin);

  if (switch_state == HIGH) {
    delay(100);
    switch_state = digitalRead(buttonPin);
    if(switch_state == HIGH) {
      // turn on speaker
      int i;

      for (i=0; i<8; i++){
        int duration = 1000 / noteDurations[i];
        tone(speakerPin, melody[i], duration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = duration * 1.30;
       delay(pauseBetweenNotes);
       // stop the tone playing:
       noTone(8);
      }
    }
  }

}
