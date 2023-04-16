/* use Earle's Boardmanager

created by Jakob Kramlich

https://github.com/Jakob0854

*/
// b1 for button1
// b1s for button1state

#include "Keyboard.h"

#include <LittleFS.h>

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

  //layout-keys
  const char layoutkeys[4][8] = {
    {'2', '3', '4', '5', '6', '7', '8', '9'},
    {'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'},
    {'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q'},
    {'r', 's', 't', 'u', 'v', 'w', 'x', 'y'}
  };

//DISPLAY-------------------------------------------------
  //create var for numbers on display
  int z1 = 10;
  int z2 = 10;
  int z3 = 10;
  int z4 = 10;

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

  //pattern
  const bool displ_pattern[11][7] = {
    {0, 0, 0, 0, 0, 0, 1},  //0
    {1, 0, 0, 1, 1, 1, 1},  //1
    {0, 0, 1, 0, 0, 1, 0},  //2
    {0, 0, 0, 0, 1, 1, 0},  //3
    {1, 0, 0, 1, 1, 0, 0},  //4
    {0, 1, 0, 0, 1, 0, 0},  //5
    {0, 1, 0, 0, 0, 0, 0},  //6
    {0, 0, 0, 1, 1, 1, 1},  //7
    {0, 0, 0, 0, 0, 0, 0},  //8
    {0, 0, 0, 0, 1, 0, 0},  //9
    {1, 1, 1, 1, 1, 1, 1},  //off
  };

  const char displ_seg_pattern[7] = {sega, segb, segc, segd, sege, segf, segg};
  const char displ_dig_pattern[4] = {dig1, dig2, dig3, dig4};
  const char displ_dig_val[4] = {z1, z2, z3, z4};
  const int displ_delay = 2;

  
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
  int rgb_isfade = 0;
  int valR = 0;
  int valG = 0;
  int valB = 0;
  String RGBcolread;
  

