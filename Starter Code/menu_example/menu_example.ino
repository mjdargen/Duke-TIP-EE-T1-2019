/*
  App Menu
  Scroll through and execute different applications
  * Magic 8-Ball
  * Rock, Paper, Scissors

  The LCD circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * 10K potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

  Scroll Wheel: potentiometer
 * 10k potentiometer:
 * ends to +5V and ground
 * wiper to A0

  Pushbutton:
 * Digital input 2
 * Configured as external interrupt
 * Connected with 10k resistor to GND
 * Other end of switch connected to 5V

*/

// include the library code:
#include <LiquidCrystal.h>

int home_menu_state = 3;
bool button_state = false;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:

  pinMode(2,INPUT);

  attachInterrupt(digitalPinToInterrupt(2), pushbutton, RISING);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome!");
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

  int ADCvalue = analogRead(0);
  

  switch (home_menu_state) {
    // magic 8-ball
    case 0:
      if (button_state == true) {
        button_state = false;
        lcd.clear();
        lcd.print("Play 8-ball");
        delay(2000);
      }
      // if Fortune state
      if ((ADCvalue>341) && (ADCvalue<=682)) {
        home_menu_state = 1;
        lcd.clear();
        lcd.print("Fortune");
      }
      // if rock paper scissors state
      else if (ADCvalue>682) {
        home_menu_state = 2;
        lcd.clear();
        //lcd.print("Rock, paper, scissors");
        oneLineScroll(0,"Rock, paper, scissors");
      }
      break;

     // fortune
     case 1:
      if (button_state == true) {
        button_state = false;
        lcd.clear();
        lcd.print("Play fortune");
        delay(2000);
      }
      // if magic 8-ball state
      if (ADCvalue<=341) {
        home_menu_state = 0;
        lcd.clear();
        lcd.print("Magic 8-ball");
      }
      // if rock paper scissors state
      else if (ADCvalue>682)  {
        home_menu_state = 2;
        lcd.clear();
        //lcd.print("Rock, paper, scissors");
        oneLineScroll(0,"Rock, paper, scissors");
      }
      break;

    // rock paper scissors
    case 2:
      oneLineScroll(0,"Rock, paper, scissors");
      if (button_state == true) {
        button_state = false;
        lcd.clear();
        lcd.print("Play RPS");
        delay(2000);
      }
      // if magic 8-ball state
      if (ADCvalue<=341) {
        home_menu_state = 0;
        lcd.clear();
        lcd.print("Magic 8-ball");
      }
      // if Fortune state
      if ((ADCvalue>341) && (ADCvalue<=682)) {
        home_menu_state = 1;
        lcd.clear();
        lcd.print("Fortune");
      }
      break;

     case 3:
      if (ADCvalue<=341) {
        home_menu_state = 0;
        lcd.clear();
        lcd.print("Magic 8-ball");
      }
      // if Fortune state
      else if ((ADCvalue>341) && (ADCvalue<=682)) {
        home_menu_state = 1;
        lcd.clear();
        lcd.print("Fortune");
      }
      // if rock paper scissors state
      else if (ADCvalue>682)  {
        home_menu_state = 2;
        lcd.clear();
        //lcd.print("Rock, paper, scissors");
        oneLineScroll(0,"Rock, paper, scissors");
      }
      break;
    
  }

}


/* if string is too large to print, scroll on single line */
void oneLineScroll (int line, String str1) {
  int i;

  // set cursor on intended line and print first 16 chars
  lcd.setCursor(0, line);
  lcd.print(str1.substring(0,15));
  delay(700);
  // for every additional letter, shift in from right
  for (i = 0; i <= (str1.length()-16); i++) {
    lcd.setCursor(0, line);
    lcd.print(str1.substring(i,i+16));
    delay(300);
  }
}

void pushbutton() {
  button_state = true;
  
}
