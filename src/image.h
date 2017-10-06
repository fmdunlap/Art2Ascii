#include "../libs/CImg.h"
#include <string>

const int MAX_BRIGHTNESS = 255;

class image{

public:
	image(char* filename);
	int compute_block_average(int start_x, int start_y, int res);
	std::string get_image_ascii(int res);
	char get_char_by_brightness(int brightnes);
	void print_ascii_to_file(char* of_path, std::string output_ascii);

private:
	cimg_library::CImg<unsigned char>* raw_image;
	std::string ascii_darkness_string = "@%#*+=-:. ";

};


