#include "ConsoleHandle.h"

int main(void) {

	getInstance()->createConsoleHandle();					//いろいろ準備

	while (1) {
		
		getInstance()->print("abcdefghijk",10,10,3,4);		//フォントが緑(3)で背景色が赤(4)abcdefghijkをx:10y:10に設定
		getInstance()->drawScreen();						//描画
		getInstance()->swapConsoleHandle();					//入れ替え
	}
	
	getInstance()->deleteConsoleHandle();					//解放の処理

	return 0;
}


