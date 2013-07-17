#include <Windows.h>
#include <stdio.h>
#include "Globals.h"

typedef struct WO_CONFIG_FILE{ // (sizeof=0xB4)
DWORD field_0;
DWORD field_4;
DWORD field_8;
WORD field_C;
WORD field_E;
WORD field_10;
WORD field_12;
WORD field_14;
WORD field_16;
WORD field_18;
WORD field_1A;
WORD field_1C;
WORD field_1E;
BYTE field_20;
BYTE field_21;
BYTE field_22;
BYTE field_23;
BYTE field_24;
BYTE field_25;
BYTE field_26;
BYTE field_27;
BYTE field_28;
BYTE field_29;
BYTE field_2A;
BYTE field_2B;
BYTE field_2C;
BYTE field_2D;
BYTE field_2E;
BYTE field_2F;
DWORD field_30;
DWORD field_34;
DWORD field_38;
DWORD field_3C;
DWORD field_40;
DWORD field_44;
DWORD field_48;
DWORD field_4C;
DWORD field_50;
DWORD field_54;
DWORD field_58;
DWORD field_5C;
DWORD field_60;
DWORD field_64;
DWORD field_68;
DWORD field_6C;
DWORD field_70;
DWORD field_74;
DWORD field_78;
DWORD field_7C;
DWORD field_80;
DWORD field_84;
DWORD field_88;
DWORD field_8C;
DWORD field_90;
DWORD field_94;
DWORD field_98;
DWORD field_9C;
DWORD field_A0;
DWORD field_A4;
DWORD field_A8;
DWORD field_AC;
DWORD field_B0;
BYTE highScores[504];	// this is probably wrong size
};//WO_CONFIG_FILE ends

void WO_ConfigLoad(){
	WO_CONFIG_FILE WO_ConfigBuf;
	DWORD configSize = 0x5B4;

	FILE *Config_DAT = fopen("config.dat", "rb");

	if(Config_DAT){
		fread(&WO_ConfigBuf, configSize, 1, Config_DAT);
		fclose(Config_DAT);
		// theres some check of WO_ConfigBuf2 != 1234(0x4D2) here. the resolution is 640x480 if true
	}


}

