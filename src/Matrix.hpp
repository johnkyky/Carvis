#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>

class Matrix
{
public:
	Matrix(const unsigned int size_m, const unsigned int size_n);
	Matrix(const Matrix& m);
	~Matrix();

	Matrix& operator=(const Matrix& m);

	float* data() const;

	void initRandom();

	void print() const;
	
	void mutate(const float rate);

	static void dot(Matrix& res, const Matrix& m1, const Matrix& m2);
	static Matrix dot(const Matrix& m1, const Matrix& m2);

	const int m, n;
	
private:
	float* m_tabl;
};