/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LiftGroup            motor_group   2, 9            
// RingIntakeMotors     motor_group   11, 21          
// RightDriveMotors     motor_group   10, 7           
// LeftDriveMotors      motor_group   1, 8            
// SideLiftMotor        motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace vex;
using std::cout;
using std::string;
using std::vector;
using std::stringstream;

int controlMode = 0;
const vector<string> controlModeTexts = {"Normal", "Point Turn"};
double speedDampener = 2;
bool rob_state = false;
bool should_be_spinning = false;
bool normally_spinning = true;

// Mapping one range to another
double MapRange(const double
 s, const double& a1, const double& a2, const double& b1, const double& b2) 
{
    return b1 + ((s-a1)*(b2-b1))/(a2-a1);
}

// print text to the controller screen
void ControllerPrint(const string& text) 
{
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(text.c_str());
}

// increment the control mode (+1 if we aren't on the last mode, otherwise revert to the first one)
void IncrementControlMode() 
{
  if (controlMode < controlModeTexts.size() - 1) 
    ++controlMode;
  else
    controlMode = 0;

  ControllerPrint(controlModeTexts[controlMode]);

  cout << controlMode;
}

// spin the motor. similar to default spin but with some default parameters
void SpinMotor(motor& motor_to_spin, const double& vel, const directionType& dir = directionType::fwd, const velocityUnits& units = velocityUnits::pct)
{
  motor_to_spin.spin(dir, vel, units);
}


void SpinMotorGroup(motor_group& motor_group_to_spin, const double& vel, const directionType& dir = directionType::fwd, const velocityUnits& units = velocityUnits::pct)
{
  motor_group_to_spin.spin(dir, vel, units);
}

void ChangeShouldBeSpinning() 
{
  if (should_be_spinning == false) 
    should_be_spinning = true;
  else
    should_be_spinning = false;
}

void ChangeDirSpinning()
{
  if (normally_spinning == false) 
    normally_spinning = true;
  else
    normally_spinning = false;
}

double CheckNormallySpinning(double val) 
{
  if (normally_spinning) 
    return val;
  else 
    return -val;  
}

int main() {
  // Initializing Robot Configuration. Keep this
  vexcodeInit();

  /*
  stringstream ss;
  ss << LiftGroup.rotation(rotationUnits::deg);
  string str = ss.str();
  ControllerPrint(str);
  */

  if (normally_spinning) 
    ControllerPrint("Normal mode");
  else
    ControllerPrint("Reverse mode");

  // main loop - runs continuously throughout driving
  while (true) {
    speedDampener = MapRange(Controller1.Axis2.value(), -127, 127, 1.5, .01);

    if (! (Controller1.ButtonUp.pressing() || Controller1.ButtonRight.pressing() || Controller1.ButtonDown.pressing() || Controller1.ButtonLeft.pressing())) {
      switch (controlMode) {
        case 0:
          SpinMotorGroup(LeftDriveMotors, CheckNormallySpinning((Controller1.Axis4.value() + Controller1.Axis3.value()))/speedDampener);
          SpinMotorGroup(RightDriveMotors, CheckNormallySpinning(Controller1.Axis4.value() - Controller1.Axis3.value())/speedDampener);
          break;
        case 1:
          SpinMotorGroup(LeftDriveMotors, CheckNormallySpinning(Controller1.Axis4.value()/speedDampener));
          SpinMotorGroup(RightDriveMotors, CheckNormallySpinning(-(Controller1.Axis4.value()/speedDampener)), directionType::rev);
          break;
        default:
          LeftDriveMotors.stop();
          RightDriveMotors.stop();
      }
    }
    else {
      if (Controller1.ButtonUp.pressing()) {
        SpinMotorGroup(LeftDriveMotors, CheckNormallySpinning(1500));
        SpinMotorGroup(RightDriveMotors, CheckNormallySpinning(1500), directionType::rev);
      }
      else if (Controller1.ButtonRight.pressing()) {
        SpinMotorGroup(LeftDriveMotors, CheckNormallySpinning(1500));
        SpinMotorGroup(RightDriveMotors, CheckNormallySpinning(1500));
      }
      else if (Controller1.ButtonDown.pressing()) {
        SpinMotorGroup(LeftDriveMotors, CheckNormallySpinning(1500), directionType::rev);
        SpinMotorGroup(RightDriveMotors, CheckNormallySpinning(-1500), directionType::rev);
      }
      else if (Controller1.ButtonLeft.pressing()) {
        SpinMotorGroup(LeftDriveMotors, CheckNormallySpinning(1500), directionType::rev);
        SpinMotorGroup(RightDriveMotors, CheckNormallySpinning(1500), directionType::rev);
      }

      else {
        LeftDriveMotors.stop();
        RightDriveMotors.stop();
      }
    }

    task::sleep(20);

    if (Controller1.ButtonX.pressing() && rob_state == false){
      IncrementControlMode();
      rob_state = true;
    }
    else if (!Controller1.ButtonX.pressing()) {
      rob_state = false;
    }

    Controller1.ButtonA.pressed(ChangeShouldBeSpinning);
      
    Controller1.ButtonB.pressed(ChangeDirSpinning);

    if (should_be_spinning) 
      SpinMotorGroup(RingIntakeMotors, 10000000000);
    else
      RingIntakeMotors.stop(brakeType::hold);

    if (Controller1.ButtonR1.pressing()) {
      SpinMotorGroup(LiftGroup, 10000000000);
    }
    else if (Controller1.ButtonR2.pressing())
      SpinMotorGroup(LiftGroup, 10000000000, directionType::rev); 
    else
      LiftGroup.stop(brakeType::hold);

    if (Controller1.ButtonL1.pressing()) {
      SpinMotor(SideLiftMotor, 10);
    }
    else if (Controller1.ButtonL2.pressing())
      SpinMotor(SideLiftMotor, 10, directionType::rev); 
    else
      LiftGroup.stop(brakeType::hold);
  }
  return 0;
}
