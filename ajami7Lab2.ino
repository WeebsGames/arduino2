/*

Areeb Jamili
Lab2 - 3 Bit counter
This code is supposed to allow an arduino with 3 leds and 2 buttons to count to seven in binary through the leds when the buttons are pressed.\
I assumed the buttons in my kit were going to work and the pull up resistor would allow the buttons to work as I thought.
I used the arduino forum to find code for debounce.
https://docs.arduino.cc/built-in-examples/digital/Debounce/ 

*/
const int BITS = 3;

int status1 = LOW;
int status2 = LOW;
int status3 = LOW;
int status[] = {status1, status2, status3};
int pinLED1 = 10;
int pinLED2 = 11;
int pinLED3 = 12;
int buttonUP = 2;
int buttonDOWN = 1;
int buttonUpLast = LOW;
int buttonDownLast = LOW;
int buttonUpState;
int buttonDownState;
int count = 0;
int temp = 0;
unsigned long lastDebounceUp = 0;
unsigned long lastDebounceDown = 0;
unsigned long debounceDelay = 50;
bool buttonDown = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
  pinMode(buttonUP, INPUT);
  pinMode(buttonDOWN, INPUT);


}

void loop() {
  // // put your main code here, to run repeatedly:
  int readingUp = digitalRead(buttonUP);
  int readingDown = digitalRead(buttonDOWN);

  if(readingUp != buttonUpLast){
    //reset countdown timer
    lastDebounceUp = millis();
  } else if(readingDown != buttonDownLast){
    //reset countdown timer
    lastDebounceDown = millis();
  }

  if((millis() - lastDebounceUp) > debounceDelay){
    //passing the if statement means its an actual input and not just noise
    
    //if the button up state has changed
    if(readingUp != buttonUpState){
      buttonUpState = readingUp;
      //count++ if button is pressed and is not at 7
      if(buttonUpState == HIGH && count < 7){
        count++;
      }
    }
  }
  if((millis() - lastDebounceDown) > debounceDelay){
    //if the button down state has changed
    if(readingDown != buttonDownState){
      buttonDownState = readingDown;
      //count-- if button is pressed and is not at 0
      if(buttonDownState == HIGH && count > 0){
        count--;
      }
    }
  }
  
  //use count to turn on/off led lights
  temp = count;
  for(int i = 0; i < BITS; i++){
    status[i] = LOW;
    if(temp%2 == 1){
      //number /2 has a remainder of one so turn on the bit associated with it
      status[i] = HIGH;
    }
    temp = temp/2;
    
  }

  //update board
  digitalWrite(pinLED1, status[0]);
  digitalWrite(pinLED2, status[1]);
  digitalWrite(pinLED3, status[2]);

  //update the last button press
  buttonDownLast = readingDown;
  buttonUpLast = readingUp;
}
