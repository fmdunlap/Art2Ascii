#include "../libs/CImg.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <math.h>

//Constructor from path of file-to-be-input.
image::image(char* file_name){

	raw_image = new cimg_library::CImg<unsigned char>(file_name);
	resolution = 6;
	pType = standard;

	//Consider putting this in an init function in the event of REALLY
	//big images.
	update_output_string();
}

//Constructor from path of file-to-be-input.
image::image(char* file_name, PROCESS_TYPE pt){

	raw_image = new cimg_library::CImg<unsigned char>(file_name);
	resolution = 6;
	pType = pt;

	switch(pt){
		case(color):
			int r;
			int g;
			int b;

			std::cout << "What color would you like to distance for?\n";
			std::cout << "R: ";
			std::cin >> r;
			std::cout << "G: ";
			std::cin >> g;
			std::cout << "B: ";
			std::cin >> b;

			base_color = new int[this->raw_image->spectrum()];
			base_color[0] = r;
			base_color[1] = g;
			base_color[2] = b;

			break;
	}

	//Consider putting this in an init function in the event of REALLY
	//big images.
	update_output_string();
}

image::~image(){
	delete raw_image;

	if(base_color != NULL){
		delete base_color;
	}
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

			int avg = 0;

			switch(this->pType){
				case(standard):
					avg = compute_block_average(col, row, res);
					break;
				case(color):
					avg = compute_block_color_distance(col, row, res, this->base_color);
					break;
				default:
					avg = 127;
			}
			this->ascii_output_string += get_char_by_brightness(avg);
		}
		this->ascii_output_string += '\n';
	}

	return this->ascii_output_string;
}


//TODO: rewrite for clarity
char image::get_char_by_brightness(int brightness){

	double index = (((double)brightness)*((double)this->ascii_darkness_string.size()))/((double) MAX_BRIGHTNESS) -.25;

	if(index < this->ascii_darkness_string.size())
		return this->ascii_darkness_string.at((int)index);
	else return ' ';
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
			
			int pixel_avg = (sum)/image_spectrum;
			average = (pixel_avg + (n*average)) / (n+1);
			n++;
		}
	}

	return average;
}


//Issue has to do with how I'm mapping characters. The brightness mapping won't work for color distance...
int image::compute_block_color_distance(int start_x, int start_y, int res, int* color_values){
	int average = 0;
	int n = 0;

	int image_spectrum = this->raw_image->spectrum();

	int max_difference = sqrt(image_spectrum*(pow(255,2)));

	int current_pixel_color_values[image_spectrum];

	for(int row = start_y; row < start_y + res && row < this->raw_image->height(); row++){
		for(int col = start_x; col < start_x + res && col < this->raw_image->width(); col++){
			int inner_sum = 0;

			for(int i = 0; i < image_spectrum; i++){
				current_pixel_color_values[i] = (*this->raw_image)(col, row, i);
				inner_sum += (int)pow(current_pixel_color_values[i] - color_values[i], 2);
			}
			
			int pixel_distance = sqrt(inner_sum);
			average = (pixel_distance + (n*average)) / (n+1);
			n++;
		}
	}

	return MAX_BRIGHTNESS - ((average*MAX_BRIGHTNESS)/max_difference);
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