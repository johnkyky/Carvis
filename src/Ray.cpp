#include "Ray.hpp"

Ray::Ray() : m_lenght(0.f)
{

}

Ray::Ray(const sf::Vector2f& position, const sf::Vector2f& rotation)
	: m_lenght(0.f)
{
	m_position = m_line[0].position = m_line[1].position = position;
	normalized(m_rotation, rotation);

	m_line[0].color = m_line[1].color = sf::Color(sf::Color::Red);
}

Ray::Ray(const Ray& r)
	: m_position(r.m_position), m_rotation(r.m_rotation), m_lenght(r.m_lenght)
{
	m_line[0] = r.m_line[0];
	m_line[1] = r.m_line[1];
}

Ray::~Ray()
{

}

/*-----------------------------------------------------------------------------------------*/

const Ray& Ray::operator=(const Ray& ray)
{
	m_position = ray.m_position;
	m_line[0] = ray.m_line[0];
	m_line[1] = ray.m_line[1];
	m_rotation = ray.m_rotation;
	return *this;
}

const Ray& Ray::operator=(const Ray&& ray)
{
	m_position = std::move(ray.m_position);
	m_line[0] = std::move(ray.m_line[0]);
	m_line[1] = std::move(ray.m_line[1]);
	m_rotation = std::move(ray.m_rotation);
	return *this;
}

/*-----------------------------------------------------------------------------------------*/

inline void Ray::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Ray::setPosition(const sf::Vector2f& position)
{
	m_position = position;
}

inline const sf::Vector2f& Ray::getPosition() const
{
	return m_position;
}

inline void Ray::setRotation(float x, float y)
{
	normalized(m_rotation, sf::Vector2f(x, y));
}

void Ray::setRotation(const sf::Vector2f& angle)
{
	normalized(m_rotation, angle);
}

inline void Ray::setRotation(const float angle)
{
	rotate(m_rotation, m_rotation, angle);
}

inline const sf::Vector2f& Ray::getRotation() const
{
	return m_rotation;
}

const float& Ray::getLenght() const
{
	return m_lenght;
}

/*-----------------------------------------------------------------------------------------*/

void Ray::update(const Circuit& circuit)
{
	m_line[1].position = m_position;

	m_lenght = std::numeric_limits<float>::max();
	for(auto&i : circuit.m_walls)
	{
		sf::Vector2f contact;
		const float dis = intersectionWall(contact, i);
		if(dis != -1 && dis < m_lenght)
		{
			m_lenght = dis;
			m_line[1].position = contact;
		}
	}

	m_line[0].position = m_position;
}

void Ray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_line, 2, sf::Lines);
}

/*-----------------------------------------------------------------------------------------*/

inline const float Ray::intersectionWall(sf::Vector2f& contact, const Wall& wall)
{
	const float x1(wall.m_position[0].x);
	const float y1(wall.m_position[0].y);
	const float x2(wall.m_position[1].x);
	const float y2(wall.m_position[1].y);

	const float x3(m_position.x);
	const float y3(m_position.y);
	const float x4(m_position.x + m_rotation.x);
	const float y4(m_position.y + m_rotation.y);

	const float denom = (x1 - x2) * (y3 - y4) - (y1 -y2) * (x3 - x4);
	if(denom == 0)
		return -1.f;

	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
	const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;

	if(t > 0 &&  t < 1 && u > 0)
	{
		contact.x = (x1 + t * (x2 - x1));
		contact.y = (y1 + t * (y2 - y1));
		return sqrt(pow(contact.x - m_position.x, 2) + pow(contact.y - m_position.y, 2));
	}
	return -1;
}