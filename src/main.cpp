//============================================================================
// Name        : Multilayer.cpp
// Author      : Bruno Alexandre Krinski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Dataset.hpp"

int main() {
	nn::Dataset data("datasets/dataset0.txt");
	data.write();
	return 0;
}
