#pragma once
#ifndef LEPTSTATE_H__
#define LEPTSTATE_H__

//���ص�״̬
enum class LeptState {
	LEPT_PARSE_OK,				//û�д���
	LEPT_PARSE_EXPECT_VALUE,	//JSON ֻ���пհ�
	LEPT_PARSE_INVALID_VALUE,	//ֵ������ null��false��true
	LEPT_PARSE_ROOT_NOT_SINGULAR//һ��ֵ�ڿհ�֮���������ַ�
};

#endif // !LEPTSTATE_H__
