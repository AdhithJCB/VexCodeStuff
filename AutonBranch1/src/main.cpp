/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LiftGroup            motor_group   2, 9            
// Controller1          controller                    
// LeftDriveMotors      motor_group   1, 11           
// RightDriveMotors     motor_group   10, 12          
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

void preauton(){
  Brain.Screen.print("gaming will initiate soon...");
  Brain.Screen.print("gaming initiated");
  Brain.Screen.clearScreen(color::green);
    vex::task::sleep(500);
}
void autontings(){
  //put the ring in the first mogo
  LiftGroup.spinToPosition(-3.1, rotationUnits::rev, 50, velocityUnits::pct);
  //move back
  RightDriveMotors.spinFor(-1, rotationUnits::rev, 20, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(-1, rotationUnits::rev, 20, velocityUnits::pct);
  //turn towards mid
  RightDriveMotors.spinFor(1, rotationUnits::rev, 50, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(-1, rotationUnits::rev, 50, velocityUnits::pct);
  //rush B
  RightDriveMotors.spinFor(3, rotationUnits::rev, 50, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(3, rotationUnits::rev, 69, velocityUnits::pct);
  LeftDriveMotors.stop();
  RightDriveMotors.stop();
  //lower arm
  LiftGroup.spinToPosition(-4, rotationUnits::rev, 50, velocityUnits::pct);
  //thrust
  
  RightDriveMotors.spinFor(1.3, rotationUnits::rev, 50, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(1.3, rotationUnits::rev, 50, velocityUnits::pct);
  //lift le moogo
  LiftGroup.spinToPosition(-2, rotationUnits::rev, 50, velocityUnits::pct);

  RightDriveMotors.spinFor(-4, rotationUnits::rev, 50, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(-4, rotationUnits::rev, 69, velocityUnits::pct);

  //stop that
  LeftDriveMotors.stop();
  RightDriveMotors.stop();
  
}
int main() {
  vexcodeInit();
  preauton();
  autontings();
  Controller1.Screen.print("YEO GO GO GO !!");
  Controller1.rumble(".-.---");
  }
