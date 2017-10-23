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
	unsigned int numClasses;
	unsigned int numVectors;
	unsigned int numFeatures;
	std::vector<std::string> labels;
	std::vector<std::string> classes;
	std::vector<float> featureVectors;

	std::vector<std::string> splitString(std::string str);

public:
	Dataset(std::string filePath);
	virtual ~Dataset();

	void write();
	unsigned int getNumClasses();
	unsigned int getNumVectors();
	unsigned int getNumFeatures();
	std::vector<std::string> getLabels();
	std::vector<std::string> getClasses();
	std::string getLabel(unsigned int index);
	std::vector<float> getFeatures(unsigned int index);
};
}

#endif
