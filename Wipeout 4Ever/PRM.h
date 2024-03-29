#ifndef __PRM_H__
#define __PRM_H__
//#include "stdafx.h"
#include "binfile.h"
#include "endian_tools.h"
#include <vector>

enum{
	TRI_FLAT = 1
};

typedef struct {
    unsigned char name[15];		 /* Object name */
    unsigned char unknown1;
    unsigned short vtx_count;	/* Number of vertices, this is correct*/
								// faces are regenerated to contain a unique copy of each vertex
								// and this count may be larger after that processing takes place
	unsigned short unkShort3;
	void *vertexPointer;		// set at runtime
	short unkShort1;
	short unkShort2;
	void *unkPtr1;
    unsigned short poly_count;	/* Number of polygones */
	unsigned short unkShort4;
	void *facePointer;			// set at runtime
	void *unkPtr2;				// set at runtime
	void *unkPtr3;				// set at runtime
	void *unkPtr4;				// points after all the hdr pointers, set at runtime
	unsigned short unk[4];
	void *nextPtr;				// points at next model in PRM file, set at runtime after all data in a 
								// model are processed
    unsigned short unknown4[32];
	unsigned short unknown5[2];
    void *unkPrt5;
	unsigned long unk2[2];
} prm_object_header_t;

//Vertices
//After the object header comes objects vertices, as an array of prm_object_vertex_t[vtx_count].
typedef struct {
    short x;
    short y;
    short z;
    short pad;  
} prm_object_vertex_t;

//Polygons
//After the array of vertices comes polygons. Polygons have variable length, depending on their type, which is the first value read:
typedef struct {
    unsigned short type; /* Polygon type */
} prm_object_polygon_type_t;


//Then the polygon data follows the type:
/*** sizes below include type byte ***/
//Polygon type 0x01
typedef struct {
	unsigned short unknown1;	// face normal?
	unsigned short vertices[3];	/* Vertices index */
	unsigned short unknown2[3]; // vertex colors?
} prm_object_polygon_1_t;

//Polygon type 0x02, 0x1C bytes
typedef struct {
	unsigned short unknown1;	// face normal?
	unsigned short vertices[3];	/* Vertices index */
	unsigned short textureID;	// added to an offset and used to index WTL. WTL contains 
								// pointers to loaded textures
	unsigned short unknown2[3]; // u/v?
	unsigned char color[3];
} prm_object_polygon_2_t;

//Polygon type 0x03, 0x10 bytes
typedef struct {
	unsigned short unknown1;
	unsigned short vertices[4];	/* Vertices index */
	unsigned short unknown2[2];
} prm_object_polygon_3_t;

//Polygon type 0x04 : Textured Quad, 0x20 bytes
typedef struct {
	unsigned short unknown1;
	unsigned short vertices[4];	/* Vertices index */
	unsigned char unknown2[16];
	unsigned char color[4];
} prm_object_polygon_4_t;

//Polygon type 0x05 : Gouraud triangle, 0x18 bytes
typedef struct {
	unsigned short unknown1;
	unsigned short vertices[3];	/* Vertices index */
	unsigned short unknown2;
	unsigned long colours[3];
} prm_object_polygon_5_t;

//Polygon type 0x06
//There are several types of polygon type 6. As for polygon type, they start with it.
typedef struct {
	unsigned short type;
} prm_object_polygon_type_6_t;

//Then follow various subtypes:
//Polygon type 0x06, subtype 0x00,0x01
typedef struct {
	unsigned short vertices[3];	/* Vertices index */
	unsigned short texture_index;
	unsigned short unknown[12];
} prm_object_polygon_6_s00s01_t;



//Polygon type 0x06, subtype 0x80
typedef struct {
	unsigned short name_count;	/* Number of names */
	unsigned short unknown;
	prm_object_polygon_6_name_t *names;
} prm_object_polygon_6_s80_t;

//After this one follows 'name_count' character strings:
typedef struct {
	unsigned char name[12];	/* Name */
} prm_object_polygon_6_name_t;



//Polygon type 0x07 : Gouraud quad, 0x1C bytes
typedef struct {
	unsigned short unknown1;
	unsigned short vertices[4];	/* Vertices index */
	unsigned long colours[4];
} prm_object_polygon_7_t;

//Polygon type 0x08 : Textured quad
typedef struct {
	WORD unknown1;
	WORD vertices[4];	/* Vertices index */
	WORD texture_index;	/* Texture index */
	BYTE name[4];
	WORD unknown2[5];
	DWORD texcoord[4];	/* Texture coordinates */	
} prm_object_polygon_8_t;

//Polygon type 0x0a,0x0b
typedef struct {
	unsigned short unknown[7];
} prm_object_polygon_10_t;

class PRM{
public:
	PRM(char *fn){
		BINFILE *infile;
		infile = NULL;
		if(fn)
			infile = binopen(fn);
		if(infile)
			Read(infile);
		binclose(infile);
	}
	~PRM(){}

private:
	
	prm_object_header_t header;
	prm_object_vertex_t *verts;

	void Read(BINFILE *in){
		 binread(&header, sizeof(header), 1, in);
		 verts = (prm_object_vertex_t*)in->current;
		 binseek(in, header.vtx_count*sizeof(prm_object_vertex_t), BIN_CUR);
		 for(int i=0;i<header.vtx_count;i++){

		 }


		
	}
};

#endif