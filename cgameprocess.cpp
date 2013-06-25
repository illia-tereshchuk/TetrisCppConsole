#include "cgameprocess.h"

void CGameProcess::MainMenu()
{
	NoCursor(); //С самого запуска программы скрываем курсор
	uc control = 5; //Положение курсора
	char keypressed = 0; //Нажатая клавіша

	system("cls"); //Очистка экрана перед переходом к меню

	Menu.Draw();
		
	Menu.SetCursorToRow(1); cout<<"\t\t     Т Е Т Р И C"; //Заголовок
	Menu.SetCursorToRow(4); cout<<"\t---------------------------------------";
	Menu.SetCursorToRow(5); cout<<"\tНовая игра"; //Позиция: 5
	Menu.SetCursorToRow(6); cout<<"\t---------------------------------------";
	Menu.SetCursorToRow(9); cout<<"\t---------------------------------------";
	Menu.SetCursorToRow(10); cout<<"\tЗагрузить из файла"; //Позиция: 10
	Menu.SetCursorToRow(11); cout<<"\t---------------------------------------";
	Menu.SetCursorToRow(14); cout<<"\t---------------------------------------";
	Menu.SetCursorToRow(15); cout<<"\tПро программу"; //Позиция: 15
	Menu.SetCursorToRow(16); cout<<"\t---------------------------------------";
	Menu.SetCursorToRow(19); cout<<"\t---------------------------------------";
	Menu.SetCursorToRow(20); cout<<"\tВыход"; //Позиция: 20
	Menu.SetCursorToRow(21); cout<<"\t---------------------------------------";

	while(keypressed != 13)
	{
		Menu.SetCursorToRow(control); cout<<" ---->"; //Установим стрелку на соответствующую позицию
			
		keypressed = _getch();
		//Если клавиша является одной из управляющих - считываем второй байт
		if(keypressed == -32) keypressed = _getch(); 
		//Если клавиша является одной из управляющих - стираем стрелку с текущей позиции
		if((keypressed == 80 || keypressed == 72)) Menu.SetCursorToRow(control); cout<<"      ";
			
		switch(keypressed)
		{
		case 72: if(control != 5) control -= 5; break;
		case 80: if(control != 20) control += 5;
		}
	}
	Menu.Erase(); 
	
	switch(control)
	{
		case 5: StartGame(); break;
		case 10: LoadFromFile(); break; 
		case 15: AboutInfo(); break; 
		case 20: exit(0);
	}
}

void CGameProcess::NoCursor() const 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.bVisible = false;
	ConCurInf.dwSize = 10;
	SetConsoleCursorInfo(hConsole, &ConCurInf);
}

void CGameProcess::AboutInfo()
{
	system("cls");
	
	About.Draw();

	//About.SetCursorToRow(1); cout<<"\t     КА ШАГ, Курсовая работа по ООП С++";
	About.SetCursorToRow(2); cout<<"Название:\tТетрис";
	About.SetCursorToRow(4); cout<<"Автор:\t\tТерещук Илья";
	About.SetCursorToRow(6); cout<<"Дата:\t\t01 августа 2012";
	//About.SetCursorToRow(14); cout<<"Поток:\t\t19HC9 - 1С ПР";
	//About.SetCursorToRow(17); cout<<"Дата:\t01 августа 2012";
	About.SetCursorToRow(10); cout<<"\t\tНажмите любую клавишу";
		
	_getch();

	About.Erase();
		
	MainMenu();
}

void CGameProcess::CreateMatrix()
{
	system("cls");
		
	MatrixCreationDialog.Draw();

	us width = 0, height = 0;

	while(width > 50 || width < 10)
	{
		MatrixCreationDialog.ClearRow(2);
		MatrixCreationDialog.SetCursorToRow(2);
		cout<<"  Введите ширину поля (10 - 50): "; cin>>width;
	}

	while(height > 40 || height < 20)
	{
		MatrixCreationDialog.ClearRow(5);
		MatrixCreationDialog.SetCursorToRow(5);
		cout<<"  Введите высоту поля (20 - 40): "; cin>>height;
	}

	field = new Cmatrix(width, height + 1);

	MatrixCreationDialog.SetCursorToRow(10); cout<<"\tНажмите любую клавишу";

	_getch();
		
	MatrixCreationDialog.Erase();
}

