#include <Arduino.h>
#include "BasicLinearAlgebra.h"
#include "mpu.h"
// #include "kalman.h"

/**
 * create an MPU6050 object
 * 0x68 is the address of the MPU
 * set gyro to max deg to 1000 deg/sec
 * set accel fs reading to 16g
*/
MPU6050 imu(0x68, 16, 1000);

// raw data from accelerometer
float x_accel, y_accel, z_accel;
float x_est, y_est; // observations

//initialise state estimates
float xh1k=0.0;
float xh2k=0.0;
float xh1k_1=0.0;
float xh2k_1=0.0;

// sampler variables
float fs = 10000.0;
float ts = 1/fs; // sampling interval


// KALMAN FILTER DATA 
using namespace BLA;

// KALMAN data
BLA::Matrix<2,2> F= {1, -ts,
		  0, 1};	// system matrix - state of the system

BLA::Matrix<2,2> Fc = {0,0,0,0}; // closed loop system matrix

BLA::Matrix<2,2> D = {ts, -0.5*ts*ts,
         0, ts};	// process noise covariance

BLA::Matrix<2,2> H;	// observation matrix
BLA::Matrix<2,2> Q; // process noise covariance
BLA::Matrix<2,2> R; // measurement noise covariance
BLA::Matrix<2,2> P; // error covraiance matrix

BLA::Matrix<2,2> K = {0.0955, -0.0055,
			-0.0045, 0.0950};
 // kalman gain

BLA::Matrix<2,2> X_HAT = {0,0,
			0,0}; // state estimates


void setup() {
	Serial.begin(115200);
	imu.init();

	// calculate Fc (closed loop system matrix)
	Fc = F - K;

}

void loop() {
	// get the raw sensor readings
	x_accel = imu.readXAcceleration();
	y_accel = imu.readYAcceleration();

	// KALMAN FILTER HERE
	x_est = x_accel; // s1
	y_est = y_accel; // s2

	// shuffle regressors of the states
	xh1k_1 = xh1k;
	xh2k_1 = xh2k;

	// Ricatti equations for Kalman filtering 
	xh1k = Fc(0)*xh1k_1 + Fc(1)*xh2k_1+K(0)*x_est+K(1)*y_est; // x acceleration estimate
	xh2k = Fc(2)*xh1k_1 + Fc(3)*xh2k_1+K(2)*x_est+K(3)*y_est; // y acceleration estimate

	// debug
	Serial.print(x_accel);Serial.print(",");Serial.println(xh1k);

}