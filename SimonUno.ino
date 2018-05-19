#include "Button.h"
#include "Keyboard.h"
#include "PeizoBuzzer.h"
#include "Led.h"

PeizoBuzzer buzzer(19);

// Setup buttons and its related keyboard
constexpr Button redButton(18, 0);
constexpr Button greenButton(8, 1);
constexpr Button blueButton(6, 2);
constexpr Button yellowButton(4, 3);
const int buttonCount = 4;
constexpr Button buttonList[buttonCount] = {
  redButton, greenButton, blueButton, yellowButton
};

Keyboard keyboard(buttonList, buttonCount);
const Button* buttonLastPressed = NULL;

// Setup LEDs
constexpr Led redButtonLed(13);
constexpr Led greenButtonLed(12);
constexpr Led blueButtonLed(7);
constexpr Led yellowButtonLed(5);
const int ledCount = 4;
constexpr Led ledList[ledCount] = { redButtonLed, greenButtonLed, blueButtonLed, yellowButtonLed };


void setup() {
  // Initialize the serial port so we can see things happening
  Serial.begin(115200);

  // Turn on color output
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  redButtonLed.begin();
  greenButtonLed.begin();
  blueButtonLed.begin();
  yellowButtonLed.begin();

  buzzer.begin();
  keyboard.begin();
}

void loop() {
  keyboard.scan();
  const Button* buttonPressed = keyboard.getButtonPressed();
  if (buttonPressed != buttonLastPressed) {
    if (buttonLastPressed != NULL) {
      Serial.println("Released");
      buzzer.turnOff();
      ledList[buttonLastPressed->getId()].turnOff();
    }
    buttonLastPressed = buttonPressed;
    if (buttonPressed) {
      Serial.print("Button ");
      Serial.print(buttonPressed->getId(), DEC);
      ledList[buttonPressed->getId()].turnOn();
      Serial.print(" Pressed - ");
      buzzer.turnOn();
    }
  }
}

