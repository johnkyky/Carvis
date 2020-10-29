#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <array>

#include "Circuit.hpp"
#include "Ray.hpp"
#include "Fonction.hpp"
#include "NeuralNetwork.hpp"
#include "Matrix.hpp"


#define MAX_SPEED 600.f
#define ACCELERATION 300.f
#define DECELERATION 2.f
#define	TURN 500.f
#define NBR_RAYS 5


class Car : public sf::Drawable
{
public:
	Car(const Circuit& circuit, const sf::Texture& texture);
	Car(const Car& c);
	~Car();

	Car& operator=(const Car& c);

	void setPosition(const sf::Vector2f &position);
	void setPosition(const float x, const float y);

	void setRotation(float x, float y);
	void setRotation(const sf::Vector2f& angle);
	void setRotation(const float angle);
	const sf::Vector2f& getRotation() const;

	sf::FloatRect getBox()
	{
		return m_sprite.getGlobalBounds();
	}

	void showRay();
	void mutate();

	void update(const float fps);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void input(const float fps);
	void think(const float fps);
	///Methode pour les neurones
	void accelerate(const float fps);
	void decelerate(const float fps);
	void left(const float fps);
	void right(const float fps);

private:
	const Circuit& m_circuit;

	sf::Vector2f m_vel;

	const sf::Texture& m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_rotation;

	Ray m_rays[NBR_RAYS];

	bool m_showLine;
	bool m_crashed;

	NeuralNetwork m_neuralN;
};