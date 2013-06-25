#pragma once
#ifndef CINTERFACE_H
#define CINTERFACE_H

#include "cframe.h"
#include "cmatrix.h"
#include "shapes_all.h"
#include <conio.h>
#include <iostream>
using namespace std;

class CGameProcess
{
	us score; //Счёт
	Cmatrix *field; //Поле
	HDC hDC;
	HPEN Edge_Pen; 
	HPEN Erase_Pen;
	Cframe *ScoreTable, *Glass, *IngameMenu, *SaveMenu, MatrixCreationDialog, Menu, About, LoadMenu; 

public:
	CGameProcess(); //Конструктор
	
#pragma region UI
	void MainMenu(); //Главное меню
	void IngameOptions(); //Игровое меню
	void StartGame(); //Начать игру
	void NoCursor() const; //Убрать курсор
	void AboutInfo(); //Про программу
	void DrawField() const; //Нарисовать поле игры
	void SetScores() const; //Обновить счет
#pragma endregion
	
#pragma region MatrixProcessing
	void CreateMatrix(); //Создать матрицу
	//Проверка возможности смещения фигуры влево
	bool FigureLeftMoveCheck(Cshape *Random, const uc &ins_y, const uc &ins_x) const;
	//Проверка возможности смещения фигуры вправо
	bool FigureRightMoveCheck(Cshape *Random, const uc &ins_y, const uc &ins_x) const; 
	void FigureErase(Cshape *Random, const uc &ins_y, const uc &ins_x); //Стирание фигуры
	void FigureInsert(Cshape *Random, const uc &ins_y, const uc &ins_x); //Вставка фигуры
	//Поворот фигуры
	bool FigureRotate(Cmatrix *field, Cshape *Random, const uc &ins_y, const uc &ins_x); 
	//Проверка на столкновение фигуры с другой
	bool FigureStopCheck(Cshape *Random, const uc &ins_y, const uc &ins_x) const; 
	Cshape *SetRandomShape() const; //Создать случайную фигуру
	bool FigureFall(); //Падение фигуры
	void MatrixEraseRow(const uc &row_index); //Удаление строки из матрицы
	void FieldCheck(); //Проверка поля на составленную строку или переполнение
	void GameOver() { MainMenu(); }
#pragma endregion

#pragma region Files
	void SaveToFile();
	void LoadFromFile();
#pragma endregion
};

#endif //CINTERFACE H