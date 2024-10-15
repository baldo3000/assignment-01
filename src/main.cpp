#include <Arduino.h>

#include <EnableInterrupt.h>
#include "functions.h"

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
State state = INIT;

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
    break;
  case SELECTION:
    // TODO display current turn number to guess
    // TODO player selects leds with buttons
    // TODO if time ended check inputs
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
