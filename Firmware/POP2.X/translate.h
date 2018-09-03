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
char* tr(size_t str);

static const unsigned char *translate_english[50] = {
	"Language: English",
	"Loading\xB0",
	"Back"
};


static const unsigned char *translate_french[50] = {
	"Langue: Francais",
	"Chargement\xB0",
	"Arrière"
};

static const unsigned char *translate_spanish[50] = {
	"Idioma: Espanol",
	"Cargando\xB0",
	"Atrás"
};

#endif	/* TRANSLATE_H */