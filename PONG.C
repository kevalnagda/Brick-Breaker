#include<stdio.h>
#include<conio.h>
#include<graphics.h>

int gm,gd=DETECT,x_board=290,y_board=460,board_width=70,rad=5;
int x_brick=20,y_brick=20,brick_width=40,i=0,brick1[14],brick2[14],brick3[14];
int x_ball=320,y_ball=460,l=0,r=1,u=1,d=0,score=0;
char key=0,ch=0,message[250];

void game_over() {
	cleardevice();
	setcolor(RED);
	settextstyle(1, 0, 8);
	outtextxy(95,60,"GAME OVER\n");
	setcolor(GREEN);
	settextstyle(1, 0, 4);
	sprintf(message,"Your Score: %d",score);
	outtextxy(200,240,message);
	setcolor(BLUE);
	settextstyle(1, 0, 1);
	outtextxy(230,430,"Press Esc to quit\n");
	ch = getch();
	if(ch == 27) {
		exit();
	}
}

void draw_ball() {
	circle(x_ball,y_ball,rad);
	floodfill(x_ball,y_ball,WHITE);
	if(x_ball >= 620) {
		l = 1;r = 0;
	}
	else if(y_ball <= 60) {
		d=1;u=0;i=0;
		while(i<=13) {
			if(x_ball >= brick3[i] && x_ball <= brick3[i]+brick_width
				&& brick3[i] != 0) {
				brick3[i] = 0;
				score += 10;
			}
			else if(x_ball >= brick2[i] && x_ball <= brick2[i]+brick_width
				&& brick3[i] == 0 && brick2[i] != 0) {
				brick2[i] = 0;
				score += 10;
			}
			else if(x_ball >= brick1[i] && x_ball <= brick1[i]+brick_width
				&& brick3[i] == 0 && brick2[i] == 0) {
				brick1[i] = 0;
				score += 10;
			}
			i++;
		}
	}
	if(y_ball <= 20) {
		d=1;u=0;i=0;
	}
	else if(x_ball <= 20) {
		l=0;r=1;
	}
	else if(x_ball >= x_board && x_ball <= x_board+board_width &&
	 y_ball >= y_board+5) {
		u=1;d=0;
	}
	else if(y_ball >= 470) {
		game_over();
	}
	if(r == 1 && u == 1) {
		x_ball += 5;y_ball -= 5;
	}
	else if(l == 1 && u == 1) {
		x_ball -= 5;y_ball -= 5;
	}
	else if(l==1 && d==1) {
		x_ball -= 5;y_ball += 5;
	}
	else if(r ==1 && d==1) {
		x_ball += 5;y_ball += 5;
	}
	else {
		x_ball += 5;y_ball += 5;
	}

}

void draw_brick() {
	i=0;
	while(i<=13) {
		if(brick1[i] != 0) {
			rectangle(brick1[i],y_brick,brick1[i]+brick_width,y_brick+10);
			floodfill(brick1[i]+brick_width/2,y_brick+5,WHITE);
		}
		if(brick2[i] != 0) {
			rectangle(brick2[i],y_brick+12,brick2[i]+brick_width,y_brick+22);
			floodfill(brick2[i]+brick_width/2,y_brick+12+5,WHITE);
		}
		if(brick3[i] != 0) {
			rectangle(brick3[i],y_brick+24,brick3[i]+brick_width,y_brick+34);
			floodfill(brick3[i]+brick_width/2,y_brick+24+5,WHITE);
		}
		i++;
	}
	delay(7);
}

void draw_board(int x_board,int y_board) {
	rectangle(x_board,y_board,x_board+board_width,y_board+10);
	floodfill(x_board+board_width/2,y_board+5,WHITE);
}

void main() {
	initgraph(&gd,&gm," ");
	rectangle(0,0,639,479);
	while(x_brick+brick_width<=620 && i<=13) {
		brick1[i] = x_brick;
		brick2[i] = x_brick;
		brick3[i] = x_brick;
		i++;
		x_brick += brick_width+2;
	}
	draw_ball();
	draw_board(x_board,y_board);
	draw_brick();
	key = getch();
	while(key != 27 && score<=420) {
		cleardevice();
		if(kbhit()) {
			key = getch();
			if(key == 77 && x_board+board_width<=620) {
				x_board += 10;
				draw_board(x_board,y_board);
			}
			if(key == 75 && x_board>=20) {
				x_board -= 10;
				draw_board(x_board,y_board);
			}
		}
		rectangle(0,0,639,479);
		draw_ball();
		draw_board(x_board,y_board);
		draw_brick();
		delay(2);
	}
	closegraph();
}