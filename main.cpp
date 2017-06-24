#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include"Matrix.h"
#include<dos.h>
#include<complex>
#include<iostream>
#include<stdlib.h>

#define max_iterations  1000
#define scale 70
#define shiftX 21200
#define shiftY 0
#define shiftColor 3

#define X_OFFSET 0
#define Y_OFFSET -150


////
//Hilbert's curve

#define DEL 0
double MaxY = 700;//479
//point has two cordinates,one for the left side and other for the right side
typedef struct hpoint{
	double lx,ly,rx,ry;
};
 
//direction enum has right = 0, up = 1,left = 2, down = 3
/*
enum direction {
	right,
	up,
	left,
	down
	};
*/
typedef int direction;
char a[][6] = {"right","up","left","down"};
void printd(direction d){
	printf("%s,%d",a[d],d);
}

void print(hpoint* a){
	//printf("lx = %f, ly = %f rx = %f, ry = %f\n",a->lx,a->ly,a->rx,a->ry);
}
//when rotating a direction pointing to
//right clockwise it returns 3 ie. down
int rotateCW(direction dir)
{
	if(dir == 0)
	return 3;
	else {
		int t = dir;
		return (--t);
	}
}
//when rotating a direction pointing to
//down anticlockwise it returns 0 ie. right
int rotateACW(direction dir){
	if(dir == 3)
	return 0;
		else {
		int t = dir;
		return (++t);
	}
}
//It draws a line between a's left point to b's right point
//and between b's right point to c's left point
//and between c's right point to d's right point
void join(hpoint *a,hpoint *b,hpoint *c,hpoint *d){
	line(a->lx, MaxY - a->ly, b->lx, MaxY - b->ly);
	delay(DEL);
	line(b->rx, MaxY - b->ry, c->lx, MaxY - c->ly);
	delay(DEL);
	line(c->rx, MaxY - c->ry, d->rx, MaxY - d->ry);
	delay(DEL);
}
//returns a struct:point whith left point as a's right point
//and right point as b's left point
hpoint *ret(hpoint *a, hpoint *b){
	  hpoint *r = (hpoint *) malloc(sizeof(hpoint));
	  r->lx = a->rx;
	  r->ly = a->ry;
	  r->rx = b->lx;
	  r->ry = b->ly;

	  return r;
}
//the x0,y0 is the coordinate of the lower left corner of the box
//L is size of the box in which Hilbert's curve will be drawn
//n is the number of approximation
//dir is where the curve will be pointing
hpoint* hilbert(double x0,double y0, double L, int n, direction dir){
	if(n == 0){
		//base case
		hpoint * p = (hpoint *) malloc(sizeof(hpoint));
		p->lx = x0 + L/2;
		p->rx = x0 + L/2;
		p->ly = y0 + L/2;
		p->ry = y0 + L/2;
		//printf("Returned:");
		print(p);
		putpixel(p->lx,MaxY - p->ly,WHITE);
		return p;

	}
	hpoint *a,*b,*c,*d;
	int p,q,r,s;
//Depending on the current direction, directions of four smaller box is found
	switch(dir){
		case 0: //right
			p = rotateACW(dir);
			q = rotateCW(dir);
			r = dir;
			s = dir;
			break;
		case 1: //up
			p = rotateCW(dir);
			q = dir;
			r = dir;
			s = rotateACW(dir);
			break;
		case 2: //left
			p = dir;
			q = dir;
			r = rotateACW(dir);
			s = rotateCW(dir);
			break;
		case 3: //down
			p = dir;
			q = rotateACW(dir);
			r = rotateCW(dir);
			s = dir;
			break;
	}
/*


	[b][c]
	[a][d]
*/
	a = hilbert(x0, y0, L/2, n-1, p);
	b = hilbert(x0, y0 + L/2, L/2, n-1, q);
	c = hilbert(x0 + L/2, y0 + L/2, L/2, n-1, r);
	d = hilbert(x0 + L/2, y0, L/2, n-1, s);
	//join the dots
	hpoint *next;
	switch(dir){
		case 0:
			join(b,c,d,a);
			next = ret(b,a);
			break;
		case 1:
			join(a,b,c,d);
			next = ret(a,d);
			break;
		case 2:
			join(d,a,b,c);
			next = ret(d,c);
			break;
		case 3:
			join(c,d,a,b);
			next = ret(c,b);
	}
	free(a);
	free(b);
	free(c);
	free(d);
	return next;
}


////


