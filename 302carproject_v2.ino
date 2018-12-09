//Motor pins
//Motor pins. 1 is right motor, 2 is left motor
const int motor1a = 8;
const int motor1b = 9;

const int motor2a = 10;
const int motor2b = 11;

//Sensor pins
const int photoLeft = A0;
const int photoRight = A1;
const int photoCenter = A2;
const int irLeft = A3;
const int irRight = A4;
const int irFront= A5;

//input values

const int photoThresRight= 325;
const int photoThresLeft= 375;


const int irClose= 400; //1.5 V threshold

//Initialization function
void setup() {
  //Put each pin in the correct mode. 
  //Motor control pins are output

  pinMode(motor1a, OUTPUT); 
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  pinMode(photoLeft, INPUT);
  pinMode(photoRight, INPUT);
  pinMode(irFront, INPUT);
  pinMode(irRight, INPUT);
  pinMode(irLeft, INPUT);

   Serial.begin(9600);

}

void serialEvent(){
//statements
  Serial.println(analogRead(irFront));
  Serial.println(analogRead(photoRight));
  Serial.println(analogRead(photoLeft));
  delay(500);
}
  
//Infinite loop called automatically by the Arduino board
void loop(){
  serialEvent();
 if (analogRead(irFront) >= irClose) {
    Serial.println("TOO CLOSE IR");
     halt();
     delay(50);
   }else{
      if((analogRead(photoRight) > photoThresRight)&& (analogRead(photoLeft) > photoThresLeft)){
        Serial.println("SHOULD GO FORWARD");
        forward();
        delay(50);
        halt();
      }
    
//    if((analogRead(photoLeft)< photoThresLeft)&&(analogRead(photoRight)< photoThresRight)){
//      Serial.println("SHOULD GO BACKWARDS");
//      backward();
//      delay(50);
//      halt();
//     
//    }
     if((analogRead(photoLeft)> photoThresLeft)&&(analogRead(photoRight)<photoThresRight)){
      Serial.println("SHOULD TURN LEFT");
       turnRight();
       delay(50);
       halt();
   
    }
    
    if ((analogRead(photoRight) > photoThresRight)&& (analogRead(photoLeft) < photoThresLeft)){
      Serial.println("SHOULD TURN RIGHT");
     turnLeft();
     delay(50);
     halt();
    }
    
    /*
    if (analogRead(irRight)>= irClose){
      turnRight();
      delay(100);
      halt();
    }
    if (analogRead(irLeft)>=irClose){
      turnLeft();
      delay(100);
      halt();
    } */
    
  
  }
  delay(500);
}

void turnLeft()
{
  //left motor backwards, right motor forward

  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);
}

void turnRight(){
  //left motor forward, right motor backwards

  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, HIGH);
}

void halt(){
  //stops motors by turning enables for both motors off
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, LOW);
}

void backward() {
  //both motors forward

  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);
}

void forward() {
  //both motors back

  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, HIGH);
  
  
}
