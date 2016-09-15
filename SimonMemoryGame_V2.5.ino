/* Created by Tim Jin
 * Simon Memory Game on Arduino
 */

#define LED_YELLOW   3
#define LED_ORANGE   5
#define LED_GREEN    7
#define LED_RED      9

#define BUTTON_YELLOW   2
#define BUTTON_ORANGE   4
#define BUTTON_GREEN    6
#define BUTTON_RED      8

#define SPEAKER   10

const int tones[] = {1915, 1700, 1519, 1432, 1200, 2700, 3500};

int lightSeq[6];      // The sequence of LED generated by the computer randomly
int rando = 0;        // Initialize random integer between 0 and 3
bool gameOn = true;   // Keep the game on
int currentLevel = 0; // This variable must be 1 in order to go to the next level
int speedFactor = 5;  // Affecting the speed of the LED

void setup() {
  // Initialize inputs :
  pinMode(BUTTON_YELLOW, INPUT);
  pinMode(BUTTON_ORANGE, INPUT);
  pinMode(BUTTON_GREEN, INPUT);
  pinMode(BUTTON_RED, INPUT);
  // Initialize outputs:
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_ORANGE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  gameStart();
  while(gameOn) {
    initiateLightSeq();
    showLightSeq();
    // Detech Button Push
    for (int i = 0; i < 6; i++) {
      while(true) {
        if (digitalRead(BUTTON_YELLOW) == HIGH) {
          buttonCheck(i,0);
          break;
        } else if (digitalRead(BUTTON_ORANGE) == HIGH) {
          buttonCheck(i,1);
          break;
        } else if (digitalRead(BUTTON_GREEN) == HIGH) {
          buttonCheck(i,2);
          break;
        } else if (digitalRead(BUTTON_RED) == HIGH) {
          buttonCheck(i,3);
          break;
        }
      }

      if(currentLevel == -1){
        gameOver();
        gameOn = false;
        break;
      } else {
        
      }
    }
    
    if(currentLevel == -1){
        gameOver();
        gameOn = false;
      } else if(currentLevel == 5) {
        gameWin();
        gameOn = false;
      } else {
        gameWin();
        currentLevel++;
        speedFactor = speedFactor * 2;
      }
  }
}

void playTone(int tones, int duration) {
  tone(SPEAKER, tones);
  delay(duration);
  noTone(SPEAKER);
}

void gameStart() {
  gameOn = true;
  currentLevel = 0;     // Reset the current level
  speedFactor = 5;      // Reset speed factor
  playTone(tones[4],500);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_YELLOW,HIGH);
    delay(100);
    digitalWrite(LED_YELLOW,LOW);
    digitalWrite(LED_ORANGE,HIGH);
    delay(100);
    digitalWrite(LED_ORANGE,LOW);
    digitalWrite(LED_GREEN,HIGH);
    delay(100);
    digitalWrite(LED_GREEN,LOW);
    digitalWrite(LED_RED,HIGH);
    delay(100);
    digitalWrite(LED_RED,LOW);
    delay(100);
  }
}

void gameWin() {
  playTone(tones[5],500);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_YELLOW,HIGH);
    digitalWrite(LED_GREEN,HIGH);
    delay(100);
    digitalWrite(LED_YELLOW,LOW);
    digitalWrite(LED_GREEN,LOW);
    digitalWrite(LED_ORANGE,HIGH);
    digitalWrite(LED_RED,HIGH);
    delay(100);
    digitalWrite(LED_ORANGE,LOW);
    digitalWrite(LED_RED,LOW);
    delay(100);
  }
}

void gameOver() {
  playTone(tones[6],500);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_YELLOW,HIGH);
    digitalWrite(LED_ORANGE,HIGH);
    digitalWrite(LED_GREEN,HIGH);
    digitalWrite(LED_RED,HIGH);
    delay(100);
    digitalWrite(LED_YELLOW,LOW);
    digitalWrite(LED_ORANGE,LOW);
    digitalWrite(LED_GREEN,LOW);
    digitalWrite(LED_RED,LOW);
    delay(100);
  }
}

void initiateLightSeq() {
  //initialize the LED sequence
  for(int i = 0; i < 6; i++) {
    lightSeq[i] = 0;          // Clear the LED sequence
    long rand_num = random(1,200);
    if (rand_num <= 50)
      rando=0;
    else if (rand_num>50 && rand_num<=100)
      rando=1;
    else if (rand_num>100 && rand_num<=150)
      rando=2;
    else if (rand_num<=200)
      rando=3;
    lightSeq[i] = rando;      // Save the random LED sequence
  }
}

void showLightSeq() {
  for (int i = 0; i < 6; i++){
    int currentPin = 0;     //initialize current pin
    int timeDelay = 5000 / speedFactor;
    currentPin = ((lightSeq[i] + 1) * 2) + 1;
    digitalWrite(currentPin, HIGH);
    playTone(tones[i],timeDelay);
    digitalWrite(currentPin, LOW);
    delay(timeDelay);
  }
}

void buttonCheck(int seqNum, int buttonNum) {
  if(lightSeq[seqNum] == buttonNum) {
    digitalWrite(((lightSeq[seqNum] + 1) * 2) + 1, HIGH);
    playTone(tones[seqNum],500);
    digitalWrite(((lightSeq[seqNum] + 1) * 2) + 1, LOW);
    delay(500);
  } else {
    currentLevel = -1;
  }
}