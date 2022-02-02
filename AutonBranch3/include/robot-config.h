using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor_group LiftGroup;
extern controller Controller1;
extern motor_group LeftDriveMotors;
extern motor_group RightDriveMotors;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );