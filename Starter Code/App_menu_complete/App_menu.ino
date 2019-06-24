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

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initialize global variables
int home_menu_state = 0;
int scroll_state;
int pushbutton_state = 0;
unsigned long previous_time;

void setup() {
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pushbutton, RISING);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome!");
  delay(1000);
}

void loop() {

  // magic 8-ball
  if (analogRead(0) < 341) scroll_state = 0;
  // Rock Paper Scissors
  else if (analogRead(0) < 682) scroll_state = 1;
  // fortune
  else scroll_state = 2;

  switch (home_menu_state) {
    
    // transition to magic 8-ball state
    case 0:
      lcd.clear();
      lcd.print("Magic 8-ball");
      home_menu_state = 1;
      if (scroll_state == 1) home_menu_state = 2;
      if (scroll_state == 2) home_menu_state = 5;
      break;
      
    // static magic 8-ball state
    case 1:
      if (scroll_state == 1) home_menu_state = 2;
      if (scroll_state == 2) home_menu_state = 5;
      if (pushbutton_state == 1) {
        pushbutton_state = 0;
        magic8ball();
        home_menu_state = 0;
      }
      break;
      
    // transition to Rock Paper Scissors
    case 2:
      lcd.clear();
      lcd.print("Rock, Paper, Scissors");
      home_menu_state = 3;
      previous_time = millis();
      if (scroll_state == 0) home_menu_state = 0;
      if (scroll_state == 2) home_menu_state = 5;
      break;
      
    // 2nd transition to Rock Paper Scissors
    case 3:
      if ((millis() - previous_time) > 500) {
        previous_time = millis();
        home_menu_state = 4;
      }
      if (scroll_state == 0) home_menu_state = 0;
      if (scroll_state == 2) home_menu_state = 5;
      break;
      
    // static Rock, Paper, Scissors
    case 4:
      if ((millis() - previous_time) > 300) {
        previous_time = millis();
        lcd.scrollDisplayLeft();
      }
      if (scroll_state == 0) home_menu_state = 0;
      if (scroll_state == 2) home_menu_state = 5;
      if (pushbutton_state == 1) {
        pushbutton_state = 0;
        rps_user_select();
        home_menu_state = 0;
      }
      break;

    // transition to fortune state
    case 5:
      lcd.clear();
      lcd.print("Fortune");
      home_menu_state = 6;
      if (scroll_state == 0) home_menu_state = 0;
      if (scroll_state == 1) home_menu_state = 2;
      break;
      
    // static fortune state
    case 6:
      if (scroll_state == 0) home_menu_state = 0;
      if (scroll_state == 1) home_menu_state = 2;
      if (pushbutton_state == 1) {
        pushbutton_state = 0;
        fortune();
        home_menu_state = 0;
      }
      break;
  }

  // delay at the end of the full loop:
  //delay(1000);

}

/* interrupt service routine triggered by button press */
void pushbutton() {
  pushbutton_state = 1;
}

/* magic eight ball */
void magic8ball() {

  // string array of 20 possible responses
  String responses[] = {"It is certain","It is decidedly so.","Without a doubt.","Yes - definitely.","You may rely on it.","As I see it, yes.",
  "Most likely.","Outlook good.","Yes.","Signs point to yes.","Reply hazy, try again.","Ask again later.","Better not tell you now.",
  "Cannot predict now.","Concentrate and ask again.","Don't count on it.","My reply is no.","My sources say no.","Outlook not so good.",
  "Very doubtful."};
  
  String response = responses[random(20)];
  
  // generate random number between 0 and 19 to select and print random response
  lcd.clear();
  lcd.print(response);

  if (response.length() <= 16) delay(5000);
  else {
    delay(500);
    for (int i=0; i < (response.length()-16); i++) {
      lcd.scrollDisplayLeft();
      delay(300);
    }
    delay(2000);
  }
}

