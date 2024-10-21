#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Arduino.h>
#include <EnableInterrupt.h>
#include <TimerOne.h>
#include <avr/sleep.h>
#include "functions.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

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
volatile long timerCounter;
volatile bool checkNumber;
int difficulty;
int currentRound;
int numberToGuess;
long turnStartTime;
int roundTime;
float timeLeft;
int score;
State state = HOME;

void reset();
void timerHandler();

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
  pinMode(RANDOM_PIN, INPUT);
  enableInterrupt(BUTTON_1, button1_handler, FALLING);
  enableInterrupt(BUTTON_2, button2_handler, FALLING);
  enableInterrupt(BUTTON_3, button3_handler, FALLING);
  enableInterrupt(BUTTON_4, button4_handler, FALLING);
  enableInterrupt(BUTTON_CHECK, buttonCheck_handler, FALLING);
  difficulty = 1;
  srand(analogRead(RANDOM_PIN));
  timeLeft = 0;
  lcd.init();
  lcd.backlight();

  Timer1.initialize(100000); // 100 milliseconds
  Timer1.attachInterrupt(timerHandler);
  Timer1.restart();
  reset();
}

void timerHandler()
{
  timerCounter = timerCounter + 100;
}

void wakeUp() {}

void sleep()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  lcd.noBacklight();
  lcd.clear();
  analogWrite(LED_RED, 0);
  enableInterrupt(BUTTON_1, wakeUp, FALLING);

  sleep_mode();

  sleep_disable();
  lcd.backlight();
  delay(300); // prevent bouncing starting the game unintentionally
  enableInterrupt(BUTTON_1, button1_handler, FALLING);
}

void reset()
{
  noInterrupts();
  led1State = false;
  led2State = false;
  led3State = false;
  led4State = false;
  timerCounter = 0L;
  checkNumber = false;
  interrupts();
  digitalWrite(LED_1_PIN, LOW);
  digitalWrite(LED_2_PIN, LOW);
  digitalWrite(LED_3_PIN, LOW);
  digitalWrite(LED_4_PIN, LOW);
}

void home()
{
  noInterrupts();
  bool curLed1State = led1State;
  long currentTimerCounter = timerCounter;
  interrupts();
  if (currentTimerCounter >= 10000)
  {
    noInterrupts();
    timerCounter = 0;
    interrupts();
    sleep();
  }
  else
  {
    welcomeMessage(lcd);
    pulsingLight();
    if (curLed1State)
    {
      state = START;
      digitalWrite(LED_RED, LOW);
      Timer1.detachInterrupt();
    }
  }
}

void start()
{
  currentRound = 0;
  score = 0;
  difficulty = selectedDifficulty();
  startMessage(lcd, difficulty);
  state = NEWROUND;
}

void newRound()
{
  currentRound++;
  numberToGuess = rand() % 16;
  reset();
  turnStartTime = millis();
  roundTime = timerCalculator(difficulty, currentRound);
  goMessage(lcd, numberToGuess, currentRound, roundTime);
  timeLeft = 0;
  state = SELECTION;
}

void selection()
{
  noInterrupts();
  bool curLed1State = led1State;
  bool curLed2State = led2State;
  bool curLed3State = led3State;
  bool curLed4State = led4State;
  bool curCheckNumber = checkNumber;
  interrupts();
  if ((long)millis() - turnStartTime > roundTime)
  {
    timeOutMessage(lcd);
    state = CHECK;
  }
  else if (curCheckNumber)
  {
    timeLeft = roundTime - (millis() - turnStartTime);
    checkMessage(lcd, timeLeft);
    state = CHECK;
  }
  else
  {
    digitalWrite(LED_1_PIN, curLed1State);
    digitalWrite(LED_2_PIN, curLed2State);
    digitalWrite(LED_3_PIN, curLed3State);
    digitalWrite(LED_4_PIN, curLed4State);
  }
}

void check()
{
  noInterrupts();
  bool curLed1State = led1State;
  bool curLed2State = led2State;
  bool curLed3State = led3State;
  bool curLed4State = led4State;
  interrupts();
  int guess = curLed1State * LED_1_VALUE + curLed2State * LED_2_VALUE + curLed3State * LED_3_VALUE + curLed4State * LED_4_VALUE;
  if (guess == numberToGuess)
  {
    roundPassedMessage(lcd, scoreCalculator(timeLeft, currentRound, difficulty));
    score += scoreCalculator(timeLeft, currentRound, difficulty);
    state = NEWROUND;
  }
  else
  {
    state = GAMEOVER;
  }
}

void gameOver()
{
  gameOver(lcd, score);
  Timer1.attachInterrupt(timerHandler);
  Timer1.restart();
  delay(200);
  reset();
  state = HOME;
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