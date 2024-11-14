#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include "winbgi.h"

double fun(double z, double X, double Y)
{
	double solve;
	solve = -0.6*z - Y - fabs(X) + 1;
	return solve;
}
double fun1(double Z)
{
	double solve;
	solve = Z;
	return solve;
}
double fun2(double Y)
{
	double solve;
	solve = Y;
	return solve;
}
double rk4z(double z, double y, double x, double h)
{
	double k, k1, k2, k3, k4;
	k1 = h * fun(z, x, y);
	k2 = h * fun(z + k1 / 2, x, y);
	k3 = h * fun(z + k2 / 2, x, y);
	k4 = h * fun(z + k3, x, y);
	k = 1.0 / 6.0*(k1 + (2*k2) +(2* k3) + k4);
	return k;
}
double rk4xy(double A,double h)
{
	double k, k1, k2, k3, k4;// since there is no independent variable present in the function  F(Y,T)=DY/DT=Z and F(X,T)=DX/DT=Y
	k1 = h * fun1(A);
	k2 = h * fun1(A);
	k3 = h * fun1(A);
	k4 = h * fun1(A);
	k = 1.0 / 6.0*(k1 +(2*k2) + (2*k3) + k4);
	return k;
}


void main()
{
	printf("\nThe chaotic flow analysis\n");
	double h, t, n;
	printf("\nenter the final value of time\n");
	scanf_s("%lf", &t);
	printf("\nenter the number of steps you want to take to make the analysis through 4th order Runge Kutta method of differential equation solving\n");
	scanf_s("%lf", &n);
	double T[2000], Z[2000], X[2000], Y[2000];
	double k;
	//FILE*f;
	//f=fopen_s(&f, "Rungekutta.dat", "wt");
	//Initial parameters were set here for the X,Y,Z,T co-ordinates
	T[0] = 0;
	Z[0] = 0;
	X[0] = 0;
	Y[0] = 0;
	h = (t - T[0]) / n;// time step to be defined here through this code
	printf("\n  T\t\t  X\t\t Y\t\t Z\t\t \n");

	for (int i = 0;i< n;i++)
	{
		k = rk4z(Z[i],Y[i],X[i],h);
		Z[i + 1] = Z[i] + k;
		k = rk4xy(Z[i],h);
		Y[i + 1] = Y[i] + k;
		k = rk4xy(Y[i],h);
		X[i + 1] = X[i] + k;
		T[i + 1] = T[i] + h;
	}
	for (int i = 0;i<= n;i++)
	{
		printf("%lf\t%lf\t%lf\t%lf\n", T[i], X[i], Y[i], Z[i]);
		//fprintf(f,"%lf\t%lf\t%lf\t%lf\n", T[i], X[i], Y[i], Z[i]);
	
	}
//	fclose(f);

	initwindow(2000,2000);
	setcolor(RED);
	line(100,50,200, 50);
	outtextxy(100, 50, "Y(t)");
	setcolor(YELLOW);
	line( 100,100,200,100);
	outtextxy(100, 100, "Z(t)");
	setcolor(GREEN); 
	line(100, 150, 200,150);
	outtextxy(100,150, "X(t)");
	
	setcolor(BLUE);
	outtextxy(400,500, "Time(s)");
	setcolor(BLUE);
	outtextxy(40,300, "F(X,Y,Z)");
	setcolor(WHITE);
	outtextxy(97,250,"A");
	line(100,500,800,500);
	line(100,250,100,500);
	
	for (int i =0;i<n;i++)
	{
		double x, y;
		x =100+50*T[i];
		y =500-50*Z[i];

	putpixel(x,y,YELLOW);
	x = 100 + 50* T[i];
	y = 500 - 50* X[i];

	putpixel(x, y, GREEN);
	x = 100 + 50 * T[i];
	y = 500 - 50 * Y[i];

	putpixel(x, y,RED);
		
	}
	_getch();
	closegraph();
}


/*
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include "winbgi.h"
double fun(double z, double X, double Y)
{
	double solve;
	solve = -0.6*z - Y - fabs(X) + 1;
	return solve;
}
double fun1(double Z)
{
	double solve;
	solve = Z;
	return solve;
}
double fun2(double Y)
{
	double solve;
	solve = Y;
	return solve;
}

void main()
{
	printf("\nThe chaotic flow analysis\n");
	double h, t, n;
	printf("\nenter the final value of time\n");
	scanf_s("%lf", &t);
	printf("\nenter the number of steps you want to take to make the analysis through eulers method of differential equation solving\n");
	scanf_s("%lf", &n);
	double T[2000], Z[2000], X[2000], Y[2000];
	double k;
	//FILE *f;
	//f = fopen_s(&f,"Euller.dat","wt");
	T[0] = 0;
	Z[0] = 0;
	X[0] = 0;
	Y[0] = 0;
	h = (t - T[0]) / n;// time step to be defined here through this code
	printf("\n  T\t\t  X\t\t Y\t\t Z\t\t \n");
	//fprintf(f,"\n  T\t\t  X\t\t Y\t\t Z\t\t \n");
	

	for (int i = 0;i< n;i++)
	{
		k = h * fun(Z[i], X[i], Y[i]);
		Z[i + 1] = Z[i] + k;
		k = h * fun1(Z[i]);
		Y[i + 1] = Y[i] + k;
		k = h * fun2(Y[i]);
		X[i + 1] = X[i] + k;
		T[i + 1] = T[i] + h;
	}
	for (int i = 0;i <= n;i++)
	{
		printf("%lf\t%lf\t%lf\t%lf\n", T[i], X[i], Y[i], Z[i]);
	//	fprintf(f,"%lf\t%lf\t%lf\t%lf\n", T[i], X[i], Y[i], Z[i]);
	}
	//fclose(f);

	initwindow(1000, 1000);
	setcolor(RED);
	line(100, 50, 200, 50);
	outtextxy(100, 50, "Y(t)");
	setcolor(YELLOW);
	line(100, 100, 200, 100);
	outtextxy(100, 100, "Z(t)");
	setcolor(GREEN);
	line(100, 150, 200, 150);
	outtextxy(100, 150, "X(t)");

	setcolor(BLUE);
	outtextxy(400, 500, "Time(s)");
	setcolor(BLUE);
	outtextxy(40, 300, "F(X,Y,Z)");
	setcolor(WHITE);
	outtextxy(97, 250, "A");
	line(100, 500, 800, 500);
	line(100, 250, 100, 500);

	for (int i = 0;i<n;i++)
	{
		double x, y;
		x = 100 + 50 * T[i];
		y = 500 - 50 * Z[i];

		putpixel(x, y, YELLOW);
		x = 100 + 50 * T[i];
		y = 500 - 50 * X[i];

		putpixel(x, y, GREEN);
		x = 100 + 50 * T[i];
		y = 500 - 50 * Y[i];

		putpixel(x, y, RED);

	}
	_getch();
	closegraph();


}
*/
