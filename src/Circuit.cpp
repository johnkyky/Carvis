#include "Circuit.hpp"

Circuit::Circuit()
{

}

Circuit::Circuit(const char* path)
{
	loadFromFile(path);
}

Circuit::Circuit(const Circuit& c)
	: m_walls(c.m_walls), m_spawnPoint(c.m_spawnPoint), m_spawnAngle(c.m_spawnAngle)
{

}

Circuit::~Circuit()
{

}

Circuit& Circuit::operator=(const Circuit& c)
{
	m_walls = c.m_walls;
	m_spawnPoint.x = c.m_spawnPoint.x;
	m_spawnPoint.y = c.m_spawnPoint.y;
	m_spawnAngle.x = c.m_spawnAngle.x;
	m_spawnAngle.y = c.m_spawnAngle.y;

	return *this;
}

/*-----------------------------------------------------------------------------------------*/

const sf::Vector2f& Circuit::getSpawnPoint() const
{
	return m_spawnPoint;
}

const sf::Vector2f& Circuit::getSpawnAngle() const
{
	return m_spawnAngle;
}

/*-----------------------------------------------------------------------------------------*/

inline void Circuit::loadFromFile(const char* path)
{
	std::ifstream file;
	file.open(path);
	if(!file)
		throw new std::ios_base::failure("Open .map has failed");


	float x1, y1, x2, y2;
	while(!file.eof())
	{
		char line[128];
		file.getline(line, 128);

		std::stringstream flux;
		flux << line;

		char junk;
		if(line[0] == 'P') // Spawn
		{
			float angle;
			flux >> junk >> m_spawnPoint.x >> m_spawnPoint.y >> angle;
			angle2vec(m_spawnAngle, angle);
		}
		else if(line[0] == 's')
		{
			flux >> junk >> x1 >> y1;
		}
		else if(line[0] == 'p')
		{
			flux >> junk >> x2 >> y2;
			m_walls.emplace_back(x1, y1, x2, y2);
			x1 = x2; 
			y1 = y2;
		}
		else if(line[0] == 'e')
		{
			flux >> junk >> x2 >> y2;
			m_walls.emplace_back(x1, y1, x2, y2);
		}
	}
	file.close();
}


inline void Circuit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto& i : m_walls)
		target.draw(i);
}