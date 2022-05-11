//Copyright Sam Collier 2022
#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

#define PI 3.14159265f

template <typename T>

class Vector
{
	public:
		static T size(sf::Vector2<T> v);
		static sf::Vector2<T> normalize(sf::Vector2<T> v);

		// divides member-wise v1/v2
		static sf::Vector2f divide(sf::Vector2<T> v1, sf::Vector2<T> v2);
		static sf::Vector2f divide(sf::Vector2<T> v, T s);

		// multiply member-wise
		static sf::Vector2<T> multiply(sf::Vector2<T> v1, sf::Vector2<T> v2);

		static T angle(sf::Vector2<T> v1, sf::Vector2<T> v2);

		static T dot(sf::Vector2<T> v1, sf::Vector2<T> v2);

		static T distance(sf::Vector2<T> v1, sf::Vector2<T> v2);
};

template <typename T>
T Vector<T>::size(sf::Vector2<T> v)
{
	return sqrtf(v.x*v.x+v.y*v.y);
}

template <typename T>
sf::Vector2<T> Vector<T>::normalize(sf::Vector2<T> v)
{
	return v / size(v);
}

template <typename T>
sf::Vector2f Vector<T>::divide(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
	return sf::Vector2f(v1.x/v2.x,v1.y/v2.y);
}

template <typename T>
sf::Vector2<T> Vector<T>::multiply(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
	return sf::Vector2f(v1.x*v2.x,v1.y*v2.y);
}

template <typename T>
T Vector<T>::angle(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
	return acosf(dot(v1,v2)/(size(v1)*size(v2)));
}

template <typename T>
T Vector<T>::dot(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}

template <typename T>
T Vector<T>::distance(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
	return sqrtf(powf(v2.x-v1.x,2.f) + powf(v2.y-v1.y,2.f));
}

template <typename T>
sf::Vector2f Vector<T>::divide(sf::Vector2<T> v, T s)
{
	return sf::Vector2f(v.x/s,v.y/s);
}
