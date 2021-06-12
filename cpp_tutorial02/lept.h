#pragma once
#ifndef LEPT_H__
#define LEPT_H__

#include "lepttype.h"
#include "leptstate.h"
#include "leptvalue.h"

//解析类
class Lept {
public:
	const char* content;		//json 内容
	LeptValue value;			//json 值

	Lept();
	Lept(const char* content, LeptValue& val);
	~Lept();

	//解析 JSON
	LeptState parse();

	//是否为 null / true / false
	LeptState parseLiteral(const char* literal, LeptType type);

	//是否为 number
	LeptState parseNumber();

	//value = null / true / false / number
	LeptState parseValue();

	//跳过空格
	void parseWhiteSpace();

	//获取 JSON 类型
	LeptType getType();

	//获取 number 值
	double getNumber();
};

#endif // !LEPTJSON_H__