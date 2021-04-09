#include <iostream>
#include <omp.h>

using namespace std;

//size of matrix
#define N 2
#define M 4
#define L 4

//init matr
int** matr(int n, int m)
{
	int** matr = new int* [n];
	for (int i = 0; i < n; i++)
		matr[i] = new int[m];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matr[i][j] = 5;

	return matr;
}

//output matr
void print(int** matr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << matr[i][j] << " ";
		cout << endl;
	}
}

//последовательный алгоритм
void linear(int** A, int** B, int n, int m, int l)
{
	int** C = matr(n, l);
	int i, j, k;

	double t1 = omp_get_wtime();
	int numTread = omp_get_thread_num();
	for (i = 0; i < n; i++)
		for (j = 0; j < l; j++)
		{
			C[i][j] = 0;
			for (k = 0; k < m; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	double t2 = omp_get_wtime();
	cout << "time linear: " << t2 - t1 << endl;
	print(C, n, l);
}

//ленточный алгоритм
void tape(int** A, int** B, int n, int m, int l)
{
	int** C = matr(n, l);
	int threadNum = omp_get_max_threads();
	int mi = n / threadNum;
	int i, j, k;

	omp_set_num_threads(threadNum);

	double t1 = omp_get_wtime();
#pragma omp parallel shared(A,B,mi,C) private(i,j,k)
	{
		int numTread = omp_get_thread_num();
		for (i = 0; i < mi; i++)
			for (j = 0; j < l; j++)
			{
				C[i + numTread * mi][j] = 0;
				for (k = 0; k < m; k++)
					C[i + numTread * mi][j] += A[i + numTread * mi][k] * B[k][j];
			}
	}
	double t2 = omp_get_wtime();
	cout << "time tape: " << t2 - t1 << endl;
	print(C, n, l);
}

//блочный алгоритм
void block(int** A, int** B, int n, int m, int l)
{
	int** C = matr(n, l);
	//int threadNum = omp_get_max_threads();
	//int mi = n / 4;
	int i, j, k;

	int ni = n / 2, mi = m / 2, li = l / 2;

	omp_set_num_threads(4);

	double t1 = omp_get_wtime();
#pragma omp parallel shared(A,B,mi,C) private(i,j,k)
	{
		int numThread = omp_get_thread_num();
		int indStr = numThread / 2;
		int indStlb = numThread % 2;
		for (i = 0; i < ni; i++)
		{
			for (j = 0; j < li; j++)
			{
				C[i + indStr * ni][j + indStlb * li] = 0;
				for (k = 0; k < mi; k++)
					C[i + indStr * ni][j + indStlb * li] += A[i + indStr * ni][k + indStlb * mi] * B[k + indStr * mi][j + indStlb * li];
			}
		}
	}
	double t2 = omp_get_wtime();
	cout << "time block: " << t2 - t1 << endl;
	print(C, n, l);
}


void main()
{
	cout << omp_get_max_threads() << endl;
	int** A = matr(N, M);
	int** B = matr(M, L);
	
	tape(A, B, N, M, L);
	linear(A, B, N, M, L);
	block(A, B, N, M, L);

	system("pause");
}

