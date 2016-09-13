// Constants
const int button1 = 2;          // 1st button controls Yellow LED 
const int button2 = 4;          // 2nd button controls Orange LED
const int button3 = 6;          // 3rd button controls Green LED
const int button4 = 8;          // 4th button controls Red LED
const int led1 = 3;             // Yellow LED
const int led2 = 5;             // Orange LED
const int led3 = 7;             // Green LED
const int led4 = 9;             // Red LED

//Variables
int buttonState[] = {0,0,0,0};
int buttonSeq[] = {0,0,0,0,0,0}
int lightState[] = {0,0,0,0};
int lightSeq[] = {0,0,0,0,0,0}
int buttonchange = 0; 
int rando = 0; //initialize random integer for loopgame_on. Will be from 1-4 later.
int currentPin = 0; //initialize current pin
int right = 0; //This variable must be 1 in order to go to the next level
int leddelay = 200; //Initializing time for LED. This will decrease as the level increases

void setup() {
  // initialize inputs :
  randomSeed(analogRead(0));
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  // initialize outputs:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  //initialize serial communication for debugging:
  Serial.begin(9600);
}

void loop() {
  initiate();
  gameStart();
  //shows the user the current sequence
  for (int i = 0; i < 6; i++){
    currentPin = ((lightSeq[i] + 1) * 2) + 1
    digitalWrite(currentPin, HIGH);
    delay(2000);
    digitalWrite(currentPin, LOW);
    delay(2000);
  }

  // i is the current position in the sequence
  for (int i = 0; i < 6; i++){
    //detect button push
    while (buttonchange == 0){
      for (int j = 0; j < 4; j++){ 
        buttonState[i] = digitalRead((i + 1) * 2);
        buttonchange = buttonchange + buttonState[i];
      }
    }
    for (int j = 0; j < 4; j++){
      if (buttonState[j] == HIGH) {
        buttonSeq[i] = j;
      }
    }
    if (buttonSeq[i] != lightSeq[i]){
      gameOver();
      break;
    } else {
      digitalWrite(((buttonSeq[i] + 1) * 2) + 1, HIGH);
      delay(500);
      digitalWrite(((buttonSeq[i] + 1) * 2) + 1, LOW);
      delay(500);
    }
  }
  gameWin();
}

void initiate(){
  //initialize the game
  for(int i = 0; i < 6; i++) {
    buttonSeq[i] = 0;
    lightSeq[i] = 0;
    long rand_num = random(1,200);
    if (rand_num <= 50)
      rando=0;
    else if (rand_num>50 && rand_num<=100)
      rando=1;
    else if (rand_num>100 && rand_num<=150)
      rando=2;
    else if (rand_num<=200)
      rando=3;
    //saves a random number in our n_array
    lightSeq[i] = rando;
  }
  //clear the variances
  currentPin = 0;
}

void gameStart() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(3,HIGH);
    delay(500);
    digitalWrite(3,LOW);
    digitalWrite(5,HIGH);
    delay(500);
    digitalWrite(5,LOW);
    digitalWrite(7,HIGH);
    delay(500);
    digitalWrite(7,LOW);
    digitalWrite(9,HIGH);
    delay(500);
    digitalWrite(9,LOW);
    delay(500);
  }
}

void gameWin() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(3,HIGH);
    digitalWrite(7,HIGH);
    delay(500);
    digitalWrite(3,LOW);
    digitalWrite(7,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(9,HIGH);
    delay(500);
    digitalWrite(5,LOW);
    digitalWrite(9,LOW);
    delay(500);
  }
}

void gameOver() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(3,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(9,HIGH);
    delay(500);
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    digitalWrite(7,LOW);
    digitalWrite(9,LOW);
    delay(500);
  }
}

