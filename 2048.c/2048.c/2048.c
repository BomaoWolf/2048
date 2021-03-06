// 2048.c.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "stdlib.h"
#include "stdio.h"
#include "2048.h"
#include "conio.h"
#include "windows.h"

int ColorX, ColorY;
int GameZone[4][4];
int Score=0;
int GameState=0;
int GameEmpty=0;

/*int TestZone[4][4] = {
	{2,4,8,16},
    {4,8,16,2},
	{8,16,2,4},
    {16,2,4,8}
};*/


void color(x)	//自定义函根据参数改变颜色 
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void CreateGame(int GameZone[4][4])					//直接GameZone可不可以
{
	int i = 0, j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			GameZone[i++][j++] = 0;
		}
	}
	int x, y;
	srand(time(0));
	x = rand() % 4;
	y = rand() % 4;
	GameZone[x][y] = 2;
	ColorX = x;
	ColorY = y;
}

void Print(int GameZone[4][4]) 
{
	system("cls");
	printf("Your score is %d!\n",Score);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i==ColorX&&j==ColorY)
			{
				color(15);		printf("%d\t", GameZone[i][j]);
				continue;
			}
			color(16); 
			printf("%d\t", GameZone[i][j]);
		}
		printf("\n");
	}
}

void JudgeGameLine(int GameZone[4][4])							//判断横竖列是否还有移动的可能 有就为1
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (GameZone[j][i] == GameZone[j + 1][i]) 
			{
				GameState = 1;								//1是游戏还可以继续的意思
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (GameZone[j][i] == GameZone[j ][i+1])
			{
				GameState = 1;								//1是游戏还可以继续的意思
			}
		}
	}
}

int GameOver(int GameZone[4][4]) 
{
	GameEmpty = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (GameZone[i][j]==0)
			{
				GameEmpty = 1;
				return 1;
			}
		}
	}
	if (GameState==0)
	{
		return 0;
	}
	return 1;
}

void StepRandNum(int GameZone[4][4]) 
{
	int x, y;
	if (!GameOver(GameZone))
	{
		printf_s("GameOver! Good luck next time!\n");
		exit(0);
	}
	GameState = 0;
	if (GameEmpty == 1)
	{
		do
		{
			x = rand() % 4;
			y = rand() % 4;
		} while (GameZone[x][y] != 0);
	GameZone[x][y] = 2;
	ColorX = x;
	ColorY = y;
	}
}

int Move(int a[4])
{
	int i = 0, j = 0;

	for (i = 1; i < 4; ++i) 
	{	
		int ZeroFlag=0;
		for (int k = i-1; k < 4; ++k)			//判断a[i]的后面是否全为0
		{
			if (a[k]!=0)
			{
				ZeroFlag = 1;					//==1时不全为0
			}
		}
		if (ZeroFlag == 0) 			
		{
			return OK;								//当a[i]后面全为0时，这一行已经不用再变动了，return
		}

		if (a[i-1]==0)
		{
			for (int j = i-1; j < 3; ++j)					//这个循环
			{
				a[j] = a[j + 1];
			}
			a[3] = 0;
			i = i - 1;
		}
		if (a[i-1]==a[i])
		{
			Score = Score+a[i - 1] + a[i];
			a[i - 1] = a[i - 1] + a[i];
			a[i] = 0;
			GameState = 1;						//==1时行还有移动的机会
		}
	}
	JudgeGameLine(GameZone);
	return OK;
}

void UpMove(int GameZone[4][4]) 
{
	int line[4],i,j;
	for (i = 0; i < 4; ++i) 
	{
		for ( j = 0; j < 4; j++)
		{
			line[j]=GameZone[j][i];
		}
		Move(line);
		for ( j = 0;  j < 4;  j++)
		{
			GameZone[j][i] = line[j];
		}
	}
	StepRandNum(GameZone);
	Print(GameZone);


}

void DownMove(int GameZone[4][4])
{
	int line[4], i, j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; j++)
		{
			line[j] = GameZone[3-j][i];
		}
		Move(line);
		for (j = 0; j < 4; j++)
		{
			GameZone[3-j][i] = line[j];
		}
	}
	StepRandNum(GameZone);
	Print(GameZone);


}

void LeftMove(int GameZone[4][4])
{
	int line[4], i, j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; j++)
		{
			line[j] = GameZone[i][j];
		}
		Move(line);
		for (j = 0; j < 4; j++)
		{
			GameZone[i][j] = line[j];
		}
	}
	StepRandNum(GameZone);
	Print(GameZone);


}

void RightMove(int GameZone[4][4])
{
	int line[4], i, j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; j++)
		{
			line[j] = GameZone[i][3-j];
		}
		Move(line);
		for (j = 0; j < 4; j++)
		{
			GameZone[i][3-j] = line[j];
		}
	}
	StepRandNum(GameZone);
	Print(GameZone);


}


void main()
{
	//int flag=1;
	char Step;						//每一步的上下左右
	CreateGame(GameZone);
	Print(GameZone);
	while (1) 
	{
		if(_kbhit)
		{
		//	scanf_s("%c", &Step);
			Step = _getch();
		}
		switch (Step)
		{
		case 'a':
			LeftMove(GameZone); break;
		case 'd':
			RightMove(GameZone); break;
		case 'w':
			UpMove(GameZone); break;
		case 's':
			DownMove(GameZone); break;
		default:
			break;
		}

	}
	

}

