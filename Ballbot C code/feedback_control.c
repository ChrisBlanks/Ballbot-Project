/*
 * File: feedback_control.c
 *
 * Code generated for Simulink model 'feedback_control'.
 *
 * Model version                  : 1.49
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Feb 27 16:41:58 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "feedback_control.h"
#include "feedback_control_private.h"

/* Block signals (auto storage) */
BlockIO_feedback_control feedback_control_B;

/* Block states (auto storage) */
D_Work_feedback_control feedback_control_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_feedback_control feedback_control_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_feedback_contro feedback_control_Y;

/* Real-time model */
RT_MODEL_feedback_control feedback_control_M_;
RT_MODEL_feedback_control *const feedback_control_M = &feedback_control_M_;

/* Model step function */
void feedback_control_step(void)
{
  /* local block i/o variables */
  boolean_T rtb_TmpSignalConversionAtDelayI[2];
  real_T rtb_Gain5;
  real32_T rtb_Switch_o;
  real_T rtb_Abs;
  real_T rtb_TmpSignalConversionAtGainIn[5];
  real_T rtb_Abs2;
  real_T rtb_Abs3;
  int32_T i;

  /* DataStoreWrite: '<S15>/Data Store Write' incorporates:
   *  DataStoreRead: '<S15>/Data Store Read'
   *  Gain: '<S15>/Gain'
   *  Gain: '<S15>/Gain1'
   *  Inport: '<Root>/gyro_y'
   *  Sum: '<S15>/Sum'
   */
  feedback_control_DWork.gyro_x_offset = (0.999 *
    feedback_control_DWork.gyro_x_offset) + (0.001 * feedback_control_U.gyro_y);

  /* DataStoreWrite: '<S16>/Data Store Write' incorporates:
   *  DataStoreRead: '<S16>/Data Store Read'
   *  Gain: '<S16>/Gain'
   *  Gain: '<S16>/Gain1'
   *  Inport: '<Root>/gyro_x'
   *  Sum: '<S16>/Sum'
   */
  feedback_control_DWork.gyro_y_offset = (0.999 *
    feedback_control_DWork.gyro_y_offset) + (0.001 * feedback_control_U.gyro_x);

  /* Gain: '<S6>/Gain5' incorporates:
   *  DataStoreRead: '<S15>/Data Store Read1'
   *  Inport: '<Root>/gyro_y'
   *  Sum: '<S6>/Sum'
   */
  rtb_Gain5 = -(feedback_control_U.gyro_y - feedback_control_DWork.gyro_x_offset);

  /* Outputs for Atomic SubSystem: '<S6>/Discrete Integrator Theta X' */
  /* Switch: '<S14>/Switch' incorporates:
   *  Constant: '<S14>/Constant'
   *  DataStoreRead: '<S14>/Data Store Read'
   *  Delay: '<S14>/Delay'
   */
  if (feedback_control_DWork.flag_firstcycle > 0.0) {
    rtb_Switch_o = 0.0F;
  } else {
    rtb_Switch_o = (real32_T)feedback_control_DWork.Delay_DSTATE_i;
  }

  /* End of Switch: '<S14>/Switch' */

  /* Sum: '<S14>/Sum' incorporates:
   *  Gain: '<S14>/Gain'
   */
  feedback_control_B.Sum_ee = (0.004 * rtb_Gain5) + rtb_Switch_o;

  /* End of Outputs for SubSystem: '<S6>/Discrete Integrator Theta X' */

  /* Sum: '<S17>/Sum' incorporates:
   *  Delay: '<S17>/Delay'
   *  Gain: '<S17>/Gain'
   *  Gain: '<S17>/Gain1'
   */
  feedback_control_B.Sum = (0.75 * rtb_Gain5) + (0.25 *
    feedback_control_DWork.Delay_DSTATE);

  /* Sum: '<S11>/Sum' incorporates:
   *  DataStoreRead: '<S2>/Data Store Read'
   *  Delay: '<S11>/Delay'
   *  Gain: '<S11>/Gain'
   *  Gain: '<S11>/Gain1'
   *  Gain: '<S2>/Gain1'
   *  Inport: '<Root>/phi_m_x'
   *  Sum: '<S2>/Sum1'
   */
  feedback_control_B.Sum_e = (((feedback_control_U.phi_m_x -
    feedback_control_DWork.motor_x_offset) * 0.017453292519943295) * 0.2) + (0.8
    * feedback_control_DWork.Delay_DSTATE_j);

  /* Outputs for Atomic SubSystem: '<S2>/Discrete Integrator  Int Phi X' */
  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S9>/Constant'
   *  DataStoreRead: '<S9>/Data Store Read'
   *  Delay: '<S9>/Delay'
   */
  if (feedback_control_DWork.flag_firstcycle > 0.0) {
    rtb_Gain5 = 0.0;
  } else {
    rtb_Gain5 = feedback_control_DWork.Delay_DSTATE_l;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Sum: '<S9>/Sum' incorporates:
   *  Delay: '<Root>/Delay'
   *  Gain: '<S9>/Gain'
   *  Product: '<S2>/Product'
   */
  feedback_control_B.Sum_b = (0.004 * (feedback_control_DWork.Delay_DSTATE_k[0] ?
    feedback_control_B.Sum_e : 0.0)) + rtb_Gain5;

  /* End of Outputs for SubSystem: '<S2>/Discrete Integrator  Int Phi X' */

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGainInport1' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Gain: '<S6>/Gain4'
   */
  rtb_TmpSignalConversionAtGainIn[0] = 0.01745329238474369 * rtb_Switch_o;
  rtb_TmpSignalConversionAtGainIn[1] = feedback_control_B.Sum_e;
  rtb_TmpSignalConversionAtGainIn[2] = 0.017453292519943295 *
    feedback_control_B.Sum;

  /* Outputs for Atomic SubSystem: '<S2>/Discrete Derivative  Phi X' */
  /* Switch: '<S7>/Switch' incorporates:
   *  DataStoreRead: '<S7>/Data Store Read'
   *  Delay: '<S7>/Delay'
   */
  if (feedback_control_DWork.flag_firstcycle > 0.0) {
    rtb_Abs3 = feedback_control_B.Sum_e;
  } else {
    rtb_Abs3 = feedback_control_DWork.Delay_DSTATE_b;
  }

  /* End of Switch: '<S7>/Switch' */

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGainInport1' incorporates:
   *  Gain: '<S7>/Gain'
   *  Sum: '<S7>/Sum'
   */
  rtb_TmpSignalConversionAtGainIn[3] = (feedback_control_B.Sum_e - rtb_Abs3) *
    250.0;

  /* End of Outputs for SubSystem: '<S2>/Discrete Derivative  Phi X' */
  rtb_TmpSignalConversionAtGainIn[4] = rtb_Gain5;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/Constant'
   *  DataStoreRead: '<Root>/Data Store Read'
   *  Gain: '<S3>/Gain'
   */
  rtb_Gain5 = (0.001089 * feedback_control_DWork.battery) - 0.625;

  /* Gain: '<Root>/Gain' */
  rtb_Abs3 = 0.0;
  for (i = 0; i < 5; i++) {
    rtb_Abs3 += feedback_control_ConstP.pooled7[i] *
      rtb_TmpSignalConversionAtGainIn[i];
  }

  /* Gain: '<S1>/Gain3' incorporates:
   *  Gain: '<Root>/Gain'
   *  Product: '<S1>/Divide'
   */
  rtb_Abs = (rtb_Abs3 / rtb_Gain5) * 100.0;

  /* Saturate: '<S1>/Saturation1' */
  if (rtb_Abs > 100.0) {
    rtb_Abs2 = 100.0;
  } else if (rtb_Abs < -100.0) {
    rtb_Abs2 = -100.0;
  } else {
    rtb_Abs2 = rtb_Abs;
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Outport: '<Root>/pwm_x' incorporates:
   *  Gain: '<S1>/Gain1'
   */
  feedback_control_Y.pwm_x = -rtb_Abs2;

  /* Gain: '<Root>/Gain1' */
  rtb_Abs3 = 0.0;
  for (i = 0; i < 5; i++) {
    rtb_Abs3 += feedback_control_ConstP.pooled7[i] *
      rtb_TmpSignalConversionAtGainIn[i];
  }

  /* Gain: '<S1>/Gain2' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Product: '<S1>/Divide1'
   */
  rtb_Abs3 = (rtb_Abs3 / rtb_Gain5) * 100.0;

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Abs3 > 100.0) {
    rtb_Gain5 = 100.0;
  } else if (rtb_Abs3 < -100.0) {
    rtb_Gain5 = -100.0;
  } else {
    rtb_Gain5 = rtb_Abs3;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Outport: '<Root>/pwm_y' incorporates:
   *  Gain: '<S1>/Gain'
   */
  feedback_control_Y.pwm_y = -rtb_Gain5;

  /* Abs: '<S1>/Abs' */
  rtb_Abs = fabs(rtb_Abs);

  /* Abs: '<S1>/Abs1' */
  rtb_Gain5 = fabs(rtb_Gain5);

  /* Abs: '<S1>/Abs2' */
  rtb_Abs2 = fabs(rtb_Abs2);

  /* Abs: '<S1>/Abs3' */
  rtb_Abs3 = fabs(rtb_Abs3);

  /* SignalConversion: '<Root>/TmpSignal ConversionAtDelayInport1' incorporates:
   *  RelationalOperator: '<S1>/Relational Operator'
   *  RelationalOperator: '<S1>/Relational Operator1'
   */
  rtb_TmpSignalConversionAtDelayI[0] = (rtb_Abs <= rtb_Abs2);
  rtb_TmpSignalConversionAtDelayI[1] = (rtb_Abs3 <= rtb_Gain5);

  /* Update for Atomic SubSystem: '<S6>/Discrete Integrator Theta X' */
  /* Update for Delay: '<S14>/Delay' */
  feedback_control_DWork.Delay_DSTATE_i = feedback_control_B.Sum_ee;

  /* End of Update for SubSystem: '<S6>/Discrete Integrator Theta X' */

  /* Update for Delay: '<S17>/Delay' */
  feedback_control_DWork.Delay_DSTATE = feedback_control_B.Sum;

  /* Update for Delay: '<S11>/Delay' */
  feedback_control_DWork.Delay_DSTATE_j = feedback_control_B.Sum_e;

  /* Update for Atomic SubSystem: '<S2>/Discrete Derivative  Phi X' */
  /* Update for Delay: '<S7>/Delay' */
  feedback_control_DWork.Delay_DSTATE_b = feedback_control_B.Sum_e;

  /* End of Update for SubSystem: '<S2>/Discrete Derivative  Phi X' */

  /* Update for Delay: '<Root>/Delay' */
  feedback_control_DWork.Delay_DSTATE_k[0] = rtb_TmpSignalConversionAtDelayI[0];
  feedback_control_DWork.Delay_DSTATE_k[1] = rtb_TmpSignalConversionAtDelayI[1];

  /* Update for Atomic SubSystem: '<S2>/Discrete Integrator  Int Phi X' */
  /* Update for Delay: '<S9>/Delay' */
  feedback_control_DWork.Delay_DSTATE_l = feedback_control_B.Sum_b;

  /* End of Update for SubSystem: '<S2>/Discrete Integrator  Int Phi X' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  feedback_control_M->Timing.t[0] =
    (++feedback_control_M->Timing.clockTick0) *
    feedback_control_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    feedback_control_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void feedback_control_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&feedback_control_M->solverInfo,
                          &feedback_control_M->Timing.simTimeStep);
    rtsiSetTPtr(&feedback_control_M->solverInfo, &rtmGetTPtr(feedback_control_M));
    rtsiSetStepSizePtr(&feedback_control_M->solverInfo,
                       &feedback_control_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&feedback_control_M->solverInfo, ((const char_T **)
      (&rtmGetErrorStatus(feedback_control_M))));
    rtsiSetRTModelPtr(&feedback_control_M->solverInfo, feedback_control_M);
  }

  rtsiSetSimTimeStep(&feedback_control_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&feedback_control_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(feedback_control_M, &feedback_control_M->Timing.tArray[0]);
  feedback_control_M->Timing.stepSize0 = 0.001;
}

/* Model terminate function */
void feedback_control_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
