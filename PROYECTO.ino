#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
//HOLA
Adafruit_BME280 bme;

const int ENA = 3;   // Pin de velocidad (PWM)
const int IN1 = 2;   // Dirección 1
const int IN2 = 4;  // Dirección 2

const int ENB = 5;   // Pin de velocidad (PWM)
const int IN3 = 7;   // Dirección 1
const int IN4 = 6;  // Dirección 2

int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);

  if (!bme.begin(0x76)) {
    Serial.println("No se encuentra el sensor BME280");
    while (1);
  }

  pinMode(8,INPUT);
  starttime = millis();//get the current time;


  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  
  if (concentration >= 0 && concentration < 10000) {

    digitalWrite(12, HIGH); 
    digitalWrite(11, LOW); 
    digitalWrite(10, LOW);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); // Giro en una dirección
    analogWrite(ENA, 100);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); // Giro en una dirección
    analogWrite(ENB, 100);
  }

  if (concentration > 1000 && concentration < 30000) {

    digitalWrite(12, LOW); 
    digitalWrite(11, HIGH); 
    digitalWrite(10, LOW);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); // Giro en una dirección
    analogWrite(ENA, 220);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); // Giro en una dirección
    analogWrite(ENB, 220);
  }

  if (concentration > 3000 && concentration < 50000) {

    digitalWrite(12, LOW); 
    digitalWrite(11, LOW); 
    digitalWrite(10, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); // Giro en una dirección
    analogWrite(ENA, 255);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); // Giro en una dirección
    analogWrite(ENB, 255);
  }


  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("FLUJO DE AIRE");
  lcd.setCursor(1,1);
  lcd.print("PROYECTO DE MICRO");
   lcd.setCursor(4,2);
  lcd.print("MEC-458");
   lcd.setCursor(8,3);
  lcd.print("UMSA");
  delay(5000);
  lcd.clear();

}


void loop(){
    float temperatura = bme.readTemperature();
    float humedad = bme.readHumidity();
    lcd.setCursor(1,0);
    lcd.print("ESTERILIZACION");
    lcd.setCursor(0,1);
    lcd.print("TEMP:");
    lcd.print(temperatura);
    lcd.setCursor(0,2);
    lcd.print("HUMEDAD:");
    lcd.print(humedad);
    delay(7000);
    
    lcd.clear();

  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;

  if ((millis()-starttime) > sampletime_ms)
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    lowpulseoccupancy = 0;

    lcd.setCursor(4,0);
    lcd.print("CALIDAD AIRE");
    lcd.setCursor(1,1);
    lcd.print("CONCENTRACION:"+String(concentration)); 

    if (concentration < 1000) {
    lcd.setCursor(7,2);
    lcd.print("LIMPIO"); 
    delay(5000);
    lcd.clear();
    }

    if (concentration > 1000 && concentration < 10000) {

    lcd.setCursor(7,2);
    lcd.print("BUENO"); 
    delay(5000);
    lcd.clear(); 
    }

     if (concentration > 10000 && concentration < 20000) {

    lcd.setCursor(7,2);
    lcd.print("ACEPTABLE"); 
    delay(5000);
    lcd.clear();
    }

    if (concentration > 20000 && concentration < 50000) {
    lcd.setCursor(7,2);
    lcd.print("PESADO"); 
    delay(5000);
    lcd.clear();
    }

    if (concentration > 50000 ) {

    lcd.setCursor(7,2);
    lcd.print("PELIGRO"); 
    delay(5000);
    lcd.clear();

    } 

    delay(1000);
  
  }
  Sereial
  

  
}
