#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  this->Kp = Kp_;
  this->Kd = Kd_;
  this->Ki = Ki_;

  p_error = 0;
  i_error = 0;
  d_error = 0;
  err = 0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
  
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  // if (steps > 100){
  //   steps = 0;
  // } else
  // {
  //   steps += 1;
  //   err += p_error*p_error;
  // }
  best_err = Kp*p_error + Kd*d_error + Ki*i_error;
  return   best_err;// TODO: Add your total error calc here!
}

void PID::CoeffFinder(){
  /**
   * Update parameter using twiddle concept
   * New error based on new param
   * Update error for 100 steps
   * */
  if (best_err == 0) {
    best_err = p_error*p_error;
    return;
  }else
  {
    for(int i=0;i<3;i++){
      p[i] += dp[i];
      err = p_error*p_error;

      if (err > best_err){
        best_err = err;
        dp[i] *= 1.1;
      }else
      {
        p[i] -= 2*dp[i];

        if (err < best_err){
          best_err = err;
          dp[i] *= 1.1;
        }else {
          p[i] += dp[i];
          dp[i] *= 0.9;
        }
      }
      
    }

    this->Kp = p[0];
    this->Kd = p[1];
    this->Kd = p[2];
  }
}