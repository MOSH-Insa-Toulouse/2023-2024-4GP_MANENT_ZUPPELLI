/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

//oled
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)
#define DEBUG
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001
//#include <SoftwareSerial.h>
#define baudrate 9600
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
#include <SoftwareSerial.h>
#define baudrate 9600
SoftwareSerial mySerial (12, 13);
int consigne=0;

#define CLK  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define DT  4  //DT Output B
#define Switch 5 // Switch connection if available

const int ssMCPin = 10; // Define the slave select for the digital pot

#define WAIT_DELAY 5000

//Flex sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int flexPin = A1;      // Pin connected to voltage divider output
const int analogInPin = A0;
const int analogOutPin = 9;
float Rflex=0;
float Resistance=0;

// Change these constants according to your project's design
int lastStateCLK;
int lastStateDT;
int stateCLK;
int stateDT;

//bouton 
bool lastButtonState = HIGH;
bool buttonState;
bool reading;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 10;

int sensorValue = 0;  // value read from the pot
int outputValue = 0; 


volatile int encoder0Pos = 0;
volatile bool rotating = false;

const char* menuItems[] = {"Capteur Graph", "FlexSensor", "Gain"};
const char menuChars[] = {'A', 'B', 'C'};
int valGain = 1; // Valeur initiale pour le menu Gain

//Potentiomètre digital

#include <SPI.h>
const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 47000.0;  // resistor used to create a voltage divider
const float flatResistance = 25000.0; // resistance when flat
const float bendResistance = 100000.0;  // resistance at 90 deg
const byte csPin           = 10;      // MCP42100 chip select pin
const int  maxPositions    = 256;     // wiper can move from 0 to 255 = 256 positions 
const long rAB             = 92500;   // 100k pot resistance between terminals A and B, 
                                      // mais pour ajuster au multimètre, je mets 92500
const byte rWiper          = 125;     // 125 ohms pot wiper resistance
const byte pot0            = 0x11;    // pot0 addr // B 0001 0001
const byte pot0Shutdown    = 0x21;    // pot0 shutdown // B 0010 0001



//Gestion du potentiomètre

void SPIWrite(uint8_t cmd, uint8_t data, uint8_t ssPin) // SPI write the command and data to the MCP IC connected to the ssPin
{
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); //https://www.arduino.cc/en/Reference/SPISettings
  
  digitalWrite(ssPin, LOW); // SS pin low to select chip
  
  SPI.transfer(cmd);        // Send command code
  SPI.transfer(data);       // Send associated value
  
  digitalWrite(ssPin, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(Switch, INPUT_PULLUP);

  lastStateCLK = digitalRead(CLK);
  lastStateDT = digitalRead(DT);

  attachInterrupt(digitalPinToInterrupt(CLK), doEncoder, CHANGE);


  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
    while (1);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  Serial.begin(9600);
  pinMode(flexPin, INPUT);
  mySerial.begin(baudrate);
  Serial.begin(baudrate);
}
// the loop routine runs over and over again forever:
void loop() {                     // Arrêt du programme (boucle infinie) si échec d'initialisation
int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * VCC / 1023.0;
  float Rflex = R_DIV * (VCC / Vflex - 1.0);
  //Serial.print(Rflex);
  //Serial.println(Rflex);

  int sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  int outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("Graphène = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.print(Rflex/100);
  Serial.println(outputValue);
  Serial.println("Resistance du Flex Sensor: " + String(Rflex) + " ohms");
  Serial.println();
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);

  if (rotating) {
    rotating = false;

  int reading = digitalRead(Switch);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        if (encoder0Pos == 2) { // Si le menu sélectionné est "Gain"
          while (digitalRead(Switch) == LOW) {} // Attend que le bouton soit relâché

          // Entrer dans le mode d'édition de la valeur de valGain
          editValGain();
          
          // Sortie de la boucle de lecture du bouton
          rotating = true; // Permet de rafraîchir l'affichage du menu après avoir édité valGain
        }
      }
    }
  }
  


  lastButtonState = reading;


    display.clearDisplay();
  display.setTextSize(1);

  for (int i = 0; i < 3; i++) {
    if (i == encoder0Pos) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.setCursor(0, i * 10);
    display.print(menuItems[i]);
    if(i == 2 && encoder0Pos == 2){
      display.print(": ");
      display.println(valGain);
    }
    if(i == 1 && encoder0Pos == 1){
      display.print(": ");
      display.println(Rflex);
  }
    if(i == 0 && encoder0Pos == 0){
      display.print(": ");
      display.println(sensorValue);   
  }
  }
  display.display();
}
}
//endodeur rotatoire

void doEncoder() {
  stateCLK = digitalRead(CLK);
  stateDT = digitalRead(DT);

  if (stateCLK != lastStateCLK) {
    if (stateDT != stateCLK) {
      encoder0Pos++;
    } else {
      encoder0Pos--;
    }

    if (encoder0Pos < 0) encoder0Pos = 2;
    else if (encoder0Pos > 2) encoder0Pos = 0;

    rotating = true;

    lastStateCLK = stateCLK;
  }

//Bluetooth
  float mesure = analogRead(Rflex);  //recup valeur capteur 
  Serial.println(mesure); //retoune la valeur 
  delay(1);
  //Serial.println(Serial.read());
//Serial.println(mySerial.available());
 while (mySerial.available()>0){
   consigne=mySerial.read();
      Serial.println(consigne,DEC);
      if (consigne==1){
        digitalWrite(13,HIGH);
      }
      if (consigne==2){
        digitalWrite(13,LOW);
      }
}
}

void editValGain() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("ValGain: ");
  display.println(valGain);
  display.display();

  while (true) {
    int newPos = encoder0Pos;
    while (encoder0Pos == newPos) {
      if (digitalRead(Switch) == LOW) {
        // Valider et sortir du mode d'édition
        while (digitalRead(Switch) == LOW) {} // Attend que le bouton soit relâché
        Serial.print("Nouvelle valeur de valGain: ");
        Serial.println(valGain);
        return;
      }
    }
    if (newPos > encoder0Pos) {
      valGain++;
    } else {
      valGain--;
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("ValGain: ");
    display.println(valGain);
    display.display();
  }
}

//SoftwareSerial mySerial(rxPin,txPin);