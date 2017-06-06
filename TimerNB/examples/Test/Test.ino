
//=================== Rough stepper tests =============================
/******************************************************
    Template for superloop
*******************************************************/
//
// =====  Includes ====================
// e.g. /#include <Servo.h>

#include <TimerNB.h>

// ===== Global decarations =============
// --- Objects from libraries ------
// e.g. Servo MyServo;

//--------- Global variables -----------
// e.g. float gfInitialTemperature;



// --- Constants -----------
// e.g. const float fPi = 3.1415926 ;
const float fFilter = 0.2;
const float fFilterDash = 1 - fFilter ;


// MOtor speed
const unsigned long MotorStepInterval_A_ = 3.7e3;  //  uS
const unsigned long MotorStepInterval_B_ = 2.7e3;  //  uS

// ---- I/O pins ------------------
// e.g. const int oRedLED = 2;
 const int oDebug = 6;
  const int oMotor_A_1 = A0;
  const int oMotor_A_2 = A1;
  const int oMotor_A_3 = A2;
  const int oMotor_A_4 = A3;

  const int oMotor_B_1 = 5;
  const int oMotor_B_2 = 4;
  const int oMotor_B_3 = 3;
  const int oMotor_B_4 = 2;


//// ---- Definitions for inline classes --------------
//// This section must be before anything is referenced. In a library it's the .h file

//============== the setup function runs once when you press reset or power the board ============
void setup() {
  Serial.begin(256000);
  Serial.println("hellooo World");
  // initialize I/O pins
  pinMode(oMotor_A_1, OUTPUT);
  pinMode(oMotor_A_2, OUTPUT);
  pinMode(oMotor_A_3, OUTPUT);
  pinMode(oMotor_A_4, OUTPUT);

  pinMode(oMotor_B_1, OUTPUT);
  pinMode(oMotor_B_2, OUTPUT);
  pinMode(oMotor_B_3, OUTPUT);
  pinMode(oMotor_B_4, OUTPUT);

  pinMode(oDebug, OUTPUT);
}

//================  the loop function runs over and over again forever ==================
void loop() {
 digitalWrite(oDebug, 1);
  MotorStep_A_();
 digitalWrite(oDebug, 0);
  MotorStep_B_();
}
// ----------------  Rough and ready, duplicate copies of the motor driver. Eventually this will be a proper class with 2 instances

// The stepper is a very simple state machine. It relies on the non-blocking TestElapsedMicros()
void MotorStep_A_() {
  static unsigned long Timer;
  static byte State = 0 ;
  if (TestElapsedMicros_NB(MotorStepInterval_A_, &Timer)) {
    switch (State) {
      case 0:
        motorWrite_A_(0, 1, 0, 0);
        State = 1;
        break;
      case 1:
        motorWrite_A_(0, 0, 1, 0);
        State = 2;
        break;
      case 2:
        motorWrite_A_(0, 0, 0, 1);
        State = 3;
        break;
      case 3:
        motorWrite_A_(1, 0, 0, 0);
        State = 0;
        break;

    }
  }
}

void motorWrite_A_(boolean w1, boolean w2, boolean w3, boolean w4 ) {
  digitalWrite(oMotor_A_1, w1); digitalWrite(oMotor_A_2, w2); digitalWrite(oMotor_A_3, w3); digitalWrite(oMotor_A_4, w4);
}




void MotorStep_B_() {
  static unsigned long Timer;
  static byte State = 0 ;
  if (TestElapsedMicros_NB(MotorStepInterval_B_, &Timer)) {
    switch (State) {
      case 0:
        motorWrite_B_(0, 1, 0, 0);
        State = 1;
        break;
      case 1:
        motorWrite_B_(0, 0, 1, 0);
        State = 2;
        break;
      case 2:
        motorWrite_B_(0, 0, 0, 1);
        State = 3;
        break;
      case 3:
        motorWrite_B_(1, 0, 0, 0);
        State = 0;
        break;

    }
  }
}

void motorWrite_B_(boolean w1, boolean w2, boolean w3, boolean w4 ) {
//  digitalWrite(oMotor_B_1, 0); digitalWrite(oMotor_B_2, 0); digitalWrite(oMotor_B_3, 0); digitalWrite(oMotor_B_4, 0);
  digitalWrite(oMotor_B_1, w1); digitalWrite(oMotor_B_2, w2); digitalWrite(oMotor_B_3, w3); digitalWrite(oMotor_B_4, w4);
}





//
///* General purpose elapsed time function, microseconds
//************************************************************
//    Call with:
//      IntervalMicros  The IntervalMicros elapsed time in uS
//       NextMicro  Pointer to an unsigned long, which is the caller's private time marker,
//
//    Return true if IntervalMicros uS have passed, alter NextMicro to the new point in time.
//
//  My first version of this did not advance the IntervalMicros, so it had cumulative error.
//  In a 20kHz square wave test program that one produced 16.6kHz when the correct frequency was 20kHz
//  (measured 19.998kHz on 'scope)
//*/
//boolean TestElapsedMicros(unsigned long IntervalMicros, unsigned long *NextMicro)
//{
//  if (micros() - *NextMicro >= IntervalMicros) {
//    *NextMicro = *NextMicro + IntervalMicros;
//    return true ;
//  }
//  else {
//    return false;
//  }
//}



