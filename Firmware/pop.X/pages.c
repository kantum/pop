/* 
 * File:   pages.c
 * Author: bocal
 *
 * Created on July 6, 2018, 1:09 PM
 */


#include "pages.h"


void pages_list(void) {
	uint32_t last_scr = 0;
	while (true) {
		UI_message("Loading|", UI_IGNORE_EVENTS, 0);
		UI_list_clear();
		struct listItem itm;
		byte i = 0;
		while (list_get_item(i, &itm)) {
			if (itm.flag != 0xFF) break;
			UI_list_set(i++, itm.name);
		}
		if (!i) UI_list_set(0, "(Empty List)");
		UI_list_start();
		UI_set_scroll(last_scr);
		UI_repaint();
		delay_ms(UI_PRESS_DELAY);
		byte evnt;
		while (true) {
			last_scr = UI_selected_item();
			wifi_async_check();
			UI_repaint();
			if (wifi_async_status == WIFI_BUSY)
				evnt = wheel_get_event_timeout(500);
			else
				evnt = wheel_get_event();
			
			if (evnt == WHEEL_TURN_LEFT) {
				if (UI_scroll(SCROLL_DOWN))
					play_note(5000, 10);
			} else if (evnt == WHEEL_TURN_RIGHT) {
				if (UI_scroll(SCROLL_UP))
					play_note(5000, 10);
			} else if (evnt == WHEEL_PRESS) {
				play_note(5000, 10);
				size_t id = UI_selected_item();
				last_scr = id;
				if (settings_mode == 0xFF || UI_prompt("Confirm?") == UI_OK) {
					list_get_item(id, &itm); // TODO Handle exception
					if (!wifi_async_order(itm.id)) {
						UI_message("Wi-Fi is Busy", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					} else {
						UI_message("Ordering|", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					}
					break;
				} else {
					break;
				}
			} else if (evnt == WHEEL_LONG_PRESS) {
				play_note(5000, 10);
				last_scr = UI_selected_item();
				pages_settings();
				break;
			}
		}
	}
}

void pages_settings(void) {
	int32_t last_scr = 0;
	while (true) {
		/* Settings List */
		/* WARNING: If you want to change the list order you have to 
		 * remap also the handlers below!! */
		UI_list_clear();
		settings_load();
		UI_list_set(0, "Back");
		
		if (wifi_async_status == WIFI_BUSY && wifi_curr_op == WIFI_UPDATE) {
			UI_list_set(1, "Updating|");
		} else {
			UI_list_set(1, "Update List");
		}
		
		if (settings_mode == 0xFF) {
			UI_list_set(2, "Mode: Fast");
		} else {
			UI_list_set(2, "Mode: Confirm");
		}
		
		UI_list_set(3, "Contrast");
		UI_list_set(4, "Set Wake Distance");
		
		if (settings_sound == 0xFF) {
			UI_list_set(5, "Sound: Yes");
		} else {
			UI_list_set(5, "Sound: No");
		}
		
		UI_list_set(6, "Test Distance");
		UI_list_set(7, "Animation: Sleepy");
		UI_list_set(8, "Animation: Look Around");

		
		UI_list_start();
		UI_set_scroll(last_scr);
		UI_repaint();
		delay_ms(UI_PRESS_DELAY);
		byte evnt;
		while (true) {
			last_scr = UI_selected_item();
			if (wifi_async_check()) break;
			UI_repaint();
			
			if (wifi_async_status == WIFI_BUSY)
				evnt = wheel_get_event_timeout(500);
			else
				evnt = wheel_get_event();
			
			if (evnt == WHEEL_TURN_LEFT) {
				if (UI_scroll(SCROLL_DOWN))
					play_note(5000, 10);
			} else if (evnt == WHEEL_TURN_RIGHT) {
				if (UI_scroll(SCROLL_UP))
					play_note(5000, 10);
			} else if (evnt == WHEEL_PRESS) {
				size_t i = UI_selected_item();
				last_scr = i;
				if (i != 5) play_note(5000, 10);
				if (i == 0) { return; }
				if (i == 1) {
					//UI_message("Updating List|", UI_IGNORE_EVENTS, 0);
					if (!wifi_async_update())
						UI_message("Wi-Fi is Busy", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					break;
				}
				if (i == 2) {
					byte val = 0xFF;
					if (settings_mode == 0xFF)
						val = 0x00;					
					settings_set_setting(SETTING_MODE, &val);
					break;
				}
				if (i == 3) {
					byte new_contrast = UI_number("Contrast", settings_contrast, 0, 255, 5, &OLED_set_contrast);
					settings_set_setting(SETTING_CONTRAST, &new_contrast);
					OLED_set_contrast(settings_contrast);
					break;
				}
				if (i == 4) {
					uint16_t new_dist = UI_distance();
					settings_set_setting(SETTING_DISTANCE, convert_short_to_arr(new_dist));
					break;
				}
				if (i == 5) {
					byte val = 0xFF;
					if (settings_sound == 0xFF) {
						val = 0x00;
					} else {
						settings_sound = 0xFF;
						play_note(5000, 50);
						delay_ms(50);
						play_note(5000, 200);
						settings_sound = 0x00;
					}
					settings_set_setting(SETTING_SOUND, &val);
					break;
				}
				if (i == 6) {
					UI_distance_test();
					break;
				}
				if (i == 7) {
					UI_animate_sleepy();
				}
				if (i == 8) {
					UI_animate_looking();
				}
			}
		}
	}
}
