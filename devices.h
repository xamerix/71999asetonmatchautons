#pragma once
#include "main.h"
using namespace pros;
extern int lF;
extern int lBt;
extern int lBb;
extern int rF;
extern int rBt;
extern int rBb;
extern int stateOP;
extern Motor leftFront;
extern Motor leftBackTop; 
extern Motor leftBackBottom;
extern Motor rightFront;
extern Motor rightBackTop;
extern Motor rightBackBottom;
extern Motor cataMotor1;
extern Motor cataMotor2;
extern MotorGroup cata;
extern Rotation cataRotate;
extern ADIDigitalOut clamper;
extern ADIDigitalOut wings;
extern ADIDigitalOut blocker;
extern ADIDigitalIn cataLimit;