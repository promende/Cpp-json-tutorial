#pragma once
#ifndef LEPTVALUE_H__
#define LEPTVALUE_H__

#include "lepttype.h"

//JSON ����
class LeptValue {
private:
	double number;		//JSON ֵ
	LeptType type;		//JSON ����
	friend class Lept;	//�� Lept Ϊ LeptValue ����Ԫ
public:
	LeptValue();
	LeptValue(LeptType type);
	~LeptValue();
};

#endif // !LEPTVALUE_H__
