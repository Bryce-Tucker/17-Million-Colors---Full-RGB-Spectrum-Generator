#include "Rgb_Spectrum.h"

Rgb_Spectrum::Rgb_Spectrum(int tilefill){
	Img = cv::Mat::zeros(cv::Size(4096, 4096), CV_8UC3);
	R = 0; G = 0; B = 0;
	if (tilefill) {
		Current_Tile = 0;
		Used_Tiles = (char*)malloc(sizeof(char) * 257);
		for (int i = 0; i <= 256; i++) Used_Tiles[i] = 0;
	}
	else Used_Tiles = nullptr;
}


int* Rgb_Spectrum::m_get_tile_coords(int tile_num) {      // Returns the coordinates to the top left pixel of given tile_num
	int coords[2];
	coords[0] = (tile_num % 16) * 256;
	coords[1] = (tile_num / 16) * 256;
	return (coords);
}

void Rgb_Spectrum::m_rgb_advance(void) {
	B++;
	if (B == 0) {
		G++;
		if (G == 0) R++;
	}
}

void Rgb_Spectrum::Erase_Tile(int tile) {
	Used_Tiles[tile] = 0;
	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int X = coords[0];
	const int Y = coords[1];
	for (int r = 0; r < 256; r++) {
		for (int c = 0; c < 256; c++) {
			Img.at<cv::Vec3b>(Y + r, X + c) = cv::Vec3b(0, 0, 0);
		}
	}
}



/*************************************************************************/
/***********************   Tile Fill Methods     *************************/
/*************************************************************************/


int Rgb_Spectrum::m_tile_validation(int tile) {
	if (Used_Tiles == nullptr || tile > 255 || tile < -1) return (-2);
	if (tile == -1) {
		int tmp_current = Current_Tile;
		while (Used_Tiles[Current_Tile]) {
			Current_Tile++;
			if (Current_Tile == tmp_current) return (-1);
		}
		return(Current_Tile);
	}
	else if (!Used_Tiles[tile]) return (tile);
	return (-1);
}


int Rgb_Spectrum::tl_vert(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];

	for (int c = x; c < (x + 256); c++) {
		for (int r = y; r < (y + 256); r++) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}

	Used_Tiles[tile] = 1;
	return (tile);
}


int Rgb_Spectrum::tl_horz(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];
	for (int r = y; r < (y + 256); r++) {
		for (int c = x; c < (x + 256); c++) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}
	Used_Tiles[tile] = 1;
	return (tile);
}

int Rgb_Spectrum::bl_vert(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];
	for (int c = x; c < (x + 256); c++) {
		for (int r = y + 255; r >= y; r--) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}
	Used_Tiles[tile] = 1;
	return (tile);
}

int Rgb_Spectrum::bl_horz(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];
	for (int r = y + 255; r >= y; r--) {
		for (int c = x; c < (x + 256); c++) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}
	Used_Tiles[tile] = 1;
	return (tile);
}

int Rgb_Spectrum::tr_vert(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];
	for (int c = x + 255; c >= x; c--) {
		for (int r = y; r < (y + 256); r++) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}
	Used_Tiles[tile] = 1;
	return (tile);
}

int Rgb_Spectrum::tr_horz(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];
	for (int r = y; r < y + 256; r++) {
		for (int c = x + 255; c >= x; c--) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}
	Used_Tiles[tile] = 1;
	return (tile);
}

int Rgb_Spectrum::br_vert(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];
	for (int c = x + 255; c >= x; c--) {
		for (int r = y + 255; r >= y; r--) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}
	Used_Tiles[tile] = 1;
	return (tile);
}

int Rgb_Spectrum::br_horz(int tile) {
	tile = Rgb_Spectrum::m_tile_validation(tile);
	if (tile < 0) return (tile);

	int* coords = Rgb_Spectrum::m_get_tile_coords(tile);
	const int x = coords[0];
	const int y = coords[1];
	for (int r = y + 255; r >= y; r--) {
		for (int c = x + 255; c >= x; c--) {
			Img.at<cv::Vec3b>(r, c) = cv::Vec3b(B, G, R);
			Rgb_Spectrum::m_rgb_advance();
		}
	}
	Used_Tiles[tile] = 1;
	return (tile);
}


