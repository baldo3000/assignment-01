#include <Arduino.h>
#include <math.h>
#include "functions.h"

long prevts1 = 0;
long prevts2 = 0;
long prevts3 = 0;
long prevts4 = 0;
long prevtsCheck = 0;

extern volatile bool led1State;
extern volatile bool led2State;
extern volatile bool led3State;
extern volatile bool led4State;
extern volatile bool checkNumber;

int brightness = 0;  // how bright the LED is
int fadeAmount = 15; // how many points to fade the LED by

void pulsingLight()
{
    analogWrite(LED_RED, brightness);

    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;
    }
}

void button1_handler()
{
    long ts = millis();
    if (ts - prevts1 > DEBOUNCE_TIME)
    {
        prevts1 = ts;
        led1State = !led1State;
    }
}

void button2_handler()
{
    long ts = millis();
    if (ts - prevts2 > DEBOUNCE_TIME)
    {
        prevts2 = ts;
        led2State = !led2State;
    }
}

void button3_handler()
{
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

void buttonCheck_handler()
{
    long ts = millis();
    if (ts - prevtsCheck > DEBOUNCE_TIME)
    {
        prevtsCheck = ts;
        checkNumber = true;
    }
}

double myMap(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int selectedDifficulty()
{
    int x = (round)(myMap(analogRead(POTENTIOMETER), 0, 1023, 1, NUMBER_OF_DIFFICULTIES)) + 0.5;
    return x;
}

int scoreCalculator(int time, int level, int difficulty)
{
    float dif = (float)difficulty;
    float t = (float)time / 1000;
    return level * level * (t + 1) * (dif * dif);
}

int timerCalculator(int difficulty, int level)
{
    return ROUND_TIME / (float)sqrt(difficulty) / (1 + (float)level / 5);
}

// LCD Messages
void welcomeMessage(LiquidCrystal_I2C lcd)
{
    lcd.setCursor(1, 1); // Set the cursor on the third column and first row.
    lcd.print("Welcome to GMB!");
    lcd.setCursor(1, 2);
    lcd.print("Press B1 to Start");
}

void startMessage(LiquidCrystal_I2C lcd, int difficulty)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game started with");
    lcd.setCursor(0, 1);
    lcd.print("difficulty: ");
    lcd.print(difficulty);
    lcd.setCursor(4, 2);
    lcd.print("3_");
    delay(1000);
    lcd.print("2_");
    delay(1000);
    lcd.print("1");
    delay(1000);
}
void checkMessage(LiquidCrystal_I2C lcd, int time)
{

    lcd.clear();
    lcd.setCursor(0, 0);
    if (time >= 2000)
    {
        lcd.print("Pretty fast!");
    }
    else
    {
        lcd.print("Just in time!");
    }
    lcd.setCursor(0, 1);
    lcd.print(time / 1000);
    lcd.print(" seconds");
    lcd.setCursor(0, 2);
    lcd.print(time % 1000);
    lcd.print(" millis ");
    lcd.setCursor(0, 3);
    lcd.print("before time ran out");
    delay(4000);
}
void timeOutMessage(LiquidCrystal_I2C lcd)
{

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Time is over!!");
    delay(3000);
}

void goMessage(LiquidCrystal_I2C lcd, int number, int currentRound, int time)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GO!: ");
    lcd.print(time / 1000);
    lcd.print("s ");
    lcd.print(time % 1000);
    lcd.print("ms");
    lcd.setCursor(0, 1);
    lcd.print("Round ");
    lcd.print(currentRound);
    lcd.print(" ! Convert ");
    lcd.setCursor(0, 2);
    lcd.print(number);
    lcd.print(" to binary using");
    lcd.setCursor(0, 3);
    lcd.print("the buttons 1-4");
}

void roundPassedMessage(LiquidCrystal_I2C lcd, int score)
{
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("GOOD! Score: ");
    lcd.print(score);
    delay(3000);
}

void gameOver(LiquidCrystal_I2C lcd, int score)
{
    lcd.clear();
    digitalWrite(LED_RED, HIGH);
    delay(1000);
    digitalWrite(LED_RED, LOW);
    lcd.setCursor(2, 1);
    lcd.print("Game Over -");
    lcd.setCursor(2, 2);
    lcd.print("Final Score ");
    lcd.print(score);
    delay(8000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Oh look at little ");
    lcd.setCursor(0, 1);
    lcd.print("goblin junior,");
    lcd.setCursor(0, 2);
    lcd.print("gonna cry?");
    delay(2000);
    lcd.clear();
    lcd.flush();
}