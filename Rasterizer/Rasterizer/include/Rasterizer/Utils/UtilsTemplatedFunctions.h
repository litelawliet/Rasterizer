#pragma once
#include <algorithm>

template<typename T>
float Min3(const T& p_first, const T& p_second, const T& p_third)
{
	return std::min(p_first, std::min(p_second, p_third));
}

template<typename T>
float Max3(const T& p_first, const T& p_second, const T& p_third)
{
	return std::max(p_first, std::max(p_second, p_third));
}