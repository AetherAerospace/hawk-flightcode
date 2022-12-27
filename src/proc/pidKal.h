// axis struct
struct Axis {
  int16_t measured_value;
  double estimate;
  double degrees;
  double value;
  double est_last = 0.0;
  double P_last  = 0.0;
  double error_last  = 0.0;
  double error_sum = 0.0;
};

// functions
void pid(Axis &axis);
void kalman(Axis &axis);
void toDegree(Axis &axis_1, Axis &axis_2);
