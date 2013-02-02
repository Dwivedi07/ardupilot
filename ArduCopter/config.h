// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
//
#ifndef __ARDUCOPTER_CONFIG_H__
#define __ARDUCOPTER_CONFIG_H__
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//
//  DO NOT EDIT this file to adjust your configuration.  Create your own
//  APM_Config.h and use APM_Config.h.example as a reference.
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
///
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// Default and automatic configuration details.
//
// Notes for maintainers:
//
// - Try to keep this file organised in the same order as APM_Config.h.example
//
#include "defines.h"

///
/// DO NOT EDIT THIS INCLUDE - if you want to make a local change, make that
/// change in your local copy of APM_Config.h.
///
#ifdef USE_CMAKE_APM_CONFIG
 #include "APM_Config_cmake.h"  // <== Prefer cmake config if it exists
#else
 #include "APM_Config.h" // <== THIS INCLUDE, DO NOT EDIT IT. EVER.
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// HARDWARE CONFIGURATION AND CONNECTIONS
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


#ifdef CONFIG_APM_HARDWARE
#error CONFIG_APM_HARDWARE option is deprecated! use CONFIG_HAL_BOARD instead
#endif

#ifndef CONFIG_HAL_BOARD
#error CONFIG_HAL_BOARD must be defined to build ArduCopter
#endif
//////////////////////////////////////////////////////////////////////////////
// APM2 HARDWARE DEFAULTS
//

#if CONFIG_HAL_BOARD == HAL_BOARD_APM2
 # define CONFIG_IMU_TYPE   CONFIG_IMU_MPU6000
 # define CONFIG_PUSHBUTTON DISABLED
 # define CONFIG_RELAY      DISABLED
 # define MAG_ORIENTATION   AP_COMPASS_APM2_SHIELD
 # define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
 # define MAGNETOMETER ENABLED
 # ifdef APM2_BETA_HARDWARE
  #  define CONFIG_BARO     AP_BARO_BMP085
 # else // APM2 Production Hardware (default)
  #  define CONFIG_BARO          AP_BARO_MS5611
  #  define CONFIG_MS5611_SERIAL AP_BARO_MS5611_SPI
 # endif
#elif CONFIG_HAL_BOARD == HAL_BOARD_AVR_SITL
 # define CONFIG_IMU_TYPE   CONFIG_IMU_SITL
 # define CONFIG_PUSHBUTTON DISABLED
 # define CONFIG_RELAY      DISABLED
 # define MAG_ORIENTATION   AP_COMPASS_COMPONENTS_DOWN_PINS_FORWARD
 # define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
 # define MAGNETOMETER ENABLED
#elif CONFIG_HAL_BOARD == HAL_BOARD_PX4
 # define CONFIG_IMU_TYPE   CONFIG_IMU_PX4
 # define CONFIG_BARO       AP_BARO_PX4
 # define CONFIG_PUSHBUTTON DISABLED
 # define CONFIG_RELAY      DISABLED
 # define MAG_ORIENTATION   ROTATION_NONE
 # define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
 # define MAGNETOMETER ENABLED
#elif CONFIG_HAL_BOARD == HAL_BOARD_SMACCM
 # define CONFIG_IMU_TYPE   CONFIG_IMU_MPU6000
 # define CONFIG_BARO       AP_BARO_MS5611
 # define CONFIG_MS5611_SERIAL AP_BARO_MS5611_I2C
 # define CONFIG_ADC        DISABLED
 # define CONFIG_PUSHBUTTON DISABLED
 # define CONFIG_RELAY      DISABLED
 # define MAG_ORIENTATION   AP_COMPASS_COMPONENTS_DOWN_PINS_BACK
 # define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
 # define MAGNETOMETER ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// FRAME_CONFIG
//
#ifndef FRAME_CONFIG
 # define FRAME_CONFIG   QUAD_FRAME
#endif
#ifndef FRAME_ORIENTATION
 # define FRAME_ORIENTATION      X_FRAME
#endif
#ifndef TOY_EDF
 # define TOY_EDF        DISABLED
#endif
#ifndef TOY_MIXER
 # define TOY_MIXER      TOY_LINEAR_MIXER
#endif

/////////////////////////////////////////////////////////////////////////////////
// Bulk defines for TradHeli
#if FRAME_CONFIG == HELI_FRAME
  # define RC_FAST_SPEED 				125
  # define RTL_YAW                  	YAW_LOOK_AT_HOME
  # define TILT_COMPENSATION 			5
  # define RATE_INTEGRATOR_LEAK_RATE 	0.02f
  # define RATE_ROLL_D    				0
  # define RATE_PITCH_D       			0
  # define HELI_PITCH_FF				0
  # define HELI_ROLL_FF					0
  # define HELI_YAW_FF					0  
  # define RC_FAST_SPEED 				125
  # define STABILIZE_THROTTLE			THROTTLE_MANUAL
  # define MPU6K_FILTER                 10
#endif


// optical flow doesn't work in SITL yet
#ifdef DESKTOP_BUILD
# define OPTFLOW DISABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// IMU Selection
//
#ifndef CONFIG_IMU_TYPE
 # define CONFIG_IMU_TYPE CONFIG_IMU_OILPAN
#endif
#ifndef MPU6K_FILTER
 # define MPU6K_FILTER MPU6K_DEFAULT_FILTER
