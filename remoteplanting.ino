#include <Servo.h>

int PINLEFT = 8;
int PINRIGHT = 4;
int PINFRONT = 12;
int PINBACK = 2;

int SERVOX = 9;
int servoXPosition = 0;
Servo servoX;

int SERVOY = 10;
int servoYPosition = 0;
Servo servoY;

int SERVOZ = 11;
int servoZPosition = 0;
Servo servoZ;

void setup() 
{
  pinMode(PINLEFT, OUTPUT);
  pinMode(PINRIGHT, OUTPUT);
  pinMode(PINFRONT, OUTPUT);
  pinMode(PINBACK, OUTPUT);
  Serial.begin(115200);

  servoX.attach(SERVOX);
  servoY.attach(SERVOY);
  servoZ.attach(SERVOZ);
  servoX.write(31);
  servoY.write(31);
  servoZ.write(31);
}

void loop() 
{
 int availableBytes = Serial.available(); 
  if (availableBytes > 0){
    for (int m=0;m<availableBytes;m++)
    { 
      byte incoming = Serial.read();
      Serial.println(incoming);
      move(incoming);         
    }

  }
  //move(incomingByte[2]);    
}

void resetLed()
{
   digitalWrite(PINLEFT, LOW);
   digitalWrite(PINRIGHT, LOW);
   digitalWrite(PINFRONT, LOW);
   digitalWrite(PINBACK, LOW);  
}

void move(byte n)
{    
  switch(n)
  {
    case 1:
      digitalWrite(PINLEFT, LOW);
      digitalWrite(PINRIGHT, LOW);
      moveServoX(31);
      moveServoY(31);
      moveServoZ(31);
      Serial.println("Case 1");
      break;
    case 2:
      digitalWrite(PINLEFT, HIGH);
      digitalWrite(PINRIGHT, LOW);
      moveServoX(42);
      moveServoY(23);
      moveServoZ(57);
      Serial.println("Case 2");
      break;
    case 3:
      digitalWrite(PINLEFT, LOW);
      digitalWrite(PINRIGHT, HIGH);
      moveServoX(42);
      moveServoY(57);
      moveServoZ(23);
      Serial.println("Case 3");
      break;
    case 7:
      digitalWrite(PINFRONT, LOW);
      digitalWrite(PINBACK, LOW);
      Serial.println("Case 7");
      break;
    case 8:
      digitalWrite(PINFRONT, HIGH);
      digitalWrite(PINBACK, LOW);
      Serial.println("Case 8");
      break;
    case 9:
      digitalWrite(PINFRONT, LOW);
      digitalWrite(PINBACK, HIGH);
      Serial.println("Case 9");    
       break;
  }
}

void moveServoX(int m)
{
  if (m == servoXPosition)
  {
    return;
  }

  servoX.write(m);
  servoXPosition = m;
}

void moveServoY(int m)
{
  if (m == servoYPosition)
  {
    return;
  }

  servoY.write(m); 
  servoYPosition = m;
}

void moveServoZ(int m)
{
  if (m == servoZPosition)
  {
    return;
  }

  servoZ.write(m); 
  servoZPosition = m;
}

