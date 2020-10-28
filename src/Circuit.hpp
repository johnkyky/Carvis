#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "Fonction.hpp"
#include "Wall.hpp"


class Circuit : public sf::Drawable
{
public:
	Circuit();
	Circuit(const char* path);
	Circuit(const Circuit& c);
	~Circuit();

	Circuit& operator=(const Circuit& c);

	const sf::Vector2f& getSpawnPoint() const;
	const sf::Vector2f& getSpawnAngle() const;

	void loadFromFile(const char* path);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Wall> m_walls;
private:
	friend class Ray;
	sf::Vector2f m_spawnPoint;
	sf::Vector2f m_spawnAngle;
};