#include "ConsoleHandle.h"

int main(void) {

	getInstance()->createConsoleHandle();					//���낢�돀��

	while (1) {
		
		getInstance()->print("abcdefghijk",10,10,3,4);		//�t�H���g����(3)�Ŕw�i�F����(4)abcdefghijk��x:10y:10�ɐݒ�
		getInstance()->drawScreen();						//�`��
		getInstance()->swapConsoleHandle();					//����ւ�
	}
	
	getInstance()->deleteConsoleHandle();					//����̏���

	return 0;
}


