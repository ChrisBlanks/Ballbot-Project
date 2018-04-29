/*
 * File: feedback_control.c
 *
 * Code generated for Simulink model 'feedback_control'.
 *
 * Model version                  : 1.53
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Thu Mar 08 21:25:06 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR (8-bit)
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#include "feedback_control.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

/* Block signals and states (auto storage) */
D_Work rtDWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern void DiscreteIntegratorIntPhi_Update(rtDW_DiscreteIntegratorIntPhiX
  *localDW);
extern real_T DiscreteIntegratorIntPhiX(real_T rtu_In1,
  rtDW_DiscreteIntegratorIntPhiX *localDW, real_T *rtd_flag_firstcycle);

/*
 * Outputs for atomic system:
 *    '<S2>/Discrete Integrator  Int Phi X'
 *    '<S2>/Discrete Integrator  Int Phi Y'
 */
real_T DiscreteIntegratorIntPhiX(real_T rtu_In1, rtDW_DiscreteIntegratorIntPhiX *
  localDW, real_T *rtd_flag_firstcycle)
{
  real_T rty_Out1_0;

  /* Delay: '<S9>/Delay' */
  localDW->Delay = localDW->Delay_DSTATE;

  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S9>/Constant'
   *  DataStoreRead: '<S9>/Data Store Read'
   */
  if (*rtd_flag_firstcycle > 0.0) {
    rty_Out1_0 = 0.0;
  } else {
    rty_Out1_0 = localDW->Delay;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Sum: '<S9>/Sum' incorporates:
   *  Gain: '<S9>/Gain'
   */
  localDW->Sum = 0.004 * rtu_In1 + rty_Out1_0;
  return rty_Out1_0;
}

/*
 * Update for atomic system:
 *    '<S2>/Discrete Integrator  Int Phi X'
 *    '<S2>/Discrete Integrator  Int Phi Y'
 */
void DiscreteIntegratorIntPhi_Update(rtDW_DiscreteIntegratorIntPhiX *localDW)
{
  /* Update for Delay: '<S9>/Delay' */
  localDW->Delay_DSTATE = localDW->Sum;
}

/* Model step function */
void feedback_control_step(void)
{
  /* local block i/o variables */
  real_T rtb_Switch_m;
  boolean_T rtb_TmpSignalConversionAtDelayI[2];
  real_T rtb_Gain5;
  real32_T rtb_Switch_o;
  real_T rtb_Abs;
  real_T rtb_TmpSignalConversionAtGainIn[5];
  real_T rtb_Abs2;
  real_T rtb_Abs3;
  int16_T i;
  real32_T tmp;
  real_T rtb_Abs3_0;

  /* DataStoreWrite: '<S15>/Data Store Write' incorporates:
   *  DataStoreRead: '<S15>/Data Store Read'
   *  Gain: '<S15>/Gain'
   *  Gain: '<S15>/Gain1'
   *  Inport: '<Root>/gyro_y'
   *  Sum: '<S15>/Sum'
   */
  rtDWork.gyro_x_offset = 0.999 * rtDWork.gyro_x_offset + 0.001 * rtU.gyro_y;

  /* DataStoreWrite: '<S16>/Data Store Write' incorporates:
   *  DataStoreRead: '<S16>/Data Store Read'
   *  Gain: '<S16>/Gain'
   *  Gain: '<S16>/Gain1'
   *  Inport: '<Root>/gyro_x'
   *  Sum: '<S16>/Sum'
   */
  rtDWork.gyro_y_offset = 0.999 * rtDWork.gyro_y_offset + 0.001 * rtU.gyro_x;

  /* Gain: '<S6>/Gain5' incorporates:
   *  DataStoreRead: '<S15>/Data Store Read1'
   *  Inport: '<Root>/gyro_y'
   *  Sum: '<S6>/Sum'
   */
  rtb_Gain5 = (rtU.gyro_y - rtDWork.gyro_x_offset) * (-1.0);

  /* Outputs for Atomic SubSystem: '<S6>/Discrete Integrator  Theta Y' */
  /* Outputs for Atomic SubSystem: '<S6>/Discrete Integrator Theta X' */
  /* Switch: '<S14>/Switch' incorporates:
   *  Constant: '<S13>/Constant'
   *  Constant: '<S14>/Constant'
   *  DataStoreRead: '<S14>/Data Store Read'
   *  Delay: '<S13>/Delay'
   *  Delay: '<S14>/Delay'
   *  Switch: '<S13>/Switch'
   */
  if (rtDWork.flag_firstcycle > 0.0) {
    rtb_Switch_o = (real32_T)0.0;
    tmp = (real32_T)0.0;
  } else {
    rtb_Switch_o = (real32_T)rtDWork.Delay_DSTATE_i0;
    tmp = (real32_T)rtDWork.Delay_DSTATE_a;
  }

  /* End of Switch: '<S14>/Switch' */
  /* End of Outputs for SubSystem: '<S6>/Discrete Integrator  Theta Y' */

  /* Sum: '<S14>/Sum' incorporates:
   *  Gain: '<S14>/Gain'
   */
  rtDWork.Sum_ee = 0.004 * rtb_Gain5 + rtb_Switch_o;

  /* End of Outputs for SubSystem: '<S6>/Discrete Integrator Theta X' */

  /* Sum: '<S17>/Sum' incorporates:
   *  Delay: '<S17>/Delay'
   *  Gain: '<S17>/Gain'
   *  Gain: '<S17>/Gain1'
   */
  rtDWork.Sum = 0.75 * rtb_Gain5 + 0.25 * rtDWork.Delay_DSTATE;

  /* Sum: '<S6>/Sum1' incorporates:
   *  DataStoreRead: '<S16>/Data Store Read1'
   *  Inport: '<Root>/gyro_x'
   */
  rtb_Gain5 = rtU.gyro_x - rtDWork.gyro_y_offset;

  /* Outputs for Atomic SubSystem: '<S6>/Discrete Integrator  Theta Y' */
  /* Sum: '<S13>/Sum' incorporates:
   *  Gain: '<S13>/Gain'
   */
  rtDWork.Sum_c = 0.004 * rtb_Gain5 + tmp;

  /* End of Outputs for SubSystem: '<S6>/Discrete Integrator  Theta Y' */

  /* Sum: '<S18>/Sum' incorporates:
   *  Delay: '<S18>/Delay'
   *  Gain: '<S18>/Gain'
   *  Gain: '<S18>/Gain1'
   */
  rtDWork.Sum_m = 0.75 * rtb_Gain5 + 0.25 * rtDWork.Delay_DSTATE_l;

  /* Sum: '<S11>/Sum' incorporates:
   *  DataStoreRead: '<S2>/Data Store Read'
   *  Delay: '<S11>/Delay'
   *  Gain: '<S11>/Gain'
   *  Gain: '<S11>/Gain1'
   *  Gain: '<S2>/Gain1'
   *  Inport: '<Root>/phi_m_x'
   *  Sum: '<S2>/Sum1'
   */
  rtDWork.Sum_e = (rtU.phi_m_x - rtDWork.motor_x_offset) * 0.017453292519943295 *
    0.2 + 0.8 * rtDWork.Delay_DSTATE_j;

  /* Sum: '<S12>/Sum' incorporates:
   *  DataStoreRead: '<S2>/Data Store Read1'
   *  Delay: '<S12>/Delay'
   *  Gain: '<S12>/Gain'
   *  Gain: '<S12>/Gain1'
   *  Gain: '<S2>/Gain'
   *  Inport: '<Root>/phi_m_y'
   *  Sum: '<S2>/Sum'
   */
  rtDWork.Sum_g = (rtU.phi_m_y - rtDWork.motor_y_offset) * 0.017453292519943295 *
    0.2 + 0.8 * rtDWork.Delay_DSTATE_i;

  /* Outputs for Atomic SubSystem: '<S2>/Discrete Integrator  Int Phi X' */

  /* Product: '<S2>/Product' incorporates:
   *  Delay: '<Root>/Delay'
   */
  rtb_Switch_m = DiscreteIntegratorIntPhiX(rtDWork.Sum_e * (real_T)
    rtDWork.Delay_DSTATE_k[0], &rtDWork.DiscreteIntegratorIntPhiX_k,
    &rtDWork.flag_firstcycle);

  /* End of Outputs for SubSystem: '<S2>/Discrete Integrator  Int Phi X' */

  /* Outputs for Atomic SubSystem: '<S2>/Discrete Integrator  Int Phi Y' */

  /* Product: '<S2>/Product1' incorporates:
   *  Delay: '<Root>/Delay'
   */
  rtb_Gain5 = DiscreteIntegratorIntPhiX(rtDWork.Sum_g * (real_T)
    rtDWork.Delay_DSTATE_k[1], &rtDWork.DiscreteIntegratorIntPhiY,
    &rtDWork.flag_firstcycle);

  /* End of Outputs for SubSystem: '<S2>/Discrete Integrator  Int Phi Y' */

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGainInport1' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Gain: '<S6>/Gain4'
   */
  rtb_TmpSignalConversionAtGainIn[0] = (real_T)0.0174532924F * rtb_Switch_o;
  rtb_TmpSignalConversionAtGainIn[1] = rtDWork.Sum_e;
  rtb_TmpSignalConversionAtGainIn[2] = 0.017453292519943295 * rtDWork.Sum;

  /* Outputs for Atomic SubSystem: '<S2>/Discrete Derivative  Phi X' */
  /* Switch: '<S7>/Switch' incorporates:
   *  DataStoreRead: '<S7>/Data Store Read'
   *  Delay: '<S7>/Delay'
   */
  if (rtDWork.flag_firstcycle > 0.0) {
    rtb_Abs3 = rtDWork.Sum_e;
  } else {
    rtb_Abs3 = rtDWork.Delay_DSTATE_b;
  }

  /* End of Switch: '<S7>/Switch' */

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGainInport1' incorporates:
   *  Gain: '<S7>/Gain'
   *  Sum: '<S7>/Sum'
   */
  rtb_TmpSignalConversionAtGainIn[3] = (rtDWork.Sum_e - rtb_Abs3) * 250.0;

  /* End of Outputs for SubSystem: '<S2>/Discrete Derivative  Phi X' */
  rtb_TmpSignalConversionAtGainIn[4] = rtb_Switch_m;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/Constant'
   *  DataStoreRead: '<Root>/Data Store Read'
   *  Gain: '<S3>/Gain'
   */
  rtb_Gain5 = 0.001089 * rtDWork.battery - 0.625;

  /* Gain: '<Root>/Gain' */
  rtb_Abs3 = 0.0;
  for (i = 0; i < 5; i++) {
    rtb_Abs3 += rtConstP.pooled12[i] * rtb_TmpSignalConversionAtGainIn[i];
  }

  /* Gain: '<S1>/Gain3' incorporates:
   *  Gain: '<Root>/Gain'
   *  Product: '<S1>/Divide'
   */
  rtb_Abs = rtb_Abs3 / rtb_Gain5 * 100.0;

  /* Signum: '<S5>/Sign' */
  if (rtb_Abs < 0.0) {
    rtb_Abs2 = -1.0;
  } else if (rtb_Abs > 0.0) {
    rtb_Abs2 = 1.0;
  } else if (rtb_Abs == 0.0) {
    rtb_Abs2 = 0.0;
  } else {
    rtb_Abs2 = rtb_Abs;
  }

  /* End of Signum: '<S5>/Sign' */

  /* Sum: '<S5>/Sum' incorporates:
   *  Gain: '<S5>/Gain'
   *  Gain: '<S5>/Gain1'
   */
  rtb_Abs = 0.0 * rtb_Abs2 + 1.0 * rtb_Abs;

  /* Saturate: '<S1>/Saturation1' */
  if (rtb_Abs > 100.0) {
    rtb_Abs2 = 100.0;
  } else if (rtb_Abs < (-100.0)) {
    rtb_Abs2 = (-100.0);
  } else {
    rtb_Abs2 = rtb_Abs;
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Outport: '<Root>/pwm_x' incorporates:
   *  Gain: '<S1>/Gain1'
   */
  rtY.pwm_x = (-1.0) * rtb_Abs2;

  /* Gain: '<Root>/Gain1' */
  rtb_Abs3 = 0.0;
  for (i = 0; i < 5; i++) {
    rtb_Abs3 += rtConstP.pooled12[i] * rtb_TmpSignalConversionAtGainIn[i];
  }

  /* Gain: '<S1>/Gain2' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Product: '<S1>/Divide1'
   */
  rtb_Abs3 = rtb_Abs3 / rtb_Gain5 * 100.0;

  /* Signum: '<S4>/Sign' */
  if (rtb_Abs3 < 0.0) {
    rtb_Abs3_0 = -1.0;
  } else if (rtb_Abs3 > 0.0) {
    rtb_Abs3_0 = 1.0;
  } else if (rtb_Abs3 == 0.0) {
    rtb_Abs3_0 = 0.0;
  } else {
    rtb_Abs3_0 = rtb_Abs3;
  }

  /* End of Signum: '<S4>/Sign' */

  /* Sum: '<S4>/Sum' incorporates:
   *  Gain: '<S4>/Gain'
   *  Gain: '<S4>/Gain1'
   */
  rtb_Abs3 = 0.0 * rtb_Abs3_0 + 1.0 * rtb_Abs3;

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Abs3 > 100.0) {
    rtb_Gain5 = 100.0;
  } else if (rtb_Abs3 < (-100.0)) {
    rtb_Gain5 = (-100.0);
  } else {
    rtb_Gain5 = rtb_Abs3;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Outport: '<Root>/pwm_y' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtY.pwm_y = (-1.0) * rtb_Gain5;

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
  rtDWork.Delay_DSTATE_i0 = rtDWork.Sum_ee;

  /* End of Update for SubSystem: '<S6>/Discrete Integrator Theta X' */

  /* Update for Delay: '<S17>/Delay' */
  rtDWork.Delay_DSTATE = rtDWork.Sum;

  /* Update for Atomic SubSystem: '<S6>/Discrete Integrator  Theta Y' */
  /* Update for Delay: '<S13>/Delay' */
  rtDWork.Delay_DSTATE_a = rtDWork.Sum_c;

  /* End of Update for SubSystem: '<S6>/Discrete Integrator  Theta Y' */

  /* Update for Delay: '<S18>/Delay' */
  rtDWork.Delay_DSTATE_l = rtDWork.Sum_m;

  /* Update for Delay: '<S11>/Delay' */
  rtDWork.Delay_DSTATE_j = rtDWork.Sum_e;

  /* Update for Atomic SubSystem: '<S2>/Discrete Derivative  Phi X' */
  /* Update for Delay: '<S7>/Delay' */
  rtDWork.Delay_DSTATE_b = rtDWork.Sum_e;

  /* End of Update for SubSystem: '<S2>/Discrete Derivative  Phi X' */

  /* Update for Delay: '<S12>/Delay' */
  rtDWork.Delay_DSTATE_i = rtDWork.Sum_g;

  /* Update for Delay: '<Root>/Delay' */
  rtDWork.Delay_DSTATE_k[0] = rtb_TmpSignalConversionAtDelayI[0];
  rtDWork.Delay_DSTATE_k[1] = rtb_TmpSignalConversionAtDelayI[1];

  /* Update for Atomic SubSystem: '<S2>/Discrete Integrator  Int Phi X' */
  DiscreteIntegratorIntPhi_Update(&rtDWork.DiscreteIntegratorIntPhiX_k);

  /* End of Update for SubSystem: '<S2>/Discrete Integrator  Int Phi X' */

  /* Update for Atomic SubSystem: '<S2>/Discrete Integrator  Int Phi Y' */
  DiscreteIntegratorIntPhi_Update(&rtDWork.DiscreteIntegratorIntPhiY);

  /* End of Update for SubSystem: '<S2>/Discrete Integrator  Int Phi Y' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rtM->Timing.t[0] =
    (++rtM->Timing.clockTick0) * rtM->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }
}

/* Model initialize function */
void feedback_control_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, ((const char_T **)
      (&rtmGetErrorStatus(rtM))));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&rtM->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.001;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

