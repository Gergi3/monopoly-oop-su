#pragma once
#include "String.h"
#include "Vector.hpp"
#include <sstream>

namespace StreamHelpers
{
	void readNWords(size_t n, std::stringstream& ss, String& data);
	void readRemaining(std::stringstream& ss, String& data);
	void splitToVector(std::stringstream& ss, Vector<String>& vector);
	void splitNToVector(size_t n, std::stringstream& ss, Vector<String>& vector);

	bool fileExists(const String& filename);
	void createEmpty(const String& filename);
}