#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <random>
#include "dataset.h"
using namespace std;

const char* PATH_TRAIN_LABELS = "train-labels-idx1-ubyte";
const char* PATH_TRAIN_IMAGES = "train-images-idx3-ubyte";
const char* PATH_TEST_LABELS = "t10k-labels-idx1-ubyte";
const char* PATH_TEST_IMAGES = "t10k-images-idx3-ubyte";


dataset::dataset() {}

dataset::~dataset() {}

void dataset::load_dataset() {
	ifstream fin;
	uint32_t MN, N, A, B;
	
	
	fin = ifstream(PATH_TRAIN_LABELS, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	N = __builtin_bswap32(N)/3;
	
	if (MN != 0x01080000) {
		cerr << "Invalid database" << endl;
		exit(1);
	}
	
	train_labels.resize(N);
	fin.read((char*)train_labels.data(), N * sizeof(uint8_t));
	
	
	fin = ifstream(PATH_TRAIN_IMAGES, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	fin.read((char*)&A, sizeof(A));
	fin.read((char*)&B, sizeof(B));
	
	N = __builtin_bswap32(N)/3;
	A = __builtin_bswap32(A);
	B = __builtin_bswap32(B);
	
	if (MN != 0x03080000 || A != COLS || B != ROWS) {
		cerr << "invalid database" << endl;
		exit(1);
	}
	
	train_images.resize(N);
	fin.read((char*)train_images.data(), N * sizeof(array<uint8_t, PIXELS>));
	
	
	fin = ifstream(PATH_TEST_LABELS, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	N = __builtin_bswap32(N)/3;
	
	if (MN != 0x01080000) {
		cerr << "Invalid database" << endl;
		exit(1);
	}
	
	test_labels.resize(N);
	fin.read((char*)test_labels.data(), N * sizeof(uint8_t));
	
	
	fin = ifstream(PATH_TEST_IMAGES, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	fin.read((char*)&A, sizeof(A));
	fin.read((char*)&B, sizeof(B));
	
	N = __builtin_bswap32(N)/3;
	A = __builtin_bswap32(A);
	B = __builtin_bswap32(B);
	
	if (MN != 0x03080000 || A != COLS || B != ROWS) {
		cerr << "invalid database" << endl;
		exit(1);
	}
	
	test_images.resize(N);
	fin.read((char*)test_images.data(), N * sizeof(array<uint8_t, PIXELS>));
}

void dataset::remove_some_train_data(const uint8_t digit, const size_t size) {
	// START OF YOUR IMPLEMENTATION
	size_t counter = 0;
	for (size_t i = train_labels.size() - 1; i >= 0 && counter < size; i--) {
		if (train_labels[i] == digit) {
			train_images.erase(train_images.begin() + i);
			train_labels.erase(train_labels.begin() + i);
			counter++;
		}
	}
	// END OF YOUR IMPLEMENTATION
}

void dataset::append_some_augmented_train_data(const uint8_t digit, const size_t size) {
	vector<size_t> indices;
	unsigned int counter = 0;
	
	for (vector<uint8_t>::iterator it = train_labels.begin(); it != train_labels.end(); it++) {
		if (*it == digit) {
			indices.push_back(distance(train_labels.begin(), it));
		}
	}
	
	vector<size_t>::iterator it2 = indices.begin();
	while(counter<size) {
		counter++;
		train_images.push_back(this->compound_augment_image(train_images[*it2]));
		train_labels.push_back(digit);
		
		it2++;
		if(it2 == indices.end()) {
			it2 = indices.begin();
		}
	}
}

array<uint8_t, PIXELS> dataset::compound_augment_image(array<uint8_t, PIXELS>& img_ar) {
	img_dt img = convert_image_dt(img_ar);
	size_t rand_num = rand()% 8;
	this->shift_image(img, shift_type(rand_num), rand()% 4);
	this->resize_image(img, rand_num, rand_num);
	if(rand_num>ROWS) {
		this->crop_image(img, (rand_num-ROWS)/2, (rand_num-COLS)/2, ROWS, COLS);
	}
	else {
		this->padding_image(img, (ROWS-rand_num)/2, ROWS-(ROWS-rand_num)/2-rand_num, (COLS-rand_num)/2, COLS-(COLS-rand_num)/2-rand_num);
	}
	array<uint8_t, PIXELS> img_ar_out = convert_image_dt(img);
	
	return img_ar_out;
}

void dataset::shift_image(img_dt& img, const enum shift_type dir, const size_t p, const uint8_t value) {
	// START OF YOUR IMPLEMENTATION
	switch (dir) {
		case LEFT:
			for (size_t row = 0; row < img.num_rows; row++) {
				for (size_t i = 0; i < p; i++) {
					img.data[row].pop_front();
					img.data[row].push_back(value);
				}
			}
			break;
		case RIGHT:
			for (size_t row = 0; row < img.num_rows; row++) {
				for (size_t i = 0; i < p; i++) {
					img.data[row].pop_back();
					img.data[row].push_front(value);
				}
			}
			break;
		case UP:
			for (size_t i = 0; i < p; i++) {
				deque<uint8_t> temp;
				for (size_t col = 0; col < img.num_cols; col++) {
					temp.push_back(value);
				}
				img.data.pop_front();
				img.data.push_back(temp);
			}
			break;
		case DOWN:
			for (size_t i = 0; i < p; i++) {
				deque<uint8_t> temp;
				for (size_t col = 0; col < img.num_cols; col++) {
					temp.push_back(value);
				}
				img.data.pop_back();
				img.data.push_front(temp);
			}
			break;
		// call shift_image twice to shift diagonally
		case UPLEFT:
			shift_image(img, UP, p, value);
			shift_image(img, LEFT, p, value);
			break;
		case UPRIGHT:
			shift_image(img, UP, p, value);
			shift_image(img, RIGHT, p, value);
			break;
		case DOWNLEFT:
			shift_image(img, DOWN, p, value);
			shift_image(img, LEFT, p, value);
			break;
		case DOWNRIGHT:
			shift_image(img, DOWN, p, value);
			shift_image(img, RIGHT, p, value);
			break;
	}
	// END OF YOUR IMPLEMENTATION
}

void dataset::resize_image(img_dt& img, const size_t new_rows, const size_t new_cols) {
	// START OF YOUR IMPLEMENTATION
	// create new image first and copy later
	img_dt new_img;
	new_img.num_rows = new_rows;
	new_img.num_cols = new_cols;
	// iterate through pixels of new_img
	for (size_t row = 0; row < new_rows; row++) {
		deque<uint8_t> temp;
		for (size_t col = 0; col < new_cols; col++) {
			size_t neighbour_row = 0;
			size_t neighbour_col = 0;
			float project_row = (float(row) + 0.5) * img.num_rows / new_rows;
			float project_col = (float(col) + 0.5) * img.num_cols / new_cols;
			float distance = PIXELS;
			// iterate through img to find the least distance
			for (size_t temp_row = 0; temp_row < img.num_rows; temp_row++) {
				for (size_t temp_col = 0; temp_col < img.num_rows; temp_col++) {
					// pythagoras without square root
					float temp_distance = ((temp_row + 0.5 - project_row)*(temp_row + 0.5 - project_row) + (temp_col + 0.5 - project_col)*(temp_col + 0.5 - project_col));
					if (temp_distance <= distance) {
						// change nearest neighbour
						distance = temp_distance;
						neighbour_row = temp_row;
						neighbour_col = temp_col;
					}
				}
			}
			
			temp.push_back(img.data[neighbour_row][neighbour_col]);
		}
		new_img.data.push_back(temp);
	}
	
	// copy data from new_img to img
	img.data.clear();
	img.num_rows = new_rows;
	img.num_cols = new_cols;
	for (size_t row = 0; row < new_rows; row++) {
		deque<uint8_t> temp;
		for (size_t col = 0; col < new_cols; col++) {
			temp.push_back(new_img.data[row][col]);
		}
		img.data.push_back(temp);
	}
	// END OF YOUR IMPLEMENTATION
}

void dataset::crop_image(img_dt& img, const size_t y0, const size_t x0, const size_t new_rows, const size_t new_cols) {
	// START OF YOUR IMPLEMENTATION
	// crop rows
	for (size_t row = 0; row < img.num_rows; row++) {
		if (row < y0) {
			// crop top
			img.data.pop_front();
		} else if (row >= (y0 + new_rows)) {
			// crop bottom
			img.data.pop_back();
		}
	}
	img.num_rows = new_rows;
	
	// crop columns
	for (size_t col = 0; col < img.num_cols; col++) {
		// iterate to pop the deque of each row
		for (size_t row = 0; row < img.num_rows; row++) {
			if (col < x0) {
				// crop left
				img.data[row].pop_front();
			} else if (col >= (x0 + new_cols)) {
				// crop right
				img.data[row].pop_back();
			}
		}
	}
	img.num_cols = new_cols;
	// END OF YOUR IMPLEMENTATION
}

void dataset::padding_image(img_dt& img, const size_t top, const size_t down, const size_t left, const size_t right, const uint8_t value) {
	// START OF YOUR IMPLEMENTATION
	// push top
	for (size_t i = 0; i < top; i++) {
		deque<uint8_t> temp;
		for (size_t col = 0; col < img.num_cols; col++) {
			temp.push_back(value);
		}
		img.data.push_front(temp);
	}
	img.num_rows += top;
	
	// push bottom
	for (size_t i = 0; i < down; i++) {
		deque<uint8_t> temp;
		for (size_t col = 0; col < img.num_cols; col++) {
			temp.push_back(value);
		}
		img.data.push_back(temp);
	}
	img.num_rows += down;
	
	// push left
	for (size_t i = 0; i < left; i++) {
		// iterate to push the deque of each row
		for (size_t row = 0; row < img.num_rows; row++) {
			img.data[row].push_front(value);
		}
	}
	img.num_cols += left;
	
	// push right
	for (size_t i = 0; i < right; i++) {
		// iterate to push the deque of each row
		for (size_t row = 0; row < img.num_rows; row++) {
			img.data[row].push_back(value);
		}
	}
	img.num_cols += right;
	// END OF YOUR IMPLEMENTATION
}

uint8_t dataset::get_a_label(const data_type mode, const size_t index) const {
	switch (mode) {
		case TRAIN_LABEL: 
			return train_labels[index];
			break;
		case TEST_LABEL: 
			return test_labels[index];
			break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}

img_dt dataset::convert_image_dt(const array<uint8_t, PIXELS>& img) const {
	// START OF YOUR IMPLEMENTATION
	img_dt new_img;
	new_img.num_rows = ROWS;
	new_img.num_cols = COLS;
	// add rows
	for (size_t row = 0; row < ROWS; row++) {
		deque<uint8_t> temp;
		// add cols
		for (size_t col = 0; col < COLS; col++) {
			temp.push_back(img[row * COLS + col]);
		}
		new_img.data.push_back(temp);
	}
	return new_img;
	// END OF YOUR IMPLEMENTATION
}

array<uint8_t, PIXELS> dataset::convert_image_dt(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	array<uint8_t, PIXELS> new_img;
	// add rows
	for (size_t row = 0; row < ROWS; row++) {
		// add cols
		for (size_t col = 0; col < COLS; col++) {
			new_img[row * COLS + col] = img.data[row][col];
		}
	}
	return new_img;
	// END OF YOUR IMPLEMENTATION
}

array<uint8_t, PIXELS> dataset::get_an_image(const enum data_type mode, const size_t index) const {
	switch (mode) {
		case TRAIN_IMAGE:
			return train_images[index];
			break;
		case TEST_IMAGE: 
			return test_images[index];
			break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}

vector<float> dataset::get_a_normalized_image(const enum data_type mode, const size_t index) const {
	const array<uint8_t, PIXELS>& img = this->get_an_image(mode, index);
	vector<float> img_normalized(PIXELS);
	
	transform(img.begin(), img.end(), img_normalized.begin(), normalize(255.0f));
	return img_normalized;
}

size_t dataset::get_data_size(const enum data_type mode) const {
	switch (mode) {
		case TRAIN_LABEL: 
			return train_labels.size();
			break;
		case TEST_LABEL:
			return test_labels.size();
			break;
		case TRAIN_IMAGE: 
			return train_images.size();
			break;
		case TEST_IMAGE: 
			return test_images.size();
			break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}

void dataset::print_image(const array<uint8_t, PIXELS>& img_ar) const {
	// START OF YOUR IMPLEMENTATION
	for (size_t row = 0; row < ROWS; row++) {
		for (size_t col = 0; col < COLS; col++) {
			cout << setw(4) << static_cast<int>(img_ar[row * COLS + col]);
		}
		cout << endl;
	}
	// END OF YOUR IMPLEMENTATION
}

void dataset::print_image(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	for (size_t row = 0; row < img.num_rows; row++) {
		for (size_t col = 0; col < img.num_cols; col++) {
			cout << setw(4) << static_cast<int>(img.data[row][col]);
		}
		cout << endl;
	}
	// END OF YOUR IMPLEMENTATION
}

void dataset::print_statistic(const enum data_type mode) const {
	// START OF YOUR IMPLEMENTATION
	size_t digit_sizes[10] = {0};
	size_t total = get_data_size(mode);
	
	// add number of labels/images for each digit
	for (size_t i = 0; i < total; i++) {
		digit_sizes[get_a_label((mode == TRAIN_IMAGE) ? TRAIN_LABEL : TEST_LABEL, i)]++;
	}
	
	for (int i = 0; i < 10; i++) {
		if (mode == TRAIN_IMAGE) {
			cout << "Number of train images for digit " << i << ": " << digit_sizes[i] << endl;
		} else if (mode == TEST_IMAGE) { 
			cout << "Number of test images for digit " << i << ": " << digit_sizes[i] << endl;
		}
		
	}
	// END OF YOUR IMPLEMENTATION
}