#endif

//////////////////////////////////////////////////////////////////////////////
// ADC Enable - used to eliminate for systems which don't have ADC.
//
#ifndef CONFIG_ADC
 # if CONFIG_IMU_TYPE == CONFIG_IMU_OILPAN
  #   define CONFIG_ADC ENABLED
 # else
  #   define CONFIG_ADC DISABLED
 # endif
#endif

//////////////////////////////////////////////////////////////////////////////
// PWM control
// default RC speed in Hz
#ifndef RC_FAST_SPEED
   #   define RC_FAST_SPEED 490
#endif

////////////////////////////////////////////////////////
// LED and IO Pins
//
#if CONFIG_HAL_BOARD == HAL_BOARD_APM1
 # define A_LED_PIN        37
 # define B_LED_PIN        36
 # define C_LED_PIN        35
 # define LED_ON           HIGH
 # define LED_OFF          LOW
 # define SLIDE_SWITCH_PIN 40
 # define PUSHBUTTON_PIN   41
 # define USB_MUX_PIN      -1
 # define CLI_SLIDER_ENABLED DISABLED
 # define BATTERY_VOLT_PIN      0      // Battery voltage on A0
 # define BATTERY_CURR_PIN      1      // Battery current on A1
#elif CONFIG_HAL_BOARD == HAL_BOARD_APM2
 # define A_LED_PIN        27
 # define B_LED_PIN        26
 # define C_LED_PIN        25
 # define LED_ON           LOW
 # define LED_OFF          HIGH
 # define SLIDE_SWITCH_PIN (-1)
 # define PUSHBUTTON_PIN   (-1)
 # define CLI_SLIDER_ENABLED DISABLED
 # define USB_MUX_PIN      23
 # define BATTERY_VOLT_PIN      1      // Battery voltage on A1
 # define BATTERY_CURR_PIN      2      // Battery current on A2
#elif CONFIG_HAL_BOARD == HAL_BOARD_AVR_SITL
 # define A_LED_PIN        27
 # define B_LED_PIN        26
 # define C_LED_PIN        25
 # define LED_ON           LOW
 # define LED_OFF          HIGH
 # define SLIDE_SWITCH_PIN (-1)
 # define PUSHBUTTON_PIN   (-1)
 # define CLI_SLIDER_ENABLED DISABLED
 # define USB_MUX_PIN      -1
 # define BATTERY_VOLT_PIN 1      // Battery voltage on A1
 # define BATTERY_CURR_PIN 2      // Battery current on A2
#elif CONFIG_HAL_BOARD == HAL_BOARD_PX4
 # define A_LED_PIN        27
 # define B_LED_PIN        26
 # define C_LED_PIN        25
 # define LED_ON           LOW
 # define LED_OFF          HIGH
 # define SLIDE_SWITCH_PIN (-1)
 # define PUSHBUTTON_PIN   (-1)
 # define CLI_SLIDER_ENABLED DISABLED
 # define USB_MUX_PIN      -1
 # define BATTERY_VOLT_PIN -1
 # define BATTERY_CURR_PIN -1
#elif CONFIG_HAL_BOARD == HAL_BOARD_SMACCM
// XXX these are just copied, may not make sense
 # define A_LED_PIN        27
 # define B_LED_PIN        26
 # define C_LED_PIN        25
 # define LED_ON           LOW
 # define LED_OFF          HIGH
 # define SLIDE_SWITCH_PIN (-1)
 # define PUSHBUTTON_PIN   (-1)
 # define CLI_SLIDER_ENABLED DISABLED
 # define USB_MUX_PIN      -1
 # define BATTERY_VOLT_PIN -1
 # define BATTERY_CURR_PIN -1
#endif

////////////////////////////////////////////////////////////////////////////////
// CopterLEDs
//

#ifndef COPTER_LEDS
 #define COPTER_LEDS ENABLED
#endif

#define COPTER_LED_ON           HIGH
#define COPTER_LED_OFF          LOW

#if CONFIG_HAL_BOARD == HAL_BOARD_APM2
 #define COPTER_LED_1 AN4       // Motor or Aux LED
 #define COPTER_LED_2 AN5       // Motor LED or Beeper
 #define COPTER_LED_3 AN6       // Motor or GPS LED
 #define COPTER_LED_4 AN7       // Motor LED
 #define COPTER_LED_5 AN8       // Motor LED
 #define COPTER_LED_6 AN9       // Motor LED
 #define COPTER_LED_7 AN10      // Motor LED
 #define COPTER_LED_8 AN11      // Motor LED
#elif CONFIG_HAL_BOARD == HAL_BOARD_APM1 || CONFIG_HAL_BOARD == HAL_BOARD_AVR_SITL || CONFIG_HAL_BOARD == HAL_BOARD_PX4 || HAL_BOARD_SMACCM
 #define COPTER_LED_1 AN8       // Motor or Aux LED
 #define COPTER_LED_2 AN9       // Motor LED
 #define COPTER_LED_3 AN10      // Motor or GPS LED
 #define COPTER_LED_4 AN11      // Motor LED
 #define COPTER_LED_5 AN12      // Motor LED
 #define COPTER_LED_6 AN13      // Motor LED
 #define COPTER_LED_7 AN14      // Motor LED
 #define COPTER_LED_8 AN15      // Motor LED
