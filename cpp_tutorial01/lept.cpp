#include <string>
#include <assert.h>
#include "lept.h"

Lept::Lept() = default;

Lept::Lept(const char* content, LeptValue& val) : content(content), value(value) {

}

Lept::~Lept() = default;

LeptState Lept::parse()
{
	assert(content != nullptr);
	value.type = LeptType::LEPT_NULL;
	parseWhiteSpace();

	LeptState state = parseValue();
	if (state == LeptState::LEPT_PARSE_OK) {
		parseWhiteSpace();
		if (*content != '\0') {
			state = LeptState::LEPT_PARSE_ROOT_NOT_SINGULAR;
		}
	}
	return state;
}

LeptState Lept::parseNull()
{
	if (content[0] != 'n' || content[1] != 'u' || content[2] != 'l' || content[3] != 'l') {
		return LeptState::LEPT_PARSE_INVALID_VALUE;
	}
	content += 4;
	value.type = LeptType::LEPT_NULL;
	return LeptState::LEPT_PARSE_OK;
}

LeptState Lept::parseTrue()
{
	if (content[0] != 't' || content[1] != 'r' || content[2] != 'u' || content[3] != 'e') {
		return LeptState::LEPT_PARSE_INVALID_VALUE;
	}
	content += 4;
	value.type = LeptType::LEPT_TRUE;

	return LeptState::LEPT_PARSE_OK;
}

LeptState Lept::parseFalse()
{
	if (content[0] != 'f' || content[1] != 'a' || content[2] != 'l' || content[3] != 's' || content[4] != 'e') {
		return LeptState::LEPT_PARSE_INVALID_VALUE;
	}
	content += 5;
	value.type = LeptType::LEPT_FALSE;

	return LeptState::LEPT_PARSE_OK;
}

LeptState Lept::parseValue()
{
	assert(content != nullptr);
	switch (*content)
	{
	case 'n':
		return parseNull(); 
		break;
	case 't':
		return parseTrue(); 
		break;
	case 'f':
		return parseFalse(); 
		break;
	case '\0':
		return LeptState::LEPT_PARSE_EXPECT_VALUE; 
		break;
	default:
		return LeptState::LEPT_PARSE_INVALID_VALUE;
		break;
	}
}

void Lept::parseWhiteSpace() 
{
	while (*content == ' ' || *content == '\t' || *content == '\n' || *content == '\r') {
		content++;
	}
}

LeptType Lept::getType()
{
	return value.type;
}