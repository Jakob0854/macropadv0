//use Earle's Code

// b1 for button1
// b1s for button1state

#include "Keyboard.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include <RGB_LED.h>
RGB_LED LED(19, 28, 27);

#include "defines.h"
#include <Timezone_Generic.h>
datetime_t currTime = { 2022, 1, 21, 5, 0, 0, 0 };

//BUTTONS--------------------------------------------------
  //define buttons pins
  const int b1 = 12;
  const int b2 = 10;
  const int b3 = 18;
  const int b4 = 13;
  const int b5 = 14;
  const int b6 = 17;
  const int b7 = 15;
  const int b8 = 16;
  const int b9 = 11;

  //create var for buttons
  int b1s = 0;
  int b2s = 0;
  int b3s = 0;
  int b4s = 0;
  int b5s = 0;
  int b6s = 0;
  int b7s = 0;
  int b8s = 0;
  int b9s = 0;

//STM POTI--------------------------------------------------
  //set pin for poti
  const int stmpoti = 26;

  //set var for snap to middle poti (stm)
  int stmpotiwert = 0;
  int stmpotimap = 0;
  int stmpotiall = 0;
  int stmpoticount = 0;
  int stmpotidelay = 0;
  int stmpotiwertanzeige = 0;
  uint8_t stmpotidown[] = {KEY_F13, KEY_F15, KEY_F17, KEY_F19};
  uint8_t stmpotiup[] = {KEY_F14, KEY_F16, KEY_F18, KEY_F20};


//LAYOUT SWITCHER-----------------------------------------
  //create var for layout switcher
  int layout = 0;

  //create var for numbers on display
  int z1 = 10;
  int z2 = 10;
  int z3 = 10;
  int z4 = 0;

//DISPLAY-------------------------------------------------
  //define display_digit pins
  const int dig1 = 3;
  const int dig2 = 0;
  const int dig3 = 21;
  const int dig4 = 9; 

  //define display_segment pins
  const int sega = 2;
  const int segb = 20;
  const int segc = 7;
  const int segd = 4;
  const int sege = 5;
  const int segf = 1;
  const int segg = 8;
  const int segh = 6;

//SERIAL
  String displaystate = "layout";
  //time
  String time_from_pc_h;
  uint8_t uint_time_from_pc_h;
  String time_from_pc_m;
  uint8_t uint_time_from_pc_m;

  uint8_t hournow;
  uint8_t minutenow;
  String timebuf2;

  int hourtens;
  int hourones;
  int minutetens;
  int minuteones;
  //commands
  String receivedCommand;
  

//MILLIS DELAY
  unsigned long previousMillis = 0;  
//RGB
  int rgbOnOff = 0;    
  int valR = 0;
  int valG = 0;
  int valB = 0;
  String RGBcolread;


int i = 0;

