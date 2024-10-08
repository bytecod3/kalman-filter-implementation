#include <Arduino.h>
#include "BasicLinearAlgebra.h"
#include "mpu.h"
#include "kalman.h"

/**
 * create an MPU6050 object
 * 0x68 is the address of the MPU
 * set gyro to max deg to 1000 deg/sec
 * set accel fs reading to 16g
*/
MPU6050 imu(0x68, 16, 1000);

float x_accel, y_accel, z_accel;

struct FilteredValues filt_vals;

void setup() {
	Serial.begin(115200);
	imu.init();
	Serial.println("IMU init OK");
}

void loop() {
	x_accel = imu.readXAcceleration();
	y_accel = imu.readYAcceleration();

	// pass through the kalman filter
	filt_vals = kalmanUpdate(x_accel, y_accel);

	// print the filtered data
	Serial.print(x_accel); Serial.print(",");Serial.print(filt_vals.x_accel_filtered);
	Serial.println();

}