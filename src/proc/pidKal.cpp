#include <Arduino.h>
#include "pidKal.h"
#include "settings/pidSet.h"

void pid(Axis &axis) {
	double error, error_diff = 0.0;

	// Calculate error
	error = PID_SETPOINT - axis.degrees;

	// Calculate integral term
	axis.error_sum += error;

	// Calculate derivative term
	error_diff = error - axis.error_last;
	axis.error_last = error;

	// Calculate PID output
	axis.value = Kp * error + Ki * axis.error_sum + Kd * error_diff;
}

void kalman(Axis &axis) {
	double P,K;
	int estimate, temp_estimate;

	// Prediction
	temp_estimate = axis.est_last;
	P = axis.P_last + Q;

	// Update
	K = P / (P + R);
	estimate = temp_estimate + K * (axis.measured_value - temp_estimate);
	P = (1 - K) * P;

	// Update last values
	axis.est_last = estimate;
	axis.P_last = P;
	axis.estimate = estimate;
}

void toDegree(Axis &axis_1, Axis &axis_2) {
  	axis_1.degrees = atan2(axis_1.estimate, axis_2.estimate) * 180 / PI;
}
