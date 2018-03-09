/*
 * File: feedback_control.h
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

#ifndef RTW_HEADER_feedback_control_h_
#define RTW_HEADER_feedback_control_h_
#include <math.h>
#ifndef feedback_control_COMMON_INCLUDES_
# define feedback_control_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* feedback_control_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (auto storage) for system '<S2>/Discrete Integrator  Int Phi X' */
typedef struct {
  real_T Delay;                        /* '<S9>/Delay' */
  real_T Sum;                          /* '<S9>/Sum' */
  real_T Delay_DSTATE;                 /* '<S9>/Delay' */
} rtDW_DiscreteIntegratorIntPhiX;

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  rtDW_DiscreteIntegratorIntPhiX DiscreteIntegratorIntPhiY;/* '<S2>/Discrete Integrator  Int Phi Y' */
  rtDW_DiscreteIntegratorIntPhiX DiscreteIntegratorIntPhiX_k;/* '<S2>/Discrete Integrator  Int Phi X' */
  real_T Sum;                          /* '<S17>/Sum' */
  real_T Sum_m;                        /* '<S18>/Sum' */
  real_T Sum_e;                        /* '<S11>/Sum' */
  real_T Sum_g;                        /* '<S12>/Sum' */
  real_T Sum_ee;                       /* '<S14>/Sum' */
  real_T Sum_c;                        /* '<S13>/Sum' */
  real_T Delay_DSTATE;                 /* '<S17>/Delay' */
  real_T Delay_DSTATE_l;               /* '<S18>/Delay' */
  real_T Delay_DSTATE_j;               /* '<S11>/Delay' */
  real_T Delay_DSTATE_i;               /* '<S12>/Delay' */
  real_T Delay_DSTATE_b;               /* '<S7>/Delay' */
  real_T Delay_DSTATE_i0;              /* '<S14>/Delay' */
  real_T Delay_DSTATE_a;               /* '<S13>/Delay' */
  real_T flag_firstcycle;              /* '<Root>/Data Store Memory' */
  real_T battery;                      /* '<Root>/Data Store Memory1' */
  real_T gyro_y_offset;                /* '<Root>/Data Store Memory2' */
  real_T motor_x_offset;               /* '<Root>/Data Store Memory3' */
  real_T gyro_x_offset;                /* '<Root>/Data Store Memory4' */
  real_T motor_y_offset;               /* '<Root>/Data Store Memory5' */
  boolean_T Delay_DSTATE_k[2];         /* '<Root>/Delay' */
} D_Work;

/* Constant parameters (auto storage) */
typedef struct {
  /* Pooled Parameter (Expression: [ 100 -1.2 15 -1 -0.3])
   * Referenced by:
   *   '<Root>/Gain'
   *   '<Root>/Gain1'
   */
  real_T pooled12[5];
} ConstParam;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T gyro_y;                       /* '<Root>/gyro_y' */
  real_T gyro_x;                       /* '<Root>/gyro_x' */
  real_T phi_m_y;                      /* '<Root>/phi_m_y' */
  real_T phi_m_x;                      /* '<Root>/phi_m_x' */
} ExternalInputs;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T pwm_x;                        /* '<Root>/pwm_x' */
  real_T pwm_y;                        /* '<Root>/pwm_y' */
} ExternalOutputs;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals and states (auto storage) */
extern D_Work rtDWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs rtY;

/* Constant parameters (auto storage) */
extern const ConstParam rtConstP;

/* Model entry point functions */
extern void feedback_control_initialize(void);
extern void feedback_control_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'feedback_control'
 * '<S1>'   : 'feedback_control/Calculate pwm'
 * '<S2>'   : 'feedback_control/Calculate x_est'
 * '<S3>'   : 'feedback_control/Calculate pwm/Calculate vol_max'
 * '<S4>'   : 'feedback_control/Calculate pwm/Friction Compensator (not sure if correct)'
 * '<S5>'   : 'feedback_control/Calculate pwm/Friction Compensator1'
 * '<S6>'   : 'feedback_control/Calculate x_est/Calculate Body Angle'
 * '<S7>'   : 'feedback_control/Calculate x_est/Discrete Derivative  Phi X'
 * '<S8>'   : 'feedback_control/Calculate x_est/Discrete Derivative  Phi Y'
 * '<S9>'   : 'feedback_control/Calculate x_est/Discrete Integrator  Int Phi X'
 * '<S10>'  : 'feedback_control/Calculate x_est/Discrete Integrator  Int Phi Y'
 * '<S11>'  : 'feedback_control/Calculate x_est/LPF Phi X Est1'
 * '<S12>'  : 'feedback_control/Calculate x_est/LPF Phi Y Est'
 * '<S13>'  : 'feedback_control/Calculate x_est/Calculate Body Angle/Discrete Integrator  Theta Y'
 * '<S14>'  : 'feedback_control/Calculate x_est/Calculate Body Angle/Discrete Integrator Theta X'
 * '<S15>'  : 'feedback_control/Calculate x_est/Calculate Body Angle/Gyro X Offset'
 * '<S16>'  : 'feedback_control/Calculate x_est/Calculate Body Angle/Gyro Y Offset'
 * '<S17>'  : 'feedback_control/Calculate x_est/Calculate Body Angle/LPF Theta Dot X'
 * '<S18>'  : 'feedback_control/Calculate x_est/Calculate Body Angle/LPF Theta Dot Y'
 */
#endif                                 /* RTW_HEADER_feedback_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