#endif


//////////////////////////////////////////////////////////////////////////////
// Pushbutton & Relay
//

#ifndef CONFIG_PUSHBUTTON
 # define CONFIG_PUSHBUTTON ENABLED
#endif

#ifndef CONFIG_RELAY
 # define CONFIG_RELAY ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// Barometer
//

#ifndef CONFIG_BARO
 # define CONFIG_BARO AP_BARO_BMP085
#endif

//////////////////////////////////////////////////////////////////////////////
// Sonar
//

#ifndef CONFIG_SONAR_SOURCE
 # define CONFIG_SONAR_SOURCE SONAR_SOURCE_ADC
#endif

#if CONFIG_SONAR_SOURCE == SONAR_SOURCE_ADC && CONFIG_ADC == DISABLED
 # warning Cannot use ADC for CONFIG_SONAR_SOURCE, becaude CONFIG_ADC is DISABLED
 # warning Defaulting CONFIG_SONAR_SOURCE to ANALOG_PIN
 # undef CONFIG_SONAR_SOURCE
 # define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
#endif

#if CONFIG_SONAR_SOURCE == SONAR_SOURCE_ADC
 # ifndef CONFIG_SONAR_SOURCE_ADC_CHANNEL
  #  define CONFIG_SONAR_SOURCE_ADC_CHANNEL 7
 # endif
#elif CONFIG_SONAR_SOURCE == SONAR_SOURCE_ANALOG_PIN
 # ifndef CONFIG_SONAR_SOURCE_ANALOG_PIN
  #  define CONFIG_SONAR_SOURCE_ANALOG_PIN 0
 # endif
#else
 # warning Invalid value for CONFIG_SONAR_SOURCE, disabling sonar
 # undef SONAR_ENABLED
 # define SONAR_ENABLED DISABLED
#endif

#ifndef CONFIG_SONAR
 # define CONFIG_SONAR ENABLED
#endif

#ifndef SONAR_ALT_HEALTH_MAX
 # define SONAR_ALT_HEALTH_MAX 3            // number of good reads that indicates a healthy sonar
#endif

#ifndef THR_SURFACE_TRACKING_P
 # define THR_SURFACE_TRACKING_P 0.2        // gain for controlling how quickly sonar range adjusts target altitude (lower means slower reaction)
#endif

#ifndef THR_SURFACE_TRACKING_VELZ_MAX
 # define THR_SURFACE_TRACKING_VELZ_MAX 30  // max speed number of good reads that indicates a healthy sonar
#endif

//////////////////////////////////////////////////////////////////////////////
// Channel 7 default option
//

#ifndef CH7_OPTION
 # define CH7_OPTION             CH7_SAVE_WP
#endif


//////////////////////////////////////////////////////////////////////////////
// HIL_MODE                                 OPTIONAL

#ifndef HIL_MODE
 #define HIL_MODE        HIL_MODE_DISABLED
#endif

#if HIL_MODE != HIL_MODE_DISABLED       // we are in HIL mode

 # undef GPS_PROTOCOL
 # define GPS_PROTOCOL GPS_PROTOCOL_NONE

 #undef CONFIG_SONAR
 #define CONFIG_SONAR DISABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// GPS_PROTOCOL
//
#ifndef GPS_PROTOCOL
 # define GPS_PROTOCOL           GPS_PROTOCOL_AUTO
#endif


#ifndef MAV_SYSTEM_ID
 # define MAV_SYSTEM_ID          1
#endif


//////////////////////////////////////////////////////////////////////////////
// Serial port speeds.
//
#ifndef SERIAL0_BAUD
 # define SERIAL0_BAUD                   115200
#endif
#ifndef SERIAL3_BAUD
 # define SERIAL3_BAUD                    57600
#endif


//////////////////////////////////////////////////////////////////////////////
// Battery monitoring
//
#ifndef LOW_VOLTAGE
 # define LOW_VOLTAGE                    10.5f
#endif
#ifndef VOLT_DIV_RATIO
 # define VOLT_DIV_RATIO                 3.56f
#endif

#ifndef CURR_AMP_PER_VOLT
 # define CURR_AMP_PER_VOLT              27.32f
#endif
#ifndef CURR_AMPS_OFFSET
 # define CURR_AMPS_OFFSET               0.0f
#endif
#ifndef HIGH_DISCHARGE
 # define HIGH_DISCHARGE                 1760
#endif

// Battery failsafe
#ifndef FS_BATTERY
 # define FS_BATTERY              DISABLED
#endif



//////////////////////////////////////////////////////////////////////////////
// INPUT_VOLTAGE
//
#ifndef INPUT_VOLTAGE
 # define INPUT_VOLTAGE                  5.0f
#endif


//////////////////////////////////////////////////////////////////////////////
//  MAGNETOMETER
#ifndef MAGNETOMETER
 # define MAGNETOMETER                   ENABLED
#endif
#ifndef MAG_ORIENTATION
 # define MAG_ORIENTATION                AP_COMPASS_COMPONENTS_DOWN_PINS_FORWARD
#endif


//////////////////////////////////////////////////////////////////////////////
//  OPTICAL_FLOW
#if defined( __AVR_ATmega2560__ )       // determines if optical flow code is included
 #define OPTFLOW                        ENABLED
