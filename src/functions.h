#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define LED_1 9
#define LED_2 10
#define LED_3 11
#define LED_4 12
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
int difficulty_changer();
int scoreCalculator(int time, int level);

#endif