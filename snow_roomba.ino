/*     -----------------------------------------------------------
 *     |  Arduino Snoomba Code                                                          | 
 *     |  based on example code: CIRC-03 .: Spin Motor Spin :. (Transistor and Motor)   |
 *     -----------------------------------------------------------
 * 
 * The Arduinos pins are great for driving LEDs however if you hook 
 * up something that requires more power you will quickly break them.
 * To control bigger items we need the help of a transistor. 
 * Here we will use a transistor to control a small toy motor
 * 
 *
 */

//int motor1Pin = 9;
int motor2Pin = 10;
int trigPin = 5;
int echoPin = 6;
int ledPin = 13;

unsigned long startTime = 0;
bool isMoving = false;



/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the motors pin to be an output (turning the pin high (+5v) or low (ground) (-))
 * rather than an input (checking whether a pin is high or low)
 */
void setup()
{
 //pinMode(motor1Pin, OUTPUT); 
 pinMode(motor2Pin, OUTPUT); 

 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(ledPin, OUTPUT);

 Serial.begin(9600);
}


/*
 * loop() - this function will start after setup finishes and then repeat
 * we call a function called motorOnThenOff()
 */

void loop()                     // run over and over again
{
  roomba();
 //motorOnThenOff();
 //motorOnThenOffWithSpeed();
 //motorAcceleration();
}

void roomba() {
  long duration, distance;

  // Send a pulse from the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo and calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 30 && !isMoving) { // If an obstacle is detected within 30 cm
    moveForward();
    isMoving = true;
    startTime = millis();
  } if (isMoving) {
    if (millis() - startTime >= 4000) { // 4 seconds to travel "length of driveway"
    stopMotors();
    isMoving = false;
    blinkLeds(3);
    delay(5000);  // wait 5 seconds before sensor starts detecting again
    }
  }

  delay(100);
}

// Function to move motor forward
void moveForward() {
  // digitalWrite(motor1Pin, HIGH);
  // digitalWrite(motor2Pin, HIGH);
  //analogWrite(motor1Pin, 255);
  analogWrite(motor2Pin, 255);
}

// Function to stop both motors
void stopMotors() {
  // digitalWrite(motor1Pin, LOW);
  // digitalWrite(motor2Pin, LOW);
  //analogWrite(motor1Pin, 0);
  analogWrite(motor2Pin, 0);
}

// blinks the led n times
void blinkLeds(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500); 
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}

/*
 * motorOnThenOff() - turns motor on then off 
 * (notice this code is identical to the code we used for
 * the blinking LED)
 */
void motorOnThenOff(){
  int onTime = 2500;  //the number of milliseconds for the motor to turn on for
  int offTime = 1000; //the number of milliseconds for the motor to turn off for
  
  //digitalWrite(motor1Pin, HIGH); // turns the motor On
  digitalWrite(motor2Pin, LOW);
  delay(onTime);                // waits for onTime milliseconds
  //digitalWrite(motor1Pin, LOW);  // turns the motor Off
  digitalWrite(motor2Pin, HIGH);
  delay(offTime);               // waits for offTime milliseconds
}

/*
 * motorOnThenOffWithSpeed() - turns motor on then off but uses speed values as well 
 * (notice this code is identical to the code we used for
 * the blinking LED)
 */
void motorOnThenOffWithSpeed(){
  
  int onSpeed = 200;  // a number between 0 (stopped) and 255 (full speed) 
  int onTime = 2500;  //the number of milliseconds for the motor to turn on for
  
  int offSpeed = 50;  // a number between 0 (stopped) and 255 (full speed) 
  int offTime = 1000; //the number of milliseconds for the motor to turn off for
  
  //analogWrite(motor1Pin, onSpeed);   // turns the motor On
  delay(onTime);                    // waits for onTime milliseconds
  //analogWrite(motor1Pin, offSpeed);  // turns the motor Off
  delay(offTime);                   // waits for offTime milliseconds
}

/*
 * motorAcceleration() - accelerates the motor to full speed then
 * back down to zero
*/
void motorAcceleration(){
  int delayTime = 50; //milliseconds between each speed step
  
  //Accelerates the motor
  for(int i = 0; i < 256; i++){ //goes through each speed from 0 to 255
    //analogWrite(motor1Pin, i);   //sets the new speed
    delay(delayTime);           // waits for delayTime milliseconds
  }
  
  //Decelerates the motor
  for(int i = 255; i >= 0; i--){ //goes through each speed from 255 to 0
    //analogWrite(motor1Pin, i);   //sets the new speed
    delay(delayTime);           // waits for delayTime milliseconds
  }
}
