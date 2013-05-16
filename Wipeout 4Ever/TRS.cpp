#include "binfile.h"
#include "endian_tools.h"
#include "TRS.h"

trs_section_t *TRS = NULL;
DWORD numsections = 0;

void TRS_Load(BINFILE *file){
	DWORD filesize = 0;
	binseek(file, 0, BIN_END);
	filesize = bintell(file);
	binseek(file, 0, SEEK_SET);

	TRS = (trs_section_t*)file->base;

	numsections = filesize/0x9c;
	for(int i = 0;i<numsections; i++){
		// need to swap endian on each of these
		SWAP_DWORD(TRS->previous);
		SWAP_DWORD(TRS->next);
		SWAP_DWORD(TRS->unk[0]);
		SWAP_DWORD(TRS->unk[1]);
		SWAP_DWORD(TRS->unk[2]);
		SWAP_DWORD(TRS->unkflag);

		for(int i = 0;i<15;i++){
			SWAP_DWORD(TRS->unk5[i]);
		}
		for(int i = 0;i<8;i++){
			SWAP_DWORD(TRS->unk6[i]);
		}
		for(int i = 0;i<6;i++){
			SWAP_DWORD(TRS->unk7[i]);
		}
	}
}

DWORD TRS_GetNumSections(){
	return numsections;
}

trs_section_t TRS_GetFace(DWORD i){
	return(TRS[i]);
}

