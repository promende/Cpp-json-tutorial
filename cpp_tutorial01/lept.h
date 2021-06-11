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

	//�Ƿ�Ϊ null
	LeptState parseNull();

	//�Ƿ�Ϊ true
	LeptState parseTrue();

	//�Ƿ�Ϊ false
	LeptState parseFalse();

	//value = null / true / false
	LeptState parseValue();

	//�����ո�
	void parseWhiteSpace();

	//��ȡ JSON ����
	LeptType getType();
};

#endif // !LEPTJSON_H__