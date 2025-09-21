// Define which pins on the Arduino are connected to the ultrasonic sensor
#define TRIG_PIN 17   // Trigger pin sends the signal
#define ECHO_PIN 18   // Echo pin receives the signal

void setup() {
  // Start the Serial Monitor at 115200 bits per second (baud rate)
  Serial.begin(115200);
  Serial.println("Program is starting!");

  // Set up the pin modes
  pinMode(TRIG_PIN, OUTPUT); // The trigger pin will send a pulse, so it's an output
  pinMode(ECHO_PIN, INPUT);  // The echo pin receives a pulse, so it's an input
}

void loop() {
  // Call the function to read the distance from the ultrasonic sensor
  int currentDistanceCm = readUltrasonicDistance();

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  if (currentDistanceCm > 0) {
    Serial.print(currentDistanceCm);
    Serial.println(" cm");
  } else {
    // If the reading is 0 or invalid, print "Out of range"
    Serial.println("Out of range");
  }

  // Wait for half a second before the next reading
  delay(500);
}

// Function to read distance from the ultrasonic sensor
int readUltrasonicDistance() {
  // Send a 10 microsecond HIGH pulse to trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);              // Short delay before starting
  digitalWrite(TRIG_PIN, HIGH);      // Start the trigger pulse
  delayMicroseconds(10);             // Pulse lasts for 10 microseconds
  digitalWrite(TRIG_PIN, LOW);       // End the pulse

  // Measure how long the echo pin stays HIGH (in microseconds)
  // This indicates how long it took for the ultrasonic pulse to return
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout after 30,000 µs (30 ms)

  // Calculate distance based on the speed of sound (343 m/s or 0.0343 cm/µs)
  // Divide by 2 because the sound travels to the object and back
  int distanceCm = 0.0343 * duration / 2;

  return distanceCm;
}
