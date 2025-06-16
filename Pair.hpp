#pragma once

template<typename F, typename S>
struct Pair
{
	F key;
	S value;

	Pair() = default;
	Pair(const F& first, const S& second);

	template<typename F, typename S>
	friend bool operator==(const Pair<F, S>& lhs, const Pair<F, S>& rhs);
	template<typename F, typename S>
	friend bool operator!=(const Pair<F, S>& lhs, const Pair<F, S>& rhs);
};

template<typename F, typename S>
Pair<F, S>::Pair(const F& first, const S& second) 
	: key(first), value(second)
{}

template<typename F, typename S>
bool operator==(const Pair<F, S>& lhs, const Pair<F, S>& rhs)
{
	return lhs.key == rhs.key && lhs.value == rhs.value;
}

template<typename F, typename S>
bool operator!=(const Pair<F, S>& lhs, const Pair<F, S>& rhs)
{
	return lhs.key != rhs.key || lhs.value != rhs.value;
}