/* Rock Paper Scissors game */
void rps_user_select() {
  int rps_state = 0;
  int complete = 1;
  
  while(complete) {
    int rps_scroll = analogRead(0);
    switch (rps_state) {
      // transition Rock state
      case 0:
        lcd.clear();
        lcd.setCursor(0, 0); // top left
        lcd.print("Rock");
        lcd.setCursor(0, 1); // bottom left
        lcd.print("Scroll options");
        rps_state = 1;
        break;
      // static Rock state
      case 1:
        if (rps_scroll < 341) ;
        else if (rps_scroll < 682) rps_state = 2;
        else rps_state = 4;
        if (pushbutton_state == 1) {
          RockPaperScissors("Rock");
          pushbutton_state = 0;
          complete = 0;
        }
        break;
      // transition Paper state
      case 2:
        lcd.clear();
        lcd.setCursor(0, 0); // top left
        lcd.print("Paper");
        lcd.setCursor(0, 1); // bottom left
        lcd.print("Scroll options");
        rps_state = 3;
        break;
      // static Paper state
      case 3:
        if (rps_scroll < 341) rps_state = 0;
        else if (rps_scroll < 682) ;
        else rps_state = 4;
        if (pushbutton_state == 1) {
          RockPaperScissors("Paper");
          pushbutton_state = 0;
          complete = 0;
        }
        break;
      // transition Scissors state
      case 4:
        lcd.clear();
        lcd.setCursor(0, 0); // top left
        lcd.print("Scissors");
        lcd.setCursor(0, 1); // bottom left
        lcd.print("Scroll options");
        rps_state = 5;
        break;
      // static Scissors state
      case 5:
        if (rps_scroll < 341) rps_state = 0;
        else if (rps_scroll < 682) rps_state = 2;
        else ;
        if (pushbutton_state == 1) {
          RockPaperScissors("Scissors");
          pushbutton_state = 0;
          complete = 0;
        }
        break;
    }
  }
}

/* Rock Paper Scissors game */
void RockPaperScissors(String input) {

  // string array of 3 options
  String options[] = {"Rock","Paper","Scissors"};
  String option = options[random(3)];
  String top_row, bottom_row;

  // user chose Rock
  if(input.equals("Rock")) {
    if (option.equals("Rock")) {
      top_row = "Rock can't beat rock.";
      bottom_row = "Tie!";
    }
    else if (option.equals("Paper")) {
      top_row = "Paper covers rock.";
      bottom_row = "Arduino wins!";
    }
    else if (option.equals("Scissors")) {
      top_row = "Rock smashes scissors.";
      bottom_row = "You win!";
    }
  }
  // user chose Paper
  else if (input.equals("Paper")) {
    if (option.equals("Rock")) {
      top_row = "Paper covers rock.";
      bottom_row = "You win!";
    }
    else if (option.equals("Paper")) {
      top_row = "Paper can't beat paper.";
      bottom_row = "Tie!";
    }
    else if (option.equals("Scissors")) {
      top_row = "Scissors cut paper.";
      bottom_row = "Arduino wins!";
    }
  }
  // user chose Scissors
  else if (input.equals("Scissors")) {
    if (option.equals("Rock")) {
      top_row = "Rock smashes scissors.";
      bottom_row = "Arduino wins!";
    }
    else if (option.equals("Paper")) {
      top_row = "Scissors cut paper.";
      bottom_row = "You win!";
    }
    else if (option.equals("Scissors")) {
      top_row = "Scissors can't beat scissors.";
      bottom_row = "Tie!";
    }
  }
  else lcd.print("Not a valid input.");

  lcd.clear();
  lcd.setCursor(0, 1); // bottom left
  lcd.print(bottom_row);
  oneLineScroll(0,top_row);
      
  delay(2000);
  
}

/* produces a random fortune */
void fortune () {

  String fortunes[] = {"Hard work pays off in the future, laziness pays off now.",
"Change can hurt, but it leads a path to something better.",
"A chance meeting opens new doors to success and friendship.",
"You cannot love life until you live the life you love.",
"Meeting adversity well is the source of your strength.",
"A dream you have will come true.",
"Our deeds determine us, as much as we determine our deeds.",
"You cannot love life until you live the life you love."};

  // generate random number between 0 and 7 to select and print random fortune
  String response = fortunes[random(8)];
  
  lcd.clear();
  lcd.setCursor(0, 1); // bottom left
  oneLineScroll(1,response);
  delay(1000);

}

/* if string is too large to print, scroll on single line */
void oneLineScroll (int line, String str1) {
  int i;

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
