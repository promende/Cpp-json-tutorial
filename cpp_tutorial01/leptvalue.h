#pragma once
#ifndef LEPTVALUE_H__
#define LEPTVALUE_H__

#include "lepttype.h"

//JSON 对象
class LeptValue {
private:
	friend class Lept;
	LeptType type;		//JSON 类型
public:
	LeptValue();
	LeptValue(LeptType type);
	~LeptValue();
};

#endif // !LEPTVALUE_H__
