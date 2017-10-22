/*
 * Dataset.cpp
 *
 *  Author: Bruno Alexandre Krinski
 *  Created on: 22 de out de 2017      
 */

#include "Dataset.hpp"

namespace nn {

Dataset::Dataset(std::string filePath) {
	/* Input: A string containing the path to the file with dataset.
	 * This will read the dataset in file.
	 */
	std::ifstream data_file(filePath);
	std::string line;

	if(data_file.is_open()){
		/* The first line of file must contain the number of vectors
		 * and the number of features in each vector.
		 */
		std::getline(data_file,line);
		std::vector<std::string> first_line = splitString(line);
		numVectors = std::stoi(first_line[0]);
		numFeatures = std::stoi(first_line[1]);
		labels.resize(numFeatures);
		featureVectors.resize(numFeatures*numVectors);

		for(unsigned int i = 0; i < numVectors; ++i){
			std::getline(data_file,line);
			std::vector<std::string> splited_line = splitString(line);
			labels[i] = splited_line[0];
			for(unsigned int j = 1; j < numFeatures; ++j){
				int index = i * numFeatures + j;
				featureVectors[index] = std::stof(splited_line[j]);
			}
		}
	} else {
		std::cout << "Could not read dataset file!!!" << std::endl;
		exit(0);
	}
}

Dataset::~Dataset() {
	// TODO Auto-generated destructor stub
}

std::vector<std::string> Dataset::splitString(std::string str){
	std::vector<std::string> splitedString;
	std::string buffer;
	std::stringstream ss(str);
	while(ss >> buffer){
		splitedString.push_back(buffer);
	}
	return splitedString;
}

void Dataset::write(){
	std::cout << "Number of vectors: " << numVectors << std::endl;
	std::cout << "Number of features: " << numFeatures << std::endl;

	for(unsigned int i = 0; i < numVectors; ++i){
		std::string str = labels[i] + "[";
		for(unsigned int j = 0; j < (numFeatures-1); ++j){
			int index = i * numFeatures + j;
			str += std::to_string(featureVectors[index]) + ",";
		}
		int index = i * numFeatures + (numFeatures-1);
		str += std::to_string(featureVectors[index]) + "]";
		std::cout << str << std::endl;
	}
}

} /* namespace nn */
