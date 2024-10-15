#pragma once
#include "Model.hpp"
#include "bmp/allBmp.hpp"
#include "debugSettings.hpp"
#include <Arduino.h>

using namespace Model;
//***************************************************************************
//*                                                                         *
//*                           BASE STATE Interface                          *
//*                                                                         *
//**************************************************************************/
class State {
public:
  // virtual
  virtual ~State() = default;

  // interface methods
  virtual void enter() = 0; // Called when entering the state
  virtual void run() = 0;   // Called repeatedly while in the state
  virtual void exit() = 0;  // Called when exiting the state

  // base methods

  // we must reset this -> nextState_
  // otherwise the state will run only once upon entering it a second time
  State *nextState() {
    if (nextState_ != this) {
      State *nextStateBuff = nextState_;
      nextState_ = this;
      return nextStateBuff;
    }
    return this;
  }

protected:
  // set the next state
  void setNextState(State *setState) { nextState_ = setState; }

  // state buffer
  State *nextState_ = this;
};

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                              STATE HANDLES                              //
//                               (pre define)                              //
/////////////////////////////////////////////////////////////////////////////

State *pStartUp;
State *pIdle; // -0
// State *pStateExample; // template for adding new states

static constexpr u_int8_t numMainStates{2};

State **mainFsmSelectPointers[numMainStates] = {&pIdle, &pIdle};

//***************************************************************************
//*                                                                         *
//*                            STATE: StartUp                               *
//*                                                                         *
//**************************************************************************/

class StartUp : public State {
public:
  StartUp(State *&stateHandle) { stateHandle = this; }
  //===========> enter
  void enter() override {
#ifdef FSM_PRINTS_ENABLED
    Serial.println("Boot -> StartUp");
#endif
    rgbHandler.pushSingleRGB(0, 0, CRGB::Green);
    dspHandler.setCursor(5, 10, 2);
    dspHandler.clear();
    dspHandler << "welcome\n to\n  NEKOPAD :3";
    dspHandler.push();
    delay(1000);
    dspHandler.pushBitmap(testCatFlipOFF, LOGO_WIDTH, LOGO_HEIGHT, 20, 0);
    delay(1500);
    dspHandler.clear();
    dspHandler.push();
  }
  //===========> run
  void run() override {
    Serial.println("Running StartUp");
    delay(1000);         // do stuff
    setNextState(pIdle); // kick off transition
  }
  //===========> exit
  void exit() override {
#ifdef FSM_PRINTS_ENABLED
    Serial.print("StartUp -> ");
#endif
  }
} stateExample(pStartUp); // instanciate and pass stateHandle

//***************************************************************************
//*                                                                         *
//*                            STATE: Idle                                  *
//*                                                                         *
//**************************************************************************/

class Idle : public State {
public:
  Idle(State *&stateHandle) { stateHandle = this; }
  //===========> enter
  void enter() override {
#ifdef FSM_PRINTS_ENABLED
    Serial.println("Idle");
    resetIcons();
    dspHandler.clear(true);
#endif
  }
  //===========> run
  void run() override {
    updateBattery();
    dspHandler.PushLine(0, 21, 128, false);

    if (firstRun) {
      firstRun = false;
    }
  }
  //===========> exit
  void exit() override {
#ifdef FSM_PRINTS_ENABLED
    Serial.print("Idle -> ");
#endif
  }

private:
  //===========> State Vareables

  bool firstRun = true;

  void updateBattery(u_int8_t x = 10, uint8_t y = 10) {
    if (batteryHandler.updateBateryHandler() || firstRun) {
      dspHandler.pushBitmap(batteryStates[batteryHandler.getChargeState()],
                            BatteryIconWidth, BatteryIconHeight, x, y, true);
      if (batteryHandler.isCharging()) {
        dspHandler.pushBitmap(batteryCharging, BatteryChargingIconWidth,
                              BatteryChargingIconHeight, x + BatteryIconWidth,
                              y, false);
      }
    }
  }

  void resetIcons() { firstRun = true; }
} Idle(pIdle); // instanciate and pass stateHandle

//***************************************************************************
//*                                                                         *
//*                            STATE: TEMPLATE                              *
//*                                                                         *
//**************************************************************************/
/*
class StateExample : public State {
public:
  StateExample(State *&stateHandle) { stateHandle = this; }
  //===========> enter
  void enter() override {
#ifdef FSM_PRINTS_ENABLED
  Serial.println("StateExample");
#endif
  }
  //===========> run
  void run() override {
    Serial.println("Running StateExample");
    delay(1000); // do stuff
    if (true)    // set next state on some condition
      setNextState(pNextExampleState); // kick off transition
  }
  //===========> exit
  void exit() override {
#ifdef FSM_PRINTS_ENABLED
  Serial.print("StateExample -> ");
#endif
  }
} stateExample(pStateExample); //instanciate and pass stateHandle
*/