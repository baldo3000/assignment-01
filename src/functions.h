#include <LiquidCrystal_I2C.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define LED_1_PIN 4
#define LED_2_PIN 6
#define LED_3_PIN 7
#define LED_4_PIN 8
#define LED_1_VALUE 8
#define LED_2_VALUE 4
#define LED_3_VALUE 2
#define LED_4_VALUE 1
#define POTENTIOMETER A0
#define LED_RED 5
#define BUTTON_1 9
#define BUTTON_2 10
#define BUTTON_3 11
#define BUTTON_4 12
#define BUTTON_CHECK 3
#define DEBOUNCE_TIME 50
#define NUMBER_OF_DIFFICULTIES 4
#define ROUND_TIME 40000

void button1_handler();
void button2_handler();
void button3_handler();
void button4_handler();
void buttonCheck_handler();
double myMap(double x, double in_min, double in_max, double out_min, double out_max);
int selectedDifficulty();
int scoreCalculator(int time, int level);
int timerCalculator(int difficulty, int level);
void welcomeMessage(LiquidCrystal_I2C lcd);
void startMessage(LiquidCrystal_I2C lcd, int difficulty);
void goMessage(LiquidCrystal_I2C lcd, int number, int currentRound);
void roundPassedMessage(LiquidCrystal_I2C lcd, int score);
void gameOver(LiquidCrystal_I2C lcd, int score);
void pulsingLight();
#endif