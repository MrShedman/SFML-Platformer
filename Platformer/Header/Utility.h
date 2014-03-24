#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <sstream>

template <class T>
void clamp(T &value, T min, T max);

template <class T>
bool outOfRange(T value, T min, T max);

template <class T>
std::string toString(const T& value);

extern std::vector<sf::VideoMode> getValidVideoModes();

extern sf::Vector2f getMousePosition(const sf::RenderWindow &window);

extern void scaleSpriteToFitWindow(sf::Sprite &sprite, const sf::RenderWindow &window);

extern float randomize(float min, float max);

extern int randomize(int min, int max);

#include <Utility.inl>