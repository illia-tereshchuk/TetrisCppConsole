#pragma once
#ifndef CMATRIX_H
#define CMATRIX_H

#include "definitions.h"

class Cmatrix
{
public:
	us width, height; //Ўирина и высота пол€
	bool **field;
	
	Cmatrix(us width, us height): width(width), height(height)
	{
		field = new bool*[height];
		for(uc i = 0; i < height; i++)
		{
			field[i] = new bool[width];
			for(uc j = 0; j < width; j++)
				field[i][j] = 0;
		}
	}

	~Cmatrix()
	{
		if(field) for(uc i = 0; i < height; i++) { delete [] field[i]; field[i] = 0; }
	}
};

#endif //CMATRIX_H