#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Arduino.h>
#include <EnableInterrupt.h>
#include "functions.h"

#define ROUND_TIME 5000

enum State
{
  HOME,      // game start screen
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
int currentRound;
int numberToGuess;
long turnStartTime;
State state = START;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
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

void home()
{
  // TODO display start message
  // TODO pulse red led
}

void sleep()
{
  // TODO goin sleep
}

void start()
{
  // TODO display game start screen
  // DONE starts round 1
  currentRound = 1;
  difficulty = selectedDifficulty();
  state = NEWROUND;
}

void newRound()
{
  // TODO randomize new turn number
  // TODO calculate new turn max time
  srand((time(NULL)));
  numberToGuess = rand() % 16;
  led1State = false;
  led2State = false;
  led3State = false;
  led4State = false;
  digitalWrite(LED_1_PIN, LOW);
  digitalWrite(LED_2_PIN, LOW);
  digitalWrite(LED_3_PIN, LOW);
  digitalWrite(LED_4_PIN, LOW);
  turnStartTime = millis();
  state = SELECTION;
}

void selection()
{
  // TODO display current turn number to guess
  // DONE player selects leds with buttons
  // DONE if time ended check inputs
  if (millis() - turnStartTime > ROUND_TIME)
  {
    state = CHECK;
  }
  else
  {
    noInterrupts();
    bool curLed1State = led1State;
    bool curLed2State = led2State;
    bool curLed3State = led3State;
    bool curLed4State = led4State;
    interrupts();
    digitalWrite(LED_1_PIN, curLed1State);
    digitalWrite(LED_2_PIN, curLed2State);
    digitalWrite(LED_3_PIN, curLed3State);
    digitalWrite(LED_4_PIN, curLed4State);
  }
}

void check()
{
  // TODO check player's inputs
  noInterrupts();
  bool curLed1State = led1State;
  bool curLed2State = led2State;
  bool curLed3State = led3State;
  bool curLed4State = led4State;
  interrupts();
  int guess = curLed1State * LED_1_VALUE + curLed2State * LED_2_VALUE + curLed3State * LED_3_VALUE + curLed4State * LED_4_VALUE;
  Serial.println(guess);
  state = NEWROUND;
}

void gameOver()
{
  // TODO display game over message and score
  // TODO resets game
}

void loop()
{
  switch (state)
  {
  case HOME:
    home();
    break;
  case SLEEP:
    sleep();
    break;
  case START:
    start();
    break;
  case NEWROUND:
    newRound();
    break;
  case SELECTION:
    selection();
    break;
  case CHECK:
    check();
    break;
  case GAMEOVER:
    gameOver();
    break;
  }
}