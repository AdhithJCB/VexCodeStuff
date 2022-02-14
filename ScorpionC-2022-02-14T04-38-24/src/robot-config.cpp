#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor ldmMotorA = motor(PORT1, ratio18_1, false);
motor ldmMotorB = motor(PORT8, ratio18_1, false);
motor_group ldm = motor_group(ldmMotorA, ldmMotorB);
motor rdmMotorA = motor(PORT10, ratio18_1, false);
motor rdmMotorB = motor(PORT7, ratio18_1, false);
motor_group rdm = motor_group(rdmMotorA, rdmMotorB);
motor intake = motor(PORT11, ratio18_1, false);
motor lift = motor(PORT21, ratio18_1, false);
motor tilter = motor(PORT12, ratio18_1, false);

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