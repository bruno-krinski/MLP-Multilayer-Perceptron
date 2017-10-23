/*
 * MLP.cpp
 *
 *  Author: Bruno Alexandre Krinski
 *  Created on: 22 de out de 2017      
 */

#include "MLP.hpp"

namespace nn {

MLP::MLP(std::vector<unsigned int> nNeuronsEachLayer, unsigned int nHiddenLayers,
		unsigned int mEpochs, float mError, float iWeights,bool v , bool p) {
	numHiddenLayers = nHiddenLayers;
	maxEpochs = mEpochs;
	maxError = mError;
	initialWeights = iWeights;
	verbose = v;
	parallel = p;
	numNeuronsEachLayer = nNeuronsEachLayer;
}

MLP::~MLP() {
	// TODO Auto-generated destructor stub
}

void MLP::train(Dataset data){
	Layer inputLayer(numNeuronsEachLayer[0],data.getNumFeatures(),initialWeights);
	layers.push_back(inputLayer);
	for(unsigned int i = 0; i < numHiddenLayers; ++i){
		Layer hiddenLayer(numNeuronsEachLayer[i+1],layers[i].getNumNeurons(),initialWeights);
		layers.push_back(hiddenLayer);
	}
	Layer outputLayer(data.getNumClasses(), layers[layers.size()-1].getNumNeurons(), initialWeights);
	layers.push_back(outputLayer);
	//snapshot();

	for(unsigned int i = 0; i < 1; ++i){
		layers[0].genOutput(data.getFeatures(1));
		layers[0].write();

		for(unsigned int j = 1; j < layers.size(); ++j){
			layers[j].genOutput(layers[j-1].getOutput());
			layers[j].write();
		}
		layers[layers.size()-1].calculateError(layers[layers.size()-1].getOutput(), data.getClasses(), data.getLabel(i));
		//layers[layers.size()-1].updateWeights();
	}
}

void MLP::snapshot(){
	for(unsigned int i = 0; i < layers.size(); ++i){
		std::cout << "==================================================" << std::endl;
		layers[i].write();
		std::cout << "==================================================" << std::endl;
	}
}
}
