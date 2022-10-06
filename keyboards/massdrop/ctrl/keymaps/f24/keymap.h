#include QMK_KEYBOARD_H

#define RGB_DEFAULT_TIME_OUT 300
#define RGB_FAST_MODE_TIME_OUT 3
#define RGB_TIME_OUT_MAX 600
#define RGB_TIME_OUT_MIN 10
#define RGB_TIME_OUT_STEP 10

#define MILLISECONDS_IN_SECOND 1000

bool disable_layer_color;

bool rgb_enabled_flag;                  // Current LED state flag. If false then LED is off.
bool rgb_time_out_enable;               // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
bool rgb_time_out_fast_mode_enabled;    // Enable flag for RGB timeout fast mode
bool rgb_time_out_user_value;           // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
uint16_t rgb_time_out_seconds;          // Idle LED timeout value, in seconds not milliseconds
uint16_t rgb_time_out_saved_seconds;    // The saved user config for RGB timeout period
led_flags_t rgb_time_out_saved_flag;    // Store LED flag before timeout so it can be restored when LED is turned on again.


#define WHITE {HSV_WHITE}
#define RED {HSV_RED}
#define CORAL {HSV_CORAL}
#define ORANGE {HSV_ORANGE}
#define GOLDEN {HSV_GOLDENROD}
#define GOLD {HSV_GOLD}
#define YELLOW {HSV_YELLOW}
#define CHART {HSV_CHARTREUSE}
#define GREEN {HSV_GREEN}
#define SPRING {HSV_SPRINGGREEN}
#define TURQ {HSV_TURQUOISE}
#define TEAL {HSV_TEAL}
#define CYAN {HSV_CYAN}
#define AZURE {HSV_AZURE}
#define BLUE {HSV_BLUE}
#define PURPLE {HSV_PURPLE}
#define MAGENT {HSV_MAGENTA}
#define PINK {HSV_PINK}

#define OFF {HSV_OFF}
#define ACTIVE RED

enum ctrl_keycodes
{
    U_T_AUTO = SAFE_RANGE, // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              // USB Toggle Automatic GCR control
    DBG_TOG,               // DEBUG Toggle On / Off
    DBG_MTRX,              // DEBUG Toggle Matrix Prints
    DBG_KBD,               // DEBUG Toggle Keyboard Prints
    DBG_MOU,               // DEBUG Toggle Mouse Prints
    DBG_PRNT,              // OUTPUT debug string
    ROUT_TG,               // Timeout Toggle. Toggle idle LED time out on or off

    MD_BOOT,               // Restart into bootloader after hold timeout
};


enum string_macro_keycodes {
    // The start of this enum should always be equal to end of ctrl_keycodes + 1
    WIN_PK = MD_BOOT + 1,
    LCAS_1,
    LCAS_2,
    LCAS_3,
    LCAS_4,
    LCAS_5,
    LCAS_6,
    LCAS_7,
    LCAS_8,
    LCAS_9,
    WCS_H,
    LS_POS, // Left Size Position
    RS_POS,
    TL_POS,
    TR_POS,
    BL_POS,
    BR_POS
};
