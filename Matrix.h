#ifndef MATRIX_H
#define MATRIX_H

#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>



using namespace std;

 struct matrix{
	double ** m;
	int r;
	int c;
	
}; 
struct point{
	double x,y;
	point(double a,double b):x(a),y(b){
	}
};
typedef struct matrix matrix;
typedef struct point point;

matrix  mul(const matrix &a ,const  matrix &b );
void print(const matrix &m);
matrix  make(int r,int c);
void free(matrix& a);
matrix  get(int r, int c);
matrix  getScale(double sx, double sy);
matrix  getScaleAt(double sx, double sy,point p);
matrix  getRotate(double angle);
matrix  getTranslate(double x,double y);
matrix  getTranslatePolar(double theta,double r);
matrix  getRand(int r,int c);
matrix  getRotateAt(double angle,point p);
matrix  getRandPoints(int n,int maxx,int  maxy);

matrix  make(int r,int c){
	matrix * t = new matrix;
	 
	t->m = new double*[r];
	for(int i = 0; i < r;i++){
		t->m[i] = new double[c];
		for(int j = 0; j < c;j++){
			t->m[i][j] = 0;
		}
	}
	t->r = r;
	t->c = c;
	return *t;
}
 
matrix mul( const matrix & a,const  matrix & b){
	matrix ans;
	if(a.c == b.r){
	
	ans = make(a.r,b.c);
	
	double sum = 0;
	for(int r = 0; r < a.r; r ++)
		for(int c = 0; c < b.c; c++){
			sum = 0;
			for(int k = 0; k < a.c; k++)
			{	
				sum += a.m[r][k]*b.m[k][c]; 
			}
			ans.m[r][c] = sum;
		}
	ans.r = a.r;
	ans.c = b.c;
	}
	
	return ans;
} 



void print(const matrix &m){
	
	for(int i = 0; i< m.r; i ++){
		cout<<"\t";
		for(int j = 0; j < m.c; j++){
		printf("%lf  ", m.m[i][j]);
		}
		cout<<endl;	
	}
	cout<<endl;
}

void free(matrix & a){
	for(int i = 0 ; i < a.r; i++)
		delete [] a.m[i];
		
	delete[] a.m;
	delete &a;
}
matrix  get(int r, int c){
		matrix a = make(r,c);
		
		cout<<"Enter the values of "<<r<<" X "<<c<<"matrix"<<endl;
	 	for(int i = 0; i< r; i++){
 		for(int j = 0; j < c; j++){
		 	cin>>a.m[i][j];
		 }
		 cout<<endl;
	}
 		return a;
}
matrix getScale(double sx, double sy){
	matrix s = make(3,3);
	s.m[0][0] = sx;
	s.m[1][1] = sy;
	s.m[2][2] = 1;
	return s;
}
matrix getRotate(double angle){
	matrix s = make(3,3);
	s.m[0][0] = cos(angle);
	s.m[0][1] = sin(angle);
	s.m[1][0] = -sin(angle);
	s.m[1][1] = cos(angle);
	s.m[2][2] = 1;
	return s;
}

matrix getTranslate(double x,double y){
	matrix s = make(3,3);
	
	for(int i = 0 ; i < 3; i++)
		for(int j = 0; j < 3; j++)
		  if(i == j)
		  	s.m[i][j] = 1;
		  	
	s.m[2][0] = x;
	s.m[2][1] = y;
	return s;
}
matrix getTranslatePolar(double theta,double r){
	matrix s = getTranslate(r*cos(theta),r*sin(theta));
	return s;
}
matrix getRand(int r,int c){
	matrix s = make(r,c);
	srand( time(NULL));
	for(int i = 0 ; i < r; i++)
		for(int j = 0; j < c; j++)
		  	s.m[i][j] = rand();
		  	
	return s;
}
matrix getRotateAt(double angle,point p){
	matrix s = make(3,3);
	s.m[0][0] = cos(angle);
	s.m[0][1] = sin(angle);
	s.m[1][0] = -sin(angle);
	s.m[1][1] = cos(angle);
	s.m[2][0] = -p.x*cos(angle) + p.y*sin(angle) + p.x;  
	s.m[2][1] = -p.x*sin(angle) - p.y*cos(angle) + p.y;
	s.m[2][2] = 1;
	return s;
}
matrix  getScaleAt(double sx, double sy,point p){
	
	matrix  s = make(3,3);
	s.m[0][0] = sx;
	s.m[1][1] = sy;
	s.m[2][0] = -sx*p.x + p.x;
	s.m[2][1] = -sy*p.y + p.y;
	s.m[2][2] = 1;
	
	return s;
}
matrix  getRandPoints(int n,int maxx, int maxy){
	matrix a = make(n,3);
	srand(time(NULL));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < 3; j++){
			switch(j){
				case 0:
					a.m[i][j] = rand()%(maxx + 1); 
					break;
				case 1:
					a.m[i][j] = rand()%(maxy + 1);
					break;
				case 2:
					a.m[i][j] = 1;
					break;
				default:
					a.m[i][j] = 0;
			}
		}
		
	return a;
}
#endif

