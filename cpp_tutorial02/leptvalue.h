#pragma once
#ifndef LEPTVALUE_H__
#define LEPTVALUE_H__

#include "lepttype.h"

//JSON 对象
class LeptValue {
private:
	double number;		//JSON 值
	LeptType type;		//JSON 类型
	friend class Lept;	//设 Lept 为 LeptValue 的友元
public:
	LeptValue();
	LeptValue(LeptType type);
	~LeptValue();
};

#endif // !LEPTVALUE_H__
