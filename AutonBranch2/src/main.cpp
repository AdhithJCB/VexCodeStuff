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
}
void autontings(){
  //SECOND TILE FROM WALL PUT LEFT WHEEL IN FIRST NOTCH
  RightDriveMotors.spinFor(.35, rotationUnits::rev, 30, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(.35, rotationUnits::rev, 30, velocityUnits::pct);
  //put the ring in the first mogo
  LiftGroup.spinToPosition(-3.1, rotationUnits::rev, 20, velocityUnits::pct);
  //move back
  RightDriveMotors.spinFor(-.8, rotationUnits::rev, 20, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(-.8, rotationUnits::rev, 20, velocityUnits::pct);
  LeftDriveMotors.stop();
  RightDriveMotors.stop();
  //stop drop set em up open up shop
  LiftGroup.spinToPosition(-4, rotationUnits::rev, 50, velocityUnits::pct);
  //run it back but with curve
  RightDriveMotors.spinFor(-.17, rotationUnits::rev, 50, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(.17, rotationUnits::rev, 50, velocityUnits::pct);
  LeftDriveMotors.stop();
  RightDriveMotors.stop();
  LeftDriveMotors.spinFor(1.3, rotationUnits::rev, 69, velocityUnits::pct, false);
  RightDriveMotors.spinFor(1.3, rotationUnits::rev, 50, velocityUnits::pct);
  //LIFTYOURSELF.mp3
  LiftGroup.spinToPosition(-2, rotationUnits::rev, 50, velocityUnits::pct);
  //run it back  pt.2
  RightDriveMotors.spinFor(-.6, rotationUnits::rev, 50, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(-.6, rotationUnits::rev, 50, velocityUnits::pct);
  //turn the other cheek
  RightDriveMotors.spinFor(1.5, rotationUnits::rev, 50, velocityUnits::pct, false);
  LeftDriveMotors.spinFor(-1.5, rotationUnits::rev, 50, velocityUnits::pct);
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
