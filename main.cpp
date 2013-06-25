#include "cgameprocess.h"

void main()
{
	setlocale(0, "Russian");
	//Параметры окна
	HWND hWnd = GetConsoleWindow();
	SetWindowPos(hWnd, HWND_TOPMOST, 5, 5, 0, 0, 0);
	
	system("mode con cols=124 lines=59"); //Для 1024 * 768
	SetConsoleTitle(L"Тетрис(c) 2012, Илья Терещук, КА ШАГ");
	system("color f0");

	CGameProcess Game; Game.MainMenu();
}