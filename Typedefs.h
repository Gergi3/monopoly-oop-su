#pragma once
#include "Pair.hpp"
#include "String.h"
#include "Vector.hpp"

class Property;

typedef size_t CommandCode;
typedef Pair<CommandCode, String> Option;
typedef Vector<Option> Options;
typedef Vector<Property*> MutableProperties;
typedef Vector<const Property*> Properties;