void CGameProcess::StartGame()
{
	system("cls");
		
	SelectObject(hDC, Edge_Pen);

	if(IngameMenu) delete IngameMenu;
	if(ScoreTable) delete ScoreTable;
	if(Glass) delete Glass;
	ScoreTable = Glass = IngameMenu = NULL;
	
	score = 0;

	CreateMatrix();
	
	IngameMenu = new Cframe(field->width * 15 + 20, 90, 200, 235, 2, 0, 0, 255);
	ScoreTable = new Cframe(field->width * 15 + 20, 5, 200, 80, 2, 255, 0, 0);
	Glass = new Cframe(5, 5, (field->width) * 15 + 5, (field->height) * 15 + 5, 2, 0, 0, 0);
	
	Glass->Draw();
	DrawField();

	while(1) { FigureFall(); }
		
	_getch();
}

void CGameProcess::DrawField() const
{
	for(uc i = 0; i < field->height; i++)
		for(uc j = 0; j < field->width; j++)
			if(field->field[i][j])
			{
				SelectObject(hDC, Edge_Pen);
				Rectangle(hDC, 15*j + 10, 15*i + 10, 15*(j+1) + 8, 15*(i+1) + 8);
			}
			else
			{
				SelectObject(hDC, Erase_Pen);
				Rectangle(hDC, 15*j + 10, 15*i + 10, 15*(j+1) + 8, 15*(i+1) + 8);
			}
}

void CGameProcess::FigureErase(Cshape *Random, const uc &ins_y, const uc &ins_x)
{
	for(us i = 0; i < Random->height; i++)
			for(us j = 0; j < Random->width; j++)
				if(Random->body[i][j]) field->field[ins_y + i][ins_x + j] = 0;
}

void CGameProcess::FigureInsert(Cshape *Random, const uc &ins_y, const uc &ins_x)
{
	for(us i = 0; i < Random->height; i++)
			for(us j = 0; j < Random->width; j++)
				if(Random->body[i][j]) field->field[ins_y + i][ins_x + j] = 1;
}

bool CGameProcess::FigureRotate(Cmatrix *field, Cshape *Random, const uc &ins_y, const uc &ins_x)
{
	if(field->width - ins_x >= Random->height && field->height - ins_y >= Random->width)
	{
		if(Random->height > Random->width)
		{
			for(uc i = 0; i < Random->height; i++)
				for(uc j = 0; j < Random->height; j++)
					if(field->field[ins_y + i][ins_x + Random->width - 1 + j]) return false;
		}
		
		else
		{
			for(uc i = 0; i < Random->width; i++)
				for(uc j = 0; j < Random->width; j++)
					if(field->field[ins_y + Random->height -1 + i][ins_x + j]) return false;
		}
		Random->Rotate();
	}
	return false;
}

bool CGameProcess::FigureStopCheck(Cshape *Random, const uc &ins_y, const uc &ins_x) const
{
	if(ins_y < field->height - Random->height)
		for(uc i = 0; i < Random->height; i++)
			for(uc j = 0; j < Random->width; j++)
				if(Random->body[i][j])
				{
					if(i < Random->height - 1 && !Random->body[i + 1][j] && field->field[i + ins_y + 1][j + ins_x]) return true;
					if(i == Random->height - 1 && Random->body[i][j] && field->field[i + ins_y + 1][j + ins_x]) return true;
				}
	return false;
}

Cshape *CGameProcess::SetRandomShape() const
{
	switch(rand() % 7)
	{
		case 0: return new CTfigure;
		case 1: return new CZfigure;
		case 2: return new CSfigure;
		case 3: return new CLfigure;
		case 4: return new CJfigure;
		case 5: return new COfigure;
		case 6: return new CIfigure;
	}
	return new CTfigure;
}