void setup() {
  // put your setup code here, to run once:
  
  //set button

    pinMode(b1, INPUT_PULLUP);
    pinMode(b2, INPUT_PULLUP);
    pinMode(b3, INPUT_PULLUP);
    pinMode(b4, INPUT_PULLUP);
    pinMode(b5, INPUT_PULLUP);
    pinMode(b6, INPUT_PULLUP);
    pinMode(b7, INPUT_PULLUP);
    pinMode(b8, INPUT_PULLUP);
    pinMode(b9, INPUT_PULLUP);

  //set display leds
    pinMode(dig1, OUTPUT);
    pinMode(dig2, OUTPUT);
    pinMode(dig3, OUTPUT);
    pinMode(dig4, OUTPUT);
    
    pinMode(sega, OUTPUT);
    pinMode(segb, OUTPUT);
    pinMode(segc, OUTPUT);
    pinMode(segd, OUTPUT);
    pinMode(sege, OUTPUT);
    pinMode(segf, OUTPUT);
    pinMode(segg, OUTPUT);
    pinMode(segh, OUTPUT);
  
  //set display pin states
    digitalWrite(dig1, LOW);
    digitalWrite(dig2, LOW);
    digitalWrite(dig3, LOW);
    digitalWrite(dig4, LOW);
    
    digitalWrite(sega, HIGH);
    digitalWrite(segb, HIGH);
    digitalWrite(segc, HIGH);
    digitalWrite(segd, HIGH);
    digitalWrite(sege, HIGH);
    digitalWrite(segf, HIGH);
    digitalWrite(segg, HIGH);
    digitalWrite(segh, HIGH);

  //set leds
    pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  rtc_init();
  rtc_set_datetime(&currTime);

  // initialize control over the keyboard:
  Keyboard.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //update button var
    b1s = digitalRead(b1);
    b2s = digitalRead(b2);
    b3s = digitalRead(b3);
    b4s = digitalRead(b4);
    b5s = digitalRead(b5);
    b6s = digitalRead(b6);
    b7s = digitalRead(b7);
    b8s = digitalRead(b8);
    b9s = digitalRead(b9);
    
  //update stm poti var
    stmpotiwert = analogRead(stmpoti);
 
  //update other
    //...

  //
  
  //layout switcher
    if (b1s == LOW) {
      
      if (layout <= 3) {
        layout++;
      }
      if (layout == 4) {
        layout = 0; 
      }
      delay(200);
    }
    if (layout == 0) {
      if (displaystate == "layout") {
        //set var for display       
        z4 = 1;
      }
      //check if key is pressed + send keys
      if (b2s == LOW) {
        Keyboard.write('2');
        delay(200);
      }
      if (b3s == LOW) {
        Keyboard.write('3');
        delay(200);
      }
      if (b4s == LOW) {
        Keyboard.write('4');
        delay(200);
      }
      if (b5s == LOW) {
        Keyboard.write('5');
        delay(200);
      }
      if (b6s == LOW) {
        Keyboard.write('6');
        delay(200);
      }
      if (b7s == LOW) {
        Keyboard.write('7');
        delay(200);
      }
      if (b8s == LOW) {
        Keyboard.write('8');
        delay(200);
      }
      if (b9s == LOW) {
        Keyboard.write('9');
        delay(200);
      }
    }
    if (layout == 1) {
      if (displaystate == "layout") {
        //set var for display
        z4 = 2;
      }
      //check if key is pressed + send keys   
      if (b2s == LOW) {
        Keyboard.write('b');
        delay(200);
      }
      if (b3s == LOW) {
        Keyboard.write('c');
        delay(200);
      }
      if (b4s == LOW) {
        Keyboard.write('d');
        delay(200);
      }
      if (b5s == LOW) {
        Keyboard.write('e');
        delay(200);
      }
      if (b6s == LOW) {
        Keyboard.write('f');
        delay(200);
      }
      if (b7s == LOW) {
        Keyboard.write('g');
        delay(200);
      }
      if (b8s == LOW) {
        Keyboard.write('h');
        delay(200);
      }
      if (b9s == LOW) {
        Keyboard.write('i');
        delay(200);
      }
    }
    if (layout == 2) {
      if (displaystate == "layout") {
        //set var for display
        z4 = 3;
      }
      //check if key is pressed + send keys    
      if (b2s == LOW) {
        Keyboard.write('j');
        delay(200);
      }
      if (b3s == LOW) {
        Keyboard.write('k');
        delay(200);
      }
      if (b4s == LOW) {
        Keyboard.write('l');
        delay(200);
      }
      if (b5s == LOW) {
        Keyboard.write('m');
        delay(200);
      }
      if (b6s == LOW) {
        Keyboard.write('n');
        delay(200);
      }
      if (b7s == LOW) {
        Keyboard.write('o');
        delay(200);
      }
      if (b8s == LOW) {
        Keyboard.write('p');
        delay(200);
      }
      if (b9s == LOW) {
        Keyboard.write('q');
        delay(200);
      }
    }
    if (layout == 3) {
      if (displaystate == "layout") {
        //set var for display
        z4 = 4;
      }
      //check if key is pressed + send keys    
      if (b2s == LOW) {
        Keyboard.write('r');
        delay(200);
      }
      if (b3s == LOW) {
        Keyboard.write('s');
        delay(200);
      }
      if (b4s == LOW) {
        Keyboard.write('t');
        delay(200);
      }
      if (b5s == LOW) {
        Keyboard.write('u');
        delay(200);
      }
      if (b6s == LOW) {
        Keyboard.write('v');
        delay(200);
      }
      if (b7s == LOW) {
        Keyboard.write('w');
        delay(200);
      }
      if (b8s == LOW) {
        Keyboard.write('x');
        delay(200);
      }
      if (b9s == LOW) {
        Keyboard.write('y');
        delay(200);
      }
    }


  //
  
  //stmpoti
    if (stmpoticount <= 49) {
      stmpotiall = stmpotiall + stmpotiwert;
      stmpoticount++;
    }
    if (stmpoticount == 50) {
      stmpotiall = (stmpotiall/50);
      stmpotiwertanzeige = map(stmpotiall, 0, 1023, 0, 100);
      stmpoticount = 0;
      stmpotiall = 0;
      
      
      if ((stmpotiwertanzeige <= 40) && (stmpotiwertanzeige >= 0)) {

        Keyboard.write(stmpotidown[layout]);
        stmpotidelay = (stmpotiwertanzeige * 10);

        //Serial.println("Wert");
        //Serial.println(stmpotiwertanzeige);
        //Serial.println("Delay");
        //Serial.println(stmpotidelay);

        delay(stmpotidelay);
      }
    
      if ((stmpotiwertanzeige <= 100) && (stmpotiwertanzeige >= 60)) {
        
        Keyboard.write(stmpotiup[layout]);
        stmpotiwertanzeige = (100 - stmpotiwertanzeige);
        stmpotidelay = (stmpotiwertanzeige * 10);

        //Serial.println("Wert");
        //Serial.println(stmpotiwertanzeige);
        //Serial.println("Delay");
        //Serial.println(stmpotidelay);

        delay(stmpotidelay);
      }
    }
  

  //
  
  //serial read
    CheckSerial();
  //
  //update time
    if (displaystate == "time") {
      displayTime();
      
      z1 = hourtens;
      z2 = hourones;
      z3 = minutetens;
      z4 = minuteones;
    }

  //
  //RGB
    if (rgbOnOff == 1) {   
    LED.run();
    }
  
  //

}

