#include "shapes_all.h"

CTfigure::CTfigure()
{
	height = 2; width = 3;
		
	body = new bool*[height];
	for(uc i = 0; i < height; i++)
	{
		body[i] = new bool[width];
		for(uc j = 0; j < width; j++) body[i][j] = 0;
	}
	body[0][1] = body[1][0] = body[1][1] = body[1][2] = 1;
}

CSfigure::CSfigure()
{
	height = 2; width = 3;
		
	body = new bool*[height];
	for(uc i = 0; i < height; i++)
	{
		body[i] = new bool[width];
		for(uc j = 0; j < width; j++) body[i][j] = 0;
	}
	body[0][1] = body[0][2] = body[1][0] = body[1][1] = 1;
}

CZfigure::CZfigure()
{
	height = 2; width = 3;
		
	body = new bool*[height];
	for(uc i = 0; i < height; i++)
	{
		body[i] = new bool[width];
		for(uc j = 0; j < width; j++) body[i][j] = 0;
	}
	body[0][0] = body[0][1] = body[1][1] = body[1][2] = 1;
}

CLfigure::CLfigure()
{
	height = 2;
	width = 3;
		
	body = new bool*[height];
	for(uc i = 0; i < height; i++)
	{
		body[i] = new bool[width];
		for(uc j = 0; j < width; j++) body[i][j] = 0;
	}
	body[0][0] = body[1][0] = body[1][1] = body[1][2] = 1;
}

CJfigure::CJfigure()
{
	height = 2;
	width = 3;
		
	body = new bool*[height];
	for(uc i = 0; i < height; i++)
	{
		body[i] = new bool[width];
		for(uc j = 0; j < width; j++) body[i][j] = 0;
	}
	body[0][2] = body[1][0] = body[1][1] = body[1][2] = 1;
}

COfigure::COfigure()
{
	height = 2;
	width = 2;
		
	body = new bool*[height];
	for(uc i = 0; i < height; i++)
	{
		body[i] = new bool[width];
		for(uc j = 0; j < width; j++) body[i][j] = 1;
	}
}

CIfigure::CIfigure()
{
	height = 4;
	width = 1;
		
	body = new bool*[height];
	for(uc i = 0; i < height; i++)
	{
		body[i] = new bool[width];
		for(uc j = 0; j < width; j++) body[i][j] = 1;
	}
}