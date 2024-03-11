// Including Arduino.h is technically redundant since we are using Arduino IDE, but if you would like to convert this project into a larger C or C++ project it will be necessary
#include <Arduino.h>
// Keyboard.h gives us the ability to send key strokes
#include <Keyboard.h>
// FastLED.h gived us the ability to manipulate the RGB LEDs
#include <FastLED.h>

// This pin is wired to the DIN of the first WS2812 LED in the chain
#define LED_PIN 13
// The number of LEDS in the main LED chain
#define NUM_LEDS 4
#define NUMBER_OF_BUTTONS 4

// The pin for the built in WS2812 LED on the Waveshare RP2040-Zero
#define BUILT_IN_LED_PIN 16

// The switch debounce time (in milliseconds)
#define DEBOUNCE_TIME 5

// The RGB color to show when a key is not pressed
#define BUTTON_COLOR CRGB(5, 0, 0)
// The RGB color to show when a key is pressed
#define BUTTON_DOWN_COLOR CRGB(20, 20, 20)

// Pins for buttons
int PINS[] = { 9, 10, 11, 12 };

// Previous state of buttons from last loop
int keys_last[] = { 0, 0, 0, 0 };
// The last time the state of the key was updated (used for calculating debounce time)
unsigned long keys_last_time[] = { 0, 0, 0, 0 };
// The current state of buttons 1 for pressed
int keys[] = { 0, 0, 0, 0 };

// The default keys assigned to the buttons
uint8_t BINDS[] = { '-', '=', '[', ']' };

// The main LED buffer for the buttons
CRGB leds[NUM_LEDS];
// The led buffer for the built in LED
CRGB built_in_led[1];

void onKeyPressed(int);
void onKeyReleased(int);

void setup() {
  // Register the buton LEDs into FastLED
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  // Register the build in LED into FastLED (for some reason we cannot specify GRB because it causes a compilation error, but we don't need it)
  FastLED.addLeds<WS2812, BUILT_IN_LED_PIN>(built_in_led, 1);

  // QMK unfortunately does not allow multiple WS2812 led strings out of the box, but writing our own firmware allows us to use both!

  // Set the initial color of all the LEDs
  fill_solid(leds, NUM_LEDS, BUTTON_COLOR);
  // "Show" (write) the current LED state registered in FastLED (`leds` in this case)
  FastLED.show();

  // Initialize keyboard capabilities
  Serial.begin(9600);
  Keyboard.begin();

  // Set the key input pins to use pullup resistor
  // No matrices here! Each key has its own pin
  for (int i = 0; i < NUMBER_OF_BUTTONS; i++) pinMode(PINS[i], INPUT_PULLUP);
}

// The current millisecond timestamp (used to reduce millis() calls)
unsigned long loopstart;
// The last time the animation was updated
unsigned long animation_timer = millis();

// The loop that continously runs on the microcontroller
void loop() {
  // Get the current time in ms
  loopstart = millis();

  // Update button state
  for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
    keys[i] = !digitalRead(PINS[i]);
    // Only update/change state if it has been >= DEBOUND_TIME ms since the last change for this button
    // Here is a good page for explaining debounce time: https://www.realdigital.org/doc/49c53dbf5b54b73f393d18a87f7c3fe0
    if (keys_last[i] != keys[i] && loopstart - keys_last_time[i] >= DEBOUNCE_TIME) {
      // Check if the key state has changed and call the corrosponding function
      if (keys[i]) {
        onKeyPressed(i);
      } else {
        onKeyReleased(i);
      }
      keys_last[i] = keys[i];
      keys_last_time[i] = loopstart;
    }
  }
  // LED animation "frame" (~60 times per second)
  if (loopstart - animation_timer >= (1000/60)) {
    animation_timer = millis();
    // Fade the build in LEDs brightness
    built_in_led[0] -= CRGB(8, 8, 8);
    FastLED.show();
  }
  // Let the controller rest for a bit
  delay(1);
}

// Called when a key is pressed (debounce is already accounted for)
void onKeyPressed(int key_index) {
  // "Press" the key
  Keyboard.press(BINDS[key_index]);
  // Change the led for the key
  leds[key_index] = BUTTON_DOWN_COLOR;

  // Set the built in led blue (it fades out in the animation loop)
  built_in_led[0] = CRGB(0, 0, 255);

  // Update the LED matrix
  FastLED.show();
}

// Called when a key is release (debounce is already accounted for)
void onKeyReleased(int key_index) {
  // "Release" the key
  Keyboard.release(BINDS[key_index]);
  // Change the led for the key
  leds[key_index] = BUTTON_COLOR;
  // Update the LED matrix
  FastLED.show();
}
