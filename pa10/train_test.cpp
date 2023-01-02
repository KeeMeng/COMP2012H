#include <algorithm>
#include <numeric>
#include "dataset.h"
#include "nn.h"
#include <iostream>
using namespace std;

void training(NN&, dataset&, const size_t&);
void testing(NN&, dataset&);

void nn_training_testing(dataset& data) {
	NN nn {
		new LayerLinear(PIXELS, 32),
		new LayerSigmoid,
		new LayerLinear(32, 16),
		new LayerSigmoid,
		new LayerLinear(16, 10),
		new LayerSigmoid,
	};
	
	for (size_t epoch = 0; epoch < 10; epoch++) {
		training(nn, data, epoch);
		testing(nn, data);
	}
}

void training(NN& nn, dataset& data, const size_t& epoch) {
	vector<size_t> Sequence(data.get_data_size(TRAIN_LABEL));
	iota(Sequence.begin(), Sequence.end(), 0);
	random_shuffle(Sequence.begin(), Sequence.end());
	
	printf("================ Epoch %lu ================\n", epoch+1);
	
	for (size_t i = 0; i < Sequence.size(); i++) {
		vector<float> input = data.get_a_normalized_image(TRAIN_IMAGE, Sequence[i]);
		vector<float> one_hot_label(10);
		one_hot_label[data.get_a_label(TRAIN_LABEL, Sequence[i])] = 1;
		
		nn.backprop(input, one_hot_label);
		
		if ((i + 1) % 10 == 0) {
			nn.apply();
		}
		
		if ((i + 1) % 500 == 0) {
			printf("Epoch %lu: %lu / %lu\r", epoch+1, i+1, Sequence.size());
			fflush(stdout);
		}
	}
}

void testing(NN& nn, dataset& data) {
	// START OF YOUR IMPLEMENTATION
	// initialise counters
	size_t digit_counts[10] = {0};
	size_t correct_counts[10] = {0};
	size_t correct_total = 0;
	size_t total = data.get_data_size(TEST_LABEL);
	
	// iterate through all test data
	for (size_t i = 0; i < total; i++) {
		vector<float> input = data.get_a_normalized_image(TEST_IMAGE, i);
		vector<float> output = nn(input);
		
		int prediction_digit = 0;
		for (int digit = 0; digit < 10; digit++) {
			// find digit with the highest probability
			if (output[digit] > output[prediction_digit]) {
				prediction_digit = digit;
			}
		}
		
		// add counters
		int actual_digit = data.get_a_label(TEST_LABEL, i);
		if (prediction_digit == actual_digit) {
			correct_counts[prediction_digit]++;
			correct_total++;
		}
		digit_counts[actual_digit]++;
	}
	
	// print statistics
	printf("Overall accuracy: %.2f%%\n", (100.0 * correct_total / total));
	for (int digit = 0; digit < 10; digit++) {
		printf("Accuracy for digit %i: %.2f%%\n", digit, (100.0 * correct_counts[digit] / digit_counts[digit]));
	}
	// END OF YOUR IMPLEMENTATION
}
