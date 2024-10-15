#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12
#define LED_1_VALUE 8
#define LED_2_VALUE 4
#define LED_3_VALUE 2
#define LED_4_VALUE 1
#define POTENTIOMETER A0
#define LED_RED 2
#define BUTTON_1 5
#define BUTTON_2 6
#define BUTTON_3 7
#define BUTTON_4 8
#define DEBOUNCE_TIME 20
#define NUMBER_OF_DIFFICULTIES 4

void button1_handler();
void button2_handler();
void button3_handler();
void button4_handler();
int selectedDifficulty();
int scoreCalculator(int time, int level);

#endif