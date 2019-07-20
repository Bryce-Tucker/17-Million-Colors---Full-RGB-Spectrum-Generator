#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "Rgb_Spectrum.h"

void interactive_creation(Rgb_Spectrum img) {
	for (int i = 0; i < 256; i++) { // Label all tiles for easy identification
		cv::Point coords;
		coords.x = img.m_get_tile_coords(i)[0] + (256 / 2);
		coords.y = img.m_get_tile_coords(i)[1] + (256 / 2);
		cv::putText(img.Img, std::to_string(i), coords, cv::FONT_HERSHEY_PLAIN, 4, cv::Scalar(255, 255, 255), 4);
	}

	std::vector<int> tiles_called;
	std::vector<std::string> functions_called;
	std::vector<int> minimums_called;

	int recording_input = 0;

	int replaying_input = -1;
	int replaying_tile;

	for (int i = 0; ;) {
		cv::imshow("Img", img.Img);
		cv::waitKey(1);

		int tile;
		int minimum = 0;
		std::string command;
		std::cout << "Enter Tile Number, -1 to Record Input, -2 to Stop Recording, 256 to Replay Recording, or -3 to Quit: ";
		std::cin >> tile;

		if (tile == -1) {
			if (!recording_input) {
				if (tiles_called.empty()) {
					std::cout << "Recording Input" << std::endl;
					recording_input = 1;
					continue;
				}
				else {
					std::cout << "A recording already exists, would you like to erase it? (0) No : (1) Yes :: ";
					std::cin >> tile;
					if (tile) {
						std::cout << "\nRecording Input" << std::endl;
						tiles_called = std::vector<int>();
						functions_called = std::vector<std::string>();
						minimums_called = std::vector<int>();
						recording_input = 1;
					}
					continue;
				}
			}
			else {
				std::cout << "Already recording, stop previous recording before starting a new one." << std::endl;
				continue;
			}
		}

		if (tile == -2) {
			if (recording_input) { std::cout << "Ending Recording" << std::endl; recording_input = 0; continue; }
			else { std::cout << "Recording Mode Wasn't Active" << std::endl; continue; }
		}

		if (tile == -3) break;

		if (tile == 256) {
			if (tiles_called.empty()) {
				std::cout << "No recording stored." << std::endl;
				continue;
			}
			else {
				std::cout << "Enter Starting Tile For Replay: ";
				std::cin >> replaying_tile;
				replaying_tile = replaying_tile - tiles_called[tiles_called.size() - 1];
				replaying_input = tiles_called.size() - 1;
			}
		}

		if (replaying_input <= -1) {
			std::cout << std::endl << "Enter Command: ";
			std::cin >> command;
		}

		do {

			if (replaying_input > -1) {
				tile = tiles_called[replaying_input] + replaying_tile;
				command = functions_called[replaying_input];
				minimum = minimums_called[replaying_input];
			}

			if (command == "Erase_Tile") { img.Erase_Tile(tile); i--; }
			else if (command == "tl_vert") { if (img.tl_vert(tile)) i++; }
			else if (command == "tl_horz") { if (img.tl_horz(tile)) i++; }
			else if (command == "bl_vert") { if (img.bl_vert(tile)) i++; }
			else if (command == "bl_horz") { if (img.bl_horz(tile)) i++; }
			else if (command == "tr_vert") { if (img.tr_vert(tile)) i++; }
			else if (command == "tr_horz") { if (img.tr_horz(tile)) i++; }
			else if (command == "br_vert") { if (img.br_vert(tile)) i++; }
			else if (command == "br_horz") { if (img.br_horz(tile)) i++; }


			else if (command == "dark_corners_quad_vert") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.dark_corners_quad_vert(tile, minimum)) i += 4;
			}
			else if (command == "dark_corners_quad_horz") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.dark_corners_quad_horz(tile, minimum)) i += 4;
			}
			else if (command == "light_corners_quad_vert") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.light_corners_quad_vert(tile, minimum)) i += 4;
			}
			else if (command == "light_corners_quad_horz") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.light_corners_quad_horz(tile, minimum)) i += 4;
			}


			else if (command == "tl_wave_quad_vert") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.tl_wave_quad_vert(tile, minimum)) i += 4;
			}
			else if (command == "tl_wave_quad_horz") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.tl_wave_quad_horz(tile, minimum)) i += 4;
			}
			else if (command == "bl_wave_quad_vert") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.bl_wave_quad_vert(tile, minimum)) i += 4;
			}
			else if (command == "bl_wave_quad_horz") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.bl_wave_quad_horz(tile, minimum)) i += 4;
			}
			else if (command == "tr_wave_quad_vert") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.tr_wave_quad_vert(tile, minimum)) i += 4;
			}
			else if (command == "tr_wave_quad_horz") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.tr_wave_quad_horz(tile, minimum)) i += 4;
			}
			else if (command == "br_wave_quad_vert") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.br_wave_quad_vert(tile, minimum)) i += 4;
			}
			else if (command == "br_wave_quad_horz") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}

				if (img.br_wave_quad_horz(tile, minimum)) i += 4;
			}


			else if (command == "br_vert_weave_quad") {
				if (replaying_input <= -1) {
					std::cout << "Enter Tile Minimum: ";
					std::cin >> minimum;
				}
				if (img.br_vert_weave_quad(tile, minimum)) i += 4;
			}


			else if (command == "tl_vert_full") {
				img.tl_vert_full();
				break;
			}
			else if (command == "tl_horz_full") {
				img.tl_horz_full();
				break;
			}
			else if (command == "bl_vert_full") {
				img.bl_vert_full();
				break;
			}
			else if (command == "bl_horz_full") {
				img.bl_horz_full();
				break;
			}
			else if (command == "tr_vert_full") {
				img.tr_vert_full();
				break;
			}
			else if (command == "tr_horz_full") {
				img.tr_horz_full();
				break;
			}
			else if (command == "br_vert_full") {
				img.br_vert_full();
				break;
			}
			else if (command == "br_horz_full") {
				img.br_horz_full();
				break;
			}

			else if (command == "dark_corners_vert_full") {
				img.dark_corners_vert_full();
				break;
			}
			else if (command == "dark_corners_horz_full") {
				img.dark_corners_horz_full();
				break;
			}
			else if (command == "light_corners_vert_full") {
				img.light_corners_vert_full();
				break;
			}
			else if (command == "light_corners_horz_full") {
				img.light_corners_horz_full();
				break;
			}


			else if (command == "tl_wave_vert_full") {
				img.tl_wave_vert_full();
				break;
			}
			else if (command == "tl_wave_horz_full") {
				img.tl_wave_horz_full();
				break;
			}
			else if (command == "bl_wave_vert_full") {
				img.bl_wave_vert_full();
				break;
			}
			else if (command == "bl_wave_horz_full") {
				img.bl_wave_horz_full();
				break;
			}
			else if (command == "tr_wave_vert_full") {
				img.tr_wave_vert_full();
				break;
			}
			else if (command == "tr_wave_horz_full") {
				img.tr_wave_horz_full();
				break;
			}
			else if (command == "br_wave_vert_full") {
				img.br_wave_vert_full();
				break;
			}
			else if (command == "br_wave_horz_full") {
				img.br_wave_horz_full();
				break;
			}

			else if (command == "br_vert_weave_full") {
				img.br_vert_weave_full();
				break;
			}

			else { std::cout << "Command Not Recognized" << std::endl; continue; }

			if (recording_input) {
				tiles_called.insert(tiles_called.begin(), tile);
				functions_called.insert(functions_called.begin(), command);
				minimums_called.insert(minimums_called.begin(), minimum);
			}
		} while (--replaying_input > -1);

		std::cout << i << std::endl;
		cv::imshow("Img", img.Img);
		cv::waitKey(1);
	}
	int response;
	std::cout << "Would you like to clean and save created image? (0) No : (1) Yes :: ";
	std::cin >> response;
	if (response) {
		for (int i = 0; i < 256; i++) {
			if (!img.Used_Tiles[i]) {
				img.Erase_Tile(i);
			}

		}
		std::string DST;
		std::cout << "Enter File Destination: ";
		std::cin >> DST;
		cv::imwrite(DST, img.Img);
	}
}

int main(void) {
	Rgb_Spectrum img;
	cv::namedWindow("Img", cv::WINDOW_FREERATIO);

	interactive_creation(img);

	return (0);
}
