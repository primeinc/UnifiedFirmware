#pragma once

#define CONFIGURATION_BACKEND_H_VERSION 020006

//===========================================================================
//======================= DO NOT MODIFY THIS FILE ===========================
//===========================================================================

/**
 * Temp Settings
 */

#define DUMMY_THERMISTOR_998_VALUE 25
#define DUMMY_THERMISTOR_999_VALUE 100
#define MAX_REDUNDANT_TEMP_SENSOR_DIFF 10

#define HEATER_0_MINTEMP   0
#define HEATER_1_MINTEMP   HEATER_0_MINTEMP
#define HEATER_2_MINTEMP   HEATER_0_MINTEMP
#define HEATER_3_MINTEMP   HEATER_0_MINTEMP
#define HEATER_4_MINTEMP   HEATER_0_MINTEMP
#define HEATER_5_MINTEMP   HEATER_0_MINTEMP
#define HEATER_6_MINTEMP   HEATER_0_MINTEMP
#define HEATER_7_MINTEMP   HEATER_0_MINTEMP
#define BED_MINTEMP        HEATER_0_MINTEMP

#if ENABLED(HIGH_TEMP_THERMISTOR)
  #define HEATER_0_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
  #define HEATER_1_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
  #define HEATER_2_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
  #define HEATER_3_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
  #define HEATER_4_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
  #define HEATER_5_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
  #define HEATER_6_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
  #define HEATER_7_MAXTEMP HIGH_TEMP_THERMISTOR_TEMP
#else
  #define HEATER_0_MAXTEMP 275
  #define HEATER_1_MAXTEMP HEATER_0_MAXTEMP
  #define HEATER_2_MAXTEMP HEATER_0_MAXTEMP
  #define HEATER_3_MAXTEMP HEATER_0_MAXTEMP
  #define HEATER_4_MAXTEMP HEATER_0_MAXTEMP
  #define HEATER_5_MAXTEMP HEATER_0_MAXTEMP
  #define HEATER_6_MAXTEMP HEATER_0_MAXTEMP
  #define HEATER_7_MAXTEMP HEATER_0_MAXTEMP
#endif

#define BED_MAXTEMP      120

#define TEMP_RESIDENCY_TIME     10
#define TEMP_WINDOW              1
#define TEMP_HYSTERESIS          3

#define TEMP_BED_RESIDENCY_TIME 10
#define TEMP_BED_WINDOW          1
#define TEMP_BED_HYSTERESIS      3

// PID Settings
#define PIDTEMP
#define BANG_MAX 255
#define PID_MAX BANG_MAX
#define PID_K1 0.95

#ifndef DEFAULT_Kp
  #define DEFAULT_Kp 22.2 // Define Marlin default PID if no machine specific PID is defined.
  #define DEFAULT_Ki 1.08
  #define DEFAULT_Kd 114
#endif

#define PIDTEMPBED
#define MAX_BED_POWER 255
#if ENABLED(PIDTEMPBED)
  #ifndef DEFAULT_bedKp
    #define DEFAULT_bedKp 10.00 // Define Marlin default bed PID if no machine specific PID is defined.
    #define DEFAULT_bedKi .023
    #define DEFAULT_bedKd 305.4
  #endif
#endif

#if EITHER(PIDTEMP, PIDTEMPBED)
  #define PID_FUNCTIONAL_RANGE 10
#endif
// End PID Settings

// Enable Thermal Protection for Bed and Hotends
#define THERMAL_PROTECTION_HOTENDS
#define THERMAL_PROTECTION_BED

/**
 * ABL Probe Settings
 */

#if ENABLED(CUSTOM_PROBE)
  #define ABL_ENABLE
#endif

