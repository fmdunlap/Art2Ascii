#include "../libs/CImg.h"
#include <string>

const int MAX_BRIGHTNESS = 255;
const int DEFAULT_RESOLUTION = 6;

class image{

public:
	image(char* filename);
	~image();

	/*Computes the average brightness of a 'block'
	  
	  A block is a square of pixels that starts at a pixel(x,y)
	  and extends to x+resolution, and y+resolution.
	*/
	int compute_block_average(int start_x, int start_y, int res);

	/*Returns character in ascii_darkness_string that should be assosciated with
	the given brightness.

	NOTE: 0 <= BRIGHNTESS <= MAX_BRIGHTNESS

	NOTE: Automatically maps from 0-MAX_BRIGHTNESS into 'ascii_darkness_string'
		  Function does not need to be updated if ascii_darkness_string is updated.
	*/
	char get_char_by_brightness(int brightness);

	//Prints current output_string to file at of_path
	void print_ascii_to_file(char* of_path);

	//If possible, updates the output ascii string to the current image & resolution.
	//Also returns the output string.
	std::string update_output_string();

//Getters & setters
	int get_resolution();

	//NOTE: CAN BE A LONG RUNNING FUNCTION IN CHANGING RESOLUTION ON LARGE IMAGE.
	void set_resolution(int res);

	//Returns output_string
	std::string get_image_ascii();

private:
	int resolution;
	cimg_library::CImg<unsigned char>* raw_image;
	std::string ascii_darkness_string = "@#%*+=-:. ";
	std::string ascii_output_string;
};