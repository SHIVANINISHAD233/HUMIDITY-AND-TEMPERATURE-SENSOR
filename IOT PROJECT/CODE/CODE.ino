#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

#define DHTPIN A3     // Pin where the DHT sensor is connected
#define DHTTYPE DHT11 // Define the sensor type (DHT11)
DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor

int h;  // Variable to store humidity value
int t;  // Variable to store temperature value

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature and Humidity Sensor Test");

  dht.begin();
  lcd.init(); 
  lcd.backlight(); 
}

void loop() {
  h = dht.readHumidity();  // Get the humidity
  t = dht.readTemperature();  // Get the temperature in Celsius

  // Check if the readings are valid
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
  } else {
    // Print temperature and humidity to the Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %, Temp: ");
    Serial.print(t);
    Serial.println(" °C");

    // Display "Simple Circuits" on the first row of the LCD
    lcd.setCursor(0, 0);
    lcd.println("Simple Circuits");

    // Display the temperature on the second row of the LCD
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(t);
    lcd.print("C");

    // Display the humidity on the second row of the LCD
    lcd.setCursor(11, 1);
    lcd.print("H:");
    lcd.print(h);
    lcd.print("%");
  }

  delay(1000);
}