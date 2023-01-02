#ifndef nn_H
#define nn_H
#include <array>
#include <fstream>
#include <vector>

using namespace std;

struct Layer {
	virtual ~Layer() = default;

	virtual vector<float> operator() (vector<float>&) = 0;
	virtual vector<float> backprop(vector<float>&, vector<float>&, const vector<float>&) = 0;
	virtual void apply() {}

	virtual void save(ofstream&) = 0;

	static Layer* fromFile(int idx, ifstream& fin);
};


struct LayerLinear : Layer {
	size_t I, O;
	float *W, *A;

	LayerLinear(size_t I, size_t O);
	~LayerLinear() override;

	LayerLinear(ifstream&);
	virtual void save(ofstream&) override;

	virtual vector<float> operator() (vector<float>&) override;
	virtual vector<float> backprop(vector<float>&, vector<float>&, const vector<float>&) override;
	virtual void apply() override;
};

struct LayerSigmoid : Layer {
	virtual void save(ofstream&) override;

	virtual vector<float> operator() (vector<float>& m) override;
	virtual vector<float> backprop(vector<float>& m, vector<float>& c, const vector<float>& p) override;
};


struct NN {
	vector<Layer*> layers;

	NN(initializer_list<Layer*> il);
	~NN();

	NN(string path);
	void save(string);

	vector<float> operator() (vector<float> I);
	void backprop(vector<float> I, const vector<float>& O);
	void apply();
};

#endif

