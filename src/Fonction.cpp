#include "Fonction.hpp"


void normalized (sf::Vector2f& res, const sf::Vector2f& v)
{
    const float len = sqrt(v.x * v.x + v.y * v.y);
    if (len != 0)
    {
        res.x = v.x / len;
        res.y = v.y / len;
    }
}

const sf::Vector2f normalized (const sf::Vector2f& v)
{
    sf::Vector2f res;
    normalized(res, v);
    return res;
}

/*-----------------------------------------------------------------------------------------*/

void rotate(sf::Vector2f& res, const sf::Vector2f& v, const float angle)// angle -> degree
{
    const float rad = DEG2RAD * angle;
    const float sin0 = sin(rad);
    const float cos0 = cos(rad);
    res.x = v.x * cos0 + v.y * -sin0;
    res.y = v.x * sin0 + v.y * cos0;
}

const sf::Vector2f rotate(const sf::Vector2f& v, const float angle)
{
    sf::Vector2f res;
    rotate(res, v, angle);
    return res;
}

/*-----------------------------------------------------------------------------------------*/

void truncate(sf::Vector2f& res, const sf::Vector2f& v, const float max)
{
    const float len = sqrt(v.x*v.x + v.y*v.y);
    if(len > max)
    {
        res = normalized(v);
        res *= max;
    }
    else
        res = v;
}

const sf::Vector2f truncate(const sf::Vector2f& v, const float max)
{
    sf::Vector2f res;
    truncate(res, v, max);
    return res;
}

/*-----------------------------------------------------------------------------------------*/

void lerp(sf::Vector2f& res, const sf::Vector2f& a, const sf::Vector2f& b, const float t)
{
    res.x = (1 - t) * a.x + t * b.x;
    res.y = (1 - t) * a.y + t * b.y;
}

const sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float t)
{
    sf::Vector2f res;
    lerp(res, a, b, t);
    return res;
}

/*-----------------------------------------------------------------------------------------*/

void vec2angle(float& res, const sf::Vector2f& v)
{
    const float len = sqrt(v.x * v.x + v.y * v.y);
    if(len != 0)
    {
        res = acos(v.x / len) * RAD2DEG;
        if(v.y < 0.f)
            res = 360 - res;
    }
    else
        res = 0.f;
}

const float vec2angle(const sf::Vector2f& v)
{
    float res;
    vec2angle(res, v);
    return res;
}

void angle2vec(sf::Vector2f& res, const float& angle)
{
    const float rad = DEG2RAD * angle;
    res.x = cos(rad);
    res.y = sin(rad);
}

const sf::Vector2f angle2vec(const float& angle)
{
    sf::Vector2f res;
    angle2vec(res, angle);
    return res;
}

/*-----------------------------------------------------------------------------------------*/

const float map(const float& x, const float& in_min, const float& in_max, const float& out_min, const float& out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}