/*************************************************************************/
/***********************   Quad Fill Methods     *************************/
/*************************************************************************/


int Rgb_Spectrum::m_quad_validation(int tile, unsigned char minimum) {

	if (tile == -1) {
		unsigned char tmp_current = Current_Tile;

		for (int i = 0; i < 256; i++) {
			if (Rgb_Spectrum::m_quad_validation(Current_Tile, minimum) != -1) return (Current_Tile);
			Current_Tile++;
		}
		return (-1);
	}

	if (tile < -1 || tile > 255 - 16 || (tile + 1) % 16 == 0) return (-1);

	else {
		unsigned char count = 0;

		if (!Used_Tiles[tile]) count++;
		if (!Used_Tiles[tile + 1]) count++;
		if (!Used_Tiles[tile + 16]) count++;
		if (!Used_Tiles[tile + 17]) count++;

		if (count >= minimum) return (tile);
	}

	return (-1);
}

int Rgb_Spectrum::dark_corners_quad_vert(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) tl_vert(tile);
	if (!Used_Tiles[tile + 1]) tr_vert(tile + 1);
	if (!Used_Tiles[tile + 16]) bl_vert(tile + 16);
	if (!Used_Tiles[tile + 17]) br_vert(tile + 17);


	return (1);
}

int Rgb_Spectrum::dark_corners_quad_horz(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) tl_horz(tile);
	if (!Used_Tiles[tile + 1]) tr_horz(tile + 1);
	if (!Used_Tiles[tile + 16]) bl_horz(tile + 16);
	if (!Used_Tiles[tile + 17]) br_horz(tile + 17);


	return (1);
}

int Rgb_Spectrum::light_corners_quad_vert(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) br_vert(tile);
	if (!Used_Tiles[tile + 1]) bl_vert(tile + 1);
	if (!Used_Tiles[tile + 16]) tr_vert(tile + 16);
	if (!Used_Tiles[tile + 17]) tl_vert(tile + 17);


	return (1);
}

int Rgb_Spectrum::light_corners_quad_horz(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) br_horz(tile);
	if (!Used_Tiles[tile + 1]) bl_horz(tile + 1);
	if (!Used_Tiles[tile + 16]) tr_horz(tile + 16);
	if (!Used_Tiles[tile + 17]) tl_horz(tile + 17);


	return (1);
}

int Rgb_Spectrum::tl_wave_quad_vert(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) tl_vert(tile);
	if (!Used_Tiles[tile + 1]) tr_vert(tile + 1);
	if (!Used_Tiles[tile + 16]) tr_vert(tile + 16);
	if (!Used_Tiles[tile + 17]) tl_vert(tile + 17);


	return (1);
}

int Rgb_Spectrum::tl_wave_quad_horz(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) tl_horz(tile);
	if (!Used_Tiles[tile + 1]) tr_horz(tile + 1);
	if (!Used_Tiles[tile + 16]) tr_horz(tile + 16);
	if (!Used_Tiles[tile + 17]) tl_horz(tile + 17);


	return (1);
}

int Rgb_Spectrum::bl_wave_quad_vert(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) bl_vert(tile);
	if (!Used_Tiles[tile + 1]) br_vert(tile + 1);
	if (!Used_Tiles[tile + 16]) br_vert(tile + 16);
	if (!Used_Tiles[tile + 17]) bl_vert(tile + 17);


	return (1);
}

int Rgb_Spectrum::bl_wave_quad_horz(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) bl_horz(tile);
	if (!Used_Tiles[tile + 1]) br_horz(tile + 1);
	if (!Used_Tiles[tile + 16]) br_horz(tile + 16);
	if (!Used_Tiles[tile + 17]) bl_horz(tile + 17);


	return (1);
}

