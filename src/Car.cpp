#include "Car.hpp"


Car::Car(const Circuit& circuit, const sf::Texture& texture)
	: m_circuit(circuit), m_vel(0.f, 0.f), m_texture(texture), m_sprite(texture),
	  m_showLine(false), m_crashed(false), m_neuralN(6, 4, 10, 1) // z s q d
{
	m_position = m_circuit.getSpawnPoint();
	m_rotation = m_circuit.getSpawnAngle();

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 4, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(m_position);

	sf::Vector2f normalAngle(rotate(m_rotation, (float)-90));
	for(int i = 0; i < NBR_RAYS; i++)
		m_rays[i] = Ray(m_position, rotate(normalAngle, 45.f * (float)i));
}

Car::Car(const Car& c)
	: m_circuit(c.m_circuit), m_vel(0.f, 0.f), m_texture(c.m_texture), m_sprite(c.m_texture),
	  m_showLine(c.m_showLine), m_crashed(false), m_neuralN(c.m_neuralN)
{
	m_position = m_circuit.getSpawnPoint();
	m_rotation = m_circuit.getSpawnAngle();

	for(unsigned int i = 0; i < NBR_RAYS; i++)
		m_rays[i] = c.m_rays[i];

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 4, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(m_position);
}

Car::~Car()
{
	
}

Car& Car::operator=(const Car& c)
{
	m_vel = c.m_vel;
	
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 4, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(m_position);

	m_position = c.m_position;
	m_rotation = c.m_rotation;

	for(unsigned int i = 0; i < NBR_RAYS; i++)
		m_rays[i] = c.m_rays[i];

	m_showLine = c.m_showLine;
	m_crashed = c.m_showLine;

	m_neuralN = m_neuralN;

	return *this;
}

/*-----------------------------------------------------------------------------------------*/

inline void Car::setPosition(const sf::Vector2f &position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
	
	for(short i = 0; i < NBR_RAYS; i++)
		m_rays[i].setPosition(m_position);
}

inline void Car::setPosition(const float x, const float y)
{
	m_position.x = x;
	m_position.y = y;
	m_sprite.setPosition(m_position.x, m_position.y);

	for(short i = 0; i < NBR_RAYS; i++)
		m_rays[i].setPosition(m_position);
}

inline void Car::setRotation(float x, float y)
{
	normalized(m_rotation, sf::Vector2f(x, y));
}

inline void Car::setRotation(const sf::Vector2f& angle)
{
	normalized(m_rotation, angle);
}

inline void Car::setRotation(const float angle)
{
	rotate(m_rotation, m_rotation, angle);
	m_sprite.setRotation(angle);
	for(short i = 0; i < NBR_RAYS; i++)
		m_rays[i].setRotation(m_rotation);
}

inline const sf::Vector2f& Car::getRotation() const
{
	return m_rotation;
}

void Car::showRay()
{
	m_showLine = !m_showLine;
}

void Car::mutate()
{
	m_neuralN.mutate();
}

/*-----------------------------------------------------------------------------------------*/

inline void Car::input(const float fps)
{
	const bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	const bool q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	const bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if(z)
		accelerate(fps);
	else
		decelerate(fps);

	if(q)
		left(fps);
	if(d)
		right(fps);
}

inline void Car::think(const float fps)
{
	Matrix input(1, 6);
	float* input_tab(input.data());

	input_tab[0] = m_rays[0].getLenght();
	input_tab[1] = m_rays[1].getLenght();
	input_tab[2] = m_rays[2].getLenght();
	input_tab[3] = m_rays[3].getLenght();
	input_tab[4] = m_rays[4].getLenght();
	input_tab[5] = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);

	const Matrix output = m_neuralN.forward(input);
	float* output_tab(output.data());

	float max(0.f);
	unsigned int index(0);
	for(unsigned int i = 0; i < 4; i++)
		if(max < output_tab[i])
		{
			max = output_tab[i];
			index = i;
		}

	switch(index)
	{
		case 0:
			accelerate(fps);
			break;
		case 1:
			break;
		case 2:
			left(fps);
			break;
		case 3:
			right(fps);
			break;
		default:
			break;
	}
}

void Car::update(const float fps)
{
	if(!m_crashed)
	{
		//input(fps);
		think(fps);
		
		truncate(m_vel, m_vel, MAX_SPEED);
		normalized(m_rotation, m_vel);

		m_sprite.setRotation(vec2angle(m_rotation));
		sf::Vector2f normalAngle(rotate(m_rotation, (float)-90));
		for(int i = 0; i < NBR_RAYS; i++)
			m_rays[i].setRotation(rotate(normalAngle, 45.f * (float)i));

		setPosition(m_position.x + m_vel.x * fps, m_position.y + m_vel.y * fps);

		for(short i = 0; i < NBR_RAYS; i++)
		{
			m_rays[i].update(m_circuit);
			if(m_rays[i].getLenght() < 20)
				m_crashed = true;
		}
	}
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!m_crashed)
		target.draw(m_sprite);

	if(!m_crashed && m_showLine)
		for(short i = 0; i < NBR_RAYS; i++)
			target.draw(m_rays[i]);
}


void Car::accelerate(const float fps)
{
	m_vel.x += ACCELERATION * fps * m_rotation.x;
	m_vel.y += ACCELERATION * fps * m_rotation.y;
}

void Car::decelerate(const float fps)
{
	lerp(m_vel, m_vel, sf::Vector2f(0.f, 0.f), DECELERATION * fps);
}

void Car::left(const float fps)
{
	rotate(m_vel, m_vel, -TURN * fps * map(sqrt(m_vel.x*m_vel.x + m_vel.y*m_vel.y), 0, MAX_SPEED, 0, 1));
}

void Car::right(const float fps)
{
	rotate(m_vel, m_vel, TURN * fps * map(sqrt(m_vel.x*m_vel.x + m_vel.y*m_vel.y), 0, MAX_SPEED, 0, 1));
}