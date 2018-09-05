#ifndef TRANSLATE_H
#define	TRANSLATE_H

#include "types.h"
#include "settings.h"

#define TR_LANGUAGE			0
#define	TR_LOADING			1
#define TR_BACK				2
#define TR_SD_MISSING		3
#define TR_FAT32_CORRUPT	4
#define TR_LOOKING_WIFI		5
#define TR_CONNECTING_WIFI	6
#define TR_UPDATING_LIST    7
#define TR_ERROR_UPDNG_LST  8
#define TR_UPDATING         9
#define TR_UPDATE_LIST      10
#define TR_MODE_FAST        11
#define TR_MODE_CONFIRM     12
#define TR_SET_CONTRAST     13
#define TR_SET_WKE_DISTANCE 14
#define TR_SOUND_YES        15
#define TR_SOUND_NO         16
#define TR_SECURITY_CODE    17
#define TR_SECURITY_NONE    18
#define TR_SET_CODE         19
#define TR_LOCK_DEVICE      20
#define TR_CONFIGURE_WIFI   21
#define TR_WIFI_BUSY        22
#define TR_ENTER_CURR_CODE  23
#define TR_WRONG_CODE       24
#define TR_SET_NEW_CODE     25
#define TR_REPEAT_NEW_CODE  26
#define TR_CODE_SET         27
#define TR_CODE_NO_MATCH    28
#define TR_CONFIRM          29
#define TR_FAST             30
#define TR_NO               31
#define TR_YES              32
#define TR_NONE             33
#define TR_FOUR_DIGIT_CODE  34
#define TR_CODE_TO_UNLOCK   35
#define TR_WRONG_CODE       36
#define TR_DISTANCE         37
#define TR_OK               38
#define TR_OK_SEL           39
#define TR_CANCEL_SEL_OK    40
#define TR_CANCEL_OK_SEL    41


char* tr(size_t str);

static const unsigned char *translate_english[50] = {
	"Language: English",
	"Loading\xB0",
	"Back",
    "SD Missing or Non-Compatible",
    "File System Corrupted",
    "Looking for Wi-Fi\xB0",
    "Connecting to Wi-Fi\xB0",
    "Updating List\xB0",
    "ERROR Updating List",
    "Updating\x80",
    "Update List",
    "Mode: Fast",
    "Mode: Confirm",
    "Contrast",
    "Set Wake Distance",
    "Sound: Yes",
    "Sound: No",
    "Security: Code",
    "Security: None",
    "Set Code",
    "Lock Device",
    "Configure Wi-Fi",
    "Wi-Fi is Busy",
    "Enter current code:",
    "Wrong Code",
    "Set your new code:",
    "Repeat your new code:",
    "Code is set",
    "Codes don't match",
    "Confirm",
    "Fast",
    "No",
    "Yes",
    "None",
    "4 Digit Code",
    "Enter Code to Unlock",
    "Wrong Code",
    "Distance",
    " OK ",
    ">OK<",
    ">CANCEL<       OK ",
    " CANCEL       >OK<"
};


static const unsigned char *translate_french[50] = {
	"Language: Francais",
	"Loading\xB0",
	"Back",
    "SD Missing or Non-Compatible",
    "File System Corrupted",
    "Looking for Wi-Fi\xB0",
    "Connecting to Wi-Fi\xB0",
    "Updating List\xB0",
    "ERROR Updating List",
    "Updating\x80",
    "Update List",
    "Mode: Fast",
    "Mode: Confirm",
    "Contrast",
    "Set Wake Distance",
    "Sound: Yes",
    "Sound: No",
    "Security: Code",
    "Security: None",
    "Set Code",
    "Lock Device",
    "Configure Wi-Fi",
    "Wi-Fi is Busy",
    "Enter current code:",
    "Wrong Code",
    "Set your new code:",
    "Repeat your new code:",
    "Code is set",
    "Codes don't match",
    "Confirm",
    "Fast",
    "No",
    "Yes",
    "None",
    "4 Digit Code",
    "Enter Code to Unlock",
    "Wrong Code",
    "Distance",
    " OK ",
    ">OK<",
    ">CANCEL<       OK ",
    " CANCEL       >OK<"
};

static const unsigned char *translate_spanish[50] = {
	"Language: Espanol",
	"Loading\xB0",
	"Back",
    "SD Missing or Non-Compatible",
    "File System Corrupted",
    "Looking for Wi-Fi\xB0",
    "Connecting to Wi-Fi\xB0",
    "Updating List\xB0",
    "ERROR Updating List",
    "Updating\x80",
    "Update List",
    "Mode: Fast",
    "Mode: Confirm",
    "Contrast",
    "Set Wake Distance",
    "Sound: Yes",
    "Sound: No",
    "Security: Code",
    "Security: None",
    "Set Code",
    "Lock Device",
    "Configure Wi-Fi",
    "Wi-Fi is Busy",
    "Enter current code:",
    "Wrong Code",
    "Set your new code:",
    "Repeat your new code:",
    "Code is set",
    "Codes don't match",
    "Confirm",
    "Fast",
    "No",
    "Yes",
    "None",
    "4 Digit Code",
    "Enter Code to Unlock",
    "Wrong Code",
    "Distance",
    " OK ",
    ">OK<",
    ">CANCEL<       OK ",
    " CANCEL       >OK<"
};

#endif	/* TRANSLATE_H */