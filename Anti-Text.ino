#include <Wire.h>
#include "rgb_lcd.h"
#include <fstream> 

rgb_lcd lcd;

char dtaUart[15];

//Pins for sensors and outputs
const int speakerPin = 8;
const int button1 = 3;
const int analogDetect = 0;
const int ir = 4;

//Variables for the audio
int length = 1; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1 };
int tempo = 300;

//Buzzer timing 
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
}

//How the buzzer sounds
void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}


void setup() 
{
  pinMode(speakerPin, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(ir,OUTPUT);
  pinMode (analogDetect, INPUT);  
  
  Serial.begin(115200);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() 
{
  //Activates Ir LED
  digitalWrite(ir,HIGH);
  
  //
  int r = (dtaUart[0]-'0')*100 + (dtaUart[1] - '0')*10 + (dtaUart[2] - '0');
  int g = (dtaUart[4]-'0')*100 + (dtaUart[5] - '0')*10 + (dtaUart[6] - '0');
  int b = (dtaUart[8]-'0')*100 + (dtaUart[9] - '0')*10 + (dtaUart[10] - '0');
   
  if(analogRead(analogDetect) > 655)
  {  
    if(!digitalRead(button1))
    {  
      for (int i = 0; i < length; i++) 
      {
        //Warning text geos here
        lcd.print("  !!Caution!!                            Calling Police");
        
        //Flashing screen, (Red, Green, Blue)
        lcd.setRGB(0, 255, 0);
        delay(100);
        lcd.setRGB(255, 0, 0);
        delay(100);
        
        if (notes[i] == ' ')
        {
          playNote(notes[i], beats[i] * tempo); // rest
        }
        else
        {
          playNote(notes[i], beats[i] * tempo);
        }
      }
    }
    //Clears screen
    lcd.clear();
   
    if(digitalRead(button1))
    {
      // Print a message to the LCD.
      lcd.print("We are cool     here!");
      lcd.setRGB(255,255,255);
    } 
  }
  else
  {
    //Warning text goes here
    lcd.print("  !!Caution!!                            Calling Police");
    for (int j = 0; j < length; j++) 
      {
        
        
        //Flashing screen, (Red, Green, Blue)
        lcd.setRGB(0, 255, 0);
        delay(100);
        lcd.setRGB(255, 0, 0);
        delay(100);
        
        if (notes[j] == ' ')
        {
          playNote(notes[j], beats[j] * tempo); // rest
        }
        else
        {
          playNote(notes[j], beats[j] * tempo);
        }
      }
  }
  //IR Calibration - Use Serial Monitor
   Serial.println(analogRead(analogDetect));
}