#if ENABLED(ABL_ENABLE)
  //#define ENABLE_LEVELING_FADE_HEIGHT // Disable for release. Can cause issues.
  #define SEGMENT_LEVELED_MOVES
  #define LEVELED_SEGMENT_LENGTH 5.0
  
  #undef Z_PROBE_OFFSET_RANGE_MIN //Some machines define these even with no probe. Override when a probe is used to ensure correct settings.
  #define Z_PROBE_OFFSET_RANGE_MIN    -5
  #undef Z_PROBE_OFFSET_RANGE_MAX //Some machines define these even with no probe. Override when a probe is used to ensure correct settings.
  #define Z_PROBE_OFFSET_RANGE_MAX     1
  
  #define Z_MIN_PROBE_REPEATABILITY_TEST
  #define Z_AFTER_PROBING              5
  #define Z_PROBE_LOW_POINT           -2
  #if DISABLED(BLTOUCH)
    #define FIX_MOUNTED_PROBE
  #endif
  #if ENABLED(SLOWER_PROBE_MOVES)
    #define XY_PROBE_SPEED 8000
  #else
    #if ENABLED(EZABL_SUPERFASTPROBE)
      #define XY_PROBE_SPEED 16000
    #else
      #define XY_PROBE_SPEED 12000
    #endif
  #endif
  #define PROBING_MARGIN EZABL_PROBE_EDGE
  #if ENABLED(FIX_MOUNTED_PROBE) && DISABLED(HEATERS_ON_DURING_PROBING)
    #define PROBING_HEATERS_OFF   
  #endif
  #define MULTIPLE_PROBING 2
  #define AUTO_BED_LEVELING_BILINEAR
  #define EXTRAPOLATE_BEYOND_GRID
  #define GRID_MAX_POINTS_X EZABL_POINTS
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X
  #define Z_SAFE_HOMING
  #if ENABLED(Z_SAFE_HOMING)
    #define Z_SAFE_HOMING_X_POINT ((X_BED_SIZE) / 2)    // X point for Z homing
    #define Z_SAFE_HOMING_Y_POINT ((Y_BED_SIZE) / 2)    // Y point for Z homing
  #endif
  
  // ABL Probe Logic Settings
  #if ENABLED(BLTOUCH) // BLTouch uses false
    #undef Z_MIN_PROBE_ENDSTOP_INVERTING
    #define Z_MIN_PROBE_ENDSTOP_INVERTING false
    #undef Z_MIN_ENDSTOP_INVERTING
    #define Z_MIN_ENDSTOP_INVERTING false
  #else                // EZABL uses true
    #undef Z_MIN_PROBE_ENDSTOP_INVERTING
    #define Z_MIN_PROBE_ENDSTOP_INVERTING true
    #undef Z_MIN_ENDSTOP_INVERTING
    #define Z_MIN_ENDSTOP_INVERTING true
  #endif

#endif

/**
 * General Firmware Settings
 */

#define STRING_CONFIG_H_AUTHOR "TH3D Studio"
#define CUSTOM_VERSION_FILE Version.h

#if ENABLED(USER_PRINTER_NAME)
  #define CUSTOM_MACHINE_NAME USER_PRINTER_NAME
#else
  #define CUSTOM_MACHINE_NAME "TH3D UFW2"
#endif

#define S_CURVE_ACCELERATION
#define DEFAULT_NOMINAL_FILAMENT_DIA 1.75
#define HOMING_FEEDRATE_XY (50*60)

#define Z_MIN_POS 0
#define X_MAX_POS X_BED_SIZE
#define Y_MAX_POS Y_BED_SIZE
#define VALIDATE_HOMING_ENDSTOPS
#define PRINTJOB_TIMER_AUTOSTART

#if DISABLED(NO_SDCARD)
  #define SDSUPPORT
#endif

#if DISABLED(SPEAKER_KILL)
  #define SPEAKER
#endif

#if ENABLED(FAN_FIX)
  #define FAN_SOFT_PWM
  #define SOFT_PWM_SCALE 1
#else
  #define SOFT_PWM_SCALE 0
#endif

#if BOTH(EZABL_SUPERFASTPROBE, ABL_ENABLE) && DISABLED(BLTOUCH)
  #define HOMING_FEEDRATE_Z  (15*60)
#elif BOTH(EZABL_FASTPROBE, ABL_ENABLE) && DISABLED(BLTOUCH)
  #define HOMING_FEEDRATE_Z  (8*60)
#else
  #define HOMING_FEEDRATE_Z  (4*60)
#endif

#define Z_PROBE_SPEED_FAST HOMING_FEEDRATE_Z
#define Z_PROBE_SPEED_SLOW (Z_PROBE_SPEED_FAST / 2)

