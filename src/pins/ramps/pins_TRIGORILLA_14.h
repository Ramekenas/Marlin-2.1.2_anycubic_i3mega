/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Arduino Mega with RAMPS v1.4 for Anycubic
 */

#define BOARD_INFO_NAME "Anycubic RAMPS 1.4"

//
// Servos
//
#if MB(TRIGORILLA_14_11)
  #define SERVO0_PIN                           5
  #define SERVO1_PIN                           6
  #define SERVO2_PIN                           4
  #define SERVO3_PIN                           11
#else
  #define PS_ON_PIN                            12
  #define SERVO0_PIN                           11
  #define SERVO1_PIN                           6
  #define SERVO2_PIN                           5
  #define SERVO3_PIN                           4
#endif



//
// PWM FETS
//
#define MOSFET_B_PIN                          45  // HEATER1

//
// Heaters / Fans
//
#define FAN_PIN                                9  // FAN0 part cooling
#define FAN1_PIN                               7  // FAN1 controller
#define FAN2_PIN                              44  // FAN2 E0
#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN               FAN2_PIN
#endif

//
// AnyCubic pin mappings
//
// Define the appropriate mapping option in Configuration.h:
// - TRIGORILLA_MAPPING_CHIRON
// - TRIGORILLA_MAPPING_I3MEGA
//

//
// Limit Switches
//
//#define ANYCUBIC_4_MAX_PRO_ENDSTOPS
#if ENABLED(ANYCUBIC_4_MAX_PRO_ENDSTOPS)
  #define X_MAX_PIN                           43
  #define Y_STOP_PIN                          19
#elif EITHER(TRIGORILLA_MAPPING_CHIRON, TRIGORILLA_MAPPING_I3MEGA)
  // Chiron uses AUX header for Y and Z endstops
  //#define Y_STOP_PIN                          42  // AUX rokas
  //#define Z_STOP_PIN                          43  // AUX rokas
  #define Z2_MIN_PIN                          Z_MIN_PIN  // Z- rokas

  #ifndef Z_MIN_PROBE_PIN
    #define Z_MIN_PROBE_PIN                    X_MAX_PIN
  #endif

  #define CONTROLLER_FAN_PIN            FAN1_PIN

  #if ENABLED(POWER_LOSS_RECOVERY)
    #define OUTAGETEST_PIN                    79
    #define OUTAGECON_PIN                     58
  #endif

  #if ENABLED(TRIGORILLA_MAPPING_CHIRON)
    #ifndef FIL_RUNOUT_PIN
      #define FIL_RUNOUT_PIN                  33
    #endif
    #define HEATER_BED_PIN          MOSFET_B_PIN  // HEATER1
  #else
    #ifndef FIL_RUNOUT_PIN
      #define FIL_RUNOUT_PIN                  42 //rokas marked as D43 on the board -.- and labeled D43 for clarity when in the box
    #endif
  #endif

  #if EITHER(TRIGORILLA_MAPPING_CHIRON, SWAP_Z_MOTORS)
    // Chiron and some Anycubic i3 MEGAs swap Z steppers
    #define Z_STEP_PIN                        36
    #define Z_DIR_PIN                         34
    #define Z_ENABLE_PIN                      30
    #define Z_CS_PIN                          44

    #define Z2_STEP_PIN                       46
    #define Z2_DIR_PIN                        48
    #define Z2_ENABLE_PIN                     62
    #define Z2_CS_PIN                         40
  #endif
#endif

//#if EITHER(ANYCUBIC_LCD_CHIRON, ANYCUBIC_LCD_I3MEGA)
//  #define BEEPER_PIN                          31
//  #define SD_DETECT_PIN                       49
//#endif

//#define HAS_TMC_UART  true // rokas test

#define Shared_TMC_RX 12 // PS_ON_PIN no fking clue why it doesn't like it ... literraly defined the same as servo pins .....
#if HAS_TMC_UART
    #define X_SERIAL_TX_PIN           SERVO1_PIN
    #define X_SERIAL_RX_PIN           Shared_TMC_RX

    #define Y_SERIAL_TX_PIN           SERVO1_PIN
    #define Y_SERIAL_RX_PIN           Shared_TMC_RX

    #define Z_SERIAL_TX_PIN           SERVO1_PIN
    #define Z_SERIAL_RX_PIN           Shared_TMC_RX

    #define E0_SERIAL_TX_PIN          SERVO1_PIN
    #define E0_SERIAL_RX_PIN          Shared_TMC_RX

    #define Z2_SERIAL_TX_PIN          SERVO2_PIN     //rokas
    //#define Z2_SERIAL_RX_PIN          SERVO0_PIN  //rokas  
    #define Z2_SERIAL_RX_PIN          66  //rokas  
#endif

#define X_HARDWARE_SERIAL Serial1 //rokas
//#define X2_HARDWARE_SERIAL Serial1
#define Y_HARDWARE_SERIAL Serial1 //rokas
//#define Y2_HARDWARE_SERIAL Serial1
#define Z_HARDWARE_SERIAL Serial1 //rokas
#define Z2_HARDWARE_SERIAL Serial3 //rokas
#define E0_HARDWARE_SERIAL Serial1 //rokas
#include "pins_RAMPS.h"

//
// AnyCubic made the following changes to 1.1.0-RC8
// If these are appropriate for your LCD let us know.
//
//#if 0 && HAS_WIRED_LCD
//
//  // LCD Display output pins
//  #if BOTH(IS_NEWPANEL, PANEL_ONE)
//    #undef LCD_PINS_D6
//    #define LCD_PINS_D6                       57
//  #endif
//
//  // LCD Display input pins
//  #if IS_NEWPANEL
//    #if EITHER(VIKI2, miniVIKI)
//      #undef DOGLCD_A0
//      #define DOGLCD_A0                       23
//    #elif ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)
//      #undef BEEPER_PIN
//      #define BEEPER_PIN                      33
//      #undef LCD_BACKLIGHT_PIN
//      #define LCD_BACKLIGHT_PIN               67
//    #endif
//  #elif ENABLED(MINIPANEL)
//    #undef BEEPER_PIN
//    #define BEEPER_PIN                        33
//    #undef DOGLCD_A0
//    #define DOGLCD_A0                         42
//  #endif
//
//#endif // HAS_WIRED_LCD
