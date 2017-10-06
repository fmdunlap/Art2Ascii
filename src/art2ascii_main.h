#include "CImg.h"
#include <string>

int compute_block_average(cimg_library::CImg<unsigned char> img, int start_x, int start_y, int res);
std::string get_image_ascii(cimg_library::CImg<unsigned char> img, int res);
char get_char_by_brightness(int brightnes);
void print_ascii_to_file(char* of_path, std::string output_ascii);