bool CGameProcess::FigureFall()
{
	Cshape *Random = SetRandomShape();
		
	register char ingamectrl = 0;

	uc ins_x = (field->width - Random->width) / 2, ins_y = 1;

	FieldCheck(); 
	
	while(ins_y <= field->height - Random->height) //Пока фигура не на дне
	{
		SetScores();
		
		FigureInsert(Random, ins_y, ins_x);
			
		for(uc i = 0; i < 25; i++)
		{
			if(_kbhit())
			{
				ingamectrl = _getch(); if(ingamectrl == -32) ingamectrl = _getch();
			
				switch(ingamectrl)
				{
					case 27: FigureErase(Random, ins_y, ins_x); IngameOptions(); break;
				
					case 72: FigureErase(Random, ins_y, ins_x); FigureRotate(field, Random, ins_y, ins_x); break;
					
					case 75: if(FigureLeftMoveCheck(Random, ins_y, ins_x)) { FigureErase(Random, ins_y, ins_x); ins_x--; } break;
					
					case 77: if(FigureRightMoveCheck(Random, ins_y, ins_x)) { FigureErase(Random, ins_y, ins_x); ins_x++; } break;
					
					case 80: FigureInsert(Random, ins_y, ins_x);
						if(!FigureStopCheck(Random, ins_y, ins_x) && ins_y < field->height - Random->height - 1)
						{
							FigureErase(Random, ins_y, ins_x); ins_y++;
						}
				}
			
				FigureInsert(Random, ins_y, ins_x);
			
			}
				
			Sleep((1000 - 50 * 1) / 25);
			
			DrawField();
		}
			
		if(FigureStopCheck(Random, ins_y, ins_x)) { DrawField(); return true; }
			
		if (ins_y < field->height - Random->height) FigureErase(Random, ins_y, ins_x); ins_y++;
	}
	
	delete Random;

	return 0;
}

bool CGameProcess::FigureLeftMoveCheck(Cshape *Random, const uc &ins_y, const uc &ins_x) const
{
	if(ins_x)
	{
		for(uc i = ins_y; i < ins_y + Random->height; i++)
			if(field->field[i][ins_x - 1] && field->field[i][ins_x]) return false;

		return true;
	}
	return false;
}

bool CGameProcess::FigureRightMoveCheck(Cshape *Random, const uc &ins_y, const uc &ins_x) const
{
	if(ins_x < field->width - Random->width)
	{
		for(uc i = ins_y; i < ins_y + Random->height; i++)
			if(field->field[i][ins_x + Random->width] && field->field[i][ins_x + Random->width - 1]) return false;
			
		return true;
	}
	return false;
}

void CGameProcess::MatrixEraseRow(const uc &row_index)
{
	for(uc i = row_index; i > 0; i--)
		for(uc j = 0; j < field->width; j++)
			field->field[i][j] = field->field[i-1][j];
}
	
void CGameProcess::FieldCheck()
{
	uc lines_erased = 0;
		
	for(uc j = 0; j < field->width; j++) if(field->field[1][j]) GameOver();
		
	for(uc i = 0; i < field->height; i++)
		for(uc j = 0; j < field->width; j++)
		{
			if(!field->field[i][j]) break;
			if(j == field->width - 1) { MatrixEraseRow(i); lines_erased++; }
		}

	switch(lines_erased)
	{
		case 1: score += 1; break;
		case 2: score += 3; break;
		case 3: score += 10; break;
		case 4: score += 25; break;
	}
}

void CGameProcess::SaveToFile()
{
	if(SaveMenu) { delete SaveMenu; SaveMenu = NULL; }
	SaveMenu = new Cframe(field->width * 15 + 20, 90, 200, 150, 2, 255, 0, 0);
	SaveMenu->Draw();
	char filename[128];
	SaveMenu->SetCursorToRow(1); cout<<"Имя файла:";
	SaveMenu->SetCursorToRow(3); cin>>filename;
	FILE *savegame = fopen(filename, "w");
	fprintf(savegame, "%u\n%u\n%u\n", score, field->width, field->height);
	for(uc i = 0; i < field->height; i++)
	{
		for(uc j = 0; j < field->width; j++) fprintf(savegame, "%u ", field->field[i][j]);
		fprintf(savegame, "\n");
	}
	fclose(savegame);

	SaveMenu->Erase();
}