//LITTLE FS
  char littlefs_buff[32];
  File littlefs_f;


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
  
  //set leds
    pinMode(LED_BUILTIN, OUTPUT);



  Serial.setTimeout(2);
  Serial.begin(115200);

  LittleFS.begin();

  rtc_init();
  rtc_set_datetime(&currTime);

  // initialize control over the keyboard:
  Keyboard.begin();

  delay(4000);

  b1s = digitalRead(b1);
  if (b1s == LOW) {

  };

  

  //read littlefs
    //RGB
      //fade
        littlefs_f = LittleFS.open("/rgb/fade.txt", "r");
        if (littlefs_f) {
          bzero(littlefs_buff, 32);
          if (littlefs_f.read((uint8_t *)littlefs_buff, 31)) {
            sscanf(littlefs_buff, "%d", &rgb_isfade);
            Serial.println(rgb_isfade);
          }
          littlefs_f.close();        
        }
        if (rgb_isfade == 1) {
          LED.setFunction(Fade);
        }

      if (rgb_isfade == 0) {
      //red
        littlefs_f = LittleFS.open("/rgb/red.txt", "r");
        if (littlefs_f) {
          bzero(littlefs_buff, 32);
          if (littlefs_f.read((uint8_t *)littlefs_buff, 31)) {
            sscanf(littlefs_buff, "%d", &valR);


            Serial.println(valR);
          }
          littlefs_f.close();        
        }

      //green
        littlefs_f = LittleFS.open("/rgb/green.txt", "r");
        if (littlefs_f) {
          bzero(littlefs_buff, 32);
          if (littlefs_f.read((uint8_t *)littlefs_buff, 31)) {
            sscanf(littlefs_buff, "%d", &valG);


            Serial.println(valG);
          }
          littlefs_f.close();        
        }

      //blue
        littlefs_f = LittleFS.open("/rgb/blue.txt", "r");
        if (littlefs_f) {
          bzero(littlefs_buff, 32);
          if (littlefs_f.read((uint8_t *)littlefs_buff, 31)) {
            sscanf(littlefs_buff, "%d", &valB);
            analogWrite(27, valB);
            
            Serial.println(valB);
          }
          littlefs_f.close();        
        }
      }        

      /* rgb_red = LittleFS.open("/rgb/red.txt", "r");
      rgb_green = LittleFS.open("/rgb/green.txt", "r");
      rgb_blue = LittleFS.open("/rgb/blue.txt", "r");
*/

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
    if (displaystate == "layout") {
        if (layout == 0) {
          //set var for display       
          z4 = 1;
        }
        if (layout == 1) {
          //set var for display       
          z4 = 2;
        }
        if (layout == 2) {
          //set var for display       
          z4 = 3;
        }
        if (layout == 3) {
          //set var for display       
          z4 = 4;
        }
    }
    //check if key is pressed + send keys
    if (b2s == LOW) {
      Keyboard.write(layoutkeys[layout][0]);
      delay(200);
    }
    if (b3s == LOW) {
      Keyboard.write(layoutkeys[layout][1]);
      delay(200);
    }
    if (b4s == LOW) {
      Keyboard.write(layoutkeys[layout][2]);
      delay(200);
    }
    if (b5s == LOW) {
      Keyboard.write(layoutkeys[layout][3]);
      delay(200);
    }
    if (b6s == LOW) {
      Keyboard.write(layoutkeys[layout][4]);
      delay(200);
    }
    if (b7s == LOW) {
      Keyboard.write(layoutkeys[layout][5]);
      delay(200);
    }
    if (b8s == LOW) {
      Keyboard.write(layoutkeys[layout][6]);
      delay(200);
    }
    if (b9s == LOW) {
      Keyboard.write(layoutkeys[layout][7]);
      delay(200);
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
    if (rgb_isfade == 1) {   
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
      rgb_isfade = 1;
      LED.setFunction(Fade);
    }

    if (receivedCommand == "set rgb_custom color") {
      LED.stop();
      rgb_isfade = 0;
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

    if (receivedCommand == "save to littlefs") {
      //RGB
        //fade
          sprintf(littlefs_buff, "%d\n", rgb_isfade);
          littlefs_f = LittleFS.open("/rgb/fade.txt", "w");
          if (littlefs_f) {
            littlefs_f.write(littlefs_buff, strlen(littlefs_buff));
            littlefs_f.close();
          }
        //red
          sprintf(littlefs_buff, "%d\n", valR);
          littlefs_f = LittleFS.open("/rgb/red.txt", "w");
          if (littlefs_f) {
            littlefs_f.write(littlefs_buff, strlen(littlefs_buff));
            littlefs_f.close();
          }

        //green
          sprintf(littlefs_buff, "%d\n", valG);
          littlefs_f = LittleFS.open("/rgb/green.txt", "w");
          if (littlefs_f) {
            littlefs_f.write(littlefs_buff, strlen(littlefs_buff));
            littlefs_f.close();
          }

        //blue
          sprintf(littlefs_buff, "%d\n", valB);
          littlefs_f = LittleFS.open("/rgb/blue.txt", "w");
          if (littlefs_f) {
            littlefs_f.write(littlefs_buff, strlen(littlefs_buff));
            littlefs_f.close();
          }

      //
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

// Running on core1
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


  void loop1() {   

    digitalWrite(displ_dig_pattern[0], HIGH);
    for (int i1 = 0; i1 < 7; i1++) {
      digitalWrite(displ_seg_pattern[i1], displ_pattern[z1][i1]);
    };
    delay(displ_delay);
    setup1();

    digitalWrite(displ_dig_pattern[1], HIGH);
    for (int i1 = 0; i1 < 7; i1++) {
      digitalWrite(displ_seg_pattern[i1], displ_pattern[z2][i1]);
    };
    delay(displ_delay);
    setup1();

    digitalWrite(displ_dig_pattern[2], HIGH);
    for (int i1 = 0; i1 < 7; i1++) {
      digitalWrite(displ_seg_pattern[i1], displ_pattern[z3][i1]);
    };
    delay(displ_delay);
    setup1();

    digitalWrite(displ_dig_pattern[3], HIGH);
    for (int i1 = 0; i1 < 7; i1++) {
      digitalWrite(displ_seg_pattern[i1], displ_pattern[z4][i1]);
    };
    delay(displ_delay);
    setup1();



}