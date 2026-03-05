  PROGRAM:
#include <Wire.h>
#include <LiquidCrystal_I2C.h> #include <Servo.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// Constants for IR sensor and LED
const int irSensorPin = 2; // IR sensor output pin connected to digital pin 2 const int irLedPin = 13; // On-board LED connected to digital pin 13
// Constants for PIR sensor and LED

const int pirPin = 3;	// PIR motion sensor pin const int pirLedPin = 12; // LED pin for PIR sensor

// Servo object Servo myservo;

// Initialize the LCD using the address 0x27 (adjust according to your module) LiquidCrystal_I2C lcd(0x27, 16, 2);

// Constants for flame and gas sensors
const int flameSensorPin = 5; // Digital pin for flame sensor const int gasSensorPin = A0; // Analog pin for gas sensor const int buzzerPin = 8;		// Pin connected to the buzzer const int ledPin = 6;	// Pin connected to the LED

// Initialize DHT sensor
#define DHTPIN 4	// Digital pin connected to the DHT sensor #define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);


// Define software serial pins for Bluetooth SoftwareSerial BTSerial(11, 1); // TX, RX

bool motionDetected = false; void setup() {

// Initialize serial communication Serial.begin(9600);

// Initialize IR sensor pin as input pinMode(irSensorPin, INPUT);

// Initialize PIR sensor pin as input pinMode(pirPin, INPUT);

// Initialize LEDs pinMode(irLedPin, OUTPUT); pinMode(pirLedPin, OUTPUT);

// Initialize Servo motor myservo.attach(9);

// Initialize LCD lcd.begin(16, 2); lcd.backlight();

// Initialize DHT sensor dht.begin();

// Set pin modes for flame and gas sensors pinMode(flameSensorPin, INPUT); pinMode(gasSensorPin, INPUT);

pinMode(buzzerPin, OUTPUT); pinMode(ledPin, OUTPUT);

// Initialize Bluetooth serial communication BTSerial.begin(9600);
pinMode(7, OUTPUT);

// Print initial message on LCD lcd.clear();
lcd.setCursor(0, 0); lcd.print("SYSTEM INITIALIZED");

// Print initial message to Serial Monitor Serial.println("SYSTEM INITIALIZED");
}

void loop() {
// Read from IR sensor
int irSensorValue = digitalRead(irSensorPin);


// Read from PIR sensor motionDetected = digitalRead(pirPin);

// Read temperature and humidity from DHT sensor float humidity = dht.readHumidity();
float temperatureC = dht.readTemperature();	// Read temperature in Celsius

float temperatureF = dht.readTemperature(true); // Read temperature in Fahrenheit


// IR sensor actions
if (irSensorValue == LOW) { digitalWrite(irLedPin, HIGH); // Turn on IR LED
myservo.write(90); // Move servo to 90 degrees
} else {
digitalWrite(irLedPin, LOW); // Turn off IR LED myservo.write(0); // Move servo to 0 degrees
}

// PIR sensor actions
if (motionDetected == HIGH) { lcd.clear();
lcd.setCursor(0, 0); lcd.print("MOTION DETECTED");
lcd.setCursor(0, 1); lcd.print(" YES ");
delay(1000); // Display motion detection for 1 second lcd.clear();
lcd.setCursor(0, 0); lcd.print("T: "); lcd.print(temperatureC); lcd.print("C "); lcd.print(temperatureF); lcd.print("F ");

lcd.setCursor(0, 1); lcd.print("H: "); lcd.print(humidity); lcd.print("%	");

digitalWrite(pirLedPin, HIGH); // Turn on PIR LED delay(2000); // Keep PIR LED on for 2 seconds digitalWrite(pirLedPin, LOW); // Turn off PIR LED
} else { lcd.clear();
lcd.setCursor(0, 0); lcd.print("MOTION DETECTED");
lcd.setCursor(0, 1); lcd.print("	NO ");
digitalWrite(pirLedPin, LOW); // Turn off PIR LED immediately if no motion
}

// Flame sensor actions
int flameDetected = digitalRead(flameSensorPin); if (flameDetected == LOW) {
lcd.clear(); lcd.setCursor(0, 0);
lcd.print("Flame detection:"); lcd.setCursor(0, 1); lcd.print(" YES!! ");
digitalWrite(buzzerPin, HIGH); // Sound the buzzer

digitalWrite(ledPin, HIGH);	// Turn on the LED
// Print message to Serial Monitor Serial.println("Flame detected! Take action.");
// Send message to Bluetooth app
BTSerial.println("Flame detected! Take action."); // Send flame detection status to Bluetooth

} else { lcd.clear();
lcd.setCursor(0, 0); lcd.print("Flame detection:"); lcd.setCursor(0, 1); lcd.print(" NO!! ");
digitalWrite(buzzerPin, LOW); // Silence the buzzer digitalWrite(ledPin, LOW);	// Turn off the LED
}

// Gas sensor actions
int gasValue = analogRead(gasSensorPin);
int gasThreshold = 800; // Set your threshold value for gas detection if (gasValue >= gasThreshold) {
digitalWrite(ledPin, HIGH); // Turn on LED digitalWrite(buzzerPin, HIGH); // Sound the buzzer
// Print message to Serial Monitor Serial.println("GAS detected! Take action.");
BTSerial.println("GAS detected! Take action."); // Send gas detection status to Bluetooth

} else {
digitalWrite(ledPin, LOW); // Turn off LED digitalWrite(buzzerPin, LOW); // Silence the buzzer
}

// Bluetooth module command processing if (BTSerial.available()) {
char command = BTSerial.read();


// Process the received command switch (command) {
case 'H':
digitalWrite(7, HIGH); // Turn on an external LED (example) break;
case 'L':
digitalWrite(7, LOW); // Turn off an external LED (example) break;
// Add more cases for additional commands as needed
}
}

// Delay for a short period to manage loop timing
delay(100); // Adjust this delay as needed, or use millis() for non-blocking timing
}