#ifndef _CONSOLE_HANDLE_H_
#define _CONSOLE_HANDLE_H_
#include <Windows.h>
#include<string.h>
#include<stdio.h>

typedef struct __CONSOLE {
	void(*swapConsoleHandle)();		//入れ替え
	void(*createConsoleHandle)();	//初期化
	void(*deleteConsoleHandle)();	//後始末
	void(*print)(const char str[],const int posX,const int posY,const SHORT fontColor,const SHORT backColor);	//引数で文字列、座標と色を渡しバッファに文字列を入れる
	void(*drawScreen)();			//描画
} *CONSOLE;	

CONSOLE getInstance();

#endif //_CONSOLE_HANDLE_H_