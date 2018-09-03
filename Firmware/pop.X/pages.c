/* 
 * File:   pages.c
 * Author: bocal
 *
 * Created on July 6, 2018, 1:09 PM
 */


#include "pages.h"
#include "device.h"
#include "UI.h"

size_t pages_push_turn(void) {
	int val = 0;
	UI_paint_number("Push & Turn", val);
	delay_ms(UI_PRESS_DELAY);
	
	byte evnt;
	while (true) {
		UI_paint_number("Push & Turn", val);
		evnt = wheel_get_event();
		if (evnt == WHEEL_PRESS_END) { return (val); }
		if (evnt == WHEEL_PRESS_TURN_LEFT) { val -= 1; }
		if (evnt == WHEEL_PRESS_TURN_RIGHT) { val += 1; }
		if (val < 0) val = 0;
		if (val > 100) val = 100;
	}
	return (UI_EXPIRED_TMOUT);
}

bool pages_list_buffer(void) {
	if (pages_list_loaded) return (false);
	struct listItem itm;
	if (list_get_item(pages_list_sz, &itm)) {
		if (itm.flag == 0xFF) {
			strcpy(pages_list_buff[pages_list_sz++], itm.name);
		} else {
			pages_list_loaded = true;
		}
	}
	return (true);
}

