#include "iGraphics.h"
#include<time.h>

#define box 9
#define row 3
#define column 3

//integers
int screen_width=600;
int screen_height=600;
int uodMove=box/column;
int lorMove=1;

//point ball
int eatMe;
int eatMeX;
int eatMeY;
int eatMeR=12;

//white ball
int position;
int eaterX;
int eaterY;
int eaterR=15;

//black ball
int destroyerX;
int destroyerY;
int destroyerR=20;
int dx;
int dy;

//pair black ball
int pairX;
int pairY;
int pairR=20;
int pairdx;
int pairdy;


//flag
int flag;		  // check from where black ball comes
int firstTime=1;  // for the first black ball to come
int touch=0;     // check whether black ball touches white ball or not
int start=1;
int level2=0;
int level3=0;
int iflag;
int iflag1;
int score;

//char
char showScore[10];


//function
void destroyerMove(void);

void initialize (void)
{
	if(start) 
	{
	position=4;
	srand(time(NULL));
	int random =  rand() % 8;
	while(random!=position) {eatMe=random; break;}
	score=0;
	destroyerX=0;
	destroyerY=0;
	firstTime=1;
	touch=0;
	flag=0;
	level2=0;
	level3=0;
	}

}

void destroy(void)
{
	srand(time(NULL));
	int random =  rand() % 5;

	if(random<3)
		{
			srand(time(NULL));
			int r1=rand() % 9;
			if(r1<3) destroyerX=200;
			else if (r1<6) destroyerX=300;
			else  destroyerX=400;
		

				srand(time(NULL));
				int r2 =  rand() % 5;
				if(r2%2) destroyerY=0;
				else destroyerY=600;
			
		}
	else
		{
			srand(time(NULL));
			int r1=rand() % 9;
			if(r1<3) destroyerY=200;
			else if (r1<6) destroyerY=300;
			else  destroyerY=400;

			srand(time(NULL));
			int r2 =  rand() % 5;
			if(r2%2) destroyerX=0;
			else destroyerX=600;

		}

	destroyerMove();
	
}
void destroyerMove(void)
{
	if(destroyerX==0) 	{dx=1;dy=0;flag=1;pairX=600;pairdx=-1;pairdy=0;}
	else if(destroyerX==600) {dx=-1;dy=0;flag=2;pairX=0;pairdx=1;pairdy=0;}
	else if(destroyerY==0) {dy=1;dx=0;flag=3;pairY=600;pairdy=-1;pairdx=0;}
	else if(destroyerY==600) {dy=-1;dx=0;flag=4;pairY=0;pairdy=1;pairdx=0;}
	if(level2 )
	{
	if(flag==1 || flag==2) 
	{
		if	   (destroyerY==200) pairY=400;
		else if(destroyerY==300) pairY=300;
		else if(destroyerY==400) pairY=200;
	}
	else if(flag==3 || flag==4) 
	{
		if	   (destroyerX==200) pairX=400;
		else if(destroyerX==300) pairX=300;
		else if(destroyerX==400) pairX=200;
	}
	
	
	if(level3)
	{
		if(flag==1 || flag==2) 
	{
		srand(time(NULL));
		int r=rand() % 9;
		if	   (destroyerY==200) {pairY=300;pairX=destroyerX; pairdx=dx;pairdy=dy;}
		else if(destroyerY==300) 
		{
			if(r>4) {pairY=400;pairX=destroyerX;pairdx=dx;pairdy=dy;}
			else {pairY=200;pairX=destroyerX;pairdx=dx;pairdy=dy;}
		}
		else if(destroyerY==400) {pairY=300;pairX=destroyerX;pairdx=dx;pairdy=dy;}
	}
	else if(flag==3 || flag==4) 
	{		
		srand(time(NULL));
		int r1=rand() % 9;
		if	   (destroyerX==200) {pairX=300;pairY=destroyerY;pairdx=dx;pairdy=dy;}
		else if(destroyerX==300) 
		{
			if(r1>4) {pairX=400;pairY=destroyerY;pairdx=dx;pairdy=dy;}
			else {pairX=200;pairY=destroyerY;pairdx=dx;pairdy=dy;}
		}
		else if(destroyerX==400) {pairX=300;pairY=destroyerY;pairdx=dx;pairdy=dy;}
	}

	}
}
}
void centrePoint(void)
{
	eaterX=200+(position%3)*100;
	eaterY=200+(position/3)*100;

	srand(time(NULL));
	int random =  rand() % 8;
	
	if(position==eatMe) 
	{
		
		while(random!=position) {eatMe=random;score++; break; }
	}

	eatMeX=200+(eatMe%3)*100;
	eatMeY=200+(eatMe/3)*100;

	
}

