#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>

class Matrix
{
public:
	Matrix(const unsigned int size_i, const unsigned int size_j);
	Matrix(const Matrix& m);
	~Matrix();

	Matrix& operator=(const Matrix& m);

	const sf::Vector2i& getSize() const;
	const float& get(const int i, const int j) const;
	void set(const int i, const int j, const float val);

	void initRandom();

	void print() const;
	
	void mutate(const float rate);

	friend void dot(Matrix& res, const Matrix& m1, const Matrix& m2);
	friend Matrix dot(const Matrix& m1, const Matrix& m2);
	
private:
	const sf::Vector2i m_size;
	float* m_tabl;
};