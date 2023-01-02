#ifndef dataset_H
#define dataset_H
#include <stdint.h>
#include <array>
#include <vector>
#include <deque>
using namespace std;

/**
 * uint8_t is unsigned integer type with width of exactly 8 bits.
 * size_t is an unsigned integral data type, which is guaranteed to be big enough to contain
 * the size of the biggest object the host system can handle. Basically the maximum 
 * permissible size is dependent on the compiler.
**/

/* Define a datatype with name img_dt*/
// START OF YOUR IMPLEMENTATION
typedef struct img_dt {
	deque<deque<uint8_t>> data = {};
	// data[row][col]
	size_t num_rows;
	size_t num_cols;
} img_dt;
// END OF YOUR IMPLEMENTATION


const size_t ROWS = 28;
const size_t COLS = 28;
const size_t PIXELS = 28*28;

enum data_type {TRAIN_LABEL, TEST_LABEL, TRAIN_IMAGE, TEST_IMAGE};
enum shift_type {LEFT, RIGHT, UP, DOWN, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

class normalize {
	private:
		float denominator;
	public:
		normalize(float i) : denominator(i) { }
		float operator()(uint8_t value) { return value/denominator;}
};

class dataset {
	public:
		// CONSTRUCTOR member functions
		dataset();
		~dataset();
		
		// MUTATOR member functions
		void load_dataset();
		void remove_some_train_data(const uint8_t digit, const size_t size);
		void append_some_augmented_train_data(const uint8_t digit, const size_t size);

		img_dt convert_image_dt(const array<uint8_t, PIXELS>& img_ar) const;
		array<uint8_t, PIXELS> convert_image_dt(const img_dt& img) const;

		array<uint8_t, PIXELS> compound_augment_image(array<uint8_t, PIXELS>& img_ar);
		void shift_image(img_dt& img, const enum shift_type dir, const size_t p, const uint8_t value=0);
		void resize_image(img_dt& img, const size_t new_rows, const size_t new_cols);
		void crop_image(img_dt& img, const size_t y0, const size_t x0, const size_t new_rows, const size_t new_cols);
		void padding_image(img_dt& img, const size_t top=0, const size_t down=0, const size_t left=0, const size_t right=0, const uint8_t value=0);
		
		// ACCESSOR member functions: don't modify data
		uint8_t get_a_label(const enum data_type mode, const size_t index) const;
		array<uint8_t, PIXELS> get_an_image(const enum data_type mode, const size_t index) const;
		vector<float> get_a_normalized_image(const enum data_type mode, const size_t index) const;
		size_t get_data_size(const enum data_type mode) const;

		void print_image(const array<uint8_t, PIXELS>& img_ar) const;
		void print_image(const img_dt& img) const;
		void print_statistic(const enum data_type mode) const;
		
	private:
		vector<uint8_t> train_labels;
		vector<uint8_t> test_labels;
		vector<array<uint8_t, PIXELS>> train_images;
		vector<array<uint8_t, PIXELS>> test_images;
};

#endif
