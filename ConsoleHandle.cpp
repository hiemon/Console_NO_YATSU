#include "ConsoleHandle.h"

const SHORT _BLACK = 0;
const SHORT _WHITE = 15;

static CONSOLE Console;
static HANDLE consoleHandle1;
static HANDLE consoleHandle2;
static CONSOLE_CURSOR_INFO cursorInfo;
static CONSOLE_SCREEN_BUFFER_INFO screenInfo;
static CHAR_INFO* buffer;
static bool isSwap;
static COORD coord;																					//書き込みを開始する位置
static COORD size;																					//画面サイズ
static SMALL_RECT rect;																				//書き込む範囲を矩形で指定する

static HANDLE getHandle();																			//書き込むハンドルを返す

//コンソールハンドルの関数
static void _swapConsoleHandle();
static void _createConsoleHandle();
static void _deleteConsoleHandle();
static void _print(const char str[],const int posX,const int posY,const SHORT fontColor,const SHORT backColor);
static void _drawScreen();




CONSOLE getInstance() {	
	if (!Console) {
		Console = (CONSOLE)malloc(sizeof(*Console));
		Console->swapConsoleHandle = _swapConsoleHandle;
		Console->createConsoleHandle = _createConsoleHandle;
		Console->deleteConsoleHandle = _deleteConsoleHandle;
		Console->print = _print;
		Console->drawScreen = _drawScreen;
	}
	return Console;
}

static void _swapConsoleHandle() {
	::SetConsoleActiveScreenBuffer(getHandle());
	isSwap = !isSwap;
}
static void _createConsoleHandle() {
	//コンソールハンドルを作る
	consoleHandle1 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	consoleHandle2 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;

	::SetConsoleCursorInfo(consoleHandle1, &cursorInfo);
	::SetConsoleCursorInfo(consoleHandle2, &cursorInfo);
	::GetConsoleScreenBufferInfo(getHandle(), &screenInfo);

	isSwap = false;																					//取り敢えずfalseで初期化
	coord = { 0, 0 };																				//書き込みを開始する位置 x:0y:0に設定
	size = { screenInfo.dwSize.X,screenInfo.dwSize.Y };												//画面サイズ
	rect = { coord.X, coord.Y, size.X, size.Y };													//書き込む範囲を矩形で指定する
	buffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * screenInfo.dwSize.Y * screenInfo.dwSize.X);		//バッファーを確保

	//バッファの中身を初期化
	for (int y = 0; y < screenInfo.dwSize.Y;++y) {
		for (int x = 0; x < screenInfo.dwSize.X;++x) {
			buffer[y * screenInfo.dwSize.X + x].Attributes = _WHITE + (_BLACK << 4);
			buffer[y * screenInfo.dwSize.X + x].Char.UnicodeChar = ' ';
		}
	}

}

static void _deleteConsoleHandle() {

	free(buffer);
	::CloseHandle(consoleHandle2);
	::CloseHandle(consoleHandle1);
	free(Console);
}

/*
@（文字列、座標x,座標y,フォントの色、背景色）
*/
void _print(const char str[], const int posX, const int posY, const SHORT fontColor, const SHORT backColor) {
	int index = 0;
	int length = strlen(str);															//文字の長さ
	const int X = posX + length;
	for (int x = posX;x < X;++x) {
		buffer[posY * (int)screenInfo.dwSize.X + x].Char.UnicodeChar = str[index];
		buffer[posY * (int)screenInfo.dwSize.X + x].Attributes = fontColor + (backColor << 4);
		++index;
	}
}

void _drawScreen() {
	::WriteConsoleOutputA(getHandle(), buffer, size, coord, &rect);
}

static HANDLE getHandle() {
	return isSwap ? consoleHandle1 : consoleHandle2;
}

