void setup() {
  Serial.begin(9600);                   //initialize serial communication at 9600 bits per second:
  pinMode(13, OUTPUT);                  //Use pin 13 as an output to control left motor(wheel)
  pinMode(14, OUTPUT);                  //Use pin 14 as an output to control right motor(wheel)
}
void checkSensor(int sensorNum) {
  if(analogRead(sensorNum)>400){        //400 is just a imaginary number, it is used to show the closeness between the car and the barrier. Cant't get the accurate number without testing the sensor
    return 1;
  }else{
    return 0;
  }
}
void loop() {
  if(checkSensor(0) == 1)               //check the left sensor, analog pin 0 is connected to the left sensor
  {
    digitalWrite(14, LOW);              //turn the right motor off so the car will turn right
    delay(2000);                        //wait for 2 second
    digitalWrite(14, HIGH);             //turn the right motor on so the car will move forward
    delay(1000);                        //wait for a second to remain stability
  }else if(checkSensor(1) == 1)         //check the right sensor, analog pin 1 is connected to the right sensor
  {
    digitalWrite(13, LOW);              //turn the left motor off so the car will turn right
    delay(2000);                        //wait for 2 second
    digitalWrite(13, HIGH);             //turn the left motor on so the car will move forward
    delay(1000);                        //wait for a second to remain stability
  }
}

