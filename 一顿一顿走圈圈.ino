int motor1pin1 = 3;//2;
int motor1pin2 = 5;//3;

int motor2pin1 = 6;//4;
int motor2pin2 = 11;//5;

// 234 
const int leftSensorPin = A0;   // Analog pin for left sensor
const int rightSensorPin = A1;  // Analog pin for right sensor
int absoluteValue(int num) {
  if (num < 0) {
    return -num;
  } else {
    return num;
  }
}
void setup() {  Serial.begin(9600); // Start the serial communication

  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}
int min_pulse_time=0;
int left_counter=0;
void left(int direction, int speed) {  // forward = 1, stop = 0, backward = -1
if (direction == 0 ) {
    // Stop
    analogWrite(motor1pin1, 0);
    analogWrite(motor1pin2, 0);
  } else if (direction == 1) {
    // Forward
    analogWrite(motor1pin1, speed);
    analogWrite(motor1pin2, 0);

  } else {
    // Backward
    analogWrite(motor1pin1, 0);
    analogWrite(motor1pin2, speed);
  }
  left_counter++;
}
int right_counter=0;
void right(int direction, int speed) {  // forward = 1, stop = 0, backward = -1
  
  // Ensure the speed is within the valid range (0 to 255)
  speed = constrain(speed, 0, 255);

  // Map the speed value to a duty cycle (0 to 100%)
  int dutyCycle = map(speed, 0, 255, 0, 100);

   if (direction == 0) {
    // Stop
    analogWrite(motor2pin1, 0);
    analogWrite(motor2pin2, 0);
   } else if  (direction == 1) {
    // Forward
    analogWrite(motor2pin1, speed);
    analogWrite(motor2pin2, 0);
  } else {
    // Backward
    analogWrite(motor2pin1, 0);
    analogWrite(motor2pin2, speed);
  }
  right_counter++;
}
int SPEED=71;
int TURNSPEED=77;
int DIRECTION=1;
int THRES = 111;
long counter=0;
const long counter_total =100;
void loop() {
    while (0) {
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  }    
  counter%=counter_total;
  counter++;
  counter%=counter_total;
  if ((counter)<counter_total*0.95){
        left(0,TURNSPEED);
    right(0,TURNSPEED);

    Serial.println(counter);
    return;
  }
  int leftSensorValue = analogRead(leftSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);
  int error = rightSensorValue - leftSensorValue;
  if (absoluteValue(rightSensorValue)>THRES && absoluteValue(leftSensorValue)>THRES){
  unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 1000) {
   
    left(-DIRECTION,SPEED*2/3);
    right(-DIRECTION,SPEED*2/3);
    }

    Serial.print("\n\n\n\n\n\n\nBACK                  =====================================\n\n");

  }
  else if(absoluteValue(error)<66)   {
    left(DIRECTION,SPEED);
    right(DIRECTION,SPEED);
    Serial.print("FORWARD");
  }
  else if (DIRECTION*error < 0) {
    left(DIRECTION,TURNSPEED);
    right(-DIRECTION,TURNSPEED);
    Serial.print("LEFT   ");
  }
  else {
    left(-DIRECTION,TURNSPEED);
    right(DIRECTION,TURNSPEED);
    Serial.print("RIGHT  ");
  } 

    Serial.print("\t error: ");
  Serial.print(error); // Print the right sensor value to the serial monitor

    Serial.print("\t L: ");
  Serial.print(rightSensorValue); // Print the right sensor value to the serial monitor
    Serial.print("\t R: ");
  Serial.println(leftSensorValue); // Print the right sensor value to the serial monitor


}
