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

	//是否为 null
	LeptState parseNull();

	//是否为 true
	LeptState parseTrue();

	//是否为 false
	LeptState parseFalse();

	//value = null / true / false
	LeptState parseValue();

	//跳过空格
	void parseWhiteSpace();

	//获取 JSON 类型
	LeptType getType();
};

#endif // !LEPTJSON_H__