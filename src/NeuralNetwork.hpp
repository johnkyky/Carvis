#pragma once

#include <iostream>
#include <cmath>

#include "Matrix.hpp"


class NeuralNetwork
{
public:
	NeuralNetwork(const unsigned int inputSize, const unsigned int outputSize, 
				  const unsigned int hiddenSize, const unsigned int hiddenNumberLayer);
	NeuralNetwork(const NeuralNetwork& n);
	~NeuralNetwork();
	
	NeuralNetwork& operator=(const NeuralNetwork& n) = delete;

	const Matrix forward(const Matrix& mat);

	void print()
	{
		for(auto&i : m_matrix)
		{
			i.print();
			printf("\n");
		}
	}

private:
	void sigmoid(Matrix& x);
	void ReLu(Matrix& x);

private:
	const unsigned int m_inputSize;
	const unsigned int m_outputSize;
	const unsigned int m_hiddenSize;
	const unsigned int m_hiddenNumberLayer;

	std::vector<Matrix> m_matrix;
};