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
#define TR_EMPTY_LIST       42
#define TR_CONFIRMATION     43
#define TR_ERROR_READING    44
#define TR_ORDERING         45
#define TR_SCANNING_NETS    46
#define TR_SCANNING_FAILED  47
#define TR_RESCAN_NETS      48
#define TR_CONNECTION_FAIL  49
#define TR_TESTING_CONN     50
#define TR_CONNECTION_SUCC  51

char* tr(size_t str);

static const unsigned char *translate_english[52] = {
	"Language",
	"Loading\x7F",
	"Back",
    "SD Missing or Non-Compatible",
    "File System Corrupted",
    "Looking for Wi-Fi\x7F",
    "Connecting to Wi-Fi\x7F",
    "Updating List\x7F",
    "ERROR Updating List",
    "Updating\x7F",
    "Update List",
    "Mode",
    "Mode",
    "Contrast",
    "Wireless Wake",
    "Sound",
    "Sound",
    "Security",
    "Security",
    "Set Code",
    "Lock Device",
    "Configure Wi-Fi",
    "Wi-Fi is Busy",
    "Enter current code",
    "Wrong Code",
    "Set your new code",
    "Repeat your new code",
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
    " CANCEL       >OK<",
    "Empty List",
    "Confirm?",
    "Error Reading",
    "Ordering\x7F",
    "Scanning Networks\x7F",
    "Scanning Failed",
    "Re-scan Networks",
    "Connection Failed",
    "Testing Connection\x7F",
    "Connection Success!"
      
};


static const unsigned char *translate_french[52] = {
	"Langue",
	"Chargement\x7F",
	"Retour",
    "SD Manquante ou Incompatible",
    "Système de Fichiers Endommagé",
    "Recherche du Wi-Fi\x7F",
    "Connection au Wi-Fi\x7F",
    "Récupération de la Liste\x7F",
    "ERREUR de Mise à Jour",
    "Actualiser\x7F",
    "MàJ Liste",
    "Mode",
    "Mode",
    "Contraste",
    "Activation Sans Fil",
    "Son",
    "Son",
    "Securité",
    "Securité",
    "Code",
    "Vérouillage",
    "Configuration Wi-Fi",
    "Wi-Fi",
    "Entrer Code Actuel",
    "Mauvais Code",
    "Entrer Nouveau Code",
    "Encore :)",
    "Code Actualisé",
    "Codes Incompatibles",
    "Confirmation",
    "Rapide",
    "Non",
    "Oui",
    "Aucun",
    "Code à 4 Chiffres",
	"Entrez le Code",
    "Mauvais Code",
    "Distance",
    " OK ",
    ">OK<",
    ">CANCEL<       OK ",
    " CANCEL       >OK<",
    "Liste Vide",
    "Confirmer ?",
    "Problème de Lecture",
    "Commande\x7F",
    "Scan Réseaux\x7F",
    "Echec du Scan",
    "Re-Scan Réseaux\x7F",
    "La Connexion a Échoué",
    "Test de la Connexion\x7F",
    "Connecté !"
};

static const unsigned char *translate_spanish[52] = {
	"Idioma",
	"Cargando\x7F",
	"Atrás",
    "SD No Compatible",
    "SD No Compatible",
    "Buscando Wi-Fi\x7F",
    "Conectándose al Wi-Fi\x7F",
    "Actualizando Lista\x7F",
    "Error Actualizando Lista",
    "Actualizando\x7F",
    "Actualizar Lista",
    "Modo: Rápido",
    "Modo: Confirmar",
    "Contraste",
    "Cambiar Distancia",
    "Sonido: Sí",
    "Sonido: No",
    "Seguridad: Código",
    "Seguridad: Ninguna",
    "Cambiar Código",
    "Bloquear Dispositivo",
    "Configurar Wi-Fi",
    "El Wi-Fi está ocupado",
    "Código actual",
    "Código Erróneo",
    "Nuevo código",
    "Repita de nuevo",
    "Código Cambiado",
    "Los códigos no coinciden",
    "Confirmar",
    "Rápido",
    "No",
    "Sí",
    "Ninguna",
    "Código de 4 cifras",
    "Código de Desbloqueo",
    "Código Erróneo",
    "Distancia",
    " OK ",
    ">OK<",
    ">CANCELAR<     OK ",
    " CANCELAR     >OK<",
    "(Lista Vacía)",
    "Confirmar?",
    "Error en la Lectura",
    "Pidiendo\x7F",
    "Buscando Redes\x7F",
    "La Búsqueda ha fallado",
    "Escanear de nuevo",
    "Conexión Fallida",
    "Probando Conexión\x7F",
    "Conexión Correcta!"
};

#endif	/* TRANSLATE_H */
