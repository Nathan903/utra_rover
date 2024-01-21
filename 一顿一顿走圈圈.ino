////////////// ports
int motor1pin1 = 3;//2;
int motor1pin2 = 5;//3;
int motor2pin1 = 6;//4;
int motor2pin2 = 11;//5;

const int leftSensorPin = A0;   // Analog pin for left sensor
const int rightSensorPin = A1;  // Analog pin for right sensor


int absoluteValue(int num) {
  if (num < 0) {return -num;} else { return num;}
}

void setup() {  
  Serial.begin(9600);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}


void left(int direction, int speed) {  
  // forward = 1, stop = 0, backward = -1
  if (direction == 0 ) { // Stop
    analogWrite(motor1pin1, 0);
    analogWrite(motor1pin2, 0);
  } else if (direction == 1) { // Forward
    analogWrite(motor1pin1, speed);
    analogWrite(motor1pin2, 0);
  } else {// Backward
    analogWrite(motor1pin1, 0);
    analogWrite(motor1pin2, speed);
  }
}

void right(int direction, int speed) {  
  // forward = 1, stop = 0, backward = -1
  if (direction == 0) {// Stop
    analogWrite(motor2pin1, 0);
    analogWrite(motor2pin2, 0);
  } else if  (direction == 1) { // Forward
    analogWrite(motor2pin1, speed);
    analogWrite(motor2pin2, 0);
  } else { // Backward
    analogWrite(motor2pin1, 0);
    analogWrite(motor2pin2, speed);
  }
}

int SPEED=71; // speed for going forward / backward
int TURNSPEED=77; // speed during turning
int DIRECTION=1; // make -1 to make car go in reverse
int THRES = 111; // threshold for determining if the sensor is seeing black
int ERROR_THRES = 66; // threshold to determine if error (diff between left and right sensor) is large enough to warrant a turn
float PERCENTAGE_OF_IDLE = 0.95; // percentage of the loops (not time) which the car is stopped.

long counter=0; // 
const long counter_total =100;
void loop() {
  while (0) { // make 1 for debug mode. 0 means debug mode off
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  }    


  // loop based pause
  counter%=counter_total; counter++; counter%=counter_total;
  if ((counter)<counter_total*PERCENTAGE_OF_IDLE){ 
    left(0,TURNSPEED); right(0,TURNSPEED);  // stop
    Serial.println(counter); // unnecessary print, but dont remove because it is important for the timing delay 
    return;
  }


// TESTTURNING
  if(counter==counter_total-1){
    int turnamount = 0;
    while(! (absoluteValue(rightSensorValue)>THRES) && !(absoluteValue(rightSensorValue)>THRES)  ){
      turnamount+=2;
      //try right
      for (int i = 0; i<=turnamount; i++{
        left(DIRECTION,TURNSPEED);
        right(-DIRECTION,TURNSPEED);        
      }
      if((absoluteValue(rightSensorValue)>THRES) && !(absoluteValue(leftSensorValue)>THRES) ){ 
        // keep turning
        while(! ((absoluteValue(rightSensorValue)<THRES) && (absoluteValue(leftSensorValue)<THRES))){
          left(DIRECTION,TURNSPEED);
          right(-DIRECTION,TURNSPEED);        
        }
        break; 
      }
      for (int i = 0; i<=2*turnamount; i++{
        left(DIRECTION,TURNSPEED);
        right(-DIRECTION,TURNSPEED);        
      }
      if(!(absoluteValue(rightSensorValue)>THRES) && (absoluteValue(leftSensorValue)>THRES) ){ 
        while(! ((absoluteValue(rightSensorValue)<THRES) && (absoluteValue(leftSensorValue)<THRES))){
          left(-DIRECTION,TURNSPEED);
          right(DIRECTION,TURNSPEED);        
        }
        break; 
      }
    }
  }
    ///////////////////////////////////

  int leftSensorValue = analogRead(leftSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);
  int error = rightSensorValue - leftSensorValue;
  if (absoluteValue(rightSensorValue)>THRES && absoluteValue(leftSensorValue)>THRES){
    Serial.print("BACKWARD=====================================");
    unsigned long startTime = millis(); 
    while (millis() - startTime < 1000) {
      left(-DIRECTION,SPEED*2/3);
      right(-DIRECTION,SPEED*2/3);
    }
  }
  else if(absoluteValue(error)<ERROR_THRES)   { // 
    Serial.print("FORWARD");
    left(DIRECTION,SPEED);
    right(DIRECTION,SPEED);
  }
  else if (DIRECTION*error < 0) {
    Serial.print("LEFT   ");
    left(DIRECTION,TURNSPEED);
    right(-DIRECTION,TURNSPEED);
  }
  else {
    Serial.print("RIGHT  ");
    left(-DIRECTION,TURNSPEED);
    right(DIRECTION,TURNSPEED);
  } 

  Serial.print("\t error: ");
  Serial.print(error); // Print the right sensor value to the serial monitor
  Serial.print("\t L: ");
  Serial.print(rightSensorValue); // Print the right sensor value to the serial monitor
  Serial.print("\t R: ");
  Serial.println(leftSensorValue); // Print the right sensor value to the serial monitor


}