void mandelbrot();
void  drawLines(const matrix & a){
	if(a.r < 1){
		cout<<"Error: in drawLines , row < 1 "<<endl;
		return;	
	}
	if(a.r == 1)
		putpixel((getmaxx() + X_OFFSET )/2 + a.m[0][0],(getmaxy()+Y_OFFSET )/2 - a.m[0][1],WHITE);
	else
	for(int i = a.r - 1; i > 0; i--){
		line((getmaxx()+ X_OFFSET )/2 + a.m[i][0],(getmaxy()+Y_OFFSET )/2 - a.m[i][1],(getmaxx()+X_OFFSET )/2 + a.m[i-1][0],(getmaxy()+Y_OFFSET )/2 - a.m[i-1][1]);
		delay(5);
	}
}
void  drawPolygon(const matrix & a){
	if(a.r < 1){
		cout<<"Error: in drawPolygon , row < 1 "<<endl;
		return;	
	}
	if(a.r == 1)
		putpixel(getmaxx()/2 + a.m[0][0],getmaxy()/2 - a.m[0][1],WHITE);
	else{
	
		int i;
		for( i = 0; i < a.r - 1 ; i++){
			line(getmaxx()/2 + a.m[i][0],getmaxy()/2 - a.m[i][1],getmaxx()/2 + a.m[i+1][0],getmaxy()/2 - a.m[i+1][1]);
		}
		
		
		line(getmaxx()/2 + a.m[i][0],getmaxy()/2 - a.m[i][1],getmaxx()/2 + a.m[0][0],getmaxy()/2 - a.m[0][1]);
	}
}
matrix append(const matrix & m, const matrix & nm){

	matrix ans = make(m.r + nm.r - 1 , nm.c);
	int j = 0; 
	for(int i = nm.r -1 ; i >= 0; i--,j++){
		ans.m[j][0] = nm.m[i][0];
		ans.m[j][1] = nm.m[i][1];	
		ans.m[j][2] = 1;
	}
	for(int i = 1; i < m.r; i++,j++){
		ans.m[j][0] = m.m[i][0];
		ans.m[j][1] = m.m[i][1];
		ans.m[j][2] = 1;
	}
	
	return ans;
}
void dragonCurve(){
		matrix m = make(2,3);
    	m.m[0][0] = 7;
		m.m[0][1] = 0;
		m.m[0][2] = 1;
				
		m.m[1][0] = 0;
		m.m[1][1] = 0;    	
    	m.m[1][2] = 1;
    	
    	
    	
    	while (!kbhit())
    	//for(int i = 0; i < 200; i++)
    	{
		
		//drawLines(m);
		matrix ro = getRotateAt(-M_PI_2,* new point(m.m[0][0],m.m[0][1]));
    	matrix nm = mul(m,ro);
    	matrix merged = append(m,nm);
    	
		free(m);
    	free(nm);
    	free(ro);
    	m = merged;
    	
		}
    	drawLines(m);
}


void fallingStars(){
	
	int R = 40*20;
	int r = 15*20;
	matrix star = getRandPoints(10,0,0);
	
	for(int i = 0,j = 0; i < 10; i++){
		if(i%2 == 0){
			star.m[i][1] = R*sin(M_PI_2+j*2*M_PI/5);		
			star.m[i][0] = R*cos(M_PI_2+j*2*M_PI/5);
		}
		else
		{
			
			star.m[i][1] = r*sin(M_PI*3/10+(++j)*2*M_PI/5);		
			star.m[i][0] = r*cos(M_PI*3/10+j*2*M_PI/5);
			
		}
	}
	
	
	matrix ro = getRotate(M_PI/50);
	//matrix tr = getTranslat/ePolar(M_PI_2,10);
	bool flag = false;
	for(int i = 0; i < 100; i++){
		
		
	
	
		cleardevice();
		drawPolygon(star);
		matrix newStar = mul(star,ro);
		//double theta = newStar.m[0][0] != 0 ? atan((newStar.m[0][1])/newStar.m[0][0]) : (newStar.m[0][1]) > 0 ? M_PI_2 : -M_PI_2;
	 	//double theta =  atan((newStar.m[0][1])/newStar.m[0][0]);
		
		matrix tr;
		if(flag)
		tr = getScale(1.05,1.05);
		else
		tr = getScale(0.95,0.95);
		
		free(star);
		
		matrix newStar2 = mul(newStar,tr);
		free(newStar);
		star = newStar2;
		delay(100);
	}
	
	
	
	
}

void mandelbrot()
//For each pixel (Px, Py) on the screen, do:
{

	double mx = getmaxy()/2*scale;
	int px,py;
	double mmx = getmaxx()/2;
	double mmy = getmaxy()/2;
	for(px = -mmx; px < mmx; px++){
		for(py = -mmy; py < mmy; py++){
		
	//x0 = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
  	//y0 = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
  	double x0 = (px  - shiftX)/mx*2;
  	double y0 = (py  - shiftY)/mx*2;
	double x = 0.0;
  	double y = 0.0, xtemp;
  	int iteration = 0;
  	
  	while (x*x + y*y < 2*2  &&  iteration < max_iterations) {
    	xtemp = x*x - y*y + x0;
    	y = 2*x*y + y0;
    	x = xtemp;
    	iteration = iteration + 1;
  	}
  	//color = palette[iteration]
  	  int color = (iteration+shiftColor)%15;
  	 //int color;
	 // color = WHITE;
	 	 
	  if(iteration == max_iterations)
	  	color = BLACK;
	  
	  putpixel(getmaxx()/2 + px, getmaxy()/2 - py, color);
	}
	}
}
/*
void normalise(){

int total = 0,i;
int histogram[10];

for (i = 0; i < max_iterations; i += 1) {
  total += histogram[i];
}

double hue = 0.0;
for (i = 0; i < iteration; i += 1) {
  hue += histogram[i] / total; // Must be floating-point division.
}

//color = palette[hue]

}
*/

/////////////////////////////////////////////////

void callHilbert(){
	direction d = 1;
	int n = 0;//the nth aproximation of the hilbert's curve
	printf("enter the order of Hilbert curve\nenter -1 to exit\n");
	double s = getmaxx()/2;
	while(1){

		scanf("%d",&n);

		if(n < 0 )
		return ;

		cleardevice();
		//hpoint* hilbert(double x0,double y0, double L, int n, direction dir);
		hilbert(getmaxx()/2 - s/2, getmaxy()/2 - s/2, s, n, d);//x,y,L,n,dir
	}

	
}
int main()
{
        
        
 		initwindow(1920, 700, "");
        std::cout << "enter a for Falling star\nenter b for Dragon cure\nenter c for Mandelbrot Set\nenter d for Hilbert's curve " << std::endl;
    	switch(getch()){
    		case 'a': fallingStars(); break;
    		case 'b': dragonCurve(); break;
    		case 'c': mandelbrot(); break;
    		case 'd': callHilbert(); break;
		}
		
   	    getch();
        closegraph();
		return 0;
}


