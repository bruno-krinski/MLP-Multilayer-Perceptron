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

	for(unsigned int i = 0; i < data.getNumVectors(); ++i){
		layers[0].genOutput(data.getFeatures(i));
		//layers[0].write();

		for(unsigned int j = 1; j < layers.size(); ++j){
			layers[j].genOutput(layers[j-1].getOutput());
			//layers[j].write();
		}
		snapshot();
		std::cout << "============================================================================================" << std::endl;
		layers[layers.size()-1].calculateOutputError(layers[layers.size()-1].getOutput(), data.getClasses(), data.getLabel(i));

		std::vector<float> e = layers[layers.size()-1].getError();//<========
		/*bool out = true;
		for(unsigned int k = 0; k < e.size(); ++k){
			std::cout << "e" << e[k] << std::endl;
			if((e[k] > maxError) || (e[k] < (-1)*maxError)){
				std::cout << "entrou" << std::endl;
				out = false;
			}
		}
		std::cout << out << std::endl;
		/*if(out == true){
			std::cout << "entrou2" << std::endl;
			//break;
		}*/

		layers[layers.size()-1].updateWeights();

		for(int j = layers.size()-2; j >= 0; j--){
			std::cout<< "Layer: " << j << std::endl;
			layers[j].calculateError(layers[j+1].getError(),layers[j+1].getWeights(),layers[j+1].getNumNeurons(),layers[j+1].getInputSize());
			std::cout<<"aqui0\n";
			layers[j].updateWeights();
			std::cout<<"aqui\n";
		}
		std::cout << "entro aquoi" << std::endl;
		snapshot();
	}
}

void MLP::snapshot(){
	for(unsigned int i = 0; i < layers.size(); ++i){
		std::cout << "==================================================" << std::endl;
		std::cout << "Layer: " << i << std::endl;
		layers[i].write();
		std::cout << "==================================================" << std::endl;
	}
}
}
