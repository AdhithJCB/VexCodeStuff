// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ldm                  motor_group   1, 8            
// rdm                  motor_group   10, 7           
// intake               motor         11              
// lift                 motor         21              
// tilter               motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition;

const int MAX_DELAY = 3000; // Give up resetting sensors after this

const int DELAY = 10; // Loop delay (ms)

const int THRES = 5; // When joystick val is += this, set motors to 0
const int TILT_IN = -20; // Tilter In Pos
const int TILT_OUT = -315; // Tilter Out Pos 

/*
Setting Motors (millivolts) - advantage in squeezing a bit more power out of motors
Range from -12000 mV to 12000 mV (-12v to 12v)
scale (-100, 100) to (-12000, 12000)
*/

const int VSCALE = 120;
void set_dt(double left, double right) {
  ldm.spin(directionType::fwd, left * VSCALE, voltageUnits::mV);
  rdm.spin(directionType::fwd, right * VSCALE, voltageUnits::mV);
}

void set_intake(double inp) {
  intake.spin(directionType::fwd, inp * VSCALE, voltageUnits::mV);
}

void set_lift(double inp) {
  lift.spin(directionType::fwd, inp * VSCALE, voltageUnits::mV);
}

void set_tilter(double inp) {
  tilter.spin(directionType::fwd, inp * VSCALE, voltageUnits::mV);
}

// Brake
void brake_dt() {
  ldm.setStopping(brakeType::hold);
  rdm.setStopping(brakeType::hold);
}

// Coast (stop applying power, allow idle spin)
void coast_dt() {
  ldm.setStopping(brakeType::coast);
  rdm.setStopping(brakeType::coast);
}

