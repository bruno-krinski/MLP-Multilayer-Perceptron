//============================================================================
// Name        : Multilayer.cpp
// Author      : Bruno Alexandre Krinski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "MLP.hpp"
#include "Dataset.hpp"

int main() {
	nn::Dataset data("datasets/dataset0.txt");
	data.write();

	nn::MLP mlp({5,10,5}, 2);
	mlp.train(data);

	return 0;
}
