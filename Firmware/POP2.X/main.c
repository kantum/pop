#include <p32xxxx.h>
#include "types.h"
#include "FAT32.h"
#include "SD.h"
#include "SPI.h"
#include "convert.h"
#include "delay.h"
#include "led.h"
#include "list.h"
#include "screen.h"
#include "settings.h"
#include "shiftreg.h"
#include "wheel.h"
#include "UI.h"
#include "piezo.h"
#include "translate.h"

void init(void) {
    pps_init();
    delay_init();
    shiftreg_init();
    photo_init();
    led_init();
    piezo_init();
    wheel_init();
    SPI_init();
    OLED_init();
    OLED_fill(0x00);

    if (!SD_init()) {
        delay_ms(100);
        UI_message(tr(TR_SD_MISSING), UI_IGNORE_EVENTS, 0);
        while (1); // TODO handle error or make
    }
    if (!FAT32_mount()) {
        delay_ms(100);
        UI_message(tr(TR_FAT32_CORRUPT), UI_IGNORE_EVENTS, 0);
        while (1);
    }
    settings_load();
    settings_get_wifi_credentials();

    OLED_set_contrast(settings_contrast);
}

uint32_t color;

void main(void) {

    struct listItem itm;
    byte i;
    byte evnt;
    char photo_buff[12];
    uint16_t photo_dist;

    init();
    //play_note(440, 4000);
    //play_song(tetris, 1000, 20);
    led_start_random();
    device_unlock();

    UI_list_clear();
    UI_message(tr(TR_LOOKING_WIFI), UI_IGNORE_EVENTS, 0);
    wifi_init();

    UI_message(tr(TR_CONNECTING_WIFI), UI_IGNORE_EVENTS, 0);
    if (!wifi_connect(wifi_ssid, wifi_pass))
        ; //UI_message("ERROR Connecting to Wi-Fi", UI_IGNORE_EVENTS, 0); while(1); //TODO Handle ERROR HERE

    UI_message(tr(TR_UPDATING_LIST), UI_IGNORE_EVENTS, 0);
    if (!wifi_async_update()) {
        UI_message(tr(TR_ERROR_UPDNG_LST), UI_IGNORE_EVENTS, 0);
        while (1); //TODO Handle ERROR HERE
    }
    UI_message(tr(TR_LOADING), UI_IGNORE_EVENTS, 0);
    
        if (!UI_load_buff(UI_BUFF_5, "sun06.dat") ||
        !UI_load_buff(UI_BUFF_6, "sun08.dat") ||
        !UI_load_buff(UI_BUFF_7, "sun10.dat") ||
        !UI_load_buff(UI_BUFF_8, "sun12.dat") ||
        !UI_load_buff(UI_BUFF_9, "sun14.dat") ||
        !UI_load_buff(UI_BUFF_10, "sun15.dat") ||
        !UI_load_buff(UI_BUFF_11, "sun16.dat") ||
        !UI_load_buff(UI_BUFF_12, "sun17.dat") ||
        !UI_load_buff(UI_BUFF_13, "sun18.dat") ||
        !UI_load_buff(UI_BUFF_14, "sun20.dat") ||
        !UI_load_buff(UI_BUFF_15, "sun21.dat") ||
        !UI_load_buff(UI_BUFF_16, "sun22.dat") ||
        !UI_load_buff(UI_BUFF_17, "sun23.dat") ||
        !UI_load_buff(UI_BUFF_18, "sun24.dat") ||
        !UI_load_buff(UI_BUFF_19, "sun25.dat") ||
        !UI_load_buff(UI_BUFF_20, "sun26.dat") ||
        !UI_load_buff(UI_BUFF_21, "sun27.dat"))
            UI_sun_loaded = false;
    //	pages_dummy_list();
    
    pages_list();
    //	led_rgb(0xff00ff);
    while (true);
}
