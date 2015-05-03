#include <iostream>
#include <stdlib.h>
#include <conio.h>


#define GM_DOMAINLEN 22
using namespace std;

struct stSnakeNode
{
	int snakeX;
	int snakeY;
	char shape;
};
struct stBean
{
	int beanX;
	int beanY;
};
struct stSNAKE
{
	
		int snakeLength;
		char snakeDirection;
		int head;
		int tail;
		stSnakeNode snakeBody[100];
};


void initGmDomain(char gmDomain[][GM_DOMAINLEN]);
void displayGmDomain(char gmDomain[][GM_DOMAINLEN],int level,double score);
void updateBean(stBean& bean,const char gmDomain[][GM_DOMAINLEN]);
void updateGmDomainWithBean(stBean& bean,char gmDomain[][GM_DOMAINLEN]);


	

int main()
{
	int level = 1;
	double score = 0;
	long start;	//start time
	int moveStep = 1000000;//speed 1s
	char gmDomain[GM_DOMAINLEN][GM_DOMAINLEN];
	int currentSnakeHeadX;
	int currentSnakeHeadY;
	int currentSnakeTailX;
	int currentSnakeTailY;
	int nextSnakeHeadX;
	int nextSnakeHeadY;

	//init snakeIns  ->to refine
	stSNAKE snakeIns;
	snakeIns.head = 1;
	snakeIns.tail = 0;
	snakeIns.snakeBody[snakeIns.head].snakeX = 1;
	snakeIns.snakeBody[snakeIns.head].snakeY = 2;
	snakeIns.snakeBody[snakeIns.tail].snakeX = 1;
	snakeIns.snakeBody[snakeIns.tail].snakeY = 1;
	snakeIns.snakeDirection = 77; //right
	snakeIns.snakeLength = 2;
	
	stBean beanIns;
	initGmDomain(gmDomain);
	updateGmDomainWithBean(beanIns,gmDomain);
	

	//couting down
	cout<<"Game ready to start..."<<endl;
	for(int i=3;i>=0;i--)
		{
			start = clock();
			while (clock() - start <= 1000000){}
			system("clear");
			if(i)
				{
					cout<<"\n\n\t\tCounting down: "<<i<<"!!!"<<endl;
				}
			else
				{
					displayGmDomain(gmDomain,level,score);
				}
		}

	while(1)
		{	
			start = clock();
			bool timeflage = true;
			currentSnakeHeadX = snakeIns.snakeBody[snakeIns.head].snakeX;
			currentSnakeHeadY = snakeIns.snakeBody[snakeIns.head].snakeY;
			currentSnakeTailX = snakeIns.snakeBody[snakeIns.tail].snakeX;
			currentSnakeTailY = snakeIns.snakeBody[snakeIns.tail].snakeY;

			//wait for keyboard input or timestep out
			while((timeflage = (clock()-start<=moveStep))&&!kbhit()){}
			if(timeflage)
				{
					getch();
					snakeIns.snakeDirection = getch();
				}
			switch(snakeIns.snakeDirection)
				{
					case 72: //up
						nextSnakeHeadX = currentSnakeHeadX - 1;
						nextSnakeHeadY= currentSnakeHeadY;
						break;
					case 80: //down
						nextSnakeHeadX = currentSnakeHeadX + 1;
						nextSnakeHeadY= currentSnakeHeadY;
						break;
					case 75: //left
						nextSnakeHeadX = currentSnakeHeadX;
						nextSnakeHeadY= currentSnakeHeadY - 1;
						break;
					case 77: //right
						nextSnakeHeadX = currentSnakeHeadX;
						nextSnakeHeadY = currentSnakeHeadY + 1;
						break;
					default:
						cout<<"Game over!"<<endl;
						return 0;
				}

			//hit border
			if(0==nextSnakeHeadX|| 0==nextSnakeHeadY
				||(GM_DOMAINLEN-1)==nextSnakeHeadX ||(GM_DOMAINLEN-1)==nextSnakeHeadY)
				{
					cout<<"\tGame Over!"<<endl;
					return 0;
				}
			//hit self
			if(gmDomain[nextSnakeHeadX][nextSnakeHeadY]!=' '
				&& gmDomain[nextSnakeHeadX][nextSnakeHeadY]!='$')
				{
					cout<<"\tGame Over!"<<endl;
					return 0;
				}
			//eat bean
			if(gmDomain[nextSnakeHeadX][nextSnakeHeadY]=='$')
				{
					snakeIns.snakeLength++;
					
					if(snakeIns.snakeLength >= 8)
						{
							snakeIns.snakeLength -= 8;
							level++;
							if(moveStep > 100000)
								{
									moveStep -= 100000;
								}
						}
					score += 50*level;
					gmDomain[currentSnakeHeadX][currentSnakeHeadY] = '*';
					gmDomain[nextSnakeHeadX][nextSnakeHeadY] = '#';
					snakeIns.head = (snakeIns.head+1)%100;
					snakeIns.snakeBody[snakeIns.head].snakeX = nextSnakeHeadX;
					snakeIns.snakeBody[snakeIns.head].snakeY = nextSnakeHeadY;
					updateGmDomainWithBean(beanIns,gmDomain);
					displayGmDomain(gmDomain,level,score);
				}
			else	//just move forward
				{
					gmDomain[currentSnakeTailX][currentSnakeTailY] = ' ';
					snakeIns.tail = (snakeIns.tail+1)%100;
					gmDomain[currentSnakeHeadX][currentSnakeHeadY] = '*';
					gmDomain[nextSnakeHeadX][nextSnakeHeadY] = '#';
					snakeIns.head = (snakeIns.head+1)%100;
					snakeIns.snakeBody[snakeIns.head].snakeX = nextSnakeHeadX;
					snakeIns.snakeBody[snakeIns.head].snakeY = nextSnakeHeadY;
					displayGmDomain(gmDomain,level,score);
				}
			
		
		}
	return 0;
}

