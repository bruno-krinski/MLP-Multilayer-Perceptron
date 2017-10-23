/*
 * Layer.cpp
 *
 *  Author: Bruno Alexandre Krinski
 *  Created on: 22 de out de 2017      
 */

#include "Layer.hpp"

namespace nn {

Layer::Layer(unsigned int nNeurons, unsigned int iSize, float iWeight) {
	inputSize = iSize;
	numNeurons = nNeurons;
	input.resize(inputSize,0);
	error.resize(numNeurons,0);
	output.resize(numNeurons,0);
	sigOutput.resize(inputSize,0);
	weights.resize(numNeurons*inputSize,iWeight);
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

unsigned int Layer::getNumNeurons(){
	return numNeurons;
}

unsigned int Layer::getInputSize(){
	return inputSize;
}

std::vector<float> Layer::getOutput(){
	return output;
}

void Layer::write(){
	std::cout << "Weights:" << std::endl;
	for(unsigned int i = 0; i < numNeurons; ++i){
		for(unsigned int j = 0; j < inputSize; ++j){
			unsigned int index = i * inputSize + j;
			std::cout << weights[index] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Output:" << std::endl;
	for(unsigned int i = 0; i < numNeurons; ++i){
		std::cout << output[i] << " " << std::endl;
	}
}

void Layer::genOutput(std::vector<float> in){

	input = in;
	for(int i = 0; i < inputSize;++i){
		std::cout << input[i] << " ";
	}
	std::cout<<std::endl;
	output = vectorMatrixMultiplication(input, weights, numNeurons, inputSize);

	for(unsigned int i = 0; i < inputSize; ++i){
		sigOutput[i] = sigmoid(output[i]);
	}
}

float Layer::sigmoid(float input){
	return 1.0 / (1.0 + std::exp(-input));
}

void Layer::calculateError(std::vector<float> predictedLabel, std::vector<std::string> labels, std::string rightLabel){

	std::vector<float> rLabels(predictedLabel.size(),0);

	int pos = std::find(labels.begin(), labels.end(), rightLabel) - labels.begin();

	rLabels[pos] = 1;

	for(unsigned int i = 0; i < error.size(); ++i){
		error[i] = rLabels[i] - predictedLabel[i];
	}
}

void Layer::updateWeights(){
	std::vector<float> weightsT = matrixTranspose(weights);

	/*for(unsigned int i = 0; i < error.size(); ++i){
		float error = 0;
		for(unsigned int j = 0; j < numNeurons; ++j){
			unsigned int index = i * numNeurons + j;
			error += weights[index]*error[i] ;
		}
	}*/
}

std::vector<float> Layer::vectorMatrixMultiplication(const std::vector<float>& v, const std::vector<float>& m, unsigned int nRows, unsigned int nCols){
	std::vector<float> result(nRows,0);
	std::cout << v.size() << std::endl;
	for(unsigned int i = 0; i < nRows; ++i){
		for(unsigned int j = 0; j < nCols; ++j){
			result[i] += v[j] * m[i*nCols+j];
		}
	}
	return result;
}


std::vector<float> Layer::matrixTranspose(std::vector<float>& matrix){
	std::vector<float> matrixT(matrix.size());

	for(unsigned int i = 0; i < numNeurons; ++i){
		for(unsigned int j = 0; j < inputSize; ++j){
			matrixT[j*numNeurons+i] = matrix[i*inputSize+j];
		}
	}
	return matrixT;
}

}
