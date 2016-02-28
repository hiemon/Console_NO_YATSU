#ifndef _CONSOLE_HANDLE_H_
#define _CONSOLE_HANDLE_H_
#include <Windows.h>
#include<string.h>
#include<stdio.h>

typedef struct __CONSOLE {
	void(*swapConsoleHandle)();		//����ւ�
	void(*createConsoleHandle)();	//������
	void(*deleteConsoleHandle)();	//��n��
	void(*print)(const char str[],const int posX,const int posY,const SHORT fontColor,const SHORT backColor);	//�����ŕ�����A���W�ƐF��n���o�b�t�@�ɕ����������
	void(*drawScreen)();			//�`��
} *CONSOLE;	

CONSOLE getInstance();

#endif //_CONSOLE_HANDLE_H_