void initGmDomain(char gmDomain[][GM_DOMAINLEN])
{
	for(int i=0;i<GM_DOMAINLEN;i++)
		{
			gmDomain[i][0] = gmDomain[i][GM_DOMAINLEN-1] = '|';
		}
	for(int j=1;j<GM_DOMAINLEN-1;j++)
		{
			gmDomain[0][j] = gmDomain[GM_DOMAINLEN-1][j] = '-';
		}
	for(int i=1;i<GM_DOMAINLEN-1;i++)
		{
			for(int j=1;j<GM_DOMAINLEN-1;j++)
				{
					gmDomain[i][j]=' ';
				}
		}
	//for(int i=1;i<4;i++)
	gmDomain[1][1]='*';
	gmDomain[1][2]='#';
}

void displayGmDomain(char gmDomain[][GM_DOMAINLEN],int level,double score)
{
	system("clear");
	cout << endl << endl;
	for(int i=0;i<GM_DOMAINLEN;i++)
		{
			cout<<"\t";
			for(int j=0;j<GM_DOMAINLEN;j++)
				{
					cout<<gmDomain[i][j]<<" ";
				}
			if(0==i)
				{
					cout<<"LEVEL: "<<level;
				}
			else if(1==i)
				{
					cout<<"SCORE: "<<score;
				}
			cout<<endl;
		}
}

void updateBean(stBean & bean,const char gmDomain[][GM_DOMAINLEN])
{
	srand(time(0));
	do
		{
			bean.beanX = rand()%20 + 1;
			bean.beanY = rand()%20 + 1;	
		}
	while
		(gmDomain[bean.beanX][bean.beanY]!=' ');
	
}
void updateGmDomainWithBean(stBean& bean,char gmDomain[][GM_DOMAINLEN])
{
	updateBean(bean,gmDomain);
	gmDomain[bean.beanX][bean.beanY]='$';
}












