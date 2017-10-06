#include "../libs/CImg.h"
#include <string>

const int MAX_BRIGHTNESS = 255;
const int DEFAULT_RESOLUTION = 6;

class image{

public:
	image(char* filename);
	~image();
	int compute_block_average(int start_x, int start_y, int res);
	std::string get_image_ascii();
	char get_char_by_brightness(int brightnes);
	void print_ascii_to_file(char* of_path, std::string output_ascii);

//Getters & setters
	int get_resolution();
	void set_resolution(int res);

private:
	int resolution;
	cimg_library::CImg<unsigned char>* raw_image;
	std::string ascii_darkness_string = "@%#*+=-:. ";
};


