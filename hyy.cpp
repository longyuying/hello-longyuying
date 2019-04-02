#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


int position_x,position_y; // 飞机位置
int bullet_x,bullet_y; // 子弹位置
int enemy_x,enemy_y; // 敌机位置
int high,width; //  游戏画面尺寸
int score;

void gotoxy(int x,int y)//类似于清屏函数，光标移动到原点位置进行重画
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup() // 数据初始化
{
	high = 20;
	width = 30;
	position_x = high/2;
	position_y = width/2;
	bullet_x = -1;
	bullet_y = position_y;
	enemy_x = 0;
	enemy_y = position_y;
	score = 0;

}


void show()  
gotoxy(0,0);  // 光标移动到原点位置进行重画清屏
	int i,j;
	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
		{
			if ((i==position_x) && (j==position_y))
				printf("*"); 
			else if ((i==enemy_x) && (j==enemy_y))
				printf("@");  
			else if ((i==bullet_x) && (j==bullet_y))
				printf("|"); 
			else
				printf(" "); 
		}
		printf("\n");
	}
	printf("得分:%d\n",score);
}	

void updateWithoutInput()  // 与用户输入无关的更新
{	
	if (bullet_x>-1)
		bullet_x--; 

	if ((bullet_x==enemy_x) && (bullet_y==enemy_y)) 
	{
		score++;               
		enemy_x = -1;          
		enemy_y = rand()%width;
		bullet_x = -2;         
	}
	if (enemy_x>high)   
	{
		enemy_x = -1;          
		enemy_y = rand()%width;
	}

	// 用来控制敌机向下移动的速度。每隔几次循环，才移动一次敌机
	// 这样修改的话，用户按键交互速度还是保持很快，但我们NPC的移动显示可以降速
	static int speed = 0;  
	if (speed<30)
		speed++;
	if (speed == 30)
	{
		enemy_x++;			
		speed = 0;
	}
}

void updateWithInput()  // 与用户输入有关的更新
{
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == 'a')   
			position_y--;  
		if (input == 'd')
			position_y++;  
		if (input == 'w')
			position_x--;  
		if (input == 's')
			position_x++;  
		if (input == ' ')  
		{
			bullet_x = position_x-1;  // 发射子弹的初始位置在飞机的正上方
			bullet_y = position_y;
		}

	}
}

void main()
{
	startup();  // 数据初始化	
	while (1) //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();  // 与用户输入有关的更新
	}
}