void CGameProcess::LoadFromFile()
{
	system("cls");
		
	char filename[128];
		
	LoadMenu.Draw();
		
	LoadMenu.SetCursorToRow(1); cout<<"\t\t  ЗАГРУЗКА ИЗ ФАЙЛА";
	
	LoadMenu.SetCursorToRow(5); cout<<"Введите имя файла:";

	LoadMenu.SetCursorToRow(9); cin>>filename;

	FILE *savegame = fopen(filename, "r");

	if(!savegame)
	{
		LoadMenu.SetCursorToRow(13); cout<<"Файл не существует";
		LoadMenu.SetCursorToRow(17); cout<<"Нажмите любую клавишу"; _getch(); MainMenu();
	}
	else
	{
		us temp_width = 0, temp_height = 0;
			
		fscanf(savegame, "%u\n%u\n%u\n", &score, &temp_width, &temp_height);
			
		if(field) { delete field; field = NULL; }
		field = new Cmatrix(temp_width, temp_height);

		for(us i = 0; i < temp_height; i++)
		{
			for(uc j = 0; j < temp_width; j++) fscanf(savegame, "%u ", &field->field[i][j]);
			fscanf(savegame, "\n");
		}

		fclose(savegame);

		LoadMenu.Erase();
			
		if(IngameMenu) delete IngameMenu;
		if(ScoreTable) delete ScoreTable;
		if(Glass) delete Glass;
		ScoreTable = Glass = NULL;

		IngameMenu = new Cframe(field->width * 15 + 20, 90, 200, 235, 2, 0, 0, 255);
		ScoreTable = new Cframe(field->width * 15 + 20, 5, 200, 80, 2, 255, 0, 0);
		Glass = new Cframe(5, 5, (field->width) * 15 + 5, (field->height) * 15 + 5, 2, 0, 0, 0);
			
		Glass->Draw();
			
		SetScores();
			
		while(1) FigureFall();
	}
}

void CGameProcess::SetScores() const
{
	ScoreTable->Draw();
	ScoreTable->SetCursorToRow(1); cout<<"  Очки: "<<score;
	ScoreTable->SetCursorToRow(3); cout<<"  ESC - меню";
}

void CGameProcess::IngameOptions()
{
	IngameMenu->Draw();

	uc control = 1;
	char keypressed = 0;
		
	IngameMenu->SetCursorToRow(1); cout<<"\t Продолжить";
	IngameMenu->SetCursorToRow(3); cout<<"\t Сохранить";
	IngameMenu->SetCursorToRow(5); cout<<"\t В главное меню";
	IngameMenu->SetCursorToRow(7); cout<<"\t Выход";

	while(keypressed != 13)
	{
		IngameMenu->SetCursorToRow(control); cout<<" ->";
			
		keypressed = _getch();
			
		if(keypressed == -32) keypressed = _getch(); 
		
		if((keypressed == 80 || keypressed == 72)) IngameMenu->SetCursorToRow(control); cout<<"   ";
			
		switch(keypressed)
		{
		case 72: if(control != 1) control -= 2; break;
		case 80: if(control != 7) control += 2;
		}
	}
	IngameMenu->Erase();
	
	switch(control)
	{
		case 1: break; 
		case 3: SaveToFile(); break; 
		case 5: ScoreTable->Erase(); Glass->Erase(); MainMenu(); break; 
		case 7: exit(0);
	}
}

CGameProcess::CGameProcess(): score(0), field(NULL), Menu(250, 180, 450, 330, 4, 0, 0, 0),
	MatrixCreationDialog(250, 200, 400, 200, 4, 0, 0, 0), About(250, 200, 450, 180, 4, 0, 0, 0), LoadMenu(250, 180, 450, 330, 4, 0, 0, 0),
	ScoreTable(NULL), Glass(NULL), IngameMenu(NULL), SaveMenu(NULL)
{
	hDC = GetDC(GetConsoleWindow());
	Edge_Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	Erase_Pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}