#endif
#ifndef OPTFLOW                         // sets global enabled/disabled flag for optflow (as seen in CLI)
 # define OPTFLOW                       DISABLED
#endif
#ifndef OPTFLOW_ORIENTATION
 # define OPTFLOW_ORIENTATION    AP_OPTICALFLOW_ADNS3080_PINS_FORWARD
#endif
#ifndef OPTFLOW_RESOLUTION
 # define OPTFLOW_RESOLUTION     ADNS3080_RESOLUTION_1600
#endif
#ifndef OPTFLOW_FOV
 # define OPTFLOW_FOV                    AP_OPTICALFLOW_ADNS3080_08_FOV
#endif
// optical flow based loiter PI values
#ifndef OPTFLOW_ROLL_P
 #define OPTFLOW_ROLL_P 2.5f
#endif
#ifndef OPTFLOW_ROLL_I
 #define OPTFLOW_ROLL_I 0.5f
#endif
#ifndef OPTFLOW_ROLL_D
 #define OPTFLOW_ROLL_D 0.12f
#endif
#ifndef OPTFLOW_PITCH_P
 #define OPTFLOW_PITCH_P 2.5f
#endif
#ifndef OPTFLOW_PITCH_I
 #define OPTFLOW_PITCH_I 0.5f
#endif
#ifndef OPTFLOW_PITCH_D
 #define OPTFLOW_PITCH_D 0.12f
#endif
#ifndef OPTFLOW_IMAX
 #define OPTFLOW_IMAX 1
#endif


//////////////////////////////////////////////////////////////////////////////
// RADIO CONFIGURATION
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// FLIGHT_MODE
//

#if !defined(FLIGHT_MODE_1)
 # define FLIGHT_MODE_1                  STABILIZE
#endif
#if !defined(FLIGHT_MODE_2)
 # define FLIGHT_MODE_2                  STABILIZE
#endif
#if !defined(FLIGHT_MODE_3)
 # define FLIGHT_MODE_3                  STABILIZE
#endif
#if !defined(FLIGHT_MODE_4)
 # define FLIGHT_MODE_4                  STABILIZE
#endif
#if !defined(FLIGHT_MODE_5)
 # define FLIGHT_MODE_5                  STABILIZE
#endif
#if !defined(FLIGHT_MODE_6)
 # define FLIGHT_MODE_6                  STABILIZE
#endif


//////////////////////////////////////////////////////////////////////////////
// Throttle Failsafe
//
// possible values for FS_THR parameter
#define FS_THR_DISABLED                    0
#define FS_THR_ENABLED_ALWAYS_RTL          1
#define FS_THR_ENABLED_CONTINUE_MISSION    2

#ifndef FS_THR_VALUE_DEFAULT
 # define FS_THR_VALUE_DEFAULT             975
#endif


#ifndef MINIMUM_THROTTLE
 # define MINIMUM_THROTTLE       130
#endif
#ifndef MAXIMUM_THROTTLE
 # define MAXIMUM_THROTTLE       1000
#endif

#ifndef LAND_SPEED
 # define LAND_SPEED    50          // the descent speed for the final stage of landing in cm/s
#endif
#ifndef LAND_START_ALT
 # define LAND_START_ALT 1000         // altitude in cm where land controller switches to slow rate of descent
#endif
#ifndef LAND_DETECTOR_TRIGGER
 # define LAND_DETECTOR_TRIGGER 50    // number of 50hz iterations with near zero climb rate and low throttle that triggers landing complete.
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// STARTUP BEHAVIOUR
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// GROUND_START_DELAY
//
#ifndef GROUND_START_DELAY
 # define GROUND_START_DELAY             3
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// FLIGHT AND NAVIGATION CONTROL
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Y6 Support

#ifndef TOP_BOTTOM_RATIO
 # define TOP_BOTTOM_RATIO       1.00f
#endif


//////////////////////////////////////////////////////////////////////////////
// CAMERA TRIGGER AND CONTROL
//
#ifndef CAMERA
 # if defined( __AVR_ATmega1280__ )
  #  define CAMERA        DISABLED
 # else
  #  define CAMERA        ENABLED
 # endif
#endif

//////////////////////////////////////////////////////////////////////////////
// MOUNT (ANTENNA OR CAMERA)
//
#ifndef MOUNT
 # if defined( __AVR_ATmega1280__ )
  #  define MOUNT         DISABLED
 # else
  #  define MOUNT         ENABLED
 # endif
#endif

#ifndef MOUNT2
 # define MOUNT2         DISABLED
#endif

#if defined( __AVR_ATmega1280__ ) && (MOUNT == ENABLED || MOUNT2 == ENABLED)
 # warning "You choose to enable MOUNT on a small ATmega1280, CLI, CAMERA and AP_LIMITS will be disabled to free some space for it"

// The small ATmega1280 chip does not have enough memory for mount support
// so disable CLI, this will allow mount support and other improvements to fit.
// This should almost have no side effects, because the APM planner can now do a complete board setup.
 # define CLI_ENABLED DISABLED

// The small ATmega1280 chip does not have enough memory for mount support
// so disable AUTO GPS support, this will allow mount support and other improvements to fit.
// This should almost have no side effects, because the most users use MTK anyways.
// If the user defined a GPS protocol, than we will NOT overwrite it
 # if GPS_PROTOCOL == GPS_PROTOCOL_AUTO
  #  undef GPS_PROTOCOL
  #  define GPS_PROTOCOL GPS_PROTOCOL_MTK
 # endif

