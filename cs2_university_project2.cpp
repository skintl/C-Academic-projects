#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<stdlib.h>
#include<time.h>
void langrangeinterpol(double *x, double *y, double n, double p)
{
	double sum = 1, f[10], t = 0;
	int i, j, k = 0;
	for (i = 0; i<n; i++)
	{
		t = 1;
		k = i;
		for (j = 0; j<n; j++)
		{
			if (k == j)
			{
				continue;
			}
			else
			{
				t = t * ((p - x[j]) / (x[k] - x[j]));
			}
		}
		f[i] = y[i] * t;
	}

	for (i = 0; i<n; i++)
	{
		sum = sum + f[i];
	}
	printf("\n\n Y=f(x=%.lf) = %lf ", p, sum);
}


double determinant(double **A, int k)
{
	double s = 1, det = 0;
	double **b = (double**)malloc(k * sizeof(double*));
	double *p = (double*)malloc(k*k * sizeof(double));


	for (int i = 0; i < k; ++i)
	{
		b[i] = p + i * k;
	}
	int i, j, m, n, c;
	if (k == 1)
	{
		return (A[0][0]);
	}
	else
	{
		det = 0;
		for (c = 0; c<k; c++)
		{
			m = 0;
			n = 0;
			for (i = 0; i<k; i++)
			{
				for (j = 0; j<k; j++)
				{
					b[i][j] = 0;
					if (i != 0 && j != c)
					{
						b[m][n] = A[i][j];
						if (n<(k - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			det = det + s * (A[0][c] * determinant(b, k - 1));
			s = -1 * s;
		}
	}

	return (det);
}
void transpose(double **num, double **fac, int r, double**invA)
{
	int i, j;
	double **b = (double**)malloc(r * sizeof(double*));
	double*p = (double*)malloc(r*r * sizeof(double));
	for (int i = 0; i < r; ++i)
	{
		b[i] = p + i * r;
	}
	double**inverse = (double**)malloc(r * sizeof(double*));
	double*n = (double*)malloc(r*r * sizeof(double));
	for (int i = 0; i < r; ++i)
	{
		inverse[i] = n + i * r;
	}

	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			b[i][j] = fac[j][i];
		}
	}
	double d = determinant(num, r);
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			inverse[i][j] = b[i][j] / d;
		}
	}
	printf("\n\n\nThe inverse of matrix is : \n");
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			invA[i][j] = inverse[i][j];
		}
	}
}
void cofactor(double **num, int f, double **invA)
{
	double **b = (double**)malloc(f * sizeof(double*));
	double*h = (double*)malloc(f*f * sizeof(double));
	for (int i = 0; i < f; ++i)
	{
		b[i] = h + i * f;
	}
	double **fac = (double**)malloc(f * sizeof(double*));
	double*l = (double*)malloc(f*f * sizeof(double));
	for (int i = 0; i < f; ++i)
	{
		fac[i] = l + i * f;
	}
	int p, q, m, n, i, j;
	for (q = 0; q<f; q++)
	{
		for (p = 0; p<f; p++)
		{
			m = 0;
			n = 0;
			for (i = 0; i<f; i++)
			{
				for (j = 0; j<f; j++)
				{
					if (i != q && j != p)
					{
						b[m][n] = num[i][j];
						if (n<(f - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
		}
	}
	transpose(num, fac, f, invA);
}
int gauselimination(int k, double **a, double *x)
{
	double c;
	for (int i = 1; i < k; i++)
	{
		c = a[i][0] / a[0][0];
		for (int j = 0; j <= k; j++)
		{
			a[i][j] = a[i][j] - c * a[0][j];
		}
	}
	for (int i = 1; i < k; i++)
	{
		c = 0;
		for (int j = 0; j <= k; j++)
		{
			if (i > j&&a[i][j] != 0)
			{
				c = a[i][j] / a[i - 1][j];
				a[i][j] = a[i][j] - c * a[i - 1][j];
			}
		}

	}
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			printf("\t%lf", a[i][j]);
		}
		printf("\n");
	}
	int H = 0, N = 0;//*algorithm to return the number of draws
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k + 1; j++)
		{
			if (a[i][j] == 0)
			{
				H = N + 1;
				N = H;
			}
		}

	}
	printf("\nno. of draws to obtain the solution=%d\n", H);
	double sum = 0;
	x[k - 1] = a[k - 1][k] / a[k - 1][k - 1];
	for (int i = k - 2; i >= 0; i--)
	{
		sum = 0;
		for (int j = i + 1; j < k; j++)
		{
			sum = sum + a[i][j] * x[j];
		}
		x[i] = (a[i][k + 1] - sum) / a[i][i];
	}
	printf("\nThe solution is: \n");
	for (int i = 0; i < k; i++)
	{
		printf("\nx%d=%f\t", i, x[i]); //solution printing
	}
	return H;//returned no. of draws
}
int main()
{
	srand(unsigned(time(NULL)));
	int k;
	printf("please enter the order of the matrix\n");
	scanf_s("%d", &k);
	double **A = (double**)malloc(k * sizeof(double*));
	double*p = (double*)malloc(k*k * sizeof(double));

	for (int i = 0; i < k; ++i)
	{
		A[i] = p + i * k;
	}
	printf("\nRandomly generated matrix\n");
	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			A[i][j] = (double)rand() * (-100.0 - 100.0) / (double)RAND_MAX + 100.0;
			printf("\tA[%d][%d]=%lf", i, j, A[i][j]);
		}
		printf("\n");
	}
	double **invA = (double**)malloc(k * sizeof(double*));
	double *J = (double*)malloc(k*k * sizeof(double));
	for (int i = 0; i < k; ++i)
	{
		invA[i] = J + i * k;
	}

	cofactor(A, k, invA);
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			printf("\t%lf", invA[i][j]);
		}
		printf("\n");
	}
	//MATRIX B formation
	double detinvA = determinant(invA, k);
	printf("\nDetinvA=%lf\n", detinvA);
	double *B = (double*)malloc(k * sizeof(double));
	double y, n = 1;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			y = n * A[i][j];
			n = y;
		}
		B[i] = (y / detinvA);
	}

	for (int i = 0; i < k; i++)
	{
		printf("\nB[%d]=%lf\n", i, B[i]);
	}

	double **C = (double**)malloc(k * sizeof(double*));
	double *R = (double*)malloc(k*(k + 1) * sizeof(double));
	for (int i = 0; i < k; ++i)
	{
		C[i] = R + i * (k + 1);
	}
	printf("\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k + 1; j++)
		{
			C[i][j] = A[i][j];
			if (j == k)
			{
				C[i][j] = B[i];
			}
			printf("\tC[%d][%d]=%lf", i, j, C[i][j]);
		}
		printf("\n");
	}
	double *x = (double*)malloc(k * sizeof(double));
	printf("\n");

	printf("Upper triangular Matrix\n");
	double draws=gauselimination(k, C, x);

	double *Y = (double *)malloc(k * sizeof(double));
	for (int i = 0; i < k; i++)
	{

		Y[i] = x[i] / 2;
		printf("\nY[%d]=%lf\t X[%d]=%lf", i, Y[i], i, x[i]);
	}
	double f;
	printf("\ngive the value of X for which you would like to find interpolated value of Y\n ");

	scanf_s("%lf", &f);
	langrangeinterpol(x, Y, k, f);
	_getch();
	return 0;
}

