#include <Keyboard.h>

void setup() {
  Serial1.begin(115200);
  while (!Serial1) 
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // initialize control over the keyboard:
  Keyboard.begin();
  Serial1.println("Starting\n");
  usage();
}

void usage() {
    Serial1.println("Select mode:");
    Serial1.println("s - single: enter a single key to be sent");
    Serial1.println("b - loop: loop over the function keys + 0x00-0xff combos");
    Serial1.println("k - loop: loop over all single key presses");
  
}

void brute_special_combos() {
  Serial1.println("Starting brute force loop of special key combos. Press SPACE to stop");
   //roll through the modifier keys with every combo
  for(int fkey=0x80;fkey < 0xFB;fkey++){
        for(int skey=0x00;skey<256;skey++){
            delay(1000);
            Serial1.println("Trying: " + String(fkey) + " + " + String(skey));
     Keyboard.press(fkey);
    Keyboard.press(skey);
            delay(100);
    Keyboard.releaseAll();
      // wait for new window to open:
            delay(500);
            int check = Serial1.read();
            if(check == 32){
              Serial1.println("Aborting run");
              usage();
              return;
            }
      }

 }
  
}

void brute_singles() {
  Serial1.println("Starting brute force loop of single keys. Press SPACE to stop");
   //roll through the modifier keys with every combo
        for(int skey=0x00;skey<256;skey++){
            delay(1000);
            Serial1.println("Trying: " + String(skey));
     // Keyboard.press('');
    Keyboard.press(skey);
            delay(100);
    Keyboard.releaseAll();
      // wait for new window to open:
            delay(500);
            int check = Serial1.read();
            if(check == 32){
              Serial1.println("Aborting run");
              usage();
              return;
            }
      }

 }
  

void single() {
  Serial1.println("Starting single mode.");
  Serial1.println("Every key typed will be send to the target. ESC ESC ESC ESC to stop.");
  int stop_sum = 0;
  int prev_key = 0;
  while(true){
    int key = -1;
    key = Serial1.read();
    if(key != -1) {
      Serial1.println("Sending: " + String(key));

      if(key == 27 && prev_key == 27){
        stop_sum += 27;
        if(stop_sum == 81){
          Serial1.println("Aborting run");
          usage();
          return;
        }
       
      }
      Keyboard.write(key);
      prev_key = key;
    }
   // delay(1000);
   // Serial1.println(String(key));
  }
  
  
}


void loop() {
  int choice = -1;
  while(choice == -1){
    choice = Serial1.read();
    switch (char(choice)) {
      case 's':
          single();
          break;
      case 'b':
          brute_special_combos();
          break;
      case 'k':
          brute_singles();
          break;
      default:
          break;
    }
  }

  
 
}
