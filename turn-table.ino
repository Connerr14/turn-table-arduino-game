const int ledPins[] = {2, 8, 7, 6, 5, 4, 3};  // Pin numbers for 7 LEDs
const int button = 9;
int buttonState = 1;
int currentLedOn = -1;

void setup() {
      // Generate random number
   randomSeed(analogRead(A0));

  pinMode(button, INPUT);

    // Initialize all the LED pins as OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
    // Get the button state
    buttonState = digitalRead(button);
      
    if (buttonState == HIGH) 
    {
      getRandomLed();
      delay(500);

    }
}

void getRandomLed() 
{
  int randomNumber = 0;

  while (randomNumber == 0 || randomNumber == 1 || randomNumber + currentLedOn == 7)
  {
     randomNumber = random(0, 7);
  }

  Serial.println("Current LED: " + String(currentLedOn));
  Serial.println("Random Number " + String(randomNumber));

  // if the random number is smaller than the currentLedOn, an overflow must be made
  if ((currentLedOn + randomNumber) >= 7) 
  {
    // Finish blinking the last index's in the array
    for (int i = currentLedOn ; i<7; i++) {
      delay(300);
      digitalWrite(ledPins[i], HIGH);
      delay(300);
      digitalWrite(ledPins[i], LOW);
    }

    // get the difference between the random number and the end of the array, to calculate how many moves we have made
    int difference1 = 7 - currentLedOn;

    // Calculate how many more moves we have to make
    int difference2 = (randomNumber - difference1);

    // Now we are back at the start of the array, we will make the rest of the moves
    for (int i = 0; i<difference2; i++) {
      delay(300);
      digitalWrite(ledPins[i], HIGH);
      delay(300);
      digitalWrite(ledPins[i], LOW);
    }
    // Turn the LED chosen on
    digitalWrite(ledPins[difference2], HIGH);
    currentLedOn = difference2;
  }
  // The random number is larger than the current one but smaller than the array size;
  else 
  {
    for (int i = currentLedOn; i<=(randomNumber + currentLedOn); i++)
    {
      delay(300);
      digitalWrite(ledPins[i], HIGH);
      delay(300);
      digitalWrite(ledPins[i], LOW);
    }
    // Turn the LED chosen on
    digitalWrite(ledPins[randomNumber + currentLedOn], HIGH);
    currentLedOn = randomNumber + currentLedOn;
  }
}