void pages_list(void) {
	uint32_t last_scr = 0;
	while (true) {
		UI_message("Loading|", UI_IGNORE_EVENTS, 0);
		while (pages_list_buffer());
		UI_list_clear();
		struct listItem itm;
		byte i = 0;
		while (i < pages_list_sz) {
			UI_list_set(i, pages_list_buff[i]);
			i++;
		}
		if (!i) UI_list_set(0, "(Empty List)");
		if (!pages_list_loaded) UI_list_set(i, "Loading...");
		UI_list_start();
		UI_set_scroll(last_scr);
		UI_repaint();
		delay_ms(UI_PRESS_DELAY);
		byte evnt;
		while (true) {
			last_scr = UI_selected_item();
			wifi_async_check();
			if (pages_list_buffer()) break;
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
				if (settings_mode == 0x01 || UI_prompt("Confirm?") == UI_OK) {
					if (!list_get_item(id, &itm)) {
						UI_message("Error Reading", UI_DISSMISSED_BY_ALL_EVENTS, 0); break;
					}
					if (!wifi_async_order(itm.id)) {
						UI_message("Wi-Fi is Busy", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					} else {
						UI_message("Ordering|", UI_DISSMISSED_BY_ALL_EVENTS, 1000);
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
			} else if (evnt == WHEEL_PRESS_BEGIN) {
				UI_paint_number("Selected!", pages_push_turn());
			}
		}
	}
}


void img_carrousel(void) {
#define IMG_SZ 4
	char *img[IMG_SZ];

	img[1]	= "sun00.dat";
	img[2]	= "sun01.dat";
	img[3]	= "sun02.dat";
	img[4]	= "sun03.dat";
	img[5]	= "sun04.dat";
	img[6]	= "sun05.dat";
	img[7]	= "sun06.dat";
	img[8]	= "sun07.dat";
	img[9]	= "sun08.dat";
	img[10]	= "sun09.dat";
	img[11]	= "sun10.dat";
	img[12]	= "sun11.dat";
	img[13]	= "sun12.dat";
	img[14]	= "sun13.dat";
	img[15]	= "sun14.dat";
	img[16]	= "sun15.dat";
	img[17]	= "sun16.dat";
	img[18]	= "sun17.dat";
	img[19]	= "sun18.dat";
	img[20]	= "sun19.dat";
	img[21]	= "sun20.dat";
	img[22]	= "sun21.dat";
	img[23]	= "sun22.dat";
	img[24]	= "sun23.dat";
	img[25]	= "sun24.dat";
	img[26]	= "sun25.dat";
	img[27]	= "sun26.dat";
	img[28]	= "sun27.dat";
	img[29]	= "sun28.dat";
	img[30]	= "sun29.dat";
	img[31]	= "sun30.dat";
	img[32]	= "sun31.dat";
	img[33]	= "sun32.dat";
	img[34]	= "sun33.dat";
	img[35]	= "choice0.dat";
	img[36]	= "choice1.dat";
	img[37]	= "choice2.dat";
	img[38]	= "choice3.dat";
	img[39]	= "bksp1.dat";
	img[40]	= "bksp2.dat";
	img[41]	= "bksp3.dat";
	img[42]	= "more.dat";
	img[43]	= "shift.dat";
	img[44]	= "e_b4_UR.dat";
	img[45]	= "eye_C.dat";
	img[46]	= "frame0.dat";
	img[47]	= "frame1.dat";
	img[48]	= "frame2.dat";
	img[49]	= "frame3.dat";
	img[50]	= "frame4.dat";
   	img[51]	= "frame5.dat";
   	img[52]	= "frame6.dat";
   	img[53]	= "frame7.dat";
   	img[54]	= "frame8.dat";
   	img[55]	= "frame9.dat";
   	img[56]	= "sk0.dat";
   	img[57]	= "sk1.dat";
   	img[58]	= "test.dat";
   	img[59]	= "wif0.dat";
   	img[60]	= "wif1.dat";
   	img[61]	= "wif2.dat";
   	img[62]	= "wif3.dat";
   	img[63]	= "wiferr.dat";
	int32_t i = 0;
	byte evnt;
	while (true) {
		UI_paint_img_old(img[i]);
		evnt = wheel_get_event();
		if (evnt == WHEEL_PRESS) return;
		if (evnt == WHEEL_TURN_LEFT) i--;
		if (evnt == WHEEL_TURN_RIGHT) i++;
		if (i < 0) i = 0;
		if (i > IMG_SZ - 1) i = IMG_SZ - 1;
	}
}

void pages_settings(void) {
	int32_t last_scr = 0xFFFFFFFF;
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
		
		if (settings_mode == 0x01) {
			UI_list_set(2, "Mode: Fast");
		} else {
			UI_list_set(2, "Mode: Confirm");
		}
		
		OLED_set_contrast(settings_contrast);
		UI_list_set(3, "Contrast");
		UI_list_set(4, "Set Wake Distance");
		
		if (settings_sound == 0xFF) {
			UI_list_set(5, "Sound: Yes");
		} else {
			UI_list_set(5, "Sound: No");
		}
		
		UI_list_set(6, "Test Distance");
	
		UI_list_set(7, "Animation: Sleepy");
		if (settings_security == 0xFF) {
			UI_list_set(8, "Security: Code");
		} else {
			UI_list_set(8, "Security: None");
		}
		UI_list_set(9, "Set Code");
		UI_list_set(10, "Lock Device");
		UI_list_set(11, "Test Code");
		UI_list_set(12, "Images Carrousel");
		UI_list_set(13, "Keyboard");

		UI_list_start();
		if (last_scr == 0xFFFFFFFF)
			UI_scroll(SCROLL_UP);
		else
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
					byte val = pages_setting(MENU_MODE, settings_mode);					
					settings_set_setting(SETTING_MODE, &val);
					break;
				}
				if (i == 3) {
					byte new_contrast = UI_number("Contrast", settings_contrast, 0, 100, 5, &OLED_set_contrast);
					settings_set_setting(SETTING_CONTRAST, &new_contrast);
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
					UI_animate_looking();
				}
				if (i == 8) {
					byte val = 0xFF;
					if (settings_security == 0xFF) {
						val = 0x00;
					} else {
						val = 0xFF;
					}
					settings_set_setting(SETTING_SECURITY, &val);
					break;
				}
				if (i == 9) {
					size_t code = UI_password("Set your code:", 4);
					if (code == UI_password("Repeat your code:", 4)) {
						settings_set_setting(SETTING_PASSWORD, convert_long_to_arr(code));
						UI_message("Code is set", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					} else {
						UI_message("Codes don't match", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					}
					break;
				}
				if (i == 10) {
					device_sleep();
					break;
				}
				if (i == 11) {
					size_t code = UI_password("Enter code to unlock:", 4);
					if (code == settings_password) {
						UI_message("Good Code", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					} else {
						UI_message("Wrong Code", UI_DISSMISSED_BY_ALL_EVENTS, 0);
					}
					break;
				}
				if (i == 12) {
					img_carrousel();
					break;
				}
				if (i == 13) {
					UI_keyboard();
					wheel_get_event();
				}
			}
		}
	}
}

size_t pages_setting(byte menu, size_t current) {
	while (true) {
		/* Settings List */
		/* WARNING: If you want to change the list order you have to 
		 * remap also the handlers below!! */
		UI_list_clear();
		size_t max = 0;
		
		if (menu == MENU_MODE) {
			UI_list_set(0, "Confirm");
			UI_list_set(1, "Fast");
			UI_list_start();
			max = 1;
		}
		
		if (current <= max && current >= 0) {
			UI_set_scroll(current);
		} else {
			UI_set_scroll(0);
		}
		
		UI_repaint();
		delay_ms(UI_PRESS_DELAY);
		byte evnt;
		while (true) {
			current = UI_selected_item();
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
				return (i);
			}
		}
	}
}
