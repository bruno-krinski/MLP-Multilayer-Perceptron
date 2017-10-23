/*
 * MLP.hpp
 *
 *  Author: Bruno Alexandre Krinski
 *  Created on: 22 de out de 2017      
 */

#ifndef MLP_HPP_
#define MLP_HPP_

#include <vector>

#include "Layer.hpp"
#include "Dataset.hpp"

namespace nn {

class MLP {

private:
	bool verbose;
	bool parallel;
	unsigned int numHiddenLayers;
	unsigned int maxEpochs;
	float maxError;
	float initialWeights;
	std::vector<Layer> layers;
	std::vector<unsigned int> numNeuronsEachLayer;

public:
	MLP(std::vector<unsigned int> nNeuronsEachLayer, unsigned int nHiddenLayers,
		unsigned int mEpochs = 200 , float mError = 0.1, float iWeights = 0.5,bool v = false, bool p = false);
	virtual ~MLP();
	void train(Dataset data);
	void snapshot();
};
}

#endif