/*
Reset sensors
- Get all sensors to start in a consistent place
- STOP once the mechanism attached to the motor has hit a hardstop
*/
void reset_sensors() {
  bool running = true;
  bool lift_reset = false;
  bool tilter_reset = false;

  bool last_lift = false;
  bool last_tilter = false;

  // if timeout exceeds MAX_DELAY, we will stop trying to reset positions
  int timeout = 0;

  set_lift(-40);
  set_tilter(40);

  wait(250, msec);

  while (running) {
    last_lift = lift_reset;
    last_tilter = tilter_reset;

    if (lift.velocity(percentUnits::pct) == 0) {
      set_lift(0);
      lift_reset = true;
      lift.resetPosition(); // reset motor encoder to 0
    }

    if (tilter.velocity(percentUnits::pct) == 0) {
      set_tilter(0);
      tilter_reset = true;
      tilter.resetPosition();
    }

    if (lift_reset && tilter_reset) {
      running = false;
    }

    if (last_lift != lift_reset || last_tilter != tilter_reset) 
      timeout = 0;
    else {
      timeout += DELAY;

      if (timeout > MAX_DELAY) 
        running = false;
    }

    wait(DELAY, msec);
  }

  // Stop motors
  set_lift(0);
  set_tilter(0);

  // Reset anything that didn't zero
  if (!lift_reset)
    lift.resetPosition();
  if (!tilter_reset)
    tilter.resetPosition();
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  reset_sensors();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void turn(int direction) {
  set_dt(80*direction, -80*direction);
  wait(400, msec);
  set_dt(0, 0);
}

bool auton_done = false;

// autonomous code - WIP
void autonomous(void) {
  /*
  brake_dt();

  int exit = 0;
  while (exit<1000) {
    exit += DELAY;
    if (abs(get_mogo())>abs(MOGO_OUT-100)) {
      if (mogo.velocity(pct)==0) 
        set_mogo(0);
      else 
        set_mogo(20);
     }
     else {
      set_mogo(127);
     }
     wait(DELAY_TIME, msec);
  }
  exit=0;
  set_tilter_position(TILTER_OUT, 100);
  
  set_tank(-127, -127);
  wait(500, msec);
  set_tank(0, 0);
  wait(500, msec);

  bool is_upp = false;
  while (exit<1000) {
    exit+=DELAY_TIME;
      if (abs(get_mogo())<150) {
        if (mogo.velocity(pct)==0) {
          is_upp = true;
          set_mogo(0);
        }
        else {
          set_mogo(is_upp?0:-20);
        }
      }
      else {
        is_upp = false;
        set_mogo(-127);
      }
    wait(DELAY_TIME, msec);
  } 
  exit=0;
  is_upp = true; 

  set_conveyor(127);
  set_intake(127);
  wait(1500, msec);
  set_conveyor(0);
  set_intake(0);

  turn_90(-1);
  wait(300, msec);

  set_tank(-127,-127);
  wait(400, msec);

  turn_90(1);
  wait(300, msec);


  set_tank(80, 80);
  wait(500, msec);
  set_tank(0, 0);

  while (exit<1000) {
    exit+=DELAY_TIME;
    if (abs(get_mogo())>abs(MOGO_OUT-100)) {
      if (mogo.velocity(pct)==0) 
        set_mogo(0);
      else 
        set_mogo(20);
     }
     else {
      set_mogo(127);
     }
     wait(DELAY_TIME, msec);
  }

  auton_done = true;
  */
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  // Parameters for user control
  bool mogo_up;
  bool neut = 0;
  int mogo_lock = 0;
  bool is_up = true;
  int mogo_timer = 0;

  bool tilter_up;
  bool tilter_lock = 0;

  if (did_auto_finish) {
    mogo_up = false;
    tilter_up = false;
  }

  int intake_conveyor_speed = 0;

  //checks if pre_auton ran and if did not run pre_auto
  while(WAS_RESET_SUCCESS == false){
    wait(10, msec);
  }

  coast_drive();

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    
    ///
    // Joysticks
    ///

    // Ternary operator (one line if statement) for controller deadzone
    // int x = some condition   ?   x is this if condition was true   :   x is this if condition was false;
    int l_joy = abs(Controller1.Axis3.value())>THRESH ? Controller1.Axis3.value() : 0;
    int r_joy = abs(Controller1.Axis2.value())>THRESH ? Controller1.Axis2.value() : 0;
    set_tank(l_joy, r_joy);
    


    ///
    // Mogo
    //  - mogo has two positions, pressing L1 toggles it between them
    ///

    // Flip boolean when button is pressed
    if (Controller1.ButtonL1.pressing() && mogo_lock==0) {
      if (neut) {
        mogo_up = false;
      } else {
        mogo_up = !mogo_up;
      }
      neut = false;
      mogo_lock = 1;
      // mogo_lock makes it so this if statement only runs once when the button is pressed
      // if this lock didn't exist, while the button is pressed, mogo_up would spam between
      // true and false, causing the mechanism to jitter
    } 
    else if (Controller1.ButtonL1.pressing()) {
      if (mogo_up) {
        mogo_timer+=DELAY_TIME;
        if (mogo_timer>=300) {
          neut = true;
        }
      }

    }
    else if (!Controller1.ButtonL1.pressing()) {
      mogo_lock = 0;
      mogo_timer = 0;
    }

    // Have the motor go to a position depending on boolean state.
    // This runs the motor at full power until the velocity of the motor is 0.
    // when the velocity is 0, we know the subsystem has reached a hardstop.
    // then it sets the motor to a low amount of power to stop it from overheating
    if (neut) {
      set_mogo_position(MOGO_NEUT, 100);
    }
    else if (mogo_up) {
      if (abs(get_mogo())<150) {
        if (mogo.velocity(pct)==0) {
          is_up = true;
          set_mogo(0);
        }
        else {
          set_mogo(is_up?0:-20);
        }
      }
      else {
        is_up = false;
        set_mogo(-127);
      }
    }
    else if (!mogo_up) {
      if (abs(get_mogo())>abs(MOGO_OUT-100)) {
        if (mogo.velocity(pct)==0) 
          set_mogo(0);
        else 
          set_mogo(20);
      }
      else {
        set_mogo(127);
      }
    }



    ///
    // Tilter
    //  - tilter has two positions, pressing L2 toggles it between them
    ///
    // Flip boolean when button is pressed
    if (Controller1.ButtonL2.pressing() && tilter_lock==0) {
      tilter_up = !tilter_up;
      tilter_lock = 1;
      // tilter_lock makes it so this if statement only runs once when the button is pressed
      // if this lock didn't exist, while the button is pressed, tilter_up would spam between
      // true and false, causing the mechanism to jitter
    } 
    else if (!Controller1.ButtonL2.pressing()) {
      tilter_lock = 0;
    }

    // Have the motor go to a position depending on boolean state
    if (tilter_up) 
      set_tilter_position(TILTER_IN, 100);
    else 
      set_tilter_position(TILTER_OUT, 100);



    ///
    // Intake and Conveyor
    ///
    if (Controller1.ButtonR1.pressing()) {
      intake_conveyor_speed =  127;
    }
    else if (Controller1.ButtonR2.pressing()) {
      intake_conveyor_speed = -127;
    }
    else {
      intake_conveyor_speed =  0;
    }
    set_intake  (intake_conveyor_speed);
    set_conveyor(intake_conveyor_speed);

    wait(DELAY_TIME, msec); // Don't hog the CPU!
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
