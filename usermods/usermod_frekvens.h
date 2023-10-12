#pragma once

#include "wled.h"

#include <Frekvens.h>

// Create the library.
Frekvens frekvens;

class UsermodFrekvens : public Usermod {
  private:
    unsigned long lastTime;

  public:
    void setup() {
      // Settings, e.g. pinouts, need to be made before call to Init.
      // See Frekvens.hpp for possible settings.
      frekvens.SetMOSI(23);
      frekvens.SetSCK(18);
      frekvens.SetLAK(5);
      frekvens.SetEN(22);
      frekvens.Init();
    }

    void loop() {
      if (WLED_CONNECTED && !offMode)
      {
        unsigned long ellapsedTime = millis() - lastTime;
        if (ellapsedTime > 100u) {
          for (uint8_t y = 0; y < 16; y++) {
            for (uint8_t x = 0; x < 16; x++)
            {
              uint32_t newColor = strip.getPixelColorXY(x, y);
              frekvens.SetPixel(x, y, R(newColor >> 1) % 127u );
            }
          }
          lastTime = millis();
        }
      }
      else
      {
        frekvens.Clear();
      }

      frekvens.Update();
    }
};