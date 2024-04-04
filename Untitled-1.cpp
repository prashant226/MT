
#include <ESP8266WiFi.h>

// WiFi credentials
// #include <ESP8266WiFi.h>

// WiFi credentials
char ssid[] = "Geek";//Enter your WIFI SSID
char pass[] = "itsGeek226";//Enter your WIFI password
// Gas sensor thresholds (you may need to adjust these values depending on your sensors)
#define GAS_THRESHOLD1 500
#define GAS_THRESHOLD2 600

// Pins
#define GAS_SENSOR_PIN1 D0
#define GAS_SENSOR_PIN2 A1
#define LED_PIN D5
#define BUZZER1_PIN D3
#define BUZZER2_PIN D4
#define FAN_PIN D6



// Initialize gas sensor readings
int gasValue1 = 0;
int gasValue2 = 0;

// Function to control the devices
void activateAlarm() {
  digitalWrite(BUZZER1_PIN, HIGH);
  digitalWrite(BUZZER2_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(FAN_PIN, HIGH);
}

void deactivateAlarm() {
  digitalWrite(BUZZER1_PIN, LOW);
  digitalWrite(BUZZER2_PIN, LOW);
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(FAN_PIN, LOW);
}

void setup() {
  // Initialize the pins
  pinMode(GAS_SENSOR_PIN1, INPUT);
  pinMode(GAS_SENSOR_PIN2, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Initially, turn off the devices
  deactivateAlarm();

  // Setup Serial Monitor (optional)
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read the gas sensor values
  gasValue1 = digitalRead(GAS_SENSOR_PIN1); // Assuming D0 is connected to a digital output gas sensor
  gasValue2 = analogRead(GAS_SENSOR_PIN2);

  // You can print the gas values for debugging (optional)
  Serial.print("Gas Value 1: ");
  Serial.print(gasValue1);
  Serial.print(", Gas Value 2: ");
  Serial.println(gasValue2);

  // Check if gas value from either sensor exceeds the thresholds
  if (gasValue1 == HIGH || gasValue2 > GAS_THRESHOLD2) {
    // Gas leakage detected, activate the alarm
    activateAlarm();
  } else {
    // Gas level is below the thresholds, deactivate the alarm
    deactivateAlarm();
  }

  // Add some delay to avoid rapid readings (adjust this based on your requirement)
  delay(1000);
}