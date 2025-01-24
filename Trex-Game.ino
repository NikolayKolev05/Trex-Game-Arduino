#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

int obstacle = 16;
const int buttonPin = 8;
int tRex = 1;
unsigned long jumpTime = 0;
bool jumping = false;
bool gameOver = false;
int score = 0;
int gameSpeed = 100;
int highScore = 0;
int powerUp = -1;
unsigned long powerUpTime = 0;
bool invincible = false;

byte tRexChar[8] = {
  B00100, //   *
  B01100, //  **
  B01110, //  ***
  B00101, //   * *
  B01110, //  ***
  B10100, // * *
  B10100, // * *
  B00000  //   
};

byte cactusChar[8] = {
  B00100, //   *
  B01110, //  ***
  B00100, //   *
  B01110, //  ***
  B10101, // * * *
  B00100, //   *
  B00100, //   *
  B00000  //   
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, tRexChar);
  lcd.createChar(1, cactusChar);
  pinMode(buttonPin, INPUT_PULLUP);
  startGame();
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (random(0, 50) == 0 && powerUp == -1) 
  {
    powerUp=16;
  }

  if (powerUp > -1) 
  {
    lcd.setCursor(powerUp, 1);
    lcd.print(" ");
    powerUp--;
    if (powerUp >= 0) 
    {
      lcd.setCursor(powerUp, 1);
      lcd.print("*");
    } else 
    {

    }
  }

  if (powerUp == 1 && tRex == 1) 
  {
    activatePower();
    powerUp = -1;
  }
  if (invincible && millis() - powerUpTime > 3000) 
  {
    invincible = false;
  }
  if (obstacle == 1 && tRex == 1 && !invincible) 
  {
    gameOver = true;
  }
  if (buttonState == LOW && !jumping)
  {
    tRex = 0;
    jumping = true;
    jumpTime = millis();
  }

  if (jumping && millis() - jumpTime > 300) {
    tRex = 1;
    jumping = false;
  }
  if (!gameOver) 
  {
    lcd.setCursor(obstacle, 1);
    lcd.print(" ");
    obstacle--;
    lcd.setCursor(obstacle, 1);
    lcd.write(byte(1));
    if (obstacle == 0) 
    {
      lcd.setCursor(obstacle, 1);
      lcd.print(" ");
      obstacle = 16;
      score++;
      lcd.setCursor(12, 0);
      lcd.print(score);
    }
    lcd.setCursor(1, 0);
    lcd.print(" ");
    lcd.setCursor(1, 1);
    lcd.print(" ");
    lcd.setCursor(1, tRex);
    lcd.write(byte(0));

    delay(gameSpeed);
    if (score % 3 == 0 && score > 0 && gameSpeed > 50) 
    {
      gameSpeed -= 5;
    }
  }
  if (gameOver) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(4, 1);
    lcd.print("Score:");
    lcd.print(score);
    delay(2000);
    lcd.clear();
    if (score > highScore) 
    {
      highScore = score;
      lcd.print("New High:");
      lcd.print(highScore);
    } else 
    {
      lcd.print("High Score:");
      lcd.print(highScore);
    }

    score = 0;
    gameSpeed = 100;
    gameOver = true;

    while (digitalRead(buttonPin) == HIGH) 
    {
    }
    obstacle = 15;
    tRex = 1;
    gameOver = false;
    lcd.clear();
  }
}
void activatePower() 
{
  invincible = true;
  powerUpTime = millis();
}

void startGame() 
{
  lcd.setCursor(4, 0);
  lcd.print("T-Rex Game");
  lcd.setCursor(2, 1);
  lcd.print("Press to Start");

  while (digitalRead(buttonPin) == HIGH) 
  {
  }
  lcd.clear();
}