// To save some more space
 # undef CAMERA
 # define CAMERA         DISABLED
 # define AP_LIMITS      DISABLED

#endif


//////////////////////////////////////////////////////////////////////////////
// Attitude Control
//

// definitions for earth frame and body frame
// used to specify frame to rate controllers
#define EARTH_FRAME     0
#define BODY_FRAME      1

// active NAV controller
#ifndef NAV_WP_ACTIVE
 # define NAV_WP_ACTIVE NAV_WP
#endif
// active LOITER controller
#ifndef NAV_LOITER_ACTIVE
 # define NAV_LOITER_ACTIVE NAV_LOITER
#endif

// Flight mode roll, pitch, yaw, throttle and navigation definitions

// Acro Mode
#ifndef ACRO_YAW
 # define ACRO_YAW           	    YAW_ACRO
#endif

#ifndef ACRO_RP
 # define ACRO_RP            	    ROLL_PITCH_ACRO
#endif

#ifndef ACRO_THR
 # define ACRO_THR           	    THROTTLE_MANUAL
#endif

#ifndef ACRO_NAV
 # define ACRO_NAV           	    NAV_NONE
#endif

// Alt Hold Mode
#ifndef ALT_HOLD_YAW
 # define ALT_HOLD_YAW           	YAW_HOLD
#endif

#ifndef ALT_HOLD_RP
 # define ALT_HOLD_RP            	ROLL_PITCH_STABLE
#endif

#ifndef ALT_HOLD_THR
 # define ALT_HOLD_THR           	THROTTLE_HOLD
#endif

#ifndef ALT_HOLD_NAV
 # define ALT_HOLD_NAV           	NAV_NONE
#endif

// AUTO Mode
#ifndef AUTO_YAW
 # define AUTO_YAW                  YAW_LOOK_AT_NEXT_WP
#endif

#ifndef AUTO_RP
 # define AUTO_RP                   ROLL_PITCH_AUTO
#endif

#ifndef AUTO_THR
 # define AUTO_THR                  THROTTLE_AUTO
#endif

// CIRCLE Mode
#ifndef CIRCLE_YAW
 # define CIRCLE_YAW             	YAW_LOOK_AT_LOCATION
#endif

#ifndef CIRCLE_RP
 # define CIRCLE_RP                 ROLL_PITCH_AUTO
#endif

#ifndef CIRCLE_THR
 # define CIRCLE_THR                THROTTLE_HOLD
#endif

#ifndef CIRCLE_NAV
 # define CIRCLE_NAV           	    NAV_CIRCLE
#endif

// Guided Mode
#ifndef GUIDED_YAW
 # define GUIDED_YAW                YAW_LOOK_AT_NEXT_WP
#endif

#ifndef GUIDED_RP
 # define GUIDED_RP                 ROLL_PITCH_AUTO
#endif

#ifndef GUIDED_THR
 # define GUIDED_THR                THROTTLE_AUTO
#endif

#ifndef GUIDED_NAV
 # define GUIDED_NAV           	    NAV_WP
#endif

// LOITER Mode
#ifndef LOITER_YAW
 # define LOITER_YAW             	YAW_HOLD
#endif

#ifndef LOITER_RP
 # define LOITER_RP                 ROLL_PITCH_AUTO
#endif

#ifndef LOITER_THR
 # define LOITER_THR                THROTTLE_HOLD
#endif

#ifndef LOITER_NAV
 # define LOITER_NAV                NAV_LOITER_ACTIVE
#endif

// POSITION Mode
#ifndef POSITION_YAW
 # define POSITION_YAW             	YAW_HOLD
#endif

#ifndef POSITION_RP
 # define POSITION_RP               ROLL_PITCH_AUTO
#endif

#ifndef POSITION_THR
 # define POSITION_THR              THROTTLE_HOLD
#endif

#ifndef POSITION_NAV
 # define POSITION_NAV              NAV_LOITER_ACTIVE
#endif


// RTL Mode
#ifndef RTL_YAW
 # define RTL_YAW                   YAW_LOOK_AT_NEXT_WP
#endif

#ifndef RTL_RP
 # define RTL_RP                    ROLL_PITCH_AUTO
#endif

#ifndef RTL_THR
 # define RTL_THR                   THROTTLE_AUTO
#endif

#ifndef SUPER_SIMPLE
 # define SUPER_SIMPLE           	DISABLED
#endif

#ifndef SUPER_SIMPLE_RADIUS
 # define SUPER_SIMPLE_RADIUS    	1000
#endif

// RTL Mode
#ifndef RTL_ALT_FINAL
 # define RTL_ALT_FINAL             200     // the altitude the vehicle will move to as the final stage of Returning to Launch.  Set to zero to land.
#endif

#ifndef RTL_ALT
 # define RTL_ALT 				    1500    // default alt to return to home in cm, 0 = Maintain current altitude
#endif

#ifndef RTL_ALT_MAX
 # define RTL_ALT_MAX               8000    // Max height to return to home in cm (i.e 80m)
#endif

#ifndef RTL_LOITER_TIME
 # define RTL_LOITER_TIME           5000    // Time (in milliseconds) to loiter above home before begining final descent
