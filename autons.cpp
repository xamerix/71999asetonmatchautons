#include "main.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void CataControlA(int num) {
  stateOP = num;
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
    delay(26500);
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
  
}


///
// Turn Example
///

double inches;
double inches1;
double theta;
int speed;
double toCem(double inches) {
  return inches*2.54;
}
void drive(double inches1, int speed) {
  chassis.set_drive_pid(toCem(inches1), speed);
  chassis.wait_drive();
}
void turn(double theta, int speed) {
  chassis.set_turn_pid(theta,speed);
  chassis.wait_drive();
}
void skills() {
  
  clamper.set_value(true);
  chassis.set_turn_pid(45,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(18),DRIVE_SPEED);
  chassis.wait_drive();
  
  chassis.set_turn_pid(0,TURN_SPEED);
  clamper.set_value(false);
  delay(300);
  chassis.wait_drive();  
  chassis.set_drive_pid(toCem(9),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-5),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING,108,SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(5),DRIVE_SPEED);
  chassis.wait_drive();
  CataControlA(2);
  chassis.set_turn_pid(46,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-14.5),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-49),90);
  chassis.wait_drive();
  chassis.set_turn_pid(0,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(15),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(80,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(15),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-50,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(22),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-15),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-70,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(22),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-15),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-70,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(22),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-18),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90,TURN_SPEED);
  chassis.wait_drive();
  wings.set_value(true);
  chassis.set_drive_pid(toCem(-22),DRIVE_SPEED);
  chassis.wait_drive();

      /*
  chassis.set_turn_pid(90,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-25),DRIVE_SPEED);
  chassis.wait_drive();

  /*
  chassis.set_turn_pid(90,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(135,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-13),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(180,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-9),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(5),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-100,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-47),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(110,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-26),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(24),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(110,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-26),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(24),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(120,DRIVE_SPEED);
  wings.set_value(true);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-26),DRIVE_SPEED);
  chassis.wait_drive();
  //-9
*/

  /*
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING,-53,SWING_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING,-63,SWING_SPEED);
  chassis.wait_drive();
  /**  
  delay(150);
  chassis.set_drive_pid(24,DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-5),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING,100,SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(6),DRIVE_SPEED);
  chassis.wait_drive();
  fireCataA(true);
*/
  
} 



///
// Combining Turn + Drive
///
void drive_and_turn(){
  //far 
  clamper.set_value(true);
  drive(13,DRIVE_SPEED);
  turn(35,TURN_SPEED);
  drive(20,DRIVE_SPEED);
  turn(-90,TURN_SPEED);
  clamper.set_value(false);
  delay(400);
  drive(16,DRIVE_SPEED);
  //delay?
  drive(-12,DRIVE_SPEED);
  turn(0,TURN_SPEED);
  clamper.set_value(true);
  delay(400);
  turn(-90,TURN_SPEED);
  clamper.set_value(false);
  delay(400);
  drive(12,DRIVE_SPEED);
  drive(-19,DRIVE_SPEED);

  
  

}



///
// Wait Until and Changing Max Speed
///
 
void nearSide() {
  chassis.set_turn_pid(0,TURN_SPEED);
  chassis.wait_drive();
  clamper.set_value(true);
  chassis.set_turn_pid(-45,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(16),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING,0,SWING_SPEED);
  chassis.wait_drive();
  clamper.set_value(false);
  delay(400);
  chassis.set_drive_pid(toCem(6),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-7),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(7),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-6),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-45,TURN_SPEED);
  chassis.wait_drive();
  wings.set_value(true);
  delay(100);
  chassis.set_drive_pid(toCem(-8),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING,-70,SWING_SPEED);
  chassis.wait_drive();
  wings.set_value(false);
  chassis.set_drive_pid(toCem(-30),DRIVE_SPEED);
  chassis.wait_drive();
  wings.set_value(true);


  
/*
  chassis.set_drive_pid(toCem(-16),DRIVE_SPEED);
  chassis.wait_drive();
  wings.set_value(false);
  chassis.set_turn_pid(-75,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-24),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,TURN_SPEED);
  chassis.wait_drive();
  wings.set_value(true);
  chassis.set_turn_pid(-95,TURN_SPEED);
  chassis.wait_drive();


  /*
 // drive(18,DRIVE_SPEED);
  chassis.set_drive_pid(toCem(18),DRIVE_SPEED);
  chassis.wait_drive();
 // turn(35,TURN_SPEED);
  chassis.set_turn_pid(35,TURN_SPEED);
  chassis.wait_drive();
  //drive(20,DRIVE_SPEED);
  chassis.set_drive_pid(toCem(20),DRIVE_SPEED);
  chassis.wait_drive();
 // turn(-90,TURN_SPEED);
  chassis.set_turn_pid(-90,TURN_SPEED);
  chassis.wait_drive();
  clamper.set_value(false);
  delay(400);
  //drive(17,DRIVE_SPEED);
  chassis.set_drive_pid(toCem(17),DRIVE_SPEED);
  chassis.wait_drive();
  //delay?
  //drive(-24,DRIVE_SPEED);
  chassis.set_drive_pid(toCem(-24),DRIVE_SPEED);
  chassis.wait_drive();
  wings.set_value(false);
 // drive(4,DRIVE_SPEED);
  chassis.set_drive_pid(toCem(4),DRIVE_SPEED);
  chassis.wait_drive();
  //turn(0,TURN_SPEED);
  chassis.set_turn_pid(0,TURN_SPEED);
  chassis.wait_drive();
  //drive(-19,DRIVE_SPEED);
  chassis.set_drive_pid(toCem(-19),DRIVE_SPEED);
  chassis.wait_drive();
  wings.set_value(true);
 // turn(20,TURN_SPEED);
  chassis.set_turn_pid(20,TURN_SPEED);
  chassis.wait_drive();
  */
}
void rightSide() {
  
  //chassis.heading
}



///
// Swing Example
///
void farSide() {
  //far side!
  clamper.set_value(true);
  chassis.set_swing_pid(ez::RIGHT_SWING,-15,SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(34),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90,TURN_SPEED);
  chassis.wait_drive();
  clamper.set_value(false);
  chassis.set_drive_pid(toCem(11),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-5),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-68,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(14.25),DRIVE_SPEED);
  chassis.wait_drive();
  clamper.set_value(true);
  delay(240);
  chassis.set_turn_pid(90,TURN_SPEED);
  chassis.wait_drive();
  clamper.set_value(false);
  chassis.set_drive_pid(toCem(18.5),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING,45,SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-25),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(-6),DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(toCem(2),DRIVE_SPEED);
  chassis.wait_drive();
  wings.set_value(true);
  chassis.set_turn_pid(-30,TURN_SPEED);
  chassis.wait_drive();

  


  
  
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .