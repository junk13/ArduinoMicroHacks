#include "Keyboard.h"
#include "Mouse.h"
#include "usToDE.h"

#define INPUT_SIZE 2056

char ctrlKey = KEY_LEFT_GUI;
int stdDelay = 50;
char* help = "std:help/splash\nCMD:\nmouser:press/release, mousel:press/release,mousemov:x,y\nkeycmd:GUIr/lock/up/down/left/right, keyln:string, key:string\nstddelay:time";
char* splash = "H4ck1ng t00l v1.0\nTo broadcast/pirate radio stations enter following cmd: radio:1003 (for 100.3)\nYou can execute multiple commands as you append them with an &.\nTo hijack USB Mouse and Keyboard on your target, type this: keycmd:GUIr&keyln:cmd&key:hacked&mouse:0 30&mouse:click\nHave fun!\n\n";
bool isSerial = 0;

void setup()
{
  Serial1.begin(9600);
  //Mouse.begin();
  Keyboard.begin();
  pinMode(LED_BUILTIN, OUTPUT);

  Serial1.println("booted successfully");
}

//digitalWrite(LED_BUILTIN, HIGH);

void loop() {
  if(Serial1.available() > 0) {
    // Get next command from Serial (add 1 for final 0)
    char input[INPUT_SIZE + 1];
    byte size = Serial1.readBytes(input, INPUT_SIZE);
    // Add the final 0 to end the C string
    input[size] = 0;

    char* command = strtok(input, "&"); //commands get separated with an &
    while (command != 0) {
    digitalWrite(LED_BUILTIN, HIGH);

    char* separator = strchr(command, ':'); // Split the command in two values
    if (separator != 0) {
      *separator = 0; //replacing ':'
      ++separator; //with 0

      char* cmd = command;
      char* val = separator;

      if(strcmp(cmd,"delay") == 0) {
      Serial1.print("delay ");
      int del = atoi(separator);
      delay(del);
      Serial1.println(del);
      }
      if(strcmp(cmd,"key") == 0) {
        Serial1.print("keyboard: ");
        Keyboard.print(separator);
        Serial1.println(separator);
      }
      if(strcmp(cmd,"keyln") == 0) {
        Serial1.print("keyboard (br): ");
        //unsigned char keys = (usToDE[separator]);
        //Keyboard.println(keys);
        Keyboard.println(separator);
        Keyboard.write(13);
        Keyboard.write(10);
        Serial1.println(separator);
      }
      if(strcmp(cmd,"keycmd") == 0) {
        if(strcmp(separator, "GUIr") == 0) {
        Keyboard.press(KEY_LEFT_GUI);

        Keyboard.press('r');
        Keyboard.releaseAll();
        Serial1.println(separator);
      }
      if(strcmp(separator, "lock") == 0) {
        Keyboard.press(KEY_LEFT_GUI);

        Keyboard.press('l');
        Keyboard.releaseAll();
        Serial1.println(separator);
      }

      if(strcmp(separator, "up") == 0)
        Keyboard.write(KEY_UP_ARROW);
        if(strcmp(separator, "down") == 0)
          Keyboard.write(KEY_DOWN_ARROW);
        if(strcmp(separator, "left") == 0)
          Keyboard.write(KEY_LEFT_ARROW);
        if(strcmp(separator, "right") == 0)
          Keyboard.write(KEY_RIGHT_ARROW);
      }
      if(strcmp(cmd,"mouser") == 0) {
        if(strcmp(separator, "press") == 0) {
        Mouse.press(MOUSE_RIGHT);
        } else if(strcmp(separator, "release") == 0) {
        Mouse.release(MOUSE_RIGHT);
        } else if(strcmp(separator, "click") == 0) {
        Mouse.click(MOUSE_RIGHT);
        }
      }
      if(strcmp(cmd,"mousel") == 0) {
        if(strcmp(separator, "press") == 0) {
        Mouse.press(MOUSE_LEFT);
        } else if(strcmp(separator, "release") == 0) {
        Mouse.release(MOUSE_LEFT);
        } else if(strcmp(separator, "click") == 0) {
        Mouse.click(MOUSE_LEFT);
        }
      }
      if(strcmp(cmd,"mousemov") == 0) {
        char* keycmd = strchr(separator, ',');
        *keycmd = 0;
        int x = atoi(separator);
        int y = atoi(keycmd+1);

        Mouse.move(x, y);

        Serial1.print("mousemov: ");
        Serial1.print(x);
        Serial1.print(", ");
        Serial1.println(y);
      }
      if(strcmp(cmd,"stddelay") == 0) {
        stdDelay = atoi(separator);
        Serial1.print("stddelay: ");
        Serial1.println(stdDelay);
      }
      if(strcmp(cmd,"std") == 0) {
        if(strcmp(separator,"help") == 0) {
          Serial1.println(help);
        }
        if(strcmp(separator,"splash") == 0) {
          Serial1.println(splash);
        }
      }
      if(strcmp(cmd,"radio") == 0) {

      }
    }
    command = strtok(0, "&"); // Find the next command in input string
    delay(stdDelay);

    digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