void CheckSerial() { //Checking the serial port via IF statements
  if (Serial.available() > 0) {
    
    receivedCommand = Serial.readString();
    receivedCommand.trim();

    if (receivedCommand == "displ_set time") {
      displaystate = "time";
      while (i == 0) {
        if (Serial.available() > 0) {
          time_from_pc_h = Serial.readString();
          i = 1;
        }
      }
      i = 0;
      while (i == 0) {
        if (Serial.available() > 0) {
          time_from_pc_m = Serial.readString();
          i = 1;          
        }
      }
      i = 0;
      

      uint8_t uint_time_from_pc_h = atoi (time_from_pc_h.substring(0).c_str());
      uint8_t uint_time_from_pc_m = atoi (time_from_pc_m.substring(0).c_str());
      
      datetime_t currTime = { 2022, 1, 21, 5, uint_time_from_pc_h, uint_time_from_pc_m, 0 };
      rtc_set_datetime(&currTime);
    }

    if (receivedCommand == "displ_layout") {
      displaystate = "layout";
      z1 = 10;
      z2 = 10;
      z3 = 10;
    }

    if (receivedCommand == "displ_off") {
      displaystate = "off";
      z1 = 10;
      z2 = 10;
      z3 = 10;
      z4 = 10;
    }

    if (receivedCommand == "set rgb_fade") {
      rgbOnOff = 1;
      LED.setFunction(Fade);
    }

    if (receivedCommand == "set rgb_custom color") {
      LED.stop();
      rgbOnOff = 0;
      while (i == 0) {
        if (Serial.available() > 0) {
          RGBcolread = Serial.readString();
          int valR = RGBcolread.toInt();
          analogWrite(19, valR);
          i = 1;
        }
      }
      i = 0;
      while (i == 0) {
        if (Serial.available() > 0) {
          RGBcolread = Serial.readString();
          int valG = RGBcolread.toInt();
          analogWrite(28, valG);
          i = 1;          
        }
      }
      i = 0;
      while (i == 0) {
        if (Serial.available() > 0) {
          RGBcolread = Serial.readString();
          int valB = RGBcolread.toInt();
          analogWrite(27, valB);
          i = 1;          
        }
      }
      i = 0;

      
    }
  }
}

