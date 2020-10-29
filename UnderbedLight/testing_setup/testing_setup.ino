const int lightSensorPin = A0; // analog read from A0
int lightSensorValue;

const int motionSensorPin = 2; // digital read from D2
int motionSensorValue;

const int ledPin = 13; // digital output from D13

void setup() {
  // Send debug info through Serial
  Serial.begin(9600);
  Serial.println("Setup");
  // Input pins
  pinMode(lightSensorPin, INPUT);
  pinMode(motionSensorPin, INPUT);
  // Output pins
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightSensorValue = analogRead(lightSensorPin);
  Serial.print("Light sensor reading = ");
  Serial.println(lightSensorValue);

  int motionSensorValue = digitalRead(motionSensorPin);
  Serial.print("Motion sensor reading = ");
  Serial.println(motionSensorValue);

  if(motionSensorValue == HIGH) {
    turnLightOn();
  } else {
    turnLightOff();
  }
  
  delay(1000);
}

void turnLightOn() {
  digitalWrite(ledPin, HIGH);
}

void turnLightOff() {
  digitalWrite(ledPin, LOW);
}
