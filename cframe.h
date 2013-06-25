#pragma once
#ifndef CFRAME_H
#define CFRAME_H

#include <iostream>
#include <Windows.h>
#include "definitions.h"
using std::cout;

class Cframe
{
	us margin_left, margin_top, width, height; //Отступ слева, отступ сверху, ширина, высота
	uc thickness, red, green, blue; //Толщина, цвет в RGB
	COORD Left_top; //Верхняя левая координата рамки
	HDC hDC;
	HPEN Edge_Pen;
	HPEN Erase_Pen;
	HANDLE hConsole;

public:
	Cframe(us margin_left, us margin_top, us width, us height, uc thickness, uc red, uc green, uc blue);
	void Draw() const;
	void SetCursorToRow(const uc row_index) const;
	void Erase() const;
	void ClearRow(const uc row_index) const;
};

#endif //CFRAME_H