#if ENABLED(BLTOUCH)
  #define Z_CLEARANCE_DEPLOY_PROBE   12
  #define Z_CLEARANCE_BETWEEN_PROBES 8
  #define Z_CLEARANCE_MULTI_PROBE    8
  #define ENDSTOPPULLUP_ZMIN
  #define ENDSTOPPULLUP_ZMIN_PROBE
#elif BOTH(EZABL_SUPERFASTPROBE, ABL_ENABLE) && DISABLED(BLTOUCH)
  #define Z_CLEARANCE_DEPLOY_PROBE   1
  #define Z_CLEARANCE_BETWEEN_PROBES 2
  #define Z_CLEARANCE_MULTI_PROBE    1
#else
  #define Z_CLEARANCE_DEPLOY_PROBE   5
  #define Z_CLEARANCE_BETWEEN_PROBES 3
  #define Z_CLEARANCE_MULTI_PROBE    3
#endif

#define HOST_KEEPALIVE_FEATURE
#define DEFAULT_KEEPALIVE_INTERVAL 2

#if DISABLED(SPACE_SAVER)
  #define BUSY_WHILE_HEATING
#endif

#define EEPROM_SETTINGS

#if ENABLED(SPACE_SAVER)
  #define DISABLE_M503
#endif

#define EEPROM_CHITCHAT
#define EEPROM_BOOT_SILENT

#if DISABLED(SPACE_SAVER)
  #define EEPROM_AUTO_INIT
#endif

#define MIN_SOFTWARE_ENDSTOPS
#if ENABLED(MIN_SOFTWARE_ENDSTOPS)
  #define MIN_SOFTWARE_ENDSTOP_X
  #define MIN_SOFTWARE_ENDSTOP_Y
  #if DISABLED(ABL_ENABLE)
    #define MIN_SOFTWARE_ENDSTOP_Z
  #endif
#endif

#define MAX_SOFTWARE_ENDSTOPS
#if ENABLED(MAX_SOFTWARE_ENDSTOPS)
  #define MAX_SOFTWARE_ENDSTOP_X
  #define MAX_SOFTWARE_ENDSTOP_Y
  #define MAX_SOFTWARE_ENDSTOP_Z
#endif

#define PREHEAT_1_LABEL       "PLA"
#define PREHEAT_1_TEMP_HOTEND 200
#define PREHEAT_1_TEMP_BED     60
#define PREHEAT_1_FAN_SPEED     0

#define PREHEAT_2_LABEL       "ABS"
#define PREHEAT_2_TEMP_HOTEND 240
#define PREHEAT_2_TEMP_BED    100
#define PREHEAT_2_FAN_SPEED     0

#define NOZZLE_PARK_FEATURE
#if ENABLED(NOZZLE_PARK_FEATURE)
  #define NOZZLE_PARK_POINT { 10, 10, 10 }
  #define NOZZLE_PARK_XY_FEEDRATE 100  
  #define NOZZLE_PARK_Z_FEEDRATE 5
#endif

#define DISABLE_X false
#define DISABLE_Y false
#define DISABLE_Z false
#define DISABLE_E false
#define DISABLE_INACTIVE_EXTRUDER

/**
 * LCD General Settings
 */

#define LCD_LANGUAGE en
#define DISPLAY_CHARSET_HD44780 JAPANESE
#define LCD_INFO_SCREEN_STYLE 0
#define DISABLE_REDUCED_ACCURACY_WARNING
#define LCD_FEEDBACK_FREQUENCY_DURATION_MS 2
#define LCD_FEEDBACK_FREQUENCY_HZ 5000
#if DISABLED(DWIN_CREALITY_LCD)
  #define SHOW_CUSTOM_BOOTSCREEN //Disable with SPACE_SAVER?
#endif

#if NONE(DWIN_CREALITY_LCD, SPACE_SAVER)
  #define INDIVIDUAL_AXIS_HOMING_MENU
#endif

#if DISABLED(SPACE_SAVER)
  #define LEVEL_BED_CORNERS
  #if ENABLED(LEVEL_BED_CORNERS)
    #define LEVEL_CORNERS_INSET_LFRB { 30, 30, 30, 30 }
    #define LEVEL_CORNERS_HEIGHT      0.0
    #define LEVEL_CORNERS_Z_HOP       4.0
    #define LEVEL_CENTER_TOO
  #endif
#endif