/*
 * Dataset.hpp
 *
 *  Author: Bruno Alexandre Krinski
 *  Created on: 22 de out de 2017      
 */

#ifndef DATASET_HPP_
#define DATASET_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace nn {

class Dataset {

private:
	unsigned int numVectors; // Number of feature vectors.
	unsigned int numFeatures; // Number of features in each feature vector.

	/* A matrix to store all features feature vectors.
	 * To access each feature, the index must be calculated as the follow:
	 * feature =  i * numFeatures + j;
	 * Where 'i' is the feature vector index and 'j' is the feature index.
	 */
	std::vector<float> featureVectors;
	std::vector<std::string> labels; // A vector of labels.
	std::vector<std::string> splitString(std::string str); // A function to split a string

public:
	Dataset(std::string filePath);
	virtual ~Dataset();
	std::vector<float> getFeatures();
	std::vector<std::string> getLabels();
	void write();
};

} /* namespace nn */

#endif /* DATASET_HPP_ */
