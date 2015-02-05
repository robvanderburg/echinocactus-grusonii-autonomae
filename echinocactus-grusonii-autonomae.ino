#include <Pushbutton.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>

Pushbutton button(ZUMO_BUTTON);
ZumoBuzzer buzzer;
ZumoMotors motors;

const int lightSensorPin = A4;

int lightSensorReadingOne = 0;
int lightSensorReadingTwo = 0;
int lightSensorReadingThree = 0;
int lightSensorReadingFour = 0;
int lightSensorThreshold = 0;


// Setup
void setup()
{
  // Assign pin 13 as an output pin
  pinMode(13, OUTPUT);
  
  // Wait for the button to be pressed
  button.waitForButton();
  
  // Play a welcome tone
  buzzer.play(">g32>>c32");
  
  // Wait for 1 second
  delay(1000);
}


// Loop
void loop()
{
  // Perform 4 light sensor readings in different directions
  lightSensorReadingOne = analogRead(lightSensorPin);
  rotateClockwise();
  lightSensorReadingTwo = analogRead(lightSensorPin);
  rotateClockwise();
  lightSensorReadingThree = analogRead(lightSensorPin);
  rotateClockwise();
  lightSensorReadingFour = analogRead(lightSensorPin);
  rotateClockwise();
  
  // Check which light sensor reading is the highest and rotate towards that direction
  if (lightSensorReadingTwo > lightSensorReadingOne && lightSensorReadingThree && lightSensorReadingFour) {
    rotateClockwise();
  }
  
  else if (lightSensorReadingThree > lightSensorReadingOne && lightSensorReadingTwo && lightSensorReadingFour) {
    rotateClockwise();
    rotateClockwise();
  }
  
  else {
    rotateClockwise();
    rotateClockwise();
    rotateClockwise();
  }
  
  // Set a threshold using the current light sensor reading
  lightSensorThreshold = analogRead(lightSensorPin) - 10;
  
  // Go forward while the light sensor reading is higher than the threshold
  while (lightSensorThreshold < analogRead(lightSensorPin)) {
    motors.setLeftSpeed(100);
    motors.setRightSpeed(100);
    
    // Update the threshold if the light sensor reading is significantly higher than the threshold and turn on LED as an indicator
    if (lightSensorThreshold + 20 < analogRead(lightSensorPin)) {
      digitalWrite(13, HIGH);
      lightSensorThreshold = analogRead(lightSensorPin) - 10;
    }
    
    // Turn of the LED if the threshold wasn't updated
    else {
      digitalWrite(13, LOW);
    }
  }
  
  // Stop
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  
  // Wait for 30 seconds
  delay(30000);
}

// Rotate clockwise
void rotateClockwise() {
  motors.setLeftSpeed(200);
  motors.setRightSpeed(-200);
  delay(500);
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}
