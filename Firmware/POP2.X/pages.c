#include "pages.h"
#include "device.h"
#include "UI.h"
#include "translate.h"
#include "string.h"

size_t pages_push_turn(void) {
	int val = 0;
	UI_paint_number("Push & Turn", val);
	wheel_pending_flush();

	byte evnt;
	while (true) {
		UI_paint_number("Push & Turn", val);
		evnt = wheel_get_event();
		if (evnt == WHEEL_PRESS_END) { wheel_pending_flush(); }
		if (evnt == WHEEL_PRESS) { return (val); }
		if (evnt == WHEEL_PRESS_TURN_LEFT || evnt == WHEEL_TURN_LEFT) { val -= 1; }
		if (evnt == WHEEL_PRESS_TURN_RIGHT || evnt == WHEEL_TURN_RIGHT) { val += 1; }
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
	} else {
        pages_list_loaded = true;
    }
	return (true);
}

void pages_list(void) {
	uint32_t last_scr = 0;
	while (true) {
		UI_message(tr(TR_LOADING), UI_IGNORE_EVENTS, 0);
		while (pages_list_buffer());
		UI_list_clear();
		struct listItem itm;
		byte i = 0;
		while (i < pages_list_sz) {
			UI_list_set(i, pages_list_buff[i]);
			i++;
		}
		if (!i) UI_list_set(0, tr(TR_EMPTY_LIST));
		if (!pages_list_loaded) UI_list_set(i, tr(TR_LOADING));
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
				if (settings_mode == 0x01 || UI_prompt(tr(TR_CONFIRMATION)) == UI_OK) {
					if (!list_get_item(id, &itm)) {
						UI_message(tr(TR_ERROR_READING), UI_DISSMISSED_BY_ALL_EVENTS, 0); break;
					}
					if (!wifi_async_order(itm.id)) {
						UI_message(tr(TR_WIFI_BUSY), UI_DISSMISSED_BY_ALL_EVENTS, 0);
					} else {
						UI_message(tr(TR_ORDERING), UI_DISSMISSED_BY_ALL_EVENTS, 1000);
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
#define IMG_SZ 64
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

void pages_wifi_setup(void) {
	char ssid[20];
	char pass[20];
	RESCAN: {
		UI_message(tr(TR_SCANNING_NETS), UI_IGNORE_EVENTS, 0);
		if (!wifi_async_scan()) {
			UI_message(tr(TR_WIFI_BUSY), UI_DISSMISSED_BY_ALL_EVENTS, 0);
			return;
		}
		while (!wifi_async_check());
		if (wifi_async_status == WIFI_ERROR) {
			UI_message(tr(TR_CONNECTION_FAIL), UI_DISSMISSED_BY_ALL_EVENTS, 0);
			return;
		}

		UI_list_set(UI_list_size + 1, "");
		UI_list_set(UI_list_size + 1, tr(TR_RESCAN_NETS));
		UI_list_set(UI_list_size + 1, tr(TR_BACK));

		UI_list_start();
	}
	byte evnt;
	while (true)
	{
		UI_repaint();
		evnt = wheel_get_event();
		if (evnt == WHEEL_TURN_LEFT) {
				if (UI_scroll(SCROLL_DOWN))
					play_note(5000, 10);
				if (UI_selected_item() == UI_list_size - 2)
					UI_scroll(SCROLL_DOWN);
			} else if (evnt == WHEEL_TURN_RIGHT) {
				if (UI_scroll(SCROLL_UP))
					play_note(5000, 10);
				if (UI_selected_item() == UI_list_size - 2)
					UI_scroll(SCROLL_UP);
			} else if (evnt == WHEEL_PRESS) {
				size_t i = UI_selected_item();
				if (i == UI_list_size - 0) return;
				if (i == UI_list_size - 1) goto RESCAN;
				if (i == UI_list_size - 2) continue;
				strcpy(ssid, (char*)UI_list_get(i));
				break;
			}
	}
	UI_message(tr(TR_TESTING_CONN), UI_IGNORE_EVENTS, 0);
	byte rt = 5;
	while (rt--) {
		if (wifi_disconnect()) break;
		if (rt == 0) {
			UI_message(tr(TR_CONNECTION_FAIL), UI_DISSMISSED_BY_ALL_EVENTS, 0);
			goto RESCAN;
		}
	}
	
	strcpy(pass, (char*)UI_keyboard());
	UI_message(tr(TR_TESTING_CONN), UI_IGNORE_EVENTS, 0);
	bool conn_failed = false;
	if (!wifi_connect(ssid, pass))
		conn_failed = true;
	
	if (!conn_failed) {
		wifi_async_update();
		while (!wifi_async_check());
	}
	
	if (wifi_async_status != WIFI_ERROR && !conn_failed)
		UI_message(tr(TR_CONNECTION_SUCC), UI_DISSMISSED_BY_ALL_EVENTS, 0);
	else 
		UI_message(tr(TR_CONNECTION_FAIL), UI_DISSMISSED_BY_ALL_EVENTS, 0);

}

void pages_settings(void) {
	int32_t last_scr = 0xFFFFFFFF;
	while (true) {
		/* Settings List */
		/* WARNING: If you want to change the list order you have to 
		 * remap also the handlers below!! */
		UI_list_clear();
		settings_load();

		UI_list_set(0, tr(TR_BACK));
        
		if (wifi_async_status == WIFI_BUSY && wifi_curr_op == WIFI_UPDATE) {
			UI_list_set(1, tr(TR_UPDATING));
		} else {
			UI_list_set(1, tr(TR_UPDATE_LIST));
		}
		
		if (settings_mode == 0x01) {
			UI_list_set(2, tr(TR_MODE_FAST));
		} else {
			UI_list_set(2, tr(TR_MODE_CONFIRM));
		}
		
		OLED_set_contrast(settings_contrast);
		UI_list_set(3, tr(TR_SET_CONTRAST));
		UI_list_set(4, tr(TR_SET_WKE_DISTANCE));
		
		if (settings_sound == 0x01) {
			UI_list_set(5, tr(TR_SOUND_YES));
		} else {
			UI_list_set(5, tr(TR_SOUND_NO));
		}
		
		UI_list_set(6, "----------");
	
		UI_list_set(7, "Animation: Sleepy");
		if (settings_security == 0x01) {
			UI_list_set(8, tr(TR_SECURITY_CODE));
		} else {
			UI_list_set(8, tr(TR_SECURITY_NONE));
		}
		UI_list_set(9, tr(TR_SET_CODE));
		UI_list_set(10, tr(TR_LOCK_DEVICE));
		UI_list_set(11, tr(TR_CONFIGURE_WIFI));
		UI_list_set(12, "Images Carrousel");
		UI_list_set(13, "----------");
		
		UI_list_set(14, tr(TR_LANGUAGE));

		UI_list_start();
		if (last_scr == 0xFFFFFFFF)
			UI_scroll(SCROLL_UP);
		else
			UI_set_scroll(last_scr);
		UI_repaint();

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
				if (i == 0) { return; } // Back
				if (i == 1) {	// Update List
					//UI_message("Updating List\xB0", UI_IGNORE_EVENTS, 0);
					if (!wifi_async_update())
						UI_message(tr(TR_WIFI_BUSY), UI_DISSMISSED_BY_ALL_EVENTS, 0);
					break;
				}
				if (i == 2) {	// Mode: Confirm
					byte val = pages_setting(MENU_MODE, settings_mode);					
					settings_set_setting(SETTING_MODE, &val);
					break;
				}
				if (i == 3) {	// Contrast
					byte new_contrast = UI_number(tr(TR_SET_CONTRAST), settings_contrast, 0, 100, 5, &OLED_set_contrast);
					settings_set_setting(SETTING_CONTRAST, &new_contrast);
					break;
				}
				if (i == 4) {	// Set Wake Distance
					uint16_t new_dist = UI_distance();
					settings_set_setting(SETTING_DISTANCE, convert_short_to_arr(new_dist));
					break;
				}
				if (i == 5) {	// Sound: Yes
					byte val = pages_setting(MENU_SOUND, settings_sound);					
					if (val == 0x01) {
						settings_sound = 0x01;
						play_note(5000, 50);
						delay_ms(50);
						play_note(5000, 200);
						settings_sound = 0x00;
					}
					settings_set_setting(SETTING_SOUND, &val);
					break;
				}
//				if (i == 6) {	// Test Distance [TST]
//					UI_distance_test();
//					break;
//				}
				if (i == 7) {	// Animation: Sleeping [TST]
					UI_animate_looking();
				}
				if (i == 8) {	// Security: Code
					if (!device_authorize(tr(TR_ENTER_CURR_CODE))) {
						UI_message(tr(TR_WRONG_CODE), UI_DISSMISSED_BY_ALL_EVENTS, 0);
						break;
					}
					byte val = pages_setting(MENU_SECURITY, settings_security);
					settings_set_setting(SETTING_SECURITY, &val);
					break;
				}
				if (i == 9) {	// Set Code
					if (!device_authorize(tr(TR_ENTER_CURR_CODE))) {
						UI_message(tr(TR_WRONG_CODE), UI_DISSMISSED_BY_ALL_EVENTS, 0);
						break;
					}
					size_t code = UI_password(tr(TR_SET_NEW_CODE), 4);
					if (code == UI_password(tr(TR_REPEAT_NEW_CODE), 4)) {
						settings_set_setting(SETTING_PASSWORD, convert_long_to_arr(code));
						UI_message(tr(TR_CODE_SET), UI_DISSMISSED_BY_ALL_EVENTS, 0);
					} else {
						UI_message(tr(TR_CODE_NO_MATCH), UI_DISSMISSED_BY_ALL_EVENTS, 0);
					}
					break;
				}
				if (i == 10) {	// Lock Device
					device_sleep();
					break;
				}
//				if (i == 11) { // Test Code [TST]
//					size_t code = UI_password("Enter code to unlock:", 4);
//					if (code == settings_password) {
//						UI_message("Good Code", UI_DISSMISSED_BY_ALL_EVENTS, 0);
//					} else {
//						UI_message("Wrong Code", UI_DISSMISSED_BY_ALL_EVENTS, 0);
//					}
//					break;
//				}
				if (i == 11) {
					pages_wifi_setup();
					break;
				}
				if (i == 12) {	// Image Carrousel [TST]
					img_carrousel();
					break;
				}
//				if (i == 13) {	// Keyboard [TST]
//					UI_message(UI_keyboard(), UI_DISSMISSED_BY_ALL_EVENTS, 0);
//					wheel_get_event();
//					break;
//				}
				if (i == 14) {	// Language: English
					byte val = pages_setting(MENU_LANGUAGE, settings_language);
					settings_set_setting(SETTING_LANGUAGE, &val);
					break;
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
			UI_list_set(0, tr(TR_CONFIRM));
			UI_list_set(1, tr(TR_FAST));
			UI_list_start();
			max = 1;
		}
		
		if (menu == MENU_SOUND) {
			UI_list_set(0, tr(TR_NO));
			UI_list_set(1, tr(TR_YES));
			UI_list_start();
			max = 1;
		}
		
		if (menu == MENU_SECURITY) {
			UI_list_set(0, tr(TR_NONE));
			UI_list_set(1, tr(TR_FOUR_DIGIT_CODE));
			UI_list_start();
			max = 1;
		}
		
		if (menu == MENU_LANGUAGE) {
			UI_list_set(0, "English");
			UI_list_set(1, "Français");
			UI_list_set(2, "Español");
			UI_list_start();
			max = 2;
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


void	pages_dummy_list(void) {
	UI_list_clear();
		
UI_list_set(0, "0");
UI_list_set(1, "1");
UI_list_set(2, "2");
UI_list_set(3, "3");
UI_list_set(4, "4");
UI_list_set(5, "5");
UI_list_set(6, "6");
UI_list_set(7, "7");
UI_list_set(8, "8");
UI_list_set(9, "9");
UI_list_set(10, "10");
UI_list_set(11, "11");
UI_list_set(12, "12");
UI_list_set(13, "13");
UI_list_set(14, "14");
UI_list_set(15, "15");
UI_list_set(16, "16");
UI_list_set(17, "17");
UI_list_set(18, "18");
UI_list_set(19, "19");
UI_list_set(20, "20");
UI_list_set(21, "21");
UI_list_set(22, "22");
UI_list_set(23, "23");
UI_list_set(24, "24");
UI_list_set(25, "25");
UI_list_set(26, "26");
UI_list_set(27, "27");
UI_list_set(28, "\x7F");
UI_list_set(29, "\x7F\x7F");
UI_list_set(30, "\x7F\x7F\x7F");
UI_list_set(31, "\x7F\x7F\x7F\x7F");
UI_list_set(32, "\x7F\x7F\x7F\x7F\x7F");
UI_list_set(33, "\x7F\x7F\x7F\x7F\x7F\x7F");
UI_list_set(34, "\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
UI_list_set(35, "\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
UI_list_set(36, "\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
UI_list_set(37, "\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
UI_list_set(38, "\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
UI_list_set(39, "39");
UI_list_set(40, "40");
UI_list_set(41, "41");
UI_list_set(42, "42");
UI_list_set(43, "43");
UI_list_set(44, "44");
UI_list_set(45, "45");
UI_list_set(46, "46");
UI_list_set(47, "47");
UI_list_set(48, "48");
UI_list_set(49, "49");

UI_list_start();
UI_repaint();
byte evnt = 0x00;
	while (true) {
		UI_repaint();
		evnt = wheel_get_event();
		if (evnt == WHEEL_TURN_LEFT) {
			if (UI_scroll(SCROLL_DOWN))
				play_note(5000, 10);
		} else if (evnt == WHEEL_TURN_RIGHT) {
			if (UI_scroll(SCROLL_UP))
				play_note(5000, 10);
		} else if (evnt == WHEEL_PRESS) {
			return;
		}
	}
}