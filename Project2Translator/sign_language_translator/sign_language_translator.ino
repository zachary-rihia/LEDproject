// Flex sensor ports
const int FLEX_PIN1 = A1;  
const int FLEX_PIN2 = A2;
const int FLEX_PIN3 = A3; 
const int FLEX_PIN4 = A4; 
const int FLEX_PIN5 = A5; 

// Flex sensor saves analog value
int angle1;
int angle2; 
int angle3; 
int angle4; 
int angle5; 

// Variables used to 
int min = 1023; 
int max = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    flexSetUp();
    sign();
    delay(1000);
}

// Initial setup for the flex sensors
void flexSetUp() 
{
    angle1 = analogRead(FLEX_PIN1);
    angle2 = analogRead(FLEX_PIN2);
    angle3 = analogRead(FLEX_PIN3);
    angle4 = analogRead(FLEX_PIN4);
    angle5 = analogRead(FLEX_PIN5);
  
    // Re-mapping the sensor output
    angle1 = map(angle1, min, max, 0, 90);
    angle2 = map(angle2, min, max, 0, 90);
    angle3 = map(angle3, min, max, 0, 90);
    angle4 = map(angle4, min, max, 0, 90);
    angle5 = map(angle5, min, max, 0, 90);
}

// Prints to the screen or console what is being signed
void talk(String temp)
{
  Serial.println(temp);
}

// Hand sign outputs
void sign() 
{
  if((angle1 <= 5) && (angle2 <= 5) && (angle4 <= 5) && (angle5 <= 5))
  {
    talk("Fuck you");
  }
  if((angle1 <= 5) && (angle3 <= 5) && (angle4 <= 5))
  {
    talk("Animal");
  }
  if((angle1 >= 11) && (angle1 <= 12) && (angle2 >= 8) && (angle2 <= 9)
    && (angle3 >= 14) && (angle3 <= 15) && (angle4 >= 17) && (angle4 <= 18))
  {
    talk("OK");
  }
  if((angle2 <= 5) && (angle3 <= 5) && (angle4 <= 5) && (angle5 <= 5))
  {
    talk("Good job");
  }

}
