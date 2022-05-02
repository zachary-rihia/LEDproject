int value; // the value of the pressure sensor
int score; // holds the users score
int level;

// RGB LED colours
const int RedPin = 5;
const int GreenPin = 4;
const int BluePin = 3;
const int piezo = 12;
const int firstTwelve = 6;
const int secondTwelve = 7;
const int thirdTwelve = 8;
const int fourthTwelve = 9;
const int newGame = 10;

/*  RickRollCode

    LINK: https://create.arduino.cc/projecthub/410027/rickroll-piezo-buzzer-a1cd11?ref=part&ref_id=8233&offset=3
    
    AUTHOR: Rowan Packard
    rowanpackard@gmail.com

    DISCLAIMER: The song "Never Gonna Give You Up" by Rick Astley
    is not the creative property of the author. This code simply
    plays a Piezo buzzer rendition of the song.
*/

#define  a3f    208     // 208 Hz
#define  b3f    233     // 233 Hz
#define  b3     247     // 247 Hz
#define  c4     261     // 261 Hz MIDDLE C
#define  c4s    277     // 277 Hz
#define  e4f    311     // 311 Hz    
#define  f4     349     // 349 Hz 
#define  a4f    415     // 415 Hz  
#define  b4f    466     // 466 Hz 
#define  b4     493     // 493 Hz 
#define  c5     523     // 523 Hz 
#define  c5s    554     // 554 Hz
#define  e5f    622     // 622 Hz  
#define  f5     698     // 698 Hz 
#define  f5s    740     // 740 Hz
#define  a5f    831     // 831 Hz 

#define rest    -1

int led = LED_BUILTIN; 

volatile int beatlength = 100; // determines tempo
float beatseparationconstant = 0.3;

int threshold;

int a; // part index
int b; // song index

// Parts 4 or 6 (Chorus)

int song1_chorus_melody[] =
{ b4f, b4f, a4f, a4f,
  f5, f5, e5f, b4f, b4f, a4f, a4f, e5f, e5f, c5s, c5, b4f,
  c5s, c5s, c5s, c5s,
  c5s, e5f, c5, b4f, a4f, a4f, a4f, e5f, c5s,
  b4f, b4f, a4f, a4f,
  f5, f5, e5f, b4f, b4f, a4f, a4f, a5f, c5, c5s, c5, b4f,
  c5s, c5s, c5s, c5s,
  c5s, e5f, c5, b4f, a4f, rest, a4f, e5f, c5s, rest
};

int song1_chorus_rhythmn[] =
{ 1, 1, 1, 1,
  3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
  1, 1, 1, 1,
  3, 3, 3, 1, 2, 2, 2, 4, 8,
  1, 1, 1, 1,
  3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
  1, 1, 1, 1,
  3, 3, 3, 1, 2, 2, 2, 4, 8, 4
};

void setup() {
  // My code
  Serial.begin(9600);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(firstTwelve, OUTPUT);
  pinMode(secondTwelve, OUTPUT);
  pinMode(thirdTwelve, OUTPUT);
  pinMode(fourthTwelve, OUTPUT);
  pinMode(newGame, OUTPUT);
  score = 0;
  level = 0;
  // Song code
  a = 4;
  b = 0;
}

void loop() {
  impact();
  // Is in the loop otherwise it does not play
  if (level >= 8) {
    magenta();
    endGame();
  }
}

// checks for the impact that happens on the 
void impact() {
  value = analogRead(A0); // to see what values are displayed when pressed or hit
  // it constantly spits out either 18 or 9 but can still read it as 1
  // I have no clue why the number defaults to 9
  if (value > 1) {
    green();
    userScore();
    // For some reason always starts and 9 in the console
     Serial.print(value + Serial.write(" value = "));
     Serial.print(score + Serial.write(" score = "));
     Serial.print(level + Serial.write(" level = "));
  }
  else {
    red();
  }
}

// Holds the users score and increases the level based on the amount of points the player has
void userScore() {
  score++;
  if ((score % 12) == 0) {
    level++;
  }
  if (level == 1) {
    digitalWrite(firstTwelve, HIGH);
    digitalWrite(secondTwelve, LOW);
    digitalWrite(thirdTwelve, LOW);
    digitalWrite(fourthTwelve, LOW);
  }
  if (level == 2) {
    digitalWrite(firstTwelve, LOW);
    digitalWrite(secondTwelve, HIGH);
    digitalWrite(thirdTwelve, LOW);
    digitalWrite(fourthTwelve, LOW);
  }
  if (level == 3) {
    digitalWrite(firstTwelve, LOW);
    digitalWrite(secondTwelve, LOW);
    digitalWrite(thirdTwelve, HIGH);
    digitalWrite(fourthTwelve, LOW);
  }
  if (level == 4) {
    digitalWrite(firstTwelve, LOW);
    digitalWrite(secondTwelve, LOW);
    digitalWrite(thirdTwelve, LOW);
    digitalWrite(fourthTwelve, HIGH);
  }
  if (level == 5) {
    digitalWrite(firstTwelve, HIGH);
    digitalWrite(secondTwelve, HIGH);
    digitalWrite(thirdTwelve, LOW);
    digitalWrite(fourthTwelve, LOW);
  }
  if (level == 6) {
    digitalWrite(firstTwelve, HIGH);
    digitalWrite(secondTwelve, HIGH);
    digitalWrite(thirdTwelve, HIGH);
    digitalWrite(fourthTwelve, LOW);
  }
  if (level == 7) {
    digitalWrite(firstTwelve, HIGH);
    digitalWrite(secondTwelve, HIGH);
    digitalWrite(thirdTwelve, HIGH);
    digitalWrite(fourthTwelve, HIGH);
  }
}

// Plays the song once the game has ended
void endGame() {
  int notelength;
  if (a == 4 || a == 6) {
    // chorus
    notelength = beatlength * song1_chorus_rhythmn[b];
    if (song1_chorus_melody[b] > 0) {
      tone(piezo, song1_chorus_melody[b], notelength);
    }
    b++;
    if (b >= sizeof(song1_chorus_melody) / sizeof(int)) {
      a++;
      b = 0;
    }
  }
  delay(notelength);
  noTone(piezo);
  delay(notelength * beatseparationconstant);
}

// Got the rest of the code from https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
// In otherwords its code from the book

void red () {
  //set the LED pins to values that make red
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}
void orange () {
  //set the LED pins to values that make orange
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 50);
  analogWrite(BluePin, 0);
}
void yellow () {
  //set the LED pins to values that make yellow
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
void green () {
  //set the LED pins to values that make green
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
void cyan () {
  //set the LED pins to values that make cyan
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 100);
}
void blue () {
  //set the LED pins to values that make blue
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 100);
}
void magenta () {
  //set the LED pins to values that make magenta
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 100);
}
