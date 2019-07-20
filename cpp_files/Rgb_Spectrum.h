#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

class Rgb_Spectrum
{
public:
	cv::Mat Img;

	// unsigned char and char* are used in place of int and int* to reduce space requirements
	// chars and unsigned chars typically have a size of 1 byte, where ints typically have a size of 4 bytes
	// the range of an unsigned char is 0 - 255, which is exactly what is needed by our program
	unsigned char R, G, B;
	unsigned char Current_Tile;
	char* Used_Tiles;

	Rgb_Spectrum(int tilefill = 1);

public: // Internal Calculation Methods
	int* m_get_tile_coords(int tile_num);      // Returns the coordinates to the top left pixel of given tile_num

	void m_rgb_advance(void);					// Updates R, G, and B to next RGB value

	void Erase_Tile(int tile);


//=======================================================================//
//====================== Tile Generation Methods ========================//
//=======================================================================//


//====================== Single Tile Fill Methods =======================//

private:
	int m_tile_validation(int tile);


public:
	/* Naming Convention : {Darkest Corner}_{RGB Progression Direction}
	// Corner Selection Keys:
		tl = top left
		tr = top right
		bl = bottom left
		br = bottom right
	// RGB Progression Keys:
		horz = horizontal
		vert = vertical

	// If a tile isn't specified by the user the function will search from left to right of the next unused tile, and fill the tile there
	*/

	int tl_vert(int tile = -1);

	int tl_horz(int tile = -1);

	int bl_vert(int tile = -1);

	int bl_horz(int tile = -1);

	int tr_vert(int tile = -1);

	int tr_horz(int tile = -1);

	int br_vert(int tile = -1);

	int br_horz(int tile = -1);


//======================== Quad Tile Fill Methods =======================//

private:
	int m_quad_validation(int tile, unsigned char minimum = 4);

public:
	int dark_corners_quad_vert(int tile = -1, unsigned char minimum = 4);

	int dark_corners_quad_horz(int tile = -1, unsigned char minimum = 4);

	int light_corners_quad_vert(int tile = -1, unsigned char minimum = 4);

	int light_corners_quad_horz(int tile = -1, unsigned char minimum = 4);


	int tl_wave_quad_vert(int tile = -1, unsigned char minimum = 4);

	int tl_wave_quad_horz(int tile = -1, unsigned char minimum = 4);

	int bl_wave_quad_vert(int tile = -1, unsigned char minimum = 4);

	int bl_wave_quad_horz(int tile = -1, unsigned char minimum = 4);

	int tr_wave_quad_vert(int tile = -1, unsigned char minimum = 4);

	int tr_wave_quad_horz(int tile = -1, unsigned char minimum = 4);

	int br_wave_quad_vert(int tile = -1, unsigned char minimum = 4);

	int br_wave_quad_horz(int tile = -1, unsigned char minimum = 4);


	int br_vert_weave_quad(int tile = -1, unsigned char minimum = 4);

//======================== Full Tile Fill Methods ========================//

	void tl_vert_full(void);

	void tl_horz_full(void);

	void bl_vert_full(void);

	void bl_horz_full(void);

	void tr_vert_full(void);

	void tr_horz_full(void);

	void br_vert_full(void);

	void br_horz_full(void);


	void dark_corners_vert_full(void);

	void dark_corners_horz_full(void);

	void light_corners_vert_full(void);

	void light_corners_horz_full(void);


	void tl_wave_vert_full(void);

	void tl_wave_horz_full(void);

	void bl_wave_vert_full(void);

	void bl_wave_horz_full(void);

	void tr_wave_vert_full(void);

	void tr_wave_horz_full(void);

	void br_wave_vert_full(void);

	void br_wave_horz_full(void);

	void br_vert_weave_full(void);

};
