using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group ldm;
extern motor_group rdm;
extern motor intake;
extern motor lift;
extern motor tilter;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );