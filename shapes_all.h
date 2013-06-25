#pragma once
#ifndef SHAPES_ALL_H
#define SHAPES_ALL_H

#include "cshape_abstract.h"

#pragma region Tetramino_Shapes

class CTfigure: public Cshape //T - фигура
{
public: CTfigure();
};

class CZfigure: public Cshape //Z - фигура
{
public: CZfigure();
};

class CSfigure: public Cshape //S - фигура
{
public: CSfigure();
};

class CLfigure: public Cshape //L - фигура
{
public: CLfigure();
};

class CJfigure: public Cshape //J - фигура
{
public: CJfigure();
};

class COfigure: public Cshape //O - фігура
{
public:
	COfigure();
	void Rotate() { } //Квадратна фігура не має функції обертання
};

class CIfigure: public Cshape //J - фігура
{
public: CIfigure();
};

#pragma endregion

#endif //SHAPES_ALL_H