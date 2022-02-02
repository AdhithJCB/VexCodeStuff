#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LiftGroupMotorA = motor(PORT2, ratio18_1, true);
motor LiftGroupMotorB = motor(PORT9, ratio18_1, false);
motor_group LiftGroup = motor_group(LiftGroupMotorA, LiftGroupMotorB);
controller Controller1 = controller(primary);
motor LeftDriveMotorsMotorA = motor(PORT1, ratio18_1, false);
motor LeftDriveMotorsMotorB = motor(PORT11, ratio18_1, false);
motor_group LeftDriveMotors = motor_group(LeftDriveMotorsMotorA, LeftDriveMotorsMotorB);
motor RightDriveMotorsMotorA = motor(PORT10, ratio18_1, true);
motor RightDriveMotorsMotorB = motor(PORT12, ratio18_1, true);
motor_group RightDriveMotors = motor_group(RightDriveMotorsMotorA, RightDriveMotorsMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}