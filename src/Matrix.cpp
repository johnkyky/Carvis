#include "Matrix.hpp"


Matrix::Matrix(const unsigned int size_i, const unsigned int size_j)
	: m(size_i), n(size_j), m_size(size_j, size_i)
{
	m_tabl = new float[m * n];

	for(int i = 0; i < m * n; i++)
		m_tabl[i] = 0.f;
}

Matrix::Matrix(const Matrix& mat)
	: m(mat.m), n(mat.n), m_size(mat.m_size)
{
	m_tabl = new float[m * n];
	for(int i = 0; i < m * n; i++)
		m_tabl[i] = mat.m_tabl[i];
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
		throw std::out_of_range("matrix index out of range");

	m_tabl[m_size.y * j + i] = val;
}

float* Matrix::data() const
{
	return m_tabl;
}

/*-----------------------------------------------------------------------------------------*/

void Matrix::initRandom()
{
	for(int i = 0; i < m * n; i++)
		m_tabl[i] = -1 + (float)rand() / (float)(RAND_MAX / 2);
}

void Matrix::mutate(const float rate)
{
	std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{0, 1};

	for(int i = 0; i < m * n; i++)
		if((float)rand() / (float)RAND_MAX < rate)
		{
			m_tabl[i] += d(gen) * 0.5;

			if(m_tabl[i] < -1)
				m_tabl[i] = -1;
			else if(m_tabl[i] > 1)
				m_tabl[i] = 1;
			//m_tabl[i] = -1 + (float)rand() / (float)(RAND_MAX / 2);
		}
}

void Matrix::print() const
{
	for(int i = 0; i < m; i++)
	{
		printf("| ");
		for(int j = 0; j < n; j++)
		{
			printf("%.5f ", m_tabl[i * n + j]);
		}
		printf("|\n");
	}
}

/*-----------------------------------------------------------------------------------------*/

void Matrix::dot(Matrix& res, const Matrix& m1, const Matrix& m2)
{
	if(m1.n != m2.m)
		throw std::out_of_range("matrix dot incompatible size");

	if(res.m != m1.m && res.n != m2.n)
		throw std::out_of_range("matrix dot result objet incompatible size");

	for(int i = 0; i < res.m * res.n; i++)
		res.m_tabl[i] = 0.0;
	
	for(int i = 0; i < m1.m; ++i)
	{
		for (int k = 0; k < m1.n; ++k)
		{
			for(int j = 0; j < m2.n; ++j)
			{
				res.m_tabl[i * res.n + j] += m1.m_tabl[i * res.n + k] * m2.m_tabl[k * res.n + j];
			}
		}
	}
}

Matrix Matrix::dot(const Matrix& m1, const Matrix& m2)
{
	Matrix res(m1.m, m2.n);
	dot(res, m1, m2);
	return res;
}