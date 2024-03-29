#include "NeuralNetwork.hpp"


NeuralNetwork::NeuralNetwork(unsigned int inputSize, unsigned int outputSize, 
							 unsigned int hiddenSize, unsigned int hiddenNumberLayer)
	: m_inputSize(inputSize), m_outputSize(outputSize), m_hiddenSize(hiddenSize), 
	  m_hiddenNumberLayer(hiddenNumberLayer)
{
	m_matrix.emplace_back(m_inputSize, m_hiddenSize);
	for(unsigned int i = 0; i < m_hiddenNumberLayer - 1; ++i)
		m_matrix.emplace_back(m_hiddenSize, m_hiddenSize);
	m_matrix.emplace_back(m_hiddenSize, m_outputSize);

	for(auto& i : m_matrix)
		i.initRandom();
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& n)
	: m_inputSize(n.m_inputSize), m_outputSize(n.m_outputSize), m_hiddenSize(n.m_hiddenSize), 
	  m_hiddenNumberLayer(n.m_hiddenNumberLayer)
{
	m_matrix = n.m_matrix;
}

NeuralNetwork::~NeuralNetwork()
{

}

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& n)
{
	m_inputSize = n.m_inputSize;
	m_outputSize = n.m_outputSize;
	m_hiddenSize = n.m_hiddenSize;
	m_hiddenNumberLayer = n.m_hiddenNumberLayer;

	m_matrix = n.m_matrix;

	return *this;
}

/*-----------------------------------------------------------------------------------------*/

const Matrix NeuralNetwork::forward(const Matrix& mat)
{
		//mat.print(); printf("\n");
		//m_matrix[0].print(); printf("\n");

	Matrix hidden = dot(mat, m_matrix[0]);
	ReLu(hidden);

		//hidden.print(); printf("\n");

	for (unsigned int i = 1; i < m_hiddenNumberLayer; ++i)
	{
		dot(hidden, hidden, m_matrix[i]);
		ReLu(hidden);

			//m_matrix[i].print(); printf("\n");
			//hidden.print(); printf("\n");
	}

		//m_matrix.back().print(); printf("\n");
	
	Matrix out = dot(hidden, m_matrix.back());
	ReLu(out);
		
		//out.print();

	return out;
}

void NeuralNetwork::mutate()
{
	for(auto& i : m_matrix)
		i.mutate(MATATION_RATE);
}


void NeuralNetwork::print()
{
	for(auto&i : m_matrix)
	{
		i.print();
		printf("\n");
	}
}


void NeuralNetwork::sigmoid(Matrix& x)
{
	for(int i = 0; i < x.getSize().y; i++)
		for(int j = 0; j < x.getSize().x; j++)
			x.set(i, j, 1 / (1 + exp(-x.get(i, j))));
}

void NeuralNetwork::ReLu(Matrix& x)
{
	for(int i = 0; i < x.getSize().y; i++)
		for(int j = 0; j < x.getSize().x; j++)
			x.set(i, j, std::max(0.f, x.get(i, j)));
}