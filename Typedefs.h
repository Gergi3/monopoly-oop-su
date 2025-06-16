#pragma once

template<typename T>
class Vector;
class Property;


typedef Vector<Property*> MutableProperties;
typedef Vector<const Property*> Properties;