#include "ConsoleHandle.h"

int main(void) {

	getInstance()->createConsoleHandle();					//‚¢‚ë‚¢‚ë€”õ

	while (1) {
		
		getInstance()->print("abcdefghijk",10,10,3,4);		//ƒtƒHƒ“ƒg‚ª—Î(3)‚Å”wŒiF‚ªÔ(4)abcdefghijk‚ğx:10y:10‚Éİ’è
		getInstance()->drawScreen();						//•`‰æ
		getInstance()->swapConsoleHandle();					//“ü‚ê‘Ö‚¦
	}
	
	getInstance()->deleteConsoleHandle();					//‰ğ•ú‚Ìˆ—

	return 0;
}


