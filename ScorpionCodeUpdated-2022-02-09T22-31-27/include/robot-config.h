using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group LiftGroup;
extern motor_group RingIntakeMotors;
extern motor_group RightDriveMotors;
extern motor_group LeftDriveMotors;
extern motor SideLiftMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );