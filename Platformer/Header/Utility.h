#pragma once

#include <algorithm>

template <class T>
void clamp(T &value, T min, T max);

template <class T>
bool outOfRange(T value, T min, T max);

extern float randomize(float min, float max);

extern int randomize(int min, int max);

#include <Utility.inl>