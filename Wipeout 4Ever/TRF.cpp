#include "binfile.h"
#include "endian_tools.h"

#include "TRF.h"

trf_face_t *TRF = NULL;
DWORD numfaces = 0;

void TRF_Load(BINFILE *file){
	DWORD filesize = 0;
	binseek(file, 0, BIN_END);
	filesize = bintell(file);
	binseek(file, 0, SEEK_SET);

	TRF = (trf_face_t*)file->base;

	numfaces = filesize/0x20;
	for(int i = 0;i<numfaces; i++){
		// need to swap endian on each of these
		SWAP_WORD(TRF->vInd[0]);
		SWAP_WORD(TRF->vInd[1]);
		SWAP_WORD(TRF->vInd[2]);
		SWAP_WORD(TRF->vInd[3]);

		SWAP_WORD(TRF->unk[0]);
		SWAP_WORD(TRF->unk[1]);
		SWAP_WORD(TRF->unk[2]);
		SWAP_WORD(TRF->unk[3]);
	}


}

trf_face_t TRF_GetFace(DWORD i){
	return(TRF[i]);
}