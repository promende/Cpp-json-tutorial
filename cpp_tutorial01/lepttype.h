#pragma once
#ifndef LEPTTYPE_H__
#define LEPTTYPE_H__

//JSON ��������
enum class LeptType {
	LEPT_DEFAULT,//��ʼֵ
	LEPT_NULL,	 //NULL
	LEPT_FALSE,	 //false
	LEPT_TRUE,	 //true
	LEPT_NUMBER, //����
	LEPT_STRING, //�ַ���
	LEPT_ARRAY,	 //����
	LEPT_OBJECT  //����
};

#endif // !LEPTTYPE_H__

