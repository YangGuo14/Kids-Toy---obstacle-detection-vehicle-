#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);

//LCD Custom Character
byte rightarrow[] = {B00000,B00100,B00110,B11111,B11111,B00110,B00100,B00000};
byte thumb1[] = {B00100,B00011,B00100,B00011,B00100,B00011,B00010,B00001};
byte thumb2[] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00011};
byte thumb3[] = {B00000,B00000,B00000,B00000,B00000,B00000,B00001,B11110};
byte thumb4[] = {B00000,B01100,B10010,B10010,B10001,B01000,B11110,B00000};
byte thumb5[] = {B00010,B00010,B00010,B00010,B00010,B01110,B10000,B00000};
byte thumb6[] = {B00000,B00000,B00000,B00000,B00000,B10000,B01000,B00110};

int userInput = 0;      //input from buttons
int led1 = 2;           //LED 1
int led2 = 3;           //LED 2
int led3 = 4;           //LED 3
int led4 = 5;           //LED 4
int buzzer = 6;        //buzzer

boolean started = false;    //Has the game started yet
boolean gameover = false;   //Has the game ended
int level = 0;              //What level is the user on (Score = current level -1, for example, you failed
                            //level 2, so your score is "1")

int gameMode = 0;           //Which game mode is being used
                            // 1 = Repeat: It will repeat previous tone and generate a new random tone.
                            // 2 = Random: each tone in every level are totally random.
boolean soundEnabled = true;  //Is the buzzer enabled or not
                            
int lastLevelSeq[50];        //The sequence for the steps used in progressive mode previous level
                             //Also used to replay correct sequence back when you press wrong button

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16,2); // set up the LCD 16x2
  lcd.createChar(0, rightarrow);
  lcd.createChar(2, thumb1);
  lcd.createChar(3, thumb2);
  lcd.createChar(4, thumb3);
  lcd.createChar(5, thumb4);
  lcd.createChar(6, thumb5);
  lcd.createChar(7, thumb6);
  lcd.home();
  delay(100);
  lcd.clear();
  lcd.print("ECE 387-KidsToy");
  lcd.setCursor(0,1);
  lcd.print("Melodic Memory");
  delay(3000);
  for (int i = 0; i < 14; i++)
    {
    lcd.scrollDisplayLeft();
    delay(300);
    }
  lcd.clear();
  lcd.print("Get Ready To");
  lcd.setCursor(0,1);
  lcd.print("Train Your Brain");
  for (int i = 1; i<7; i++)
  {
    playTone(i);    //Play each tone we used in this game
  }
}
  
  void loop()
  {
  lcd.clear();
  lcd.print("PRESS ANY BUTTON");
  lcd.setCursor(0,1);
  lcd.print("Button4");
  lcd.setCursor(8,1);
  lcd.write(byte(0));
  lcd.setCursor(9,1);
  lcd.print("Button1");
    while (started == false)
    {
      if (checkButtonPressed() > 0)
      {
        playTone(5);
        started=true;
      }
    }
    
    //Clear the previous game Last Level Steps
    for (int s=0; s < 50; s++)
    {
      lastLevelSeq[s] = 0;
    }
    
     delay(500);
     
     // Select Game Mode Here
     lcd.clear();
     lcd.print("1:Repeat");
     
     while (gameMode == 0)
    {
     lcd.setCursor(0,1);
     lcd.print("2:Random 4:Sound");
     
      switch (checkButtonPressed())
      {
      case 1:
        if (soundEnabled)
        {
          playTone(5);
        }
        gameMode = 1;
        lcd.clear();
        lcd.print("Repeat");
        lcd.setCursor(0,1);
        lcd.print("Mode Selected");
        break;
       
      case 2:
        if (soundEnabled)
        {
          playTone(5);
        }
        
        gameMode = 2;
        lcd.clear();
        lcd.print("Random");
        lcd.setCursor(0,1);
        lcd.print("Mode Selected");
        break;
      
      case 4:
        soundEnabled = (!soundEnabled);
        lcd.setCursor(0,1);
        
        if (soundEnabled)
        {
          lcd.print("Sound Mode: ON  "); 
          playTone(5);          
        }
        else
        {
         lcd.print("Sound Mode: OFF "); 
        }
        delay(1000);
        break;  
      }
    }    
    
    delay(1000);
    
     //Set start level
     level =1;
     
    while (gameover == false)
    {
      if (doLevel(level)==true)
        {
          //Level Correct, increment Level and repeat
          lcd.clear();
          lcd.print("LEVEL: "); lcd.print(level);
          lcd.setCursor(0,1);
          lcd.print("Completed!"); 
          lcd.setCursor(12,1);
          lcd.write(2);
          lcd.setCursor(12,0);
          lcd.write(3);
          lcd.setCursor(13,1);
          lcd.write(4);
          lcd.setCursor(13,0);
          lcd.write(5);
          lcd.setCursor(14,1);
          lcd.write(6);
          lcd.setCursor(14,0);
          lcd.write(7);
          
          
          if (soundEnabled)
          {
            //play level correct sound
            for (int i =0; i < 3; i++)
            {
              playTone(5);
              delay(50);
            }
          }
          else
          {
            delay(125);
          }
          delay(1000);    // Delay so user can see level completed message
          level++;        // To next level
        } 
       else
      {
       // set game over
       gameover = true;
      }  
    }
    
    if (gameover == true)
    {
      lcd.clear();
      lcd.print("WRONG! ");
      lcd.setCursor(0,1);
      lcd.print("SCORE: "); lcd.print(level-1);
      
      if (soundEnabled)
      {
        for (int i = 0; i < 5; i++)
        {
          playTone(6);
          delay(50);
        }
      }
      else
      {
        delay(125);
      }
    }
        
      //Playback the correct sequence
      lcd.clear();
      lcd.print("Right Sequence");
      lcd.setCursor(0,1);
      lcd.print("should be");
      delay(500);
      for(int s=0; s < level; s++)
      {
        playStep(lastLevelSeq[s]);
      }

      lcd.clear();
      lcd.print("Your Score: "); lcd.print(level-1);
      lcd.setCursor(0,1);
      lcd.print("PRESS ANY BUTTON");
      
      while (gameover == true)
      {
       if (checkButtonPressed() > 0)
        {
        level = 0;
        
        if (soundEnabled)
        {
          playTone(5);
        }
        gameover = false;
        started = false;
        gameMode = 0;
        }        
      }     
    }
  
   /*
    Check which button has been pressed
  */  
  int checkButtonPressed()
  {
    int userValue = 0;      // What is the pushbutton resistor matrix value
    userValue = analogRead(userInput);
    
    int buttonPressed = 0;
      
    if (userValue > 850)
    {
      buttonPressed = 0;      //No Button Pressed
    }
    if (userValue < 850)
    { 
      buttonPressed = 4;      // Button 4 still to check others
    }
    if (userValue < 800)
    {
      buttonPressed = 3;      // Button 3 still to check others
    }
    if (userValue < 700)
    {
      buttonPressed = 2;      // Button 2 still to check last one
    }
    if (userValue < 600)
    {
      buttonPressed = 1;      
    }
    return buttonPressed;  
  }
  
  /*
  This will light the led, play the tone, switch off the led 
  */
  void playStep(int number)
  {
    lightLed(number);
    if (soundEnabled)
    {
      playTone(number);
    }
    else
    {
      delay(100);
    }
    delay(250);
    lightLed(0);
  }
  
  
  /*
  Light the Relevant LED
  */
  void lightLed(int led)
  {
    switch (led)
    {
    case 0:
      digitalWrite(led1,LOW);          //Set all the LEDs off
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      delay(50);                      
      break;
    case 1:
      digitalWrite(led1,HIGH);        //LED 1 on
      break;
    case 2:
      digitalWrite(led2,HIGH);        //LED 2 on
      break;
    case 3:
      digitalWrite(led3,HIGH);        //LED 3 on
      break;
    case 4:
      digitalWrite(led4,HIGH);        //LED 4 on
      break;
    }
  }
 
  /*
  Play the tones for the game
  param tone = which tone to play
  tone 1 to 4 are the button tones
  tone 5 is level correct tone / start tone (any button pressed)
  tone 6 is level wrong and game over tone
  */
  void playTone(int tone)
  {
      int tones[6] = { 1000, 1250, 1500, 1750, 500, 3000}; 
      for (long i = 0; i < 125; i++)
      {
        //generate a square wave
        digitalWrite(buzzer, HIGH);
        delayMicroseconds(tones[tone-1]);
        digitalWrite(buzzer, LOW);
        delayMicroseconds(tones[tone-1]);
      }
  }

