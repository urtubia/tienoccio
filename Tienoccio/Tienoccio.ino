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

numvar neopixelFadeOut(void)
{
  neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(255,255,255), 800));
}

/*

The following event handler allows for being able to respond to messages sent to the pinoccio. This is convenient when receiving
directly form the scout leader or remotely from the API.

The following PHP snippet can be used to trigger these messages:

<?php
// The "3" refers to the scout id on your troop that is receiving the message
$r = file_get_contents("https://api.pinocc.io/v1/1/4/command/message.scout(3,20)?token=YOUR_OWN_TOKEN_HERE");
?>

*/

numvar neopixelCustomMessageEventHandler(void)
{
  switch(getarg(2)){
    case 20:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(255,160,80), 200));
      break;
    case 21:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(160,255,160), 200));
      break;
    case 22:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(0,255,0), 200));
      break;
    case 23:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(255,255,255), 200));
      break;
    case 24:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(255,0,255), 200));
      break;
    case 25:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(0,0,255), 200));
      break;
    case 26:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(255,0,0), 200));
      break;
    case 27:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(180,200,40), 200));
      break;
    case 28:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(0,255,80), 200));
      break;
    case 29:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(160,255,80), 200));
      break;
    case 30:
      neoPixelStripAnimator.startAnimation(new FadeOutAnimation(Adafruit_NeoPixel::Color(80,255,80), 200));
      break;
    default:
      neopixelClear();

  }
}

void setup() {
  Scout.setup();
  neoPixelStripAnimator.setup();
  addBitlashFunction("pixels.clear", (bitlash_function)neopixelClear);
  addBitlashFunction("pixels.greenwipe", (bitlash_function)startGreenWipeAnim);
  addBitlashFunction("pixels.bluewipe", (bitlash_function)startBlueWipeAnim);
  addBitlashFunction("pixels.redwipe", (bitlash_function)startRedWipeAnim);
  addBitlashFunction("pixels.nightrider", (bitlash_function)neopixelNightrider);
  addBitlashFunction("pixels.fadeout", (bitlash_function)neopixelFadeOut);
  addBitlashFunction("on.message.scout", (bitlash_function)neopixelCustomMessageEventHandler);
}

void loop() {
  Scout.loop();
  neoPixelStripAnimator.loop();
}