#endif



// Optical Flow LOITER Mode
#ifndef OF_LOITER_YAW
 # define OF_LOITER_YAW          	YAW_HOLD
#endif

#ifndef OF_LOITER_RP
 # define OF_LOITER_RP              ROLL_PITCH_STABLE_OF
#endif

#ifndef OF_LOITER_THR
 # define OF_LOITER_THR             THROTTLE_HOLD
#endif

#ifndef OF_LOITER_NAV
 # define OF_LOITER_NAV             NAV_NONE
#endif

//////////////////////////////////////////////////////////////////////////////
// Attitude Control
//

// Extra motor values that are changed from time to time by jani @ jDrones as software
// and charachteristics changes.
#ifdef MOTORS_JD880
 # define STABILIZE_ROLL_P          3.7f
 # define STABILIZE_ROLL_I          0.0f
 # define STABILIZE_ROLL_IMAX    	8.0f            // degrees
 # define STABILIZE_PITCH_P         3.7f
 # define STABILIZE_PITCH_I         0.0f
 # define STABILIZE_PITCH_IMAX   	8.0f            // degrees
#endif

#ifdef MOTORS_JD850
 # define STABILIZE_ROLL_P          4.2f
 # define STABILIZE_ROLL_I          0.0f
 # define STABILIZE_ROLL_IMAX    	8.0f            // degrees
 # define STABILIZE_PITCH_P         4.2f
 # define STABILIZE_PITCH_I         0.0f
 # define STABILIZE_PITCH_IMAX   	8.0f            // degrees
#endif


#ifndef ACRO_P
 # define ACRO_P                 4.5f
#endif

#ifndef AXIS_LOCK_ENABLED
 # define AXIS_LOCK_ENABLED      ENABLED
#endif

// Good for smaller payload motors.
#ifndef STABILIZE_ROLL_P
 # define STABILIZE_ROLL_P          4.5f
#endif
#ifndef STABILIZE_ROLL_I
 # define STABILIZE_ROLL_I          0.0f
#endif
#ifndef STABILIZE_ROLL_IMAX
 # define STABILIZE_ROLL_IMAX    	8.0f            // degrees
#endif

#ifndef STABILIZE_PITCH_P
 # define STABILIZE_PITCH_P         4.5f
#endif
#ifndef STABILIZE_PITCH_I
 # define STABILIZE_PITCH_I         0.0f
#endif
#ifndef STABILIZE_PITCH_IMAX
 # define STABILIZE_PITCH_IMAX   	8.0f            // degrees
#endif

#ifndef  STABILIZE_YAW_P
 # define STABILIZE_YAW_P           4.5f            // increase for more aggressive Yaw Hold, decrease if it's bouncy
#endif
#ifndef  STABILIZE_YAW_I
 # define STABILIZE_YAW_I           0.0f
#endif
#ifndef  STABILIZE_YAW_IMAX
 # define STABILIZE_YAW_IMAX        8.0f            // degrees * 100
#endif

#ifndef YAW_LOOK_AHEAD_MIN_SPEED
 # define YAW_LOOK_AHEAD_MIN_SPEED  1000             // minimum ground speed in cm/s required before copter is aimed at ground course
#endif


//////////////////////////////////////////////////////////////////////////////
// Stabilize Rate Control
//

#ifndef MAX_INPUT_ROLL_ANGLE
 # define MAX_INPUT_ROLL_ANGLE      4500
#endif
#ifndef MAX_INPUT_PITCH_ANGLE
 # define MAX_INPUT_PITCH_ANGLE     4500
#endif
#ifndef RATE_ROLL_P
 # define RATE_ROLL_P        		0.150f
#endif
#ifndef RATE_ROLL_I
 # define RATE_ROLL_I        		0.100f
#endif
#ifndef RATE_ROLL_D
 # define RATE_ROLL_D        		0.004f
#endif
#ifndef RATE_ROLL_IMAX
 # define RATE_ROLL_IMAX         	5.0f                    // degrees
#endif

#ifndef RATE_PITCH_P
 # define RATE_PITCH_P       		0.150f
#endif
#ifndef RATE_PITCH_I
 # define RATE_PITCH_I       		0.100f
#endif
#ifndef RATE_PITCH_D
 # define RATE_PITCH_D       		0.004f
#endif
#ifndef RATE_PITCH_IMAX
 # define RATE_PITCH_IMAX        	5.0f                    // degrees
#endif

#ifndef RATE_YAW_P
 # define RATE_YAW_P              	0.25f
#endif
#ifndef RATE_YAW_I
 # define RATE_YAW_I              	0.015f
#endif
#ifndef RATE_YAW_D
 # define RATE_YAW_D              	0.000f
#endif
#ifndef RATE_YAW_IMAX
 # define RATE_YAW_IMAX            	8.0f          // degrees
#endif


//////////////////////////////////////////////////////////////////////////////
// Rate controlled stabilized variables
//

#ifndef MAX_ROLL_OVERSHOOT
 #define MAX_ROLL_OVERSHOOT			3000
#endif

#ifndef MAX_PITCH_OVERSHOOT
 #define MAX_PITCH_OVERSHOOT		3000
#endif

#ifndef MAX_YAW_OVERSHOOT
 #define MAX_YAW_OVERSHOOT			1000
#endif

