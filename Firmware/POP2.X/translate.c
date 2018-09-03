#include "translate.h"


char* tr(size_t str) {
	if (settings_language == 0x00) //English
		return ((char *)translate_english[str]);
	else if (settings_language == 0x01) // French
		return ((char *)translate_french[str]);
	else if (settings_language == 0x02) // Spanish
		return ((char *)translate_spanish[str]);
	else								// Default to English
		return ((char *)translate_english[str]);	
}