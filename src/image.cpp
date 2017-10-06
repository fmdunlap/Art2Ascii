#include "../libs/CImg.h"
#include "image.h"
#include <fstream>
#include <iostream>

//Constructor from path of file-to-be-input.
image::image(char* file_name){

	raw_image = new cimg_library::CImg<unsigned char>(file_name);
	resolution = 6;

	//Consider putting this in an init function in the event of REALLY
	//big images.
	update_output_string();
}

image::~image(){
	delete raw_image;
}


std::string image::update_output_string(){
	this->ascii_output_string = "";

	int res = this->get_resolution();



	if(this->raw_image->depth() != 1){
		std::cout << "ERROR: Image is not strictly 2D.\n";
		return NULL;
	}

	for(int row = 0; row < this->raw_image->height(); row += res){
		for(int col = 0; col < this->raw_image->width(); col += res){

			int avg = compute_block_average(col, row, res);
			this->ascii_output_string += get_char_by_brightness(avg);
		}
		this->ascii_output_string += '\n';
	}

	return this->ascii_output_string;
}


//TODO: rewrite for clarity
char image::get_char_by_brightness(int brightness){

	double index = (((double)brightness)*((double)this->ascii_darkness_string.size()))/((double) MAX_BRIGHTNESS) -.25;
	return this->ascii_darkness_string.at((int)index);
}

int image::compute_block_average(int start_x, int start_y, int res){
	int average = 0;
	int n = 0;

	int image_spectrum = this->raw_image->spectrum();

	for(int row = start_y; row < start_y + res && row < this->raw_image->height(); row++){
		for(int col = start_x; col < start_x + res && col < this->raw_image->width(); col++){
			int sum = 0;

			for(int i = 0; i < image_spectrum; i++){
				sum += (*this->raw_image)(col, row, i);
			}
			
			int pixel_avg = (sum)/image_spectrum;   // Read blue value at coordinates (10,10) (Z-coordinate can be omitted).
			average = (pixel_avg + (n*average)) / (n+1);
			n++;
		}
	}

	return average;
}

void image::print_ascii_to_file(char* of_path){
	if(!this->ascii_output_string.empty()){
		std::ofstream ofile;
		ofile.open(of_path);
		ofile << this->ascii_output_string;
		ofile.close();
	} else {
		std::cout << "Output error occurred.\n";
	}
}

bool has_suffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}


//Getters/Setters
void image::set_resolution(int res){
	//Lil optimization in the even someone tries to set the
	//resolution to its current value.
	if(res != this->resolution){
		this->resolution = res;
		update_output_string();
	}
}

int image::get_resolution(){
	return this->resolution;
}

std::string image::get_image_ascii(){
	return this->ascii_output_string;
}