//RTC
  void displayTime() {
    rtc_get_datetime(&currTime);
    // Display time from RTC
    DateTime now = DateTime(currTime);
    time_t utc = now.get_time_t();
    printDateTime(utc, "UTC");
  }

  // format and print a time_t value, with a time zone appended.
  void printDateTime(time_t t, const char *tz) {
    char timebuf[32];
    sprintf(timebuf, "%.2d",
    hour(t), tz);
    //Serial.println(timebuf);
    timebuf2 = timebuf;
    uint8_t hournow = atoi (timebuf2.substring(0).c_str());
    hourtens = hournow / 10;
    hourones = hournow % 10;
    sprintf(timebuf, "%.2d",
    minute(t), tz);
    //Serial.println(timebuf);
    timebuf2 = timebuf;
    uint8_t minutenow = atoi (timebuf2.substring(0).c_str());
    minutetens = minutenow / 10;
    minuteones = minutenow % 10;
  }

//

// Running on core1k
  void setup1() {
    //set display pin states
    digitalWrite(dig1, LOW);
    digitalWrite(dig2, LOW);
    digitalWrite(dig3, LOW);
    digitalWrite(dig4, LOW);
    
    digitalWrite(sega, HIGH);
    digitalWrite(segb, HIGH);
    digitalWrite(segc, HIGH);
    digitalWrite(segd, HIGH);
    digitalWrite(sege, HIGH);
    digitalWrite(segf, HIGH);
    digitalWrite(segg, HIGH);
    digitalWrite(segh, HIGH);
  }
    
  void n0(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segb, LOW);
      digitalWrite(segc, LOW);
      digitalWrite(segd, LOW);
      digitalWrite(sege, LOW);
      digitalWrite(segf, LOW);
      delay(2);
      setup1();
  }
  void n1(bool isCore1 = true) {
      digitalWrite(segb, LOW);
      digitalWrite(segc, LOW);
      delay(2);
      setup1();
  }
  void n2(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segb, LOW);
      digitalWrite(segd, LOW);
      digitalWrite(sege, LOW);
      digitalWrite(segg, LOW);
      delay(2);
      setup1();
  }
  void n3(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segb, LOW);
      digitalWrite(segc, LOW);
      digitalWrite(segd, LOW);
      digitalWrite(segg, LOW);
      delay(2);
      setup1();
  }
  void n4(bool isCore1 = true) {
      digitalWrite(segb, LOW);
      digitalWrite(segc, LOW);
      digitalWrite(segf, LOW);
      digitalWrite(segg, LOW);
      delay(2);
      setup1();
  }
  void n5(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segc, LOW);
      digitalWrite(segd, LOW);
      digitalWrite(segf, LOW);
      digitalWrite(segg, LOW);
      delay(2);
      setup1();
  }
  void n6(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segc, LOW);
      digitalWrite(segd, LOW);
      digitalWrite(sege, LOW);
      digitalWrite(segf, LOW);
      digitalWrite(segg, LOW);
      delay(2);
      setup1();
  }
  void n7(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segb, LOW);
      digitalWrite(segc, LOW);
      delay(2);
      setup1();
  }
  void n8(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segb, LOW);
      digitalWrite(segc, LOW);
      digitalWrite(segd, LOW);
      digitalWrite(sege, LOW);
      digitalWrite(segf, LOW);
      digitalWrite(segg, LOW);
      delay(2);
      setup1();
  }
  void n9(bool isCore1 = true) {
      digitalWrite(sega, LOW);
      digitalWrite(segb, LOW);
      digitalWrite(segc, LOW);
      digitalWrite(segd, LOW);
      digitalWrite(segf, LOW);
      digitalWrite(segg, LOW);
      delay(2);
      setup1();
  }
  void dot(bool isCore1 = true) {
    digitalWrite(segh, LOW);
    delay(2);
    setup1();
  }



  void loop1() {
    //111111111111111111111111111111111
    if (z1 == 0) {
      digitalWrite(dig1, HIGH);
      n0();
    }
    if (z1 == 1) {
      digitalWrite(dig1, HIGH);
      n1();
    }
    if (z1 == 2) {
      digitalWrite(dig1, HIGH);
      n2();
    }
    if (z1 == 3) {
      digitalWrite(dig1, HIGH);
      n3();
    }
    if (z1 == 4) {
      digitalWrite(dig1, HIGH);
      n4();
    }
    if (z1 == 5) {
      digitalWrite(dig1, HIGH);
      n5();
    }
    if (z1 == 6) {
      digitalWrite(dig1, HIGH);
      n6();
    }
    if (z1 == 7) {
      digitalWrite(dig1, HIGH);
      n7();
    }
    if (z1 ==8) {
      digitalWrite(dig1, HIGH);
      n8();    
    }
    if (z1 == 9) {
      digitalWrite(dig1, HIGH);
      n9();
    }
    if (z1 == 10) {
      setup1();
    }
    if (z1 == 11) {
      digitalWrite(dig1, HIGH);
      dot();
    }
    //222222222222222222222222222222222222
    if (z2 == 0) {
      digitalWrite(dig2, HIGH);
      n0();
    }
    if (z2 == 1) {
      digitalWrite(dig2, HIGH);
      n1();
    }
    if (z2 == 2) {
      digitalWrite(dig2, HIGH);
      n2();
    }
    if (z2 == 3) {
      digitalWrite(dig2, HIGH);
      n3();
    }
    if (z2 == 4) {
      digitalWrite(dig2, HIGH);
      n4();
    }
    if (z2 == 5) {
      digitalWrite(dig2, HIGH);
      n5();
    }
    if (z2 == 6) {
      digitalWrite(dig2, HIGH);
      n6();
    }
    if (z2 == 7) {
      digitalWrite(dig2, HIGH);
      n7();
    }
    if (z2 ==8) {
      digitalWrite(dig2, HIGH);
      n8();    
    }
    if (z2 == 9) {
      digitalWrite(dig2, HIGH);
      n9();
    }
    if (z2 == 10) {
      setup1();
    }
    if (z2 == 11) {
      digitalWrite(dig2, HIGH);
      dot();
    }
    //extra rtc dot blink
    if (displaystate == "time") {
      digitalWrite(dig2, HIGH);
      dot();
    }

    //33333333333333333333333333333333333
    if (z3 == 0) {
      digitalWrite(dig3, HIGH);
      n0();
    }
    if (z3 == 1) {
      digitalWrite(dig3, HIGH);
      n1();
    }
    if (z3 == 2) {
      digitalWrite(dig3, HIGH);
      n2();
    }
    if (z3 == 3) {
      digitalWrite(dig3, HIGH);
      n3();
    }
    if (z3 == 4) {
      digitalWrite(dig3, HIGH);
      n4();
    }
    if (z3 == 5) {
      digitalWrite(dig3, HIGH);
      n5();
    }
    if (z3 == 6) {
      digitalWrite(dig3, HIGH);
      n6();
    }
    if (z3 == 7) {
      digitalWrite(dig3, HIGH);
      n7();
    }
    if (z3 ==8) {
      digitalWrite(dig3, HIGH);
      n8();    
    }
    if (z3 == 9) {
      digitalWrite(dig3, HIGH);
      n9();
    }
    if (z3 == 10) {
      setup1();
    }
    if (z3 == 11) {
      digitalWrite(dig3, HIGH);
      dot();
    }
    //44444444444444444444444444444444444444444
    if (z4 == 0) {
      digitalWrite(dig4, HIGH);
      n0();
    }
    if (z4 == 1) {
      digitalWrite(dig4, HIGH);
      n1();
    }
    if (z4 == 2) {
      digitalWrite(dig4, HIGH);
      n2();
    }
    if (z4 == 3) {
      digitalWrite(dig4, HIGH);
      n3();
    }
    if (z4 == 4) {
      digitalWrite(dig4, HIGH);
      n4();
    }
    if (z4 == 5) {
      digitalWrite(dig4, HIGH);
      n5();
    }
    if (z4 == 6) {
      digitalWrite(dig4, HIGH);
      n6();
    }
    if (z4 == 7) {
      digitalWrite(dig4, HIGH);
      n7();
    }
    if (z4 ==8) {
      digitalWrite(dig4, HIGH);
      n8();    
    }
    if (z4 == 9) {
      digitalWrite(dig4, HIGH);
      n9();
    }
    if (z4 == 10) {
      setup1();
    }
    if (z3 == 11) {
      digitalWrite(dig4, HIGH);
      dot();
    }


  }

