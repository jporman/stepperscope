// Define pin connections & motor's steps per revolution
const int dirPin = 5;
const int stepPin = 2;
const int enablePin = 8;
const int stepsPerRevolution = 3200;
double degAngle = 0;
double hourAngleHr = 0;
double hourAngleMin = 0; 
float hourAngleSec = 0;
String hourAngle = "";

String degreesToHours(double degreeAngle)
{
    hourAngleHr = degreeAngle / (15*10^12); // in degrees x10^12
    hourAngleMin = (degreeAngle - (hourAngleHr*(15*10^12)))/(25*10^10); // in degrees x10^12
    hourAngleSec = (degreeAngle - hourAngleHr*(15*10^12) - hourAngleMin/60*(15*10^12))*(3600/(15*10^12)); // in degrees x10^12

    //add hours
    if (hourAngleHr < 10){
      hourAngle = "0" + String(hourAngleHr);
    } else { hourAngle = hourAngle + String(hourAngleHr);
    }
    //add minutes
    if (hourAngleMin < 10){
      hourAngle = hourAngle + ":0" + String(hourAngleMin);
    } else { hourAngle = hourAngle + String(hourAngleMin);
    }
    //add seconds
    if (hourAngleSec < 10){
      hourAngle = hourAngle + ":0" + String(hourAngleSec);
    } else {
      hourAngle = hourAngle + String(hourAngleSec, 5);
    }
   return hourAngle;
}


void setup()
{
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT); digitalWrite(enablePin, LOW);
  Serial.begin(9600);
}
void loop()
{
  // Set motor direction clockwise (+)
  digitalWrite(dirPin, HIGH);

  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    //turn motor on and spin clockwise for 2000 microseconds
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    //turn motor off for 2000 microseconds
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
    
    //increment degree and convert to incremental hour angle for Azimuth axis
    if (dirPin == HIGH) {
      degAngle += 312500; //increment in degrees x10^12;
    } else if (dirPin == LOW) {
      degAngle -= 312500;
    }
    String hourAngle = degreesToHours(degAngle);
    Serial.println(hourAngle);
  }
  
  delay(1000); // Wait a second
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);

  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);

    //increment degree and convert to incremental hour angle for Azimuth axis
    if (dirPin == HIGH) {
      degAngle += 312500; //increment in degrees x10^12;
    } else if (dirPin == LOW) {
      degAngle -= 312500;
    }
    String hourAngle = degreesToHours(degAngle);
    Serial.println(hourAngle);
  }
  delay(1000); // Wait a second
}
