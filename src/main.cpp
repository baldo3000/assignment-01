#include <Arduino.h>

#include <EnableInterrupt.h>
#include "functions.h"

volatile bool led1State;
volatile bool led2State;
volatile bool led3State;
volatile bool led4State;
int difficulty;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  pinMode(POTENTIOMETER, INPUT);
  enableInterrupt(BUTTON_1, button1_handler, FALLING);
  enableInterrupt(BUTTON_2, button2_handler, FALLING);
  enableInterrupt(BUTTON_3, button3_handler, FALLING);
  enableInterrupt(BUTTON_4, button4_handler, FALLING);
  difficulty = 1;
}

void loop()
{
  difficulty = difficulty_changer();
  Serial.println(difficulty);
  delay(1000);
}
