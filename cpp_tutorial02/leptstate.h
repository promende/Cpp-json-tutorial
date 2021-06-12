#pragma once
#ifndef LEPTSTATE_H__
#define LEPTSTATE_H__

//返回的状态
enum class LeptState {
	LEPT_PARSE_OK,					//没有错误
	LEPT_PARSE_EXPECT_VALUE,		//JSON 只含有空白
	LEPT_PARSE_INVALID_VALUE,		//值不等于 null、false、true、number
	LEPT_PARSE_ROOT_NOT_SINGULAR,	//一个值在空白之后还有其他字符
	LEPT_PARSE_NUMBER_TOO_BIG		//LeptType 为 number 且 数值过大
};

#endif // !LEPTSTATE_H__
