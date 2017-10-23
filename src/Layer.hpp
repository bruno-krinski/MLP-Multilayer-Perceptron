/*
 * Layer.hpp
 *
 *  Author: Bruno Alexandre Krinski
 *  Created on: 22 de out de 2017      
 */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

namespace nn {

class Layer {

private:
	unsigned int inputSize;
	unsigned int numNeurons;
	std::vector<float> input;
	std::vector<float> error;
	std::vector<float> output;
	std::vector<float> weights;
	std::vector<float> sigOutput;

	float sigmoid(float input);
	float dSigmoid(float input);
	std::vector<float> matrixTranspose(std::vector<float>& matrix);
	std::vector<float> vectorMatrixMultiplication(const std::vector<float>& v, const std::vector<float>& m, unsigned int nRows, unsigned int nCols);

public:
	Layer(unsigned int nNeurons, unsigned int iSize, float iWeight);
	virtual ~Layer();

	void write();
	void updateWeights();
	unsigned int getInputSize();
	unsigned int getNumNeurons();
	std::vector<float> getOutput();
	void genOutput(std::vector<float> in);
	void calculateError(std::vector<float> predictedLabel, std::vector<std::string> labels, std::string rightLabel);
};

} /* namespace nn */

#endif /* LAYER_HPP_ */
