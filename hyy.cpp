#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


int position_x,position_y; // �ɻ�λ��
int bullet_x,bullet_y; // �ӵ�λ��
int enemy_x,enemy_y; // �л�λ��
int high,width; //  ��Ϸ����ߴ�
int score;

void gotoxy(int x,int y)//��������������������ƶ���ԭ��λ�ý����ػ�
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup() // ���ݳ�ʼ��
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
gotoxy(0,0);  // ����ƶ���ԭ��λ�ý����ػ�����
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
	printf("�÷�:%d\n",score);
}	

void updateWithoutInput()  // ���û������޹صĸ���
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

	// �������Ƶл������ƶ����ٶȡ�ÿ������ѭ�������ƶ�һ�εл�
	// �����޸ĵĻ����û����������ٶȻ��Ǳ��ֺܿ죬������NPC���ƶ���ʾ���Խ���
	static int speed = 0;  
	if (speed<30)
		speed++;
	if (speed == 30)
	{
		enemy_x++;			
		speed = 0;
	}
}

void updateWithInput()  // ���û������йصĸ���
{
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
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
			bullet_x = position_x-1;  // �����ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
			bullet_y = position_y;
		}

	}
}

void main()
{
	startup();  // ���ݳ�ʼ��	
	while (1) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();  // ���û������йصĸ���
	}
}
