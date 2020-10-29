#include "Matrix.hpp"


Matrix::Matrix(const unsigned int size_i, const unsigned int size_j)
	: m_size(size_j, size_i)
{
	m_tabl = new float[m_size.x * m_size.y];

	for(int i = 0; i < m_size.x * m_size.y; i++)
		m_tabl[i] = 0.f;
}

Matrix::Matrix(const Matrix& m)
	: m_size(m.m_size)
{
	m_tabl = new float[m_size.x * m_size.y];
	for(int i = 0; i < m_size.x * m_size.y; i++)
		m_tabl[i] = m.m_tabl[i];
}

Matrix::~Matrix()
{
	delete[] m_tabl;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	throw std::out_of_range("hum copy matrix");
	return *this;
}

/*-----------------------------------------------------------------------------------------*/

const sf::Vector2i& Matrix::getSize() const
{
	return m_size;
}

const float& Matrix::get(const int i, const int j) const
{
	if(i >= m_size.y || j >= m_size.x || i < 0 || j < 0)
		throw std::out_of_range("matrix index out of range");

	return m_tabl[m_size.y * j + i];
}

void Matrix::set(const int i, const int j, const float val)
{
	if(i >= m_size.y || j >= m_size.x || i < 0 || j < 0)
		throw std::out_of_range("mmatrix index out of range");

	m_tabl[m_size.y * j + i] = val;
}

/*-----------------------------------------------------------------------------------------*/

void Matrix::initRandom()
{
	for(int i = 0; i < m_size.x * m_size.y; i++)
		m_tabl[i] = -1 + (float)rand() / (float)(RAND_MAX / 2);
}

void Matrix::mutate(const float rate)
{
	for(int i = 0; i < m_size.x * m_size.y; i++)
		if((float)rand() / (float)RAND_MAX < rate)
			m_tabl[i] = -1 + (float)rand() / (float)(RAND_MAX / 2);
}

void Matrix::print() const
{
	for(int i = 0; i < m_size.y; i++)
	{
		printf("| ");
		for(int j = 0; j < m_size.x; j++)
		{
			printf("%.5f ", m_tabl[m_size.y * j + i]);
		}
		printf("|\n");
	}
}

/*-----------------------------------------------------------------------------------------*/

void dot(Matrix& res, const Matrix& m1, const Matrix& m2)
{
	if(m1.m_size.x != m2.m_size.y)
		throw std::out_of_range("matrix dot incompatible size");

	if(res.m_size.x != m2.m_size.x && res.m_size.y != m1.m_size.y)
		throw std::out_of_range("matrix dot result objet incompatible size");
	
	for(int i = 0; i < m1.m_size.y; ++i) // 2
	{
		for (int j = 0; j < m2.m_size.x; ++j) // 2
		{
			float buffer = 0.f; 
			for (int k = 0; k < m1.m_size.x; ++k)
			{
				//printf("%f %f\n", m1.get(i, k), m2.get(k, j));
				buffer += m1.get(i, k) * m2.get(k, j);
			}
			//printf("\n");
			res.set(i, j, buffer);
		}
	}
}

Matrix dot(const Matrix& m1, const Matrix& m2)
{
	Matrix res(m1.m_size.y, m2.m_size.x);
	dot(res, m1, m2);
	return res;
}