/**
 * BatteryHandler.hpp
 * brief   : this class handles all the tasks required to handle the battery
 * created : 14.10.2024
 * creator : @tigmit Licence : opensource
 */

#pragma once

#include "debugSettings.hpp"
#include "hardwareDef.hpp"
#include <Arduino.h>
#include <math.h>

class BatteryHandler {
public:
  void init() {
    pinMode(batteryChargeSense, INPUT);
    pinMode(batteryVoltage, INPUT);
    updateBateryHandler();
  }

  bool updateBateryHandler() {
    bool ret = false;

    chargingState = digitalRead(batteryChargeSense);
    if (chargingState != currentchargingState) {
      currentchargingState = chargingState;
      ret = true;
    }

    calculateSOC();
    calculateChargeState();
    if (!chargingState) { // not charging
      if (chargeState < currentChargeState) {
        currentChargeState = chargeState;
        ret = true;
      }
    } else { // charging
      if (chargeState > currentChargeState) {
        currentChargeState = chargeState;
        ret = true;
      }
    }

    // kbd.setBatteryLevel((uint8_t)soc);
    return ret;
  }

  bool isCharging() {
    // returns true if the battery is charging else false
    return digitalRead(batteryChargeSense);
  }

  float getSOC() {
    // returns the estimated state of charge (e.g. 79%)
    return soc;
  }

  float getVoltage() {
    // returns the estimated state of charge (e.g. 79%)
    return voltage;
  }

  bool getAlertStatus() {
    // resturns the charge me alert status
    return alert;
  }

  uint8_t getChargeState() {
    // returns the current chargestate in five steps
    return chargeState;
  }

private:
  void calculateSOC() {
    double average = 0;
    for (int i = 0; i < 20; i++) {
      average += analogRead(batteryVoltage);
    }
    average /= 20;
    voltage = floorf(330 * average / 4095) / 100; // rounded to two decimals
    soc = 100.0 - ((voltage * (-1) + upperVoltage) / rate);
    alert = (soc < 20.0); // if soc below 20% please charge

#ifdef SOC_PRINT
    Serial.print("Raw: ");
    Serial.print(average);
    Serial.print("  SOC: ");
    Serial.println(soc);
#endif
  }

  void calculateChargeState() {
    if (!chargingState) { // not charging right now
      if (soc < 20) {
        chargeState = 4;
        return;
      }
      if (soc < 40) {
        chargeState = 3;
        return;
      }
      if (soc < 60) {
        chargeState = 2;
        return;
      }
      if (soc < 80) {
        chargeState = 1;
        return;
      }
      chargeState = 0;
      return;
    } else { // currently charging
      if (soc > 80) {
        chargeState = 0;
        return;
      }
      if (soc > 60) {
        chargeState = 1;
        return;
      }
      if (soc > 40) {
        chargeState = 2;
        return;
      }
      if (soc > 20) {
        chargeState = 3;
        return;
      }
      chargeState = 4;
      return;
    }
  }

  float voltage = 0.0; // Variable to keep track of LiPo voltage
  int soc = 0;         // Variable to keep track of LiPo state-of-charge (SOC)
  bool alert = false;  // keep track of whether alert has been triggered
  bool chargingState = false;
  bool currentchargingState = true;
  uint8_t chargeState = 0;
  uint8_t currentChargeState = 255; // dangerous.. its out of bounds

  // 50/50 voltage devider bounds
  float upperVoltage = 1.95; // translating to about 4.12V battry voltage
  float lowerVoltage = 1.53; // translating to about 3.30V battry voltage
  float rate = (upperVoltage - lowerVoltage) / 100.0;
};