#ifndef ACRO_BALANCE_ROLL
 #define ACRO_BALANCE_ROLL			200
#endif

#ifndef ACRO_BALANCE_PITCH
 #define ACRO_BALANCE_PITCH			200
#endif

#ifndef ACRO_TRAINER_ENABLED
 #define ACRO_TRAINER_ENABLED       ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// Loiter control gains
//
#ifndef LOITER_P
 # define LOITER_P             		.20f
#endif
#ifndef LOITER_I
 # define LOITER_I             		0.0f
#endif
#ifndef LOITER_IMAX
 # define LOITER_IMAX          		30             // degrees
#endif

//////////////////////////////////////////////////////////////////////////////
// Loiter Navigation control gains
//
#ifndef LOITER_RATE_P
 # define LOITER_RATE_P          	5.0f            //
#endif
#ifndef LOITER_RATE_I
 # define LOITER_RATE_I          	0.04f           // Wind control
#endif
#ifndef LOITER_RATE_D
 # define LOITER_RATE_D          	0.40f           // try 2 or 3 for LOITER_RATE 1
#endif
#ifndef LOITER_RATE_IMAX
 # define LOITER_RATE_IMAX       	30                     // degrees
#endif

//////////////////////////////////////////////////////////////////////////////
// WP Navigation control gains
//
#ifndef NAV_P
 # define NAV_P                     2.4f                    //
#endif
#ifndef NAV_I
 # define NAV_I                     0.17f           // Wind control
#endif
#ifndef NAV_D
 # define NAV_D                     0.00f           // .95
#endif
#ifndef NAV_IMAX
 # define NAV_IMAX                  18                     // degrees
#endif

#ifndef AUTO_SLEW_RATE
 # define AUTO_SLEW_RATE         	30                     // degrees/sec
#endif

#ifndef AUTO_YAW_SLEW_RATE
 # define AUTO_YAW_SLEW_RATE        60                     // degrees/sec
#endif


#ifndef WAYPOINT_SPEED_MAX
 # define WAYPOINT_SPEED_MAX        500                    // 6m/s error = 13mph
#endif

#ifndef WAYPOINT_SPEED_MIN
 # define WAYPOINT_SPEED_MIN        150                    // 1m/s
#endif

#ifndef TILT_COMPENSATION
  #   define TILT_COMPENSATION 54
#endif



//////////////////////////////////////////////////////////////////////////////
// Throttle control gains
//
#ifndef THROTTLE_CRUISE
 # define THROTTLE_CRUISE       450            //
#endif

#ifndef THR_MID
 # define THR_MID        500                            // Throttle output (0 ~ 1000) when throttle stick is in mid position
#endif

#ifndef ALT_HOLD_P
 # define ALT_HOLD_P            2.0f
#endif
#ifndef ALT_HOLD_I
 # define ALT_HOLD_I            0.0f
#endif
#ifndef ALT_HOLD_IMAX
 # define ALT_HOLD_IMAX         300
#endif

// RATE control
#ifndef THROTTLE_P
 # define THROTTLE_P            6.0f
#endif
#ifndef THROTTLE_I
 # define THROTTLE_I            0.0f
#endif
#ifndef THROTTLE_D
 # define THROTTLE_D            0.2f
#endif

#ifndef THROTTLE_IMAX
 # define THROTTLE_IMAX         300
#endif


// default minimum and maximum vertical velocity the autopilot may request
#ifndef AUTO_VELZ_MIN
 # define AUTO_VELZ_MIN -125
#endif
#ifndef AUTO_VELZ_MAX
 # define AUTO_VELZ_MAX 125
#endif

// default maximum vertical velocity the pilot may request
#ifndef PILOT_VELZ_MAX
 # define PILOT_VELZ_MAX    250     // maximum vertical velocity in cm/s
#endif
#define ACCELERATION_MAX_Z  750     // maximum veritcal acceleration in cm/s/s

// Throttle Accel control
#ifndef THROTTLE_ACCEL_P
 # define THROTTLE_ACCEL_P  0.75f
#endif
#ifndef THROTTLE_ACCEL_I
 # define THROTTLE_ACCEL_I  1.50f
#endif
#ifndef THROTTLE_ACCEL_D
 # define THROTTLE_ACCEL_D 0.0f
#endif
#ifndef THROTTLE_ACCEL_IMAX
 # define THROTTLE_ACCEL_IMAX 500
#endif


//////////////////////////////////////////////////////////////////////////////
// Crosstrack compensation
//
#ifndef CROSSTRACK_GAIN
 # define CROSSTRACK_GAIN       .2f
#endif
#ifndef CROSSTRACK_MIN_DISTANCE
 # define CROSSTRACK_MIN_DISTANCE       15
#endif




//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// DEBUGGING
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// DEBUG_LEVEL
//
#ifndef DEBUG_LEVEL
 # define DEBUG_LEVEL SEVERITY_LOW
#endif

//////////////////////////////////////////////////////////////////////////////
// Dataflash logging control
//
// Logging must be disabled for 1280 build.
#if defined( __AVR_ATmega1280__ )
 # if LOGGING_ENABLED == ENABLED
// If logging was enabled in APM_Config or command line, warn the user.
  #  warning "Logging is not supported on ATmega1280"
  #  undef LOGGING_ENABLED
 # endif
 # ifndef LOGGING_ENABLED
  #  define LOGGING_ENABLED    DISABLED
 # endif