/* 
Return TRUE if success or FALSE if fail
*/
boolean doLevel(int level)
{
  int steps[level];                //Which steps
  int userStep = 0;                //Which button has pressed
  int userLength =0;               //How many steps has the user entered
  boolean levelPass = false;       //Level was won or lost  
  boolean inProgress = true;       //Level currently running
    
  //Tell player game start and should notice the LEDs
  lcd.clear();
  lcd.print("Arduino Turn");
  lcd.setCursor(0,1);
  lcd.print("Pay Attention");
  delay(1000);                    //Add a delay
  
  //Seed the random number generator
  randomSeed(analogRead(0) + analogRead(1) + analogRead(2)+ analogRead(3)+analogRead(4)+analogRead(5));
  
  
  if (gameMode == 1)
  {
     //Progressive 
     //Get last level
     for (int s=0; s < level; s++)
     {
       if (level > 1)
       {
         // Can only copy if higher than level 1
         steps[s] = lastLevelSeq[s];
       }
       //Add new step
       steps[level-1] = (int)random(1,5);
     }
  }
  if (gameMode == 2)
  {
     //Random
    for (int s=0; s < level; s++)
    {
      steps[s] = (int)random(1,5);
    }
  }
  
     //Back to last level for next time and gameOver
     for (int s=0; s < level; s++)
     {
       lastLevelSeq[s] = steps[s];
     }
  
  //Play the steps
  for (int s=0; s < level; s++)
  {
    playStep(steps[s]);
  }
  
  //Display user turn message
  lcd.clear();
  lcd.print("LEVEL: "); lcd.print(level);
  lcd.setCursor(0,1);
  lcd.print("Your Turn Hurry!");
  
  while (inProgress)
  {
    //Get the user input  
   userStep = checkButtonPressed();
   if (userStep >0)
   {
     userLength++;
     playStep(userStep);
   
     //Check the user input against the sequence
     if (steps[userLength-1] == userStep)
     {
       //Correct button pressed, check if sequence still to complete
       if (userLength ==level)
       {
         //finished the sequence
         inProgress = false;
         levelPass = true;
       }
     }
     else
     {
       //wrong button pressed
       inProgress = false;
       levelPass = false;
     }
    }
  }
  return levelPass;
}
