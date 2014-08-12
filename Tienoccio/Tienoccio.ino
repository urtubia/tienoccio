#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>
#include <Adafruit_NeoPixel.h>
#include <NeoPixelStripAnimator.h>

#define PIN 6


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);

NeoPixelStripAnimator neoPixelStripAnimator(&strip);

numvar startRedWipeAnim()
{
  neoPixelStripAnimator.startAnimation(new ColorWipeAnimation(Adafruit_NeoPixel::Color(255, 0, 0), 300));
}

numvar startGreenWipeAnim(void)
{
  neoPixelStripAnimator.startAnimation(new ColorWipeAnimation(Adafruit_NeoPixel::Color(0, 255, 0), 300));
}

numvar startBlueWipeAnim()
{
  neoPixelStripAnimator.startAnimation(new ColorWipeAnimation(Adafruit_NeoPixel::Color(0, 0, 255), 300));
}

numvar neopixelClear(void)
{
  neoPixelStripAnimator.clear();
}

numvar neopixelNightrider(void)
{
  neoPixelStripAnimator.startAnimation(new NightRiderAnimation(Adafruit_NeoPixel::Color(255,0,0), 70));
}

void setup() {
  Scout.setup();
  neoPixelStripAnimator.setup();
  addBitlashFunction("pixels.clear", (bitlash_function)neopixelClear);
  addBitlashFunction("pixels.greenwipe", (bitlash_function)startGreenWipeAnim);
  addBitlashFunction("pixels.bluewipe", (bitlash_function)startBlueWipeAnim);
  addBitlashFunction("pixels.redwipe", (bitlash_function)startRedWipeAnim);
  addBitlashFunction("pixels.nightrider", (bitlash_function)neopixelNightrider);
}

void loop() {
  Scout.loop();
  neoPixelStripAnimator.loop();
}

