#pragma once
#ifndef LEPT_H__
#define LEPT_H__

#include "lepttype.h"
#include "leptstate.h"
#include "leptvalue.h"

//������
class Lept {
public:
	const char* content;		//json ����
	LeptValue value;			//json ֵ

	Lept();
	Lept(const char* content, LeptValue& val);
	~Lept();

	//���� JSON
	LeptState parse();

	//�Ƿ�Ϊ null / true / false
	LeptState parseLiteral(const char* literal, LeptType type);

	//�Ƿ�Ϊ number
	LeptState parseNumber();

	//value = null / true / false / number
	LeptState parseValue();

	//�����ո�
	void parseWhiteSpace();

	//��ȡ JSON ����
	LeptType getType();

	//��ȡ number ֵ
	double getNumber();
};

#endif // !LEPTJSON_H__