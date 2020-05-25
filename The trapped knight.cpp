#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <iostream>
#include <sstream>
#define mx 80
#define my 80
using namespace std;

DWORD fx=GetSystemMetrics(SM_CXSCREEN);
DWORD fy=GetSystemMetrics(SM_CYSCREEN);
int sx=50,sy=50,c;
int mat[mx][my];

void draw_matrix(int x,int y,int w){
	for(int i=0;i<=x;i++)
		line(sx+w*i,sy,sx+w*i,sy+w*x);
	for(int i=0;i<=y;i++)
		line(sx,sy+w*i,sx+w*y,sy+w*i);
}

void create_spiral_matrix(){
	int x,y,i=1,c=2,r=1;
	if(mx%2==0) x=(mx/2)-1;
	else x=mx/2;
	if(my%2==0) y=(my/2)-1;
	else y=my/2;
	while(i<=mx*my){
		mat[x][y]=i;
		if(c%4==0)
			if(r<=c/2) x--;
			else y--;
		else
			if(r<=c/2) x++;
			else y++;
		r++;i++;
		if(r>c){
			r=1;
			c+=2;
		}
	}
}

void draw(int x,int y,int a,int b,int w){
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(sx+a*w+1,sy+b*w+1,WHITE);
	setfillstyle(SOLID_FILL, RED);
	floodfill(sx+x*w+1,sy+y*w+1,WHITE);
}

main(){
	int w=15;
	char tx[5];
	initwindow(fx+100,fy+100);
	create_spiral_matrix();
	draw_matrix(mx,my,w);
	
	bool bl[mx][my]={0};
	int x,y,a,b,min=1,dx,dy;
	if(mx%2==0) x=(mx/2)-1;
	else x=mx/2;
	if(my%2==0) y=(my/2)-1;
	else y=my/2;
	a=x;
	b=y;
	while(true){
		draw(x,y,a,b,w);
		/*settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
		sprintf(tx, "%d", min);
    	outtextxy(0, 0, tx);*/
		bl[x][y]=1;
		a=x;
		b=y;
		min=mx*my+1;
		if(mat[x-1][y-2]<min && !bl[x-1][y-2]){
			min=mat[x-1][y-2];
			dx=x-1;dy=y-2;
		}
		if(mat[x+1][y-2]<min && !bl[x+1][y-2]){
			min=mat[x+1][y-2];
			dx=x+1;dy=y-2;
		}
		if(mat[x+2][y-1]<min && !bl[x+2][y-1]){
			min=mat[x+2][y-1];
			dx=x+2;dy=y-1;
		}
		if(mat[x+2][y+1]<min && !bl[x+2][y+1]){
			min=mat[x+2][y+1];
			dx=x+2;dy=y+1;
		}
		if(mat[x+1][y+2]<min && !bl[x+1][y+2]){
			min=mat[x+1][y+2];
			dx=x+1;dy=y+2;
		}
		if(mat[x-1][y+2]<min && !bl[x-1][y+2]){
			min=mat[x-1][y+2];
			dx=x-1;dy=y+2;
		}
		if(mat[x-2][y+1]<min && !bl[x-2][y+1]){
			min=mat[x-2][y+1];
			dx=x-2;dy=y+1;
		}
		if(mat[x-2][y-1]<min && !bl[x-2][y-1]){
			min=mat[x-2][y-1];
			dx=x-2;dy=y-1;
		}
		x=dx;
		y=dy;
		if(min==mx*my+1) break;
		_sleep(10);
	}
	
	getch();
	closegraph();
}
