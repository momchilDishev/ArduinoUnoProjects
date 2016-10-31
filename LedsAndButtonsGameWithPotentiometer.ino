byte ledPins[] = {2,3,4,5,6,7};
byte btnStop = 8;
byte btnStart = 9;
byte pin;
byte potPin = A0;
byte formerPin = 0;
byte selectCount = 5;
byte alarm = 11;
const byte win = 3;
byte winCount = 0;
int speedVal = 0;

int buttonState;             
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(potPin));
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  pinMode(ledPins[3], OUTPUT);
  pinMode(ledPins[4], OUTPUT);
  pinMode(ledPins[5], OUTPUT);
  pinMode(btnStop, INPUT);
  pinMode(btnStart, INPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  int reading = digitalRead(btnStart);
  speedVal = analogRead(A0);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        //enter selectMode
        do{
           selectLed();
        }while(selectCount!=0);
        
        //exit selectMode  
        endOfGameSound();
        Serial.println(winCount);
        //new game credits
        selectCount = 5;  
        winCount = 0; 
      }
    }
  }
  lastButtonState = reading;
}

void selectLed(){
  int readingStop = digitalRead(btnStop);
  if (readingStop == HIGH) {
    digitalWrite(pin, HIGH);
    delay(1500);
    //check winnerPin...greens
    if(pin == 5||pin==3){
      Serial.println("RIGHT!");
      winCount++;
    }else{
      Serial.println("WRONG!");
    }
    selectCount--;
  }else{
    randomLeds();
  }
  Serial.println(selectCount);
}

void randomLeds(){
  if(formerPin!=0){
    digitalWrite(formerPin,LOW);
    
  }
  pin = random(2,8);
  digitalWrite(pin, HIGH);
  formerPin = pin;
  delay(speedVal); 
  
}
void endOfGameSound(){
  if(winCount >= win){
    //winner sound
    Serial.println("Congratulations! You have won!");
    analogWrite(alarm,30);
    delay(1500);
    analogWrite(alarm,80);
    delay(1500);
    analogWrite(alarm,170);
    delay(1500);
    analogWrite(alarm,255);
    delay(1500);
    analogWrite(alarm,0);
  }else{
    //loser sound
    Serial.println("Sorry! You have lost!");
    analogWrite(alarm,255);
    delay(1500);
    analogWrite(alarm,170);
    delay(1500);
    analogWrite(alarm,80);
    delay(1500);
    analogWrite(alarm,30);
    delay(1500);
    analogWrite(alarm,0);
  }
}
