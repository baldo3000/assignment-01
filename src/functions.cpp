#include <Arduino.h>
#include "functions.h"

long prevts1 = 0;
long prevts2 = 0;
long prevts3 = 0;
long prevts4 = 0;

extern volatile bool led1State;
extern volatile bool led2State;
extern volatile bool led3State;
extern volatile bool led4State;

void button1_handler()
{
    // static long prevts = millis();
    long ts = millis();
    if (ts - prevts1 > DEBOUNCE_TIME)
    {
        prevts1 = ts;
        led1State = !led1State;
    }
}
void button2_handler()
{
    // static long prevts = millis();
    long ts = millis();
    if (ts - prevts2 > DEBOUNCE_TIME)
    {
        prevts2 = ts;
        led2State = !led2State;
    }
}
void button3_handler()
{
    // static long prevts = millis();
    long ts = millis();
    if (ts - prevts3 > DEBOUNCE_TIME)
    {
        prevts3 = ts;
        led3State = !led3State;
    }
}
void button4_handler()
{
    long ts = millis();
    if (ts - prevts4 > DEBOUNCE_TIME)
    {
        prevts4 = ts;
        led4State = !led4State;
    }
}
int selectedDifficulty()
{
    /*
   int range = 255;
   int divider = range/4 + 1;
   int outputValue = abs(map(analogRead(POTENTIOMETER), 0, 1023, 0, range) - 1);
   Serial.print(outputValue);
    Serial.print("\t");
   return outputValue/divider + 1;
   */
    return abs(map(analogRead(POTENTIOMETER), 0, 1023, 1, NUMBER_OF_DIFFICULTIES));
}
int scoreCalculator(int time, int level)
{
    return level * level * time;
}