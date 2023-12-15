#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

/*
int lF = 8;
int lBt = 7;
int lBb = 6;
int rF = 16;
int rBt = 5;
int rBb = 14;
int cata1Port = 17;
int cata2Port = 9;
Motor leftFront(lF,E_MOTOR_GEARSET_06, true);
Motor leftBackTop(lBt, E_MOTOR_GEARSET_06, false); 
Motor leftBackBottom(lBb, E_MOTOR_GEARSET_06, true);
Motor rightFront(rF, E_MOTOR_GEARSET_06, false);
Motor rightBackTop(rBt, E_MOTOR_GEARSET_06, true);
Motor rightBackBottom(rBb, E_MOTOR_GEARSET_06, false);*/
// Chassis constructor
Drive chassis (
   // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-lF, lBt, -lBb}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{rF,-rBt, rBb}

  // IMU Port
  ,11

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,60/36

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);
void CataControl(void*p) {
  while (true) {
  if (stateOP == 0) {
        if (!cataLimit.get_value()) {
          cata.move(127);
        }
        if (cataLimit.get_value()) {
          cata.brake();
         }
        }
  
  if (stateOP == 1) {
        cata.move(127);
        delay(400);
        stateOP = 0;
        
  }
  else if (stateOP == 2) {
    cata.move(127);
    delay(29000);
    stateOP = 1;
  }
  else if (stateOP == 3) {
    cata.move(127);
    delay(400);
    cata.brake();
  }
  else if (stateOP == 4) {
    cata.brake();
  }
  else {
    stateOP = 0;
  }
  
delay(20);
}
}
bool matchloading;
void fireCata(bool matchloading) {
  if (!matchloading) {
    stateOP = 1;
  }
  else {
    for (int i = 0; i < 47; i++) {
      stateOP = 1;
    }
  }
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  // Print our branding over your terminal :D
  wings.set_value(false);
  clamper.set_value(false);
  cata.set_brake_modes(E_MOTOR_BRAKE_HOLD);
  pros::Task cataCtrl(CataControl);
  //stateOP = 0;
  ez::print_ez_template();
 // cata.move_relative(-250,100);
  
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=[68=]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
  chassis.toggle_modify_curve_with_controller(false); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("skills", skills),
    Auton("simple auton",nearSide),
    Auton("Drive and Turn\n\nSlow down during drive.", drive_and_turn),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
  
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void skillsStart() {
  // SKILLS ONLY
/*
  wings.set_value(true);
  delay(500);
  wings.set_value(false);
  // turn robot
  chassis.set_swing_pid(ez::LEFT_SWING, -80, SWING_SPEED);
  chassis.wait_drive();
  // back up 
  cataInit();
  chassis.set_drive_pid(24,DRIVE_SPEED-25);
  chassis.wait_drive();
  // center robot
  chassis.set_turn_pid(-67,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(12,30);
  delay(500);
*/
}

bool clampState = false;
bool wingState = false;
bool blockerState = false;
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  cata.set_brake_modes(MOTOR_BRAKE_HOLD);
  //wingState = false;
  // skills only
  // /*
 // skillsStart();
  // */
  //wings.set_value(false);
  //intakePistons.set_value(true);

  stateOP = 0;
  while (true) {
    
    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade
    ///*
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)) {
      clampState = !clampState;
			clamper.set_value(clampState);
		}
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
      wingState = !wingState;
      wings.set_value(wingState);
    }
    //*/
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
      stateOP = 1;
    }
    else if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
      stateOP = 2;
    }
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
      blockerState = !blockerState;
      blocker.set_value(blockerState);
      stateOP = 3;
    }
  
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}