void drawDestroyer(void)
{
	if(score==9) {if(iflag==0) 
		level2=1;}
	else if(score==19)
	{
		if(iflag1==0) 
		{
			level3=1;
			
		}
	}


	if (firstTime==1)
	{
		destroy();
		firstTime=0;
		
	}
	else
	{
		if((flag==1 && destroyerX==600) || (flag==2 && destroyerX==0) ||( flag==3 && destroyerY==600) ||(flag==4 && destroyerY==0) )
			{
				if(score==9) iflag=0;
				else {iflag=1;}
				if(score==19) iflag1=0;
				else if(score>4) {iflag1=1;}
				destroy();		
			}
	}
		if(
			(((destroyerX>=eaterX && destroyerY>=eaterY) && (destroyerX-eaterX <=30 && destroyerY-eaterY<=30 ))  
										||
			((destroyerX<=eaterX && destroyerY<=eaterY) && (destroyerX-eaterX >=-30 && destroyerY-eaterY>=-30 ))) 
										||
			(((pairX>=eaterX && pairY>=eaterY) && (pairX-eaterX <=30 && pairY-eaterY<=30 ))  
										||
			((pairX<=eaterX && pairY<=eaterY) && (pairX-eaterX >=-30 && pairY-eaterY>=-30 ))) 

			)
		{
			touch=1;
			start=0;
		}
		if(touch==0) 	
		{
			iSetcolor(0,0,0);
			destroyerY+=dy;
			destroyerX+=dx;
			iFilledCircle(destroyerX,destroyerY,destroyerR,200);
			if((level2 && iflag) || (level3 && iflag1))
			{
				pairY+=pairdy;
				pairX+=pairdx;
				iFilledCircle(pairX,pairY,pairR,200);
				if(level3)printf ("%d %d %d ",level3 ,destroyerX,pairX);
			
			}
			
		}

		

}
void drawLevel(void)
{
	iSetcolor(0,0,1);
	if(level3)
	iText(270, 550, "Level 3", GLUT_BITMAP_HELVETICA_18);
	else if(level2) iText(270, 550, "Level 2", GLUT_BITMAP_HELVETICA_18);
	else iText(270, 550, "Level 1", GLUT_BITMAP_HELVETICA_18);
	
}
void drawBackground(void)
{
	iSetcolor(.7,.5,.5);
	iFilledRectangle(0,0,screen_width,screen_height);
	iSetcolor(1,1,1);
	iRectangle(screen_width/4,screen_height/4,screen_width/2,screen_height/2);

	for(int i=1;i<3;i++)
	{
		iLine(screen_width/4+i*(screen_width/6),screen_height/4,screen_width/4+i*(screen_width/6),screen_height/4+screen_height/2);
		iLine(screen_width/4,screen_height/4+i*(screen_height/6),screen_width/4+screen_width/2,screen_height/4+i*(screen_height/6));
	}
}
void drawPointnball(void)
{
	centrePoint();
	iSetcolor(1,1,1);
	iFilledCircle(eaterX,eaterY,eaterR,200);
	iSetcolor(0,0,1);
	iFilledCircle(eatMeX,eatMeY,eatMeR,4);
}
void printScore(int scr)
{
	iSetcolor(0,0,1);
	sprintf_s(showScore, " %d", score);
	iText(270, 500, "POINT", GLUT_BITMAP_HELVETICA_18);
	iText(280, 480, showScore, GLUT_BITMAP_HELVETICA_18);
}
void gameOver(void)
{
	iSetcolor(.7,.5,.5);
	iFilledRectangle(0,0,screen_width,screen_height);
	iSetcolor(0,0,1);
	if(score==30) iText(250, 400, "YOU WIN", GLUT_BITMAP_HELVETICA_18);
	iText(270, 305, "POINT", GLUT_BITMAP_HELVETICA_18);
	iText(280, 285, showScore, GLUT_BITMAP_HELVETICA_18);
	iRectangle(240,200,135,60);
	iText(255, 220, "PLAY AGAIN", GLUT_BITMAP_HELVETICA_18);

}
void iDraw()
{
	iClear();
	if(start)
	{
	drawBackground();
	drawPointnball();
	printScore(score);
	drawDestroyer();
	drawLevel();
	}
	else gameOver();
	if(score==30) {gameOver(); start=0;}
	
	
}

void iKeyboard(unsigned char key)
{
	if (key=='q' || key=='Q') exit(0);
	if(key=='d' || key=='D') 
	{
		if(position%3!=2) position+=lorMove;
	}
	else if(key=='a' || key=='A') 
	{
		if(position%3!=0) position-=lorMove;

	}
	else if(key=='w' || key=='W') 
	{
		if(position<6) position+=uodMove;
	}
	else if(key=='s' || key=='S') 
	{
		if(position>2) position-=uodMove;
	}
	else if(key==' ' ) 
	{
		if(!start)
		{
			start=1;initialize();
		}
	}

	

}
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(!start)
		{
			if(mx<=375 && mx>=240 && my<=260 &&my>=200 ) {start=1;initialize();}
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){}

}
void iMouseMove(int mx, int my){}


int main()
{
	
	initialize();
	iInitialize(600,600,"SMOVE...");
	return 0;
}
