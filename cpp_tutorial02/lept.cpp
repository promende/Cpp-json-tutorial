#include <string>
#include <assert.h>
#include "lept.h"

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')

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
			value.type = LeptType::LEPT_NULL;
			state = LeptState::LEPT_PARSE_ROOT_NOT_SINGULAR;
		}
	}

	return state;
}

LeptState Lept::parseLiteral(const char* literal, LeptType type)
{
	size_t index = 0;
	for (index = 0; literal[index] != '\0'; index++) {
		if (content[index] != literal[index]) {
			return LeptState::LEPT_PARSE_INVALID_VALUE;
		}
	}
	content += index;
	value.type = type;

	return LeptState::LEPT_PARSE_OK;
}

LeptState Lept::parseNumber()
{
	const char* p = content;
	//Ìø¹ý¸ººÅ
	if (*p == '-') {
		p++;
	}
	
	if (*p == '0') {
		p++;
	}
	else {
		if (!ISDIGIT1TO9(*p)) {
			return LeptState::LEPT_PARSE_INVALID_VALUE;
		}

		while (ISDIGIT(*p)) {
			p++;
		}
	}

	if (*p == '.') {
		p++;
		if (!ISDIGIT(*p)) {
			return LeptState::LEPT_PARSE_INVALID_VALUE;
		}

		while (ISDIGIT(*p)) {
			p++;
		}
	}

	if (*p == 'e' || *p == 'E') {
		p++;
		if (*p == '+' || *p == '-') {
			p++;
		}
		if (!ISDIGIT(*p)) {
			return LeptState::LEPT_PARSE_INVALID_VALUE;
		}
		while (ISDIGIT(*p)) {
			p++;
		}
	}

	errno = 0;
	value.number = strtod(content, nullptr);
	if (errno == ERANGE && (value.number == HUGE_VAL || value.number == -HUGE_VAL)) {
		return LeptState::LEPT_PARSE_NUMBER_TOO_BIG;
	}
	value.type = LeptType::LEPT_NUMBER;
	content = p;

	return LeptState::LEPT_PARSE_OK;
}

LeptState Lept::parseValue()
{
	assert(content != nullptr);

	switch (*content)
	{
	case 'n':
		return parseLiteral("null", LeptType::LEPT_NULL);
		break;
	case 't':
		return parseLiteral("true", LeptType::LEPT_TRUE);
		break;
	case 'f':
		return parseLiteral("false", LeptType::LEPT_FALSE);
		break;
	case '\0':
		return LeptState::LEPT_PARSE_EXPECT_VALUE; 
		break;
	default:
		return parseNumber();
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
	assert(&value != nullptr);

	return value.type;
}

double Lept::getNumber()
{
	assert(&value != nullptr);
	assert(value.type == LeptType::LEPT_NUMBER);

	return value.number;
}
