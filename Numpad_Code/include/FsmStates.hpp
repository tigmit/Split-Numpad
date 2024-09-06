#pragma once
#include "Model.hpp"
#include "debugSettings.hpp"
#include <Arduino.h>

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

static constexpr u_int8_t numMainStates{2};

State **mainFsmSelectPointers[numMainStates] = {&pIdle, &pIdle};

// State *pStateExample; // template for adding new states

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
    delay(1000);           // do stuff
    if (true)              // set next state on some condition
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
//*                            STATE: Idle                              *
//*                                                                         *
//**************************************************************************/

class Idle : public State {
public:
  Idle(State *&stateHandle) { stateHandle = this; }
  //===========> enter
  void enter() override {
#ifdef FSM_PRINTS_ENABLED
    Serial.println(" -> Idle");
#endif
    dspHandler.pushExample();
  }
  //===========> run
  void run() override {
    Serial.println("Running Idle");
    delay(1000); // do stuff
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
  Serial.println(" -> StateExample");
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