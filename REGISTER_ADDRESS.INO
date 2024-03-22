echo "# GY_906-with-REGISTER-ADDRESS" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/ironkid99/GY_906-with-REGISTER-ADDRESS.git
git push -u origin main


// #include <Wire.h>

// #define TA 0x06   
// #define TOBJ1 0x07 

// void readTemperature(float &ambientTemp, float &objectTemp) {

//   Wire.beginTransmission(0x5A);
//   Wire.write(0x06);
//   Wire.endTransmission(false);
//   Wire.requestFrom(0X05, 3);
//   uint16_t ambientData = Wire.read() | (Wire.read() << 8);
//   ambientTemp = (ambientData * 0.02) - 273.15;


//   Wire.beginTransmission(0X5A);
//   Wire.write(0x07);
//   Wire.endTransmission(false);
//   Wire.requestFrom(0x5A, 3);
//   uint16_t objectData = Wire.read() | (Wire.read() << 8);
//   objectTemp = (objectData * 0.02) - 273.15;
// }


// void setup() {
//   Serial.begin(9600);
//   Wire.begin();
// }


// void loop() {
//   float ambientTemp, objectTemp;
//   readTemperature(ambientTemp, objectTemp);
//   Serial.print("Ambient Temperature: ");
//   Serial.print(ambientTemp, 2); 
//   Serial.println(" °C");
//   Serial.print("Object Temperature: ");
//   Serial.print(objectTemp, 2); 
//   Serial.println(" °C");
//   Serial.println("-----------------------------");

//   delay(2000); 
// }

#include <Wire.h>

// GY906 I2C address
#define GY906_ADDR 0x5A

// Register addresses for temperature data
#define TA 0x06   // Ambient temperature
#define TOBJ1 0x07 // Object temperature 1

void setup() {
  Serial.begin(9600);

  // I2C setup
  Wire.begin();
}

void readTemperature(float &ambientTemp, float &objectTemp) {
  // Read ambient temperature
  Wire.beginTransmission(GY906_ADDR);
  Wire.write(TA);
  Wire.endTransmission();
  Wire.requestFrom(GY906_ADDR, 3);
  uint16_t ambientData = Wire.read() | (Wire.read() << 8);
  ambientTemp = (ambientData * 0.02) - 273.15;

  // Read object temperature
  Wire.beginTransmission(GY906_ADDR);
  Wire.write(TOBJ1);
  Wire.endTransmission();
  Wire.requestFrom(GY906_ADDR, 3);
  uint16_t objectData = Wire.read() | (Wire.read() << 8);
  objectTemp = (objectData * 0.02) - 273.15;
}

void loop() {
  float ambientTemp, objectTemp;
  
  readTemperature(ambientTemp, objectTemp);

  Serial.print("Ambient Temperature: ");
  Serial.print(ambientTemp, 2); // Print with 2 decimal places
  Serial.println(" °C");

  Serial.print("Object Temperature: ");
  Serial.print(objectTemp, 2); // Print with 2 decimal places
  Serial.println(" °C");

  Serial.println("-----------------------------");

  delay(1000); // Delay for 1 second
}
