#include <Arduino.h>

#include <EnableInterrupt.h>
#include "functions.h"

#define ROUND_TIME 10000

enum State
{
  INIT,      // game start screen
  SLEEP,     // board went to sleep after inactivity
  START,     // game started
  NEWROUND,  // configuration for next round
  SELECTION, // player is guessing binary conversion
  CHECK,     // checking player's inputs
  GAMEOVER   // end of game
};

volatile bool led1State;
volatile bool led2State;
volatile bool led3State;
volatile bool led4State;
int difficulty;
long turnStartTime;
State state = NEWROUND;

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
  switch (state)
  {
  case INIT:
    // TODO display start message
    // TODO pulse red led
    break;
  case SLEEP:
    // TODO goin sleep
    break;
  case START:
    // TODO display game start screen
    // TODO starts round 1
    break;
  case NEWROUND:
    // TODO randomize new turn number
    // TODO calculate new turn max time
    led1State = false;
    led2State = false;
    led3State = false;
    led4State = false;
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    turnStartTime = millis();
    state = SELECTION;
    break;
  case SELECTION:
    // TODO display current turn number to guess
    // TODO player selects leds with buttons
    // TODO if time ended check inputs
    if (millis() - turnStartTime > ROUND_TIME)
    {
      state = NEWROUND;
    }
    else
    {
      noInterrupts();
      bool curLed1State = led1State;
      bool curLed2State = led2State;
      bool curLed3State = led3State;
      bool curLed4State = led4State;
      interrupts();
      digitalWrite(LED_1, led1State);
      digitalWrite(LED_2, led2State);
      digitalWrite(LED_3, led3State);
      digitalWrite(LED_4, led4State);
    }
    break;
  case CHECK:
    // TODO check player's inputs
    break;
  case GAMEOVER:
    // TODO display game over message and score
    // TODO resets game
    break;
  }
}