#elif !defined(LOGGING_ENABLED)
// Logging is enabled by default for all other builds.
 # define LOGGING_ENABLED                ENABLED
#endif


#ifndef LOG_ATTITUDE_FAST
 # define LOG_ATTITUDE_FAST             DISABLED
#endif
#ifndef LOG_ATTITUDE_MED
 # define LOG_ATTITUDE_MED              ENABLED
#endif
#ifndef LOG_GPS
 # define LOG_GPS                       ENABLED
#endif
#ifndef LOG_PM
 # define LOG_PM                        ENABLED
#endif
#ifndef LOG_CTUN
 # define LOG_CTUN                      ENABLED
#endif
#ifndef LOG_NTUN
 # define LOG_NTUN                      ENABLED
#endif
#ifndef LOG_MODE
 # define LOG_MODE                      ENABLED
#endif
#ifndef LOG_IMU
 # define LOG_IMU                       DISABLED
#endif
#ifndef LOG_CMD
 # define LOG_CMD                       ENABLED
#endif
// current
#ifndef LOG_CURRENT
 # define LOG_CURRENT                   DISABLED
#endif
// quad motor PWMs
#ifndef LOG_MOTORS
 # define LOG_MOTORS                    DISABLED
#endif
// optical flow
#ifndef LOG_OPTFLOW
 # define LOG_OPTFLOW                   DISABLED
#endif
#ifndef LOG_PID
 # define LOG_PID                       DISABLED
#endif
#ifndef LOG_ITERM
 # define LOG_ITERM                     DISABLED
#endif
#ifndef LOG_INAV
 # define LOG_INAV                      DISABLED
#endif
#ifndef LOG_CAMERA
 # define LOG_CAMERA                    DISABLED
#endif

// calculate the default log_bitmask
#define LOGBIT(_s)     (LOG_ ## _s ? MASK_LOG_ ## _s : 0)

#define DEFAULT_LOG_BITMASK \
    LOGBIT(ATTITUDE_FAST)   | \
    LOGBIT(ATTITUDE_MED)    | \
    LOGBIT(GPS)             | \
    LOGBIT(PM)              | \
    LOGBIT(CTUN)            | \
    LOGBIT(NTUN)            | \
    LOGBIT(MODE)            | \
    LOGBIT(IMU)             | \
    LOGBIT(CMD)             | \
    LOGBIT(CURRENT)         | \
    LOGBIT(MOTORS)          | \
    LOGBIT(OPTFLOW)         | \
    LOGBIT(PID)             | \
    LOGBIT(ITERM)           | \
    LOGBIT(INAV)

// if we are using fast, Disable Medium
//#if LOG_ATTITUDE_FAST == ENABLED
//	#undef LOG_ATTITUDE_MED
//	#define LOG_ATTITUDE_MED        DISABLED
//#endif

//////////////////////////////////////////////////////////////////////////////
// Navigation defaults
//
#ifndef WP_RADIUS_DEFAULT
 # define WP_RADIUS_DEFAULT      2
#endif

#ifndef CIRCLE_RADIUS
 # define CIRCLE_RADIUS 10              // meters for circle mode
#endif

#ifndef USE_CURRENT_ALT
 # define USE_CURRENT_ALT FALSE
#endif

//////////////////////////////////////////////////////////////////////////////
// AP_Limits Defaults
//


// Enable/disable AP_Limits
#ifndef AP_LIMITS
 #define AP_LIMITS ENABLED
#endif

// Use PIN for displaying LIMITS status. 0 is disabled.
#ifndef LIMITS_TRIGGERED_PIN
 #define LIMITS_TRIGGERED_PIN 0
#endif

// PWM of "on" state for LIM_CHANNEL
#ifndef LIMITS_ENABLE_PWM
 #define LIMITS_ENABLE_PWM 1800
#endif

#ifndef LIM_ENABLED
 #define LIM_ENABLED 0
#endif

#ifndef LIM_ALT_ON
 #define LIM_ALT_ON 0
#endif

#ifndef LIM_FNC_ON
 #define LIM_FNC_ON 0
#endif

#ifndef LIM_GPSLCK_ON
 #define LIM_GPSLCK_ON 0
#endif



//////////////////////////////////////////////////////////////////////////////
// Developer Items
//

// use this to completely disable the CLI
#ifndef CLI_ENABLED
// Sorry the chip is just too small to let this fit
 # if defined( __AVR_ATmega1280__ )
  #  define CLI_ENABLED           DISABLED
 # else
  #  define CLI_ENABLED           ENABLED
 # endif
#endif

// use this to disable the CLI slider switch
#ifndef CLI_SLIDER_ENABLED
 # define CLI_SLIDER_ENABLED DISABLED
#endif

// experimental mpu6000 DMP code
#ifndef DMP_ENABLED
 # define DMP_ENABLED DISABLED
#endif

// experimental mpu6000 DMP code
#ifndef SECONDARY_DMP_ENABLED
 # define SECONDARY_DMP_ENABLED DISABLED
#endif

// Inertia based contollers.
#ifndef INERTIAL_NAV_XY
 # define INERTIAL_NAV_XY DISABLED
#endif

#endif // __ARDUCOPTER_CONFIG_H__
