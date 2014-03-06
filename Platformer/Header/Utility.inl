template <class T>
void clamp(T &value, T min, T max)
{
	value = std::max(value, min);
	value = std::min(value, max);
}