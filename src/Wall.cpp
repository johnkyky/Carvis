#include "Wall.hpp"


Wall::Wall()
{

}

Wall::Wall(const float x1, const float y1, const float x2, const float y2)
{
	m_position[0] = m_vertices[0].position = sf::Vector2f(x1, y1);
	m_position[1] = m_vertices[1].position = sf::Vector2f(x2, y2);

	m_vertices[0].color = m_vertices[1].color = sf::Color::Black;
}

Wall::Wall(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
	m_position[0] = m_vertices[0].position = pos1;
	m_position[1] = m_vertices[1].position = pos2;

	m_vertices[0].color = m_vertices[1].color = sf::Color::Black;
}

Wall::Wall(const Wall& w)
{
	m_position[0].x = w.m_position[0].x;
	m_position[0].y = w.m_position[0].y;
	m_position[1].x = w.m_position[1].x;
	m_position[1].y = w.m_position[1].y;

	m_vertices[0] = w.m_vertices[0];
	m_vertices[1] = w.m_vertices[1];
}

Wall::~Wall()
{

}

Wall& Wall::operator=(const Wall& w)
{
	m_position[0].x = w.m_position[0].x;
	m_position[0].y = w.m_position[0].y;

	m_vertices[0] = w.m_vertices[0];
	m_vertices[1] = w.m_vertices[1];

	return *this;
}

/*-----------------------------------------------------------------------------------------*/

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vertices, 2, sf::Lines);
}