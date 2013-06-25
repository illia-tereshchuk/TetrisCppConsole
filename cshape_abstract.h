#pragma once
#ifndef CSHAPE_H
#define CSHAPE_H

#include "definitions.h"
#include <iostream>
using namespace std;

class Cshape //Фигуру можно представить в виде двумерного bool - массива
{
protected:
	bool **body; //Фигура
	uc width, height; //Параметры

public:
	virtual void Rotate();
	friend class CGameProcess;
	~Cshape() { for(uc i = 0; i < height; i++) delete [] body[i]; }
};

#endif //CSHAPE_H