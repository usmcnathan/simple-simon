
// buttons / input
int buttonPin[4] = {2,3,4,5};
// Pins / output 
int LEDPins[4] = {6,7,8,9};
// Stages
int LEDSeq[32];

void setup()
{
  //setting up your input buttons and pins
  for(int i = 0; i < 4; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
    pinMode(buttonPin[i], INPUT);
    
  }//set randomizer
  randomSeed(analogRead(A0));
}


void loop()
  {
  bool Lose = false;
  
  //generate random sequence 
  for (int i =0; i < 32; i++)
    {
     LEDSeq[i] = random(4);
    
    }
  //lets play
  for (int Level =0; Level < 32; Level++)
  {
    //show lights
    for(int i = 0; i < Level; i++)
    {
      digitalWrite(LEDPins[LEDSeq[i]], HIGH);
      delay(750);
      digitalWrite(LEDPins[LEDSeq[i]], LOW);
      delay(750);
    }
    //wait for response
    
  for (int i = 0; i < Level; i++)
    {
      int button = -1;
      
      while (button < 0)
      {
        button = buttonPressed();
      }
      digitalWrite(LEDPins[button], HIGH);
      delay(250);
      digitalWrite(LEDPins[button], LOW);
      delay(250);
      
      if (LEDSeq[i] !=button)
      {
        Lose = true;
        break;
      }
    }
       // win or lose seq
    if (Lose == true)
    {
     loseSeq();
      break;
    }
    else if (Lose == false && Level == 31)
    {
      winSeq();    
    }
  }
}
       
// win sequence
void winSeq()
{
 for (int i = 0; i < 32; i++)
 {
   for (int x = 0; x < 4; x++)
   {
     digitalWrite(LEDPins[x], HIGH);
   }
   
    delay(750);
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(LEDPins[j], LOW);
    }
    delay(750);  
  }
}
//lose sequence
void loseSeq()
{
  for (int i = 0; i < 4; i++)
      {
      digitalWrite(LEDPins[i], HIGH);
   }
     delay(750);

     for (int i = 0; i < 4; i++)
      {
      digitalWrite(LEDPins[i], LOW);
      delay(750);
      }
}

// tells what button is pressed
bool isPressed(int switchNum)
  { 
    bool pressed = false;
    if(digitalRead(buttonPin[switchNum]) == HIGH)
  {
  //de-bounce
    delay(10);
  
    
    while(digitalRead(buttonPin[switchNum]) == HIGH){}
    delay(10);
    pressed = true;
    }
    return pressed;
}
// button pressed function
int buttonPressed()
{ 
    int switchNum = -1;
    for(int i = 0; i < 4; i++)
    {
    if(isPressed(i) == true)
    {
        switchNum = i;
    }
    }
  
    return switchNum;
  
}
