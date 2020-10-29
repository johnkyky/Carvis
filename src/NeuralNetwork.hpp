#pragma once

#include <iostream>
#include <cmath>

#include "Matrix.hpp"


#define MATATION_RATE 0.1


class NeuralNetwork
{
public:
	NeuralNetwork(unsigned int inputSize, unsigned int outputSize, 
				  unsigned int hiddenSize, unsigned int hiddenNumberLayer);
	NeuralNetwork(const NeuralNetwork& n);
	~NeuralNetwork();
	
	NeuralNetwork& operator=(const NeuralNetwork& n);

	const Matrix forward(const Matrix& mat);
	void mutate();

	void print();

private:
	void sigmoid(Matrix& x);
	void ReLu(Matrix& x);

private:
	unsigned int m_inputSize;
	unsigned int m_outputSize;
	unsigned int m_hiddenSize;
	unsigned int m_hiddenNumberLayer;

	std::vector<Matrix> m_matrix;
};