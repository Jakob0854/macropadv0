#include <LittleFS.h>

void setup() {
  Serial.setTimeout(2);
  Serial.begin(115200);
  LittleFS.begin();

  delay(5000);
  char littlefs_buff[32];
  int rgb_isfade = 0;
  int valR = 255;
  int valG = 0;
  int valB = 255;

  File littlefs_f;
  LittleFS.format();

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

/*  littlefs_f = LittleFS.open("/rgb/fade.txt", "r");
  if (f) {
    bzero(buff, 32);
    if (f.read((uint8_t *)buff, 31)) {
      sscanf(buff, "%d", &cnt);
      Serial.println(cnt);
    }
    f.close();
  }

  */
/*
  rgb_red = LittleFS.open("/rgb/red.txt", "r");
  rgb_green = LittleFS.open("/rgb/green.txt", "r");
  rgb_blue = LittleFS.open("/rgb/blue.txt", "r");
*/
}

void loop() {
  // put your main code here, to run repeatedly:

}
