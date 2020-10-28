#include "Car.hpp"


Car::Car(const Circuit& circuit, const sf::Texture& texture)
	: m_circuit(circuit), m_vel(0.f, 0.f), m_texture(texture), m_sprite(texture),
	  m_showLine(false), m_crashed(false), m_neuralN(6, 4, 10, 2) // z s q d
{
	m_position = m_circuit.getSpawnPoint();
	m_rotation = m_circuit.getSpawnAngle();

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 4, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(m_position);

	sf::Vector2f normalAngle(rotate(m_rotation, (float)-90));
	for(int i = 0; i < NBR_RAYS; i++)
		m_rays[i] = Ray(m_position, rotate(normalAngle, 45.f * (float)i));

	//printf("const\n");
	//m_neuralN.print();
}

Car::Car(const Car& m)
	: m_circuit(m.m_circuit), m_vel(m.m_vel), m_texture(m.m_texture), m_sprite(m.m_texture),
	  m_position(m.m_position), m_rotation(m.m_rotation), m_showLine(m.m_showLine),
	  m_crashed(m.m_crashed), m_neuralN(m.m_neuralN)
{

	for(unsigned int i = 0; i < NBR_RAYS; i++)
		m_rays[i] = m.m_rays[i];

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 4, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(m_position);
}

Car::~Car()
{
	
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

/*-----------------------------------------------------------------------------------------*/

inline void Car::input(const float fps)
{
	//bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	//bool q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	//bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	const bool z = rand() % 2;
	const bool q = rand() % 2;
	const bool d = rand() % 2;

	if(z)
		accelerate(fps);
	else
		decelerate(fps);

	if(q)
		left(fps);
	if(d)
		right(fps);
}

void Car::update(const float fps)
{
	if(!m_crashed)
	{
		//input(fps);
		Matrix in(1, 6);
		for(unsigned int i = 0; i < NBR_RAYS; i++)
			in.set(0, i, m_rays[i].getLenght());
		in.set(0, 5, sqrt(m_vel.x*m_vel.x + m_vel.y*m_vel.y));


		const Matrix out = m_neuralN.forward(in);

		if(out.get(0, 0) > 0.5)
			accelerate(fps);
		if(out.get(0, 2) > 0.5)
			left(fps);
		if(out.get(0, 3) > 0.5)
			right(fps);


		//in.print();
		//out.print();
		//for(unsigned int i = 0; i < NBR_RAYS; i++)
		//	printf("%f ", m_rays[i].getLenght());
		//printf(">%f\n", sqrt(m_vel.x*m_vel.x + m_vel.y*m_vel.y));


		
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
	target.draw(m_sprite);

	if(m_showLine)
	{
		for(short i = 0; i < NBR_RAYS; i++)
			target.draw(m_rays[i]);
	}
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
	rotate(m_vel, m_vel, -TURN * fps);
}

void Car::right(const float fps)
{
	rotate(m_vel, m_vel, TURN * fps);
}