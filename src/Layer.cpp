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
	sigOutput.resize(numNeurons,0);
	weights.resize(numNeurons*inputSize,iWeight);
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

unsigned int Layer::getNumNeurons(){
	return numNeurons;
}

std::vector<float> Layer::getError(){
	return error;
}

std::vector<float> Layer::getWeights(){
	return weights;
}

unsigned int Layer::getInputSize(){
	return inputSize;
}

std::vector<float> Layer::getOutput(){
	return sigOutput;
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
	std::cout << "sigOutput:" << std::endl;
	for(unsigned int i = 0; i < numNeurons; ++i){
		std::cout << sigOutput[i] << " " << std::endl;
	}

	std::cout << "Error:" << std::endl;
	for(unsigned int i = 0; i < numNeurons; ++i){
		std::cout << error[i] << " " << std::endl;
	}

}

void Layer::genOutput(std::vector<float> in){

	input = in;
	output = vectorMatrixMultiplication(input, weights, numNeurons, inputSize);

	for(unsigned int i = 0; i < numNeurons; ++i){
		sigOutput[i] = sigmoid(output[i]);
	}
}

float Layer::sigmoid(float input){
	return 1.0 / (1.0 + std::exp(-input));
}

float Layer::dSigmoid(float input){
	return std::exp(-input)/((1+std::exp(-input))*(1+std::exp(-input)));
}

void Layer::calculateOutputError(std::vector<float> predictedLabel, std::vector<std::string> labels, std::string rightLabel){

	std::vector<float> rLabels(predictedLabel.size(),0);

	int pos = std::find(labels.begin(), labels.end(), rightLabel) - labels.begin();

	rLabels[pos] = 1;

	for(unsigned int i = 0; i < error.size(); ++i){
		error[i] = rLabels[i] - predictedLabel[i];
		//std::cout << rLabels[i] << std::endl;
		//std::cout << predictedLabel[i] << std::endl;
		//std::cout << error[i] << std::endl;
	}
}

void Layer::calculateError(std::vector<float> nextLayerError, std::vector<float> nextLayerWeights, unsigned int nNeurons, unsigned int iSize){
	std::cout << "entrou" << std::endl;
	std::vector<float> weightsT = matrixTranspose(nextLayerWeights);
	std::cout << "calculou" << std::endl;
	error = vectorMatrixMultiplication(nextLayerError, weightsT, iSize, nNeurons);
	std::cout << "saiu" << std::endl;
}

void Layer::updateWeights(){
	for(unsigned int i = 0; i < numNeurons; ++i){
		for(unsigned int j = 0; j < inputSize; ++j){
			unsigned int index = i * inputSize + j;
			weights[index] += error[i] * dSigmoid(output[i]) * input[j];
			//std::cout << error[i]  << std::endl;
		}
	}
}

std::vector<float> Layer::vectorMatrixMultiplication(const std::vector<float>& v, const std::vector<float>& m, unsigned int nRows, unsigned int nCols){
	std::cout << "entrou0" << std::endl;
	std::vector<float> result;
	std::cout << "entrou1" << std::endl;
	result.resize(nRows,0); //<-----------------------
	std::cout << "entrou2" << std::endl;
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
