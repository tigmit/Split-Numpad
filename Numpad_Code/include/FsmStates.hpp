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
//*                            STATE: StartUp                              *
//*                                                                         *
//**************************************************************************/

class StartUp : public State {
public:
  StartUp(State *&stateHandle) { stateHandle = this; }
  //===========> enter
  void enter() override {
#ifdef FSM_PRINTS_ENABLED
    Serial.println(" -> StartUp");
#endif
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
    Serial.print(" StartUp ->");
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
    Serial.println(" Idle");
#endif
    rgbHandler.pushSingleRGB(0, 0, CRGB::Green);
    dspHandler.setCursor(5, 10, 2);
    dspHandler.clear();
    dspHandler << "welcome\n to\n  NEKOPAD";
    dspHandler.push();
    delay(1000);
    dspHandler.pushBitmap(testCatFlipOFF, LOGO_WIDTH, LOGO_HEIGHT, 0, 0);
    delay(1500);
    dspHandler.clear();
    dspHandler.push();
  }
  //===========> run
  void run() override { // TODO: it works but this is so fucking ugly...
    switch (encHandler.updateMainMenueSelect()) {
    case 0:
      dspHandler.clear();
      dspHandler.pushBitmap(batteryWARNING, BatteryIconWidth, BatteryIconHeight,
                            10, 10);
      break;
    case 1:
      dspHandler.clear();
      dspHandler.pushBitmap(battery25Percent, BatteryIconWidth,
                            BatteryIconHeight, 10, 10);
      break;
    case 2:
      dspHandler.clear();
      dspHandler.pushBitmap(battery50Percent, BatteryIconWidth,
                            BatteryIconHeight, 10, 10);
      break;
    case 3:
      dspHandler.clear();
      dspHandler.pushBitmap(battery75Percent, BatteryIconWidth,
                            BatteryIconHeight, 10, 10);
      break;
    case 4:
      dspHandler.clear();
      dspHandler.pushBitmap(battery100Percent, BatteryIconWidth,
                            BatteryIconHeight, 10, 10);
      break;

    default:
      dspHandler.setCursor(1, 1, 1);
      dspHandler.clear();
      dspHandler << "fucked. out of bounds";
      dspHandler.push();
      break;
    }
    dspHandler.PushLine(0, 21, 128, false);
  }
  //===========> exit
  void exit() override {
#ifdef FSM_PRINTS_ENABLED
    Serial.print(" Idle ->");
#endif
  }
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
  Serial.println(" StateExample");
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
  Serial.print(" StateExample ->");
#endif
  }
} stateExample(pStateExample); //instanciate and pass stateHandle
*/