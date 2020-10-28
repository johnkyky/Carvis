#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <limits>

#include "Fonction.hpp"
#include "Circuit.hpp"


class Ray : public sf::Drawable
{
public:
	Ray();
	Ray(const sf::Vector2f& position, const sf::Vector2f& rotation);
	Ray(const Ray& r);
	~Ray();

	const Ray& operator=(const Ray& ray);
	const Ray& operator=(const Ray&& ray);

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f& getPosition() const;

	void setRotation(float x, float y);
	void setRotation(const sf::Vector2f& angle);
	void setRotation(const float angle);
	const sf::Vector2f& getRotation() const;

	const float& getLenght() const;
		
	void update(const Circuit& circuit);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	const float intersectionWall(sf::Vector2f& contact, const Wall& wall);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_rotation;
	sf::Vertex m_line[2];
	float m_lenght;
};