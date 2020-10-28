#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <stdio.h>


#define RAD2DEG 57.2957795056
#define DEG2RAD 0.01745329252


void normalized(sf::Vector2f& res, const sf::Vector2f& v);

const sf::Vector2f normalized(const sf::Vector2f& v);

/*-----------------------------------------------------------------------------------------*/

void rotate(sf::Vector2f& res, const sf::Vector2f& v, const float angle);// angle -> degree

const sf::Vector2f rotate(const sf::Vector2f& v, const float angle);

/*-----------------------------------------------------------------------------------------*/

void truncate(sf::Vector2f& res, const sf::Vector2f& v, float max);

const sf::Vector2f truncate(const sf::Vector2f& v, const float max);

/*-----------------------------------------------------------------------------------------*/

void lerp(sf::Vector2f& res, const sf::Vector2f& a, const sf::Vector2f& b, const float t);

const sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float t);

/*-----------------------------------------------------------------------------------------*/

void vec2angle(float& res, const sf::Vector2f& v);// res -> degree

const float vec2angle(const sf::Vector2f& v);// res -> degree

void angle2vec(sf::Vector2f& res, const float& angle);// res -> degree

const sf::Vector2f angle2vec(const float& angle);// res -> degree
/*-----------------------------------------------------------------------------------------*/

const float map(const float& x, const float& in_min, const float& in_max, 
				const float& out_min, const float& out_max);