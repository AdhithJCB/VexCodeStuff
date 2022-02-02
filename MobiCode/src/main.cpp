/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LiftGroup            motor_group   2, 9            
// LeftDriveMotors      motor         1               
// RightDriveMotors     motor         10              
// RingIntakeMotors     motor_group   11, 20          
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
//using std::to_string;

// A global instance of vex::brain used for printing to the V5 brain screen

// configure motors

// define your global instances of motors and other devices
// device type, name, device port
int controlMode = 0;
const vector<string> controlModeTexts = {"Normal", "Point Turn", "Drag Turn", "Arc Turn"};
double speedDampener = 2;
bool rob_state = false;

// Mapping one range to another
double MapRange(const double& s, const double& a1, const double& a2, const double& b1, const double& b2) 
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

int main() {
  // Initializing Robot Configuration. Keep this
  vexcodeInit();
  ControllerPrint(controlModeTexts[controlMode]);

  // main loop - runs continuously throughout driving
  while (true) {
    speedDampener = MapRange(Controller1.Axis2.value(), -127, 127, 4, .00001);

    switch (controlMode) {
      case 0:
        SpinMotor(LeftDriveMotors, (Controller1.Axis4.value() + Controller1.Axis3.value())/speedDampener);
        SpinMotor(RightDriveMotors, (Controller1.Axis4.value() - Controller1.Axis3.value())/speedDampener);
        break;
      case 1:
        SpinMotor(LeftDriveMotors, Controller1.Axis4.value()/speedDampener);
        SpinMotor(RightDriveMotors, -(Controller1.Axis4.value()/speedDampener), directionType::rev);
        break;
      case 2:
        if (Controller1.Axis4.value() > 30)
          SpinMotor(LeftDriveMotors, Controller1.Axis4.value()/speedDampener);
        else if (Controller1.Axis4.value() < -30)
          SpinMotor(RightDriveMotors, Controller1.Axis4.value()/speedDampener);
        else {
          LeftDriveMotors.stop();
          RightDriveMotors.stop();
        }

        break;
      case 3:
        SpinMotor(LeftDriveMotors, Controller1.Axis4.value()/speedDampener);
        SpinMotor(RightDriveMotors, -(Controller1.Axis4.value())/(speedDampener*2));
        break;
      default:
        LeftDriveMotors.stop();
        RightDriveMotors.stop();
    }

    task::sleep(20);

    if (Controller1.ButtonX.pressing() && rob_state == false){
      IncrementControlMode();
      rob_state = true;
    }
    else if (!Controller1.ButtonX.pressing()) {
      rob_state = false;
    }

    if (Controller1.ButtonR1.pressing()) {
      SpinMotorGroup(LiftGroup, 10000000000);
      cout << LiftGroup.rotation(rotationUnits::deg) << std::endl;
    }
    else if (Controller1.ButtonR2.pressing())
      SpinMotorGroup(LiftGroup, 10000000000, directionType::rev); 
    else
      LiftGroup.stop(brakeType::hold);

    if (Controller1.ButtonA.pressing()) 
      SpinMotorGroup(LiftGroup, 10000000000);
    else
      RingIntakeMotors.stop(brakeType::hold);

    if (Controller1.ButtonB.pressing()) 
      LiftGroup.rotateTo(1000, rotationUnits::deg, false);
    else
      RingIntakeMotors.stop(brakeType::hold);

    stringstream ss;
    ss << LiftGroup.rotation(rotationUnits::deg);
    string str = ss.str();
  }
  return 0;
}
