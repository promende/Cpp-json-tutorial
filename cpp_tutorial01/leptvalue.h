#pragma once
#ifndef LEPTVALUE_H__
#define LEPTVALUE_H__

#include "lepttype.h"

//JSON ����
class LeptValue {
private:
	friend class Lept;
	LeptType type;		//JSON ����
public:
	LeptValue();
	LeptValue(LeptType type);
	~LeptValue();
};

#endif // !LEPTVALUE_H__
