#pragma once
#include "String.h"

enum class FieldType
{
	Property = 0,
	Railroad = 1,
	Utility = 2,
	CardField = 3,
	TextField = 4,
	TaxField = 5,
};

namespace FieldTypeHelpers
{
	inline static String getFieldTypeStr(FieldType fieldType)
	{
		switch (fieldType)
		{
			case FieldType::Property: return "property";
			case FieldType::Railroad: return "railroad";
			case FieldType::Utility: return "utility";
			case FieldType::CardField: return "card field";
			case FieldType::TextField: return "text field";
			case FieldType::TaxField: return "tax field";
			default: return "unknown field";
		}
	}
}