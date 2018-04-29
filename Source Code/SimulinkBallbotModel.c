/*
 * File: SimulinkBallbotModel.c
 *
 * Code generated for Simulink model 'SimulinkBallbotModel'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Sat Apr 28 17:57:18 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "SimulinkBallbotModel.h"

/* Block signals and states (auto storage) */
DW rtDW;

/* Model step function */
void SimulinkBallbotModel_custom(boolean_T arg_flag_firstcycle, real32_T
  arg_gyro_x_offset, real32_T arg_gyro_y_offset, real32_T arg_motor_x_offset,
  real32_T arg_motor_y_offset, uint16_T *arg_gyro_y, uint16_T *arg_gyro_x,
  int32_T *arg_phi_m_y, int32_T *arg_phi_m_x, real32_T *arg_Battery, int8_T
  *arg_pwm_x, int8_T *arg_pwm_y)
{
  real32_T rtb_Inverter;
  real32_T rtb_Switch_k;
  real32_T rtb_Gain_m;
  real32_T rtb_Sum_n3;
  boolean_T rtb_RelationalOperator;
  real32_T rtb_Switch_j;
  real32_T rtb_Switch_c;
  real32_T rtb_Switch_n;
  real32_T rtb_Switch;
  real32_T tmp[5];
  int16_T i;

  /* Gain: '<S7>/Inverter' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion5'
   *  Gain: '<S16>/1-a_gd'
   *  Gain: '<S16>/a_gd'
   *  Inport: '<Root>/gyro_x'
   *  Inport: '<Root>/gyro_x_offset'
   *  Sum: '<S16>/Sum'
   *  Sum: '<S7>/Sum'
   */
  rtb_Inverter = -((real32_T)*arg_gyro_x - (0.999F * arg_gyro_x_offset + 0.001F *
    (real32_T)*arg_gyro_x));

  /* Outputs for Atomic SubSystem: '<S7>/Discrete Integrator Theta X' */
  /* Switch: '<S15>/Switch' incorporates:
   *  Constant: '<S15>/Constant'
   *  Delay: '<S15>/Delay'
   *  Inport: '<Root>/flag_firstcycle'
   */
  if (arg_flag_firstcycle) {
    rtb_Switch_k = 0.0F;
  } else {
    rtb_Switch_k = rtDW.Delay_DSTATE_l;
  }

  /* End of Switch: '<S15>/Switch' */

  /* Update for Delay: '<S15>/Delay' incorporates:
   *  Gain: '<S15>/Gain'
   *  Sum: '<S15>/Sum'
   */
  rtDW.Delay_DSTATE_l = 0.004F * rtb_Inverter + rtb_Switch_k;

  /* End of Outputs for SubSystem: '<S7>/Discrete Integrator Theta X' */

  /* Sum: '<S12>/Sum' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion4'
   *  Delay: '<S12>/Delay'
   *  Gain: '<S12>/Gain'
   *  Gain: '<S12>/Gain1'
   *  Gain: '<S1>/Invert'
   *  Gain: '<S3>/Gain1'
   *  Inport: '<Root>/motor_x_offset'
   *  Inport: '<Root>/phi_m_x'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Sum_n3 = (real32_T)(uint8_T)((uint16_T)(uint8_T)-(real32_T)*arg_phi_m_x -
    (uint8_T)arg_motor_x_offset) * 0.0174532924F * 0.2F + 0.8F *
    rtDW.Delay_DSTATE;

  /* Outputs for Atomic SubSystem: '<S3>/Discrete Integrator  Int Phi X' */
  /* Outputs for Atomic SubSystem: '<S3>/Discrete Derivative  Phi X' */
  /* Switch: '<S8>/Switch' incorporates:
   *  Constant: '<S10>/Constant'
   *  Delay: '<S10>/Delay'
   *  Delay: '<S8>/Delay'
   *  Inport: '<Root>/flag_firstcycle'
   *  Switch: '<S10>/Switch'
   */
  if (arg_flag_firstcycle) {
    rtb_Switch_j = rtb_Sum_n3;
    rtb_Switch_c = 0.0F;
  } else {
    rtb_Switch_j = rtDW.Delay_DSTATE_bo;
    rtb_Switch_c = rtDW.Delay_DSTATE_p;
  }

  /* End of Switch: '<S8>/Switch' */
  /* End of Outputs for SubSystem: '<S3>/Discrete Integrator  Int Phi X' */

  /* Update for Delay: '<S8>/Delay' */
  rtDW.Delay_DSTATE_bo = rtb_Sum_n3;

  /* End of Outputs for SubSystem: '<S3>/Discrete Derivative  Phi X' */

  /* Sum: '<S18>/Sum' incorporates:
   *  Delay: '<S18>/Delay'
   *  Gain: '<S18>/1-a_gyro'
   *  Gain: '<S18>/a_gyro'
   */
  rtb_Inverter = 0.75F * rtb_Inverter + 0.25F * rtDW.Delay_DSTATE_j;

  /* Outputs for Atomic SubSystem: '<S3>/Discrete Integrator  Int Phi X' */
  /* Update for Delay: '<S10>/Delay' incorporates:
   *  Delay: '<S1>/Delay'
   *  Gain: '<S10>/Gain'
   *  Product: '<S3>/Product'
   *  Sum: '<S10>/Sum'
   */
  rtDW.Delay_DSTATE_p = 0.004F * (rtDW.Delay_DSTATE_o[0] ? rtb_Sum_n3 : 0.0F) +
    rtb_Switch_c;

  /* End of Outputs for SubSystem: '<S3>/Discrete Integrator  Int Phi X' */

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Gain'
   *  Inport: '<Root>/Battery'
   */
  rtb_Gain_m = 0.001089F * *arg_Battery - 0.625F;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtGainInport1' incorporates:
   *  Gain: '<S7>/deg2rad'
   *  Gain: '<S7>/deg2rad2'
   *  Gain: '<S8>/Gain'
   *  Sum: '<S8>/Sum'
   */
  tmp[0] = 0.0174532924F * rtb_Switch_k;
  tmp[1] = rtb_Sum_n3;
  tmp[2] = 0.0174532924F * rtb_Inverter;

  /* Outputs for Atomic SubSystem: '<S3>/Discrete Derivative  Phi X' */
  tmp[3] = (rtb_Sum_n3 - rtb_Switch_j) * 250.0F;

  /* End of Outputs for SubSystem: '<S3>/Discrete Derivative  Phi X' */
  tmp[4] = rtb_Switch_c;

  /* Gain: '<S1>/Gain' */
  rtb_Switch_c = 0.0F;
  for (i = 0; i < 5; i++) {
    rtb_Switch_c += rtConstP.pooled12[i] * tmp[i];
  }

  /* Gain: '<S2>/Gain3' incorporates:
   *  Gain: '<S1>/Gain'
   *  Product: '<S2>/Divide'
   */
  rtb_Switch_c = rtb_Switch_c / rtb_Gain_m * 100.0F;

  /* Saturate: '<S2>/Saturation1' */
  if (rtb_Switch_c > 100.0F) {
    rtb_Switch_k = 100.0F;
  } else if (rtb_Switch_c < -100.0F) {
    rtb_Switch_k = -100.0F;
  } else {
    rtb_Switch_k = rtb_Switch_c;
  }

  /* End of Saturate: '<S2>/Saturation1' */

  /* Outport: '<Root>/pwm_x' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion2'
   *  Gain: '<S2>/Gain1'
   */
  *arg_pwm_x = (int8_T)-rtb_Switch_k;

  /* Abs: '<S2>/Abs2' */
  rtb_Switch_k = fabsf(rtb_Switch_k);

  /* Abs: '<S2>/Abs' */
  rtb_Switch_c = fabsf(rtb_Switch_c);

  /* RelationalOperator: '<S2>/Relational Operator' */
  rtb_RelationalOperator = (rtb_Switch_c <= rtb_Switch_k);

  /* Sum: '<S7>/Sum1' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion6'
   *  Gain: '<S17>/1-a_gd'
   *  Gain: '<S17>/a_gd'
   *  Inport: '<Root>/gyro_y'
   *  Inport: '<Root>/gyro_y_offset'
   *  Sum: '<S17>/Sum'
   */
  rtb_Switch_j = (real32_T)*arg_gyro_y - ((real32_T)(uint8_T)(0.999F *
    arg_gyro_y_offset) + 0.001F * (real32_T)*arg_gyro_y);

  /* Outputs for Atomic SubSystem: '<S7>/Discrete Integrator  Theta Y' */
  /* Switch: '<S14>/Switch' incorporates:
   *  Constant: '<S14>/Constant'
   *  Delay: '<S14>/Delay'
   *  Inport: '<Root>/flag_firstcycle'
   */
  if (arg_flag_firstcycle) {
    rtb_Switch_c = 0.0F;
  } else {
    rtb_Switch_c = rtDW.Delay_DSTATE_pb;
  }

  /* End of Switch: '<S14>/Switch' */

  /* Update for Delay: '<S14>/Delay' incorporates:
   *  Gain: '<S14>/Gain'
   *  Sum: '<S14>/Sum'
   */
  rtDW.Delay_DSTATE_pb = 0.004F * rtb_Switch_j + rtb_Switch_c;

  /* End of Outputs for SubSystem: '<S7>/Discrete Integrator  Theta Y' */

  /* Sum: '<S13>/Sum' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   *  Delay: '<S13>/Delay'
   *  Gain: '<S13>/Gain'
   *  Gain: '<S13>/Gain1'
   *  Gain: '<S1>/Invert1'
   *  Gain: '<S3>/Gain'
   *  Inport: '<Root>/motor_y_offset'
   *  Inport: '<Root>/phi_m_y'
   *  Sum: '<S3>/Sum'
   */
  rtb_Switch_k = (-(real32_T)*arg_phi_m_y - arg_motor_y_offset) * 0.0174532924F *
    0.2F + 0.8F * rtDW.Delay_DSTATE_b;

  /* Outputs for Atomic SubSystem: '<S3>/Discrete Integrator  Int Phi Y' */
  /* Outputs for Atomic SubSystem: '<S3>/Discrete Derivative  Phi Y' */
  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S11>/Constant'
   *  Delay: '<S11>/Delay'
   *  Delay: '<S9>/Delay'
   *  Inport: '<Root>/flag_firstcycle'
   *  Switch: '<S11>/Switch'
   */
  if (arg_flag_firstcycle) {
    rtb_Switch_n = rtb_Switch_k;
    rtb_Switch = 0.0F;
  } else {
    rtb_Switch_n = rtDW.Delay_DSTATE_d;
    rtb_Switch = rtDW.Delay_DSTATE_m;
  }

  /* End of Switch: '<S9>/Switch' */
  /* End of Outputs for SubSystem: '<S3>/Discrete Integrator  Int Phi Y' */

  /* Update for Delay: '<S9>/Delay' */
  rtDW.Delay_DSTATE_d = rtb_Switch_k;

  /* End of Outputs for SubSystem: '<S3>/Discrete Derivative  Phi Y' */

  /* Outputs for Atomic SubSystem: '<S3>/Discrete Integrator  Int Phi Y' */
  /* Update for Delay: '<S11>/Delay' incorporates:
   *  Delay: '<S1>/Delay'
   *  Gain: '<S11>/Gain'
   *  Product: '<S3>/Product1'
   *  Sum: '<S11>/Sum'
   */
  rtDW.Delay_DSTATE_m = 0.004F * (rtDW.Delay_DSTATE_o[1] ? rtb_Switch_k : 0.0F)
    + rtb_Switch;

  /* End of Outputs for SubSystem: '<S3>/Discrete Integrator  Int Phi Y' */

  /* Sum: '<S19>/Sum' incorporates:
   *  Delay: '<S19>/Delay'
   *  Gain: '<S19>/1-a_gyro'
   *  Gain: '<S19>/a_gyro'
   */
  rtb_Switch_j = 0.75F * rtb_Switch_j + 0.25F * rtDW.Delay_DSTATE_k;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtGain1Inport1' incorporates:
   *  Gain: '<S7>/deg2rad3'
   *  Gain: '<S7>/deg2rad4'
   *  Gain: '<S9>/Gain'
   *  Sum: '<S9>/Sum'
   */
  tmp[0] = 0.0174532924F * rtb_Switch_c;
  tmp[1] = rtb_Switch_k;
  tmp[2] = 0.0174532924F * rtb_Switch_j;

  /* Outputs for Atomic SubSystem: '<S3>/Discrete Derivative  Phi Y' */
  tmp[3] = (rtb_Switch_k - rtb_Switch_n) * 250.0F;

  /* End of Outputs for SubSystem: '<S3>/Discrete Derivative  Phi Y' */
  tmp[4] = rtb_Switch;

  /* Gain: '<S1>/Gain1' */
  rtb_Switch_c = 0.0F;
  for (i = 0; i < 5; i++) {
    rtb_Switch_c += rtConstP.pooled12[i] * tmp[i];
  }

  /* Gain: '<S2>/Gain2' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Product: '<S2>/Divide1'
   */
  rtb_Gain_m = rtb_Switch_c / rtb_Gain_m * 100.0F;

  /* Saturate: '<S2>/Saturation' */
  if (rtb_Gain_m > 100.0F) {
    rtb_Switch_c = 100.0F;
  } else if (rtb_Gain_m < -100.0F) {
    rtb_Switch_c = -100.0F;
  } else {
    rtb_Switch_c = rtb_Gain_m;
  }

  /* End of Saturate: '<S2>/Saturation' */

  /* Outport: '<Root>/pwm_y' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion3'
   *  Gain: '<S2>/Gain'
   */
  *arg_pwm_y = (int8_T)-rtb_Switch_c;

  /* Abs: '<S2>/Abs1' */
  rtb_Switch_c = fabsf(rtb_Switch_c);

  /* Abs: '<S2>/Abs3' */
  rtb_Gain_m = fabsf(rtb_Gain_m);

  /* Update for Delay: '<S12>/Delay' */
  rtDW.Delay_DSTATE = rtb_Sum_n3;

  /* Update for Delay: '<S18>/Delay' */
  rtDW.Delay_DSTATE_j = rtb_Inverter;

  /* Update for Delay: '<S1>/Delay' incorporates:
   *  RelationalOperator: '<S2>/Relational Operator1'
   *  SignalConversion: '<S1>/TmpSignal ConversionAtDelayInport1'
   */
  rtDW.Delay_DSTATE_o[0] = rtb_RelationalOperator;
  rtDW.Delay_DSTATE_o[1] = (rtb_Gain_m <= rtb_Switch_c);

  /* Update for Delay: '<S13>/Delay' */
  rtDW.Delay_DSTATE_b = rtb_Switch_k;

  /* Update for Delay: '<S19>/Delay' */
  rtDW.Delay_DSTATE_k = rtb_Switch_j;
}

/* Model initialize function */
void SimulinkBallbotModel_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
