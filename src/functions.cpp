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

int brightness = 0;  // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by

// the loop routine runs over and over again forever:
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
    return abs(map(analogRead(POTENTIOMETER), 0, 1023, 1, NUMBER_OF_DIFFICULTIES));
}

int scoreCalculator(int time, int level)
{
    return level * level * time;
}

int timerCalculator(int difficulty, int level)
{
    return ROUND_TIME / difficulty / (1 + level / 5);
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

void goMessage(LiquidCrystal_I2C lcd, int number, int currentRound)
{
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("GO!");
    lcd.setCursor(0, 1);
    lcd.print("Round ");
    lcd.print(currentRound);
    lcd.print(" ! Convert ");
    lcd.print(number);
    lcd.setCursor(0, 2);
    lcd.print("to binary using");
    lcd.setCursor(0, 3);
    lcd.print("the buttons 1-4");
}

void roundPassedMessage(LiquidCrystal_I2C lcd, int score)
{
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("GOOD! Score: ");
    lcd.print(score);
}

void gameOver(LiquidCrystal_I2C lcd, int score)
{
    lcd.clear();
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    lcd.setCursor(2, 1);
    lcd.print("Game Over -");
    lcd.setCursor(2, 2);
    lcd.print("Final Score ");
    lcd.print(score);
    delay(8000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Oh look at little ");
    lcd.setCursor(0, 2);
    lcd.print("goblin junior,");
    lcd.setCursor(0, 3);
    lcd.print("gonna cry?");
    delay(2000);
    lcd.clear();
    lcd.flush();
}