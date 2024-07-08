#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "posture.h"

#define flex1 A6
#define flex2 A7
const int ledPin1 = 2;      // LED 1 pin
const int ledPin2 = 3;      // LED 2 pin
const int ledPin3 = 4;  
const int ledPin4 = 5;      // LED 2 pin
const int ledPin5 = 6;
#define BUZZER_PIN 7
/* 
remember
scl = A5
sda = A4
*/
int flexValue1 = 0;
int flexValue2 = 0;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
  display.clearDisplay();
  display.drawBitmap(0, 0, good_posture, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  display.display();


}

void loop() {
  // put your main code here, to run repeatedly:
    flexValue1 = analogRead(flex1);
    flexValue2 = analogRead(flex2);
    int avg = (flexValue1 + flexValue2)/2;

    int brightness =  map(avg, 0, 1023, 0, 255);





      if (avg < 700) {  // If flex value is in the first third of the range
        analogWrite(ledPin1, brightness);    // analogWrite(ledPin1, brightness);
        analogWrite(ledPin2, 0);
        analogWrite(ledPin3, 0); 
        analogWrite(ledPin4, 0);
        analogWrite(ledPin5, 0); 
        // tone(BUZZER_PIN, 1000); // Generate a tone of 1000Hz on the buzzer pin
        // delay(500); // Wait for 500 milliseconds
        // noTone(BUZZER_PIN); // Turn off the buzzer
        // delay(500);
        display.clearDisplay();
        display.drawBitmap(0, 0, good_posture, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
        display.display();

      }

   else if (avg >= 700 && avg < 750) {  // If flex value is in the second third of the range
        analogWrite(ledPin2, brightness);
        analogWrite(ledPin1, brightness); 
        analogWrite(ledPin3, 0);
        analogWrite(ledPin4, 0);
        analogWrite(ledPin5, 0);  
        tone(BUZZER_PIN, 1000); // Generate a tone of 1000Hz on the buzzer pin
        delay(400); // Wait for 500 milliseconds
        noTone(BUZZER_PIN); // Turn off the buzzer
        delay(400);
        display.clearDisplay();
        display.drawBitmap(0, 0, good_posture, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
        display.display();
      }
    
    else if (avg >= 750 && avg < 800) {  // If flex value is in the second third of the range
        analogWrite(ledPin2, brightness);
        analogWrite(ledPin1, brightness); 
        analogWrite(ledPin3, brightness);
        analogWrite(ledPin4, 0);
        analogWrite(ledPin5, 0); 
        // tone(BUZZER_PIN, 1000); // Generate a tone of 1000Hz on the buzzer pin
        // delay(300); // Wait for 500 milliseconds
        // noTone(BUZZER_PIN); // Turn off the buzzer
        // delay(300); 
        display.clearDisplay();
        display.drawBitmap(0, 0, bad_posture, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
        display.display();
  }

    else if (avg >= 800 && avg < 850) {  // If flex value is in the second third of the range
      analogWrite(ledPin2, brightness);
      analogWrite(ledPin1, brightness); 
      analogWrite(ledPin3, brightness);
      analogWrite(ledPin4, brightness);
      analogWrite(ledPin5, 0); 
      tone(BUZZER_PIN, 1000); // Generate a tone of 1000Hz on the buzzer pin
      delay(200); // Wait for 500 milliseconds
      noTone(BUZZER_PIN); // Turn off the buzzer
      delay(200); 
      display.clearDisplay();
      display.drawBitmap(0, 0, bad_posture, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
      display.display();
}

   else  {  // If flex value is in the last third of the range
    analogWrite(ledPin3, brightness);
    analogWrite(ledPin1, brightness); 
    analogWrite(ledPin2, brightness); 
    analogWrite(ledPin4, brightness);
    analogWrite(ledPin5, brightness);
    tone(BUZZER_PIN, 1000); // Generate a tone of 1000Hz on the buzzer pin
    delay(100); // Wait for 500 milliseconds
    noTone(BUZZER_PIN); // Turn off the buzzer
    delay(100);
    display.clearDisplay();
    display.drawBitmap(0, 0, bad_posture, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.display();

  }

  Serial.print("Flex Value: ");
  Serial.println(avg);
  Serial.println(flexValue1);
  Serial.println(flexValue2);
  // delay(100);
}