int Rgb_Spectrum::tr_wave_quad_vert(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) tr_vert(tile);
	if (!Used_Tiles[tile + 1]) tl_vert(tile + 1);
	if (!Used_Tiles[tile + 16]) tl_vert(tile + 16);
	if (!Used_Tiles[tile + 17]) tr_vert(tile + 17);


	return (1);
}

int Rgb_Spectrum::tr_wave_quad_horz(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) tr_horz(tile);
	if (!Used_Tiles[tile + 1]) tl_horz(tile + 1);
	if (!Used_Tiles[tile + 16]) tl_horz(tile + 16);
	if (!Used_Tiles[tile + 17]) tr_horz(tile + 17);


	return (1);
}

int Rgb_Spectrum::br_wave_quad_vert(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) br_vert(tile);
	if (!Used_Tiles[tile + 1]) bl_vert(tile + 1);
	if (!Used_Tiles[tile + 16]) bl_vert(tile + 16);
	if (!Used_Tiles[tile + 17]) br_vert(tile + 17);


	return (1);
}

int Rgb_Spectrum::br_wave_quad_horz(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) br_horz(tile);
	if (!Used_Tiles[tile + 1]) bl_horz(tile + 1);
	if (!Used_Tiles[tile + 16]) bl_horz(tile + 16);
	if (!Used_Tiles[tile + 17]) br_horz(tile + 17);


	return (1);
}


int Rgb_Spectrum::br_vert_weave_quad(int tile, unsigned char minimum) {
	tile = Rgb_Spectrum::m_quad_validation(tile, minimum);

	if (tile == -1) return (0);

	if (!Used_Tiles[tile]) br_vert(tile);
	if (!Used_Tiles[tile + 1]) tr_vert(tile + 1);
	if (!Used_Tiles[tile + 16]) bl_horz(tile + 16);
	if (!Used_Tiles[tile + 17]) tl_horz(tile + 17);


	return (1);
}



/*************************************************************************/
/***********************   Full Fill Methods     *************************/
/*************************************************************************/


void Rgb_Spectrum::tl_vert_full(void) {
	for (int i = 0; i < 256; i++) {
		tl_vert(i);
	}
}

void Rgb_Spectrum::tl_horz_full(void) {
	for (int i = 0; i < 256; i++) {
		tl_horz(i);
	}
}

void Rgb_Spectrum::bl_vert_full(void) {
	for (int i = 0; i < 256; i++) {
		bl_vert(i);
	}
}

void Rgb_Spectrum::bl_horz_full(void) {
	for (int i = 0; i < 256; i++) {
		bl_horz(i);
	}
}

void Rgb_Spectrum::tr_vert_full(void) {
	for (int i = 0; i < 256; i++) {
		tr_vert(i);
	}
}

void Rgb_Spectrum::tr_horz_full(void) {
	for (int i = 0; i < 256; i++) {
		tr_horz(i);
	}
}

void Rgb_Spectrum::br_vert_full(void) {
	for (int i = 0; i < 256; i++) {
		br_vert(i);
	}
}

void Rgb_Spectrum::br_horz_full(void) {
	for (int i = 0; i < 256; i++) {
		br_horz(i);
	}
}


void Rgb_Spectrum::dark_corners_vert_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::dark_corners_quad_vert();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::dark_corners_horz_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::dark_corners_quad_horz();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::light_corners_vert_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::light_corners_quad_vert();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::light_corners_horz_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::light_corners_quad_horz();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::tl_wave_vert_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::tl_wave_quad_vert();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::tl_wave_horz_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::tl_wave_quad_horz();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::bl_wave_vert_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::bl_wave_quad_vert();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::bl_wave_horz_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::bl_wave_quad_horz();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::tr_wave_vert_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::tr_wave_quad_vert();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::tr_wave_horz_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::tr_wave_quad_horz();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::br_wave_vert_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::br_wave_quad_vert();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::br_wave_horz_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::br_wave_quad_horz();
		}
		Current_Tile += 16;
	}
}

void Rgb_Spectrum::br_vert_weave_full(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Rgb_Spectrum::br_vert_weave_quad();
		}
		Current_Tile += 16;
	}
}
