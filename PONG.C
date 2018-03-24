#include<stdio.h>
#include<conio.h>
#include<graphics.h>

int gm,gd=DETECT,x_board=290,y_board=460,board_width=70,rad=5;
int x_brick=20,y_brick=20,brick_width=40,brick1[14],brick2[14],i=0;
int x_ball=320,y_ball=460,l=0,r=1,u=1,d=0;
char key=0;

void draw_ball() {
	circle(x_ball,y_ball,rad);
	floodfill(x_ball,y_ball,WHITE);
	if(x_ball >= 620) {
		l = 1;r = 0;
	}
	else if(y_ball <= 40) {
		d=1;u=0;i=0;
		while(i<=13) {
			if(x_ball >= brick1[i] && x_ball <= brick1[i]+brick_width &&
				brick2[i] == 0) {
				brick1[i] = 0;
			}
			if(x_ball >= brick2[i] && x_ball <= brick2[i]+brick_width) {
				brick2[i] = 0;
			}
			i++;
		}
	}
	else if(y_ball <= 20) {
		d=1;u=0;i=0;
		while(i<=13) {

			i++;
		}
	}
	else if(x_ball <= 20) {
		l=0;r=1;
	}
	else if(x_ball >= x_board && x_ball <= x_board+board_width &&
	 y_ball == y_board) {
		u=1;d=0;
	}
	else if(y_ball >= 470) {
		printf("Game Over");
		exit();
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
	delay(30);
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
		i++;
	}
}

void draw_board(int x_board,int y_board) {
	rectangle(x_board,y_board,x_board+board_width,y_board+10);
	floodfill(x_board+board_width/2,y_board+5,WHITE);
}

void main() {
	initgraph(&gd,&gm," ");
	while(x_brick+brick_width<=620 && i<=13) {
		brick1[i] = x_brick;
		brick2[i] = x_brick;
		i++;
		x_brick += brick_width+2;
	}
	key = getch();
	while(key != 27) {
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
		draw_brick();
		draw_board(x_board,y_board);
		draw_ball();
		cleardevice();
	}
	closegraph();
}