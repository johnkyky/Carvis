#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


#define SIZE_ARRAY 2


class Wall : public sf::Drawable
{
public:
	Wall();
	Wall(const float x1, const float y1, const float x2, const float y2);
	Wall(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	Wall(const Wall& w);
	~Wall();

	Wall& operator=(const Wall& w);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	friend class Ray;

	sf::Vector2f m_position[SIZE_ARRAY];
	sf::Vertex m_vertices[SIZE_ARRAY];
};