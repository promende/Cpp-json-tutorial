#pragma once
#ifndef LEPTTYPE_H__
#define LEPTTYPE_H__

//JSON 对象类型
enum class LeptType {
	LEPT_DEFAULT,//初始值
	LEPT_NULL,	 //NULL
	LEPT_FALSE,	 //false
	LEPT_TRUE,	 //true
	LEPT_NUMBER, //数字
	LEPT_STRING, //字符串
	LEPT_ARRAY,	 //数组
	LEPT_OBJECT  //对象
};

#endif // !LEPTTYPE_H__

