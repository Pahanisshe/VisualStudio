#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include <math.h>

using namespace std;

//size of matrix
//#define N 1000
//#define M 2000
//#define L 1500


#define siz 500
#define eps 0.000001

class Matrixes {
public:
	static int sumMatr(int** A, int n)
	{
		int sum = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				sum += A[i][j];
		return sum;
	}

	//init matr
	static int** matr(int n, int m, int value)
	{
		int** matr = new int* [n];
		for (int i = 0; i < n; i++)
			matr[i] = new int[m];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				matr[i][j] = value;

		return matr;
	}

	//init matr
	static double** matr(int n, int m, double value)
	{
		double** matr = new double* [n];
		for (int i = 0; i < n; i++)
			matr[i] = new double[m];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				matr[i][j] = value;

		return matr;
	}

	//init matr in vectors
	static vector<vector<int>> matrInit(int n)
	{
		vector<vector<int>> matr(siz, vector<int>(siz, 0));


		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matr[i][j] = 2;

		return matr;
	}

	//out matr in vectors
	static void matrOut(vector<vector<int>> matr, int n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cout << matr[i][j] << " ";
			cout << endl;
		}
	}

	//output matr
	static void print(int** matr, int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << matr[i][j] << " ";
			cout << endl;
		}
	}

	//output matr
	static void print(double** matr, int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << matr[i][j] << " ";
			cout << endl;
		}
	}

	//последовательный алгоритм
	static void linear(int** A, int** B, int n, int m, int l)
	{
		int** C = matr(n, l, 0);
		int i, j, k, sum = 0;

		double t1 = omp_get_wtime();
		int numTread = omp_get_thread_num();
		for (i = 0; i < n; i++)
			for (j = 0; j < l; j++)
			{
				for (k = 0; k < m; k++)
					C[i][j] += A[i][k] * B[k][j];
				sum += C[i][j];
			}
		double t2 = omp_get_wtime();

		cout << "sum linear: " << sum << endl;
		cout << "time linear: " << t2 - t1 << endl << endl;
	}
	
	//ленточный алгоритм
	static void tape(int** A, int** B, int n, int m, int l)
	{
		int** C = matr(n, l, 0);
		int threadNum = 4;
		int mi = n / threadNum;
		int i, j, k;

		omp_set_num_threads(threadNum);

		double t1 = omp_get_wtime();
#pragma omp parallel num_threads(4) shared(A,B,mi,C) private(i,j,k)
		{
			int numTread = omp_get_thread_num();
			for (i = 0; i < mi; i++)
				for (j = 0; j < l; j++)
				{
					C[i + numTread * mi][j] = 0;
					for (k = 0; k < m; k++)
						C[i + numTread * mi][j] += A[i + numTread * mi][k] * B[k][j];
					//sum += C[i][j];
				}
		}
		double t2 = omp_get_wtime();

		cout << "sum tape: " << sumMatr(C, n) << endl;
		cout << "time tape: " << t2 - t1 << endl << endl;
		//print(C, n, l);
	}

	////блочный алгоритм для векторов
	static void BlockV(vector<vector<int>> a, vector<vector<int>> b)
	{
		int blockSize = siz / 4;

		vector<vector<int>> c(siz, vector<int>(siz, 0));
		int sum = 0;
		double t = omp_get_wtime();
#pragma omp parallel
		{
			int cur = omp_get_thread_num();
			for (int k = 0; k < 4; k++)
			{
				for (int i = 0; i < blockSize; i++)
				{
					for (int j = 0; j < blockSize; ++j)
					{
						for (int m = 0; m < siz; ++m) {
							c[((cur + k) % 4) * blockSize + i][(cur % 4) * blockSize + j] += a[((cur + k) % 4) * blockSize + i][m] * b[m][(cur % 4) * blockSize + j];
						}
						/*#pragma omp critical
						{
							cout << c[i][j] << " - c";
						}*/
						//sum += c[i][j];
					}
				}
			}
		}
		t = omp_get_wtime() - t;

		cout << "\nSum is " << sum << endl;

		cout << "Blocky algorithm time = " << t << endl << endl;
		/*matrOut(a, size);
		cout << endl;
		matrOut(b, size);
		cout << endl;
		matrOut(c, size);*/
	}

	static void BlockAr(int** A, int** B)
	{
		int blockSize = siz / 4;

		int** C = matr(siz, siz, 0);

		int sum = 0;

		double t = omp_get_wtime();
#pragma omp parallel
		{
			int cur = omp_get_thread_num();
			for (int k = 0; k < 4; k++)
			{
				for (int i = 0; i < blockSize; i++)
				{
					for (int j = 0; j < blockSize; ++j)
					{
						for (int m = 0; m < siz; ++m) {
							C[((cur + k) % 4) * blockSize + i][(cur % 4) * blockSize + j] += A[((cur + k) % 4) * blockSize + i][m] * B[m][(cur % 4) * blockSize + j];
						}
						/*#pragma omp critical
						{
							cout << c[i][j] << " - c";
						}*/

						sum += C[i][j];
					}
				}
			}
		}
		t = omp_get_wtime() - t;

		cout << "Sum is " << sumMatr(C, siz) << endl;

		cout << "Blocky algorithm time = " << t << endl << endl;
		/*print(A, size, size);
		cout << endl;
		print(B, size, size);
		cout << endl;
		print(C, size, size);*/
	}

	static double** ReadMatrFile(string fileName)
	{
		setlocale(LC_ALL, "RUSSIAN");

		//Создаем файловый поток и связываем его с файлом
		ifstream in(fileName);

		if (in.is_open())
		{
			//Если открытие файла прошло успешно

			//Вначале посчитаем сколько чисел в файле
			int count = 0;// число чисел в файле
			int temp;//Временная переменная

			while (!in.eof())// пробегаем пока не встретим конец файла eof
			{
				in >> temp;//в пустоту считываем из файла числа
				count++;// увеличиваем счетчик числа чисел
			}

			//Число чисел посчитано, теперь нам нужно понять сколько
			//чисел в одной строке
			//Для этого посчитаем число пробелов до знака перевода на новую строку 

			//Вначале переведем каретку в потоке в начало файла
			in.seekg(0, ios::beg);
			in.clear();

			//Число пробелов в первой строчке вначале равно 0
			int count_space = 0;
			char symbol;
			while (!in.eof())//на всякий случай цикл ограничиваем концом файла
			{
				//теперь нам нужно считывать не числа, а посимвольно считывать данные
				in.get(symbol);//считали текущий символ
				if (symbol == ' ') count_space++;//Если это пробел, то число пробелов увеличиваем
				if (symbol == '\n') break;//Если дошли до конца строки, то выходим из цикла
			}
			//cout << count_space << endl;

			//Опять переходим в потоке в начало файла
			in.seekg(0, ios::beg);
			in.clear();

			//Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
			//Теперь можем считать матрицу.

			int n = count / (count_space + 1);//число строк
			int m = count_space + 1;//число столбцов на единицу больше числа пробелов
			double** x;
			x = new double* [n];
			for (int i = 0; i < n; i++) x[i] = new double[m];

			//Считаем матрицу из файла
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					in >> x[i][j];



			//Выведем матрицу
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
					cout << x[i][j] << "\t";
				cout << "\n";
			}
			/*
			for (int i = 0; i < n; i++) delete[] x[i];
			delete[] x;*/

			in.close();//под конец закроем файла

			return x;
		}
		else
		{
			//Если открытие файла прошло не успешно
			cout << "Файл не найден.";
			return NULL;
		}
	}
};

class JakobiMethod {
public:

	//умножение матрицы на вектор
	static double* mulMatrVec(double** A, double* B, int n, int m)
	{
		double* C = initVector(m, 0);
		int i, k, sum = 0;

		//double t1 = omp_get_wtime();
		//int numTread = omp_get_thread_num();
		for (i = 0; i < n; i++)
		{
			for (k = 0; k < m; k++)
				C[i] += A[i][k] * B[k];
		}
		//double t2 = omp_get_wtime();

		return C;

		//cout << "sum linear: " << sum << endl;
		//cout << "time linear: " << t2 - t1 << endl << endl;
	}

	//init vector
	static double* initVector(int n, double value)
	{
		double* vector = new double[n];
		for (int i = 0; i < n; i++)
			vector[i] = value;

		return vector;
	}

	//print vector
	static void printVector(int n, double* vector)
	{
		for (int i = 0; i < n; i++)
			cout << vector[i] << " ";
		cout << endl;
	}

	static void printVector(vector<double> vector)
	{
		for (int i = 0; i < vector.size(); i++)
			cout << vector[i] << " ";
		cout << endl;
	}

	static void JacobiParallel(int N, double** A, double* F, double* X)
	{
		double* TempX = initVector(siz, 0.0);
		double norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.
		double t = omp_get_wtime();
		do {
#pragma omp parallel for 
			for (int i = 0; i < N; i++) {
				TempX[i] = F[i];
				for (int g = 0; g < N; g++) {
					if (i != g)
						TempX[i] -= A[i][g] * X[g];
				}
				TempX[i] /= A[i][i];
			}
			norm = fabs(X[0] - TempX[0]);
			for (int h = 0; h < N; h++) {
				if (fabs(X[h] - TempX[h]) > norm)
					norm = fabs(X[h] - TempX[h]);
				X[h] = TempX[h];
			}
		} while (norm > eps);
		t = omp_get_wtime() - t;
		cout << "\n\nTime of parallel Jakobi: " << t << endl;
		//printVector(N, X);
		//cout << "Sum parallel: " << sumVectorX(N, X) << endl;
		cout << endl;
		// norma max raznosti
		
		double* b1 = mulMatrVec(A, X, N, N);

		//cout << "\n";
		//printVector(N, F);
		//printVector(N, b1);
		//cout << "\n";
		double norma = fabs(b1[0] - F[0]);
		for (int i = 1; i < N; i++)
		{
			if (fabs(b1[i] - F[i]) > norma)
				norma = fabs(b1[i] - F[i]);
		}
		/*cout << norma << " - norma" << endl;*/
		if (norma < eps)
			cout << true << " -------" << endl;
		else
			cout << false << " -------" << endl;

	}

	static void JacobiLinear(int N, double** A, double* F, double* X)
	{
		double* TempX = initVector(siz, 0.0);
		double norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.
		double t = omp_get_wtime();
		int cnt = 0;
		do {
			for (int i = 0; i < N; i++) {
				TempX[i] = F[i];

				for (int g = 0; g < N; g++) {
					if (i != g)
						TempX[i] -= A[i][g] * X[g];
					// cout << "tempx = " << TempX[i] << endl;
				}
				TempX[i] /= A[i][i];

			}
			norm = fabs(X[0] - TempX[0]);
			for (int h = 0; h < N; h++) {
				if (fabs(X[h] - TempX[h]) > norm)
					norm = fabs(X[h] - TempX[h]);
				X[h] = TempX[h];
			}
			cnt++;
			//cout << "norma = " << norm << endl;
		} while (norm > eps);
		t = omp_get_wtime() - t;
		cout << "Time of linear Jakobi: " << t << endl;
		//printVector(N, X);
		//cout << "Sum linear: " << sumVectorX(N, X) << endl;
		cout << endl;
		double* b1 = mulMatrVec(A, X, N, N);

		//printVector(N, F);
		//printVector(N, b1);

		// norma max raznosti
		double norma = fabs(b1[0] - F[0]);
		for (int i = 1; i < N; i++)
		{
			if (fabs(b1[i] - F[i]) > norma)
				norma = fabs(b1[i] - F[i]);
		}
		cout << norma << endl;
		norma = sqrt1(norma);
		cout << norma << " - new norm"<< endl;
		/*cout << norma << " - norma" << endl;*/
		if (norma < eps)
			cout << true << "-------" << endl;
		else
			cout << false << endl;


		// norma kvadratov
		/*double norma = 0;
		for (int i = 0; i < N; i++)
		{
			norma += (b1[i] - F[i]) * (b1[i] - F[i]);
		}
		norma = sqrt(norma);
		cout << norma << " - norma" << endl;
		if (norma < eps)
			cout << true << endl;
		else
			cout << false << endl;*/


	}



	static void JacobiParallelVec(int N, vector<vector<double>> A, vector<double> F, vector<double> X)
	{
		vector<double> TempX(N, 0.0);
		double norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.
		double t = omp_get_wtime();
		do {
#pragma omp parallel for 
			for (int i = 0; i < N; i++) {
				TempX[i] = F[i];
				for (int g = 0; g < N; g++) {
					if (i != g)
						TempX[i] -= A[i][g] * X[g];
				}
				TempX[i] /= A[i][i];
			}
			norm = fabs(X[0] - TempX[0]);
			for (int h = 0; h < N; h++) {
				if (fabs(X[h] - TempX[h]) > norm)
					norm = fabs(X[h] - TempX[h]);
				X[h] = TempX[h];
			}
		} while (norm > eps);
		t = omp_get_wtime() - t;
		cout << t << endl;
		printVector(X);
	}

	static void JacobiLinearVec(int N, vector<vector<double>> A, vector<double> F, vector<double> X)
	{
		vector<double> TempX(N, 0.0);
		double norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.
		double t = omp_get_wtime();
		do {
			for (int i = 0; i < N; i++) {
				TempX[i] = F[i];
				for (int g = 0; g < N; g++) {
					if (i != g)
						TempX[i] -= A[i][g] * X[g];
				}
				TempX[i] /= A[i][i];
			}
			norm = fabs(X[0] - TempX[0]);
			for (int h = 0; h < N; h++) {
				if (fabs(X[h] - TempX[h]) > norm)
					norm = fabs(X[h] - TempX[h]);
				X[h] = TempX[h];
			}
		} while (norm > eps);
		t = omp_get_wtime() - t;
		cout << t << endl;
		printVector(X);
	}

	static double sumVectorX(int n, double* X)
	{
		double sum = 0.0;
		for (int i = 0; i < n; i++)
			sum += X[i];
		return sum;
	}

	static double** initMatr(int n)
	{
		double** A = new double*[n];
		for (int i = 0; i < n; i++)
			A[i] = new double[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i == j)
					A[i][j] = n * 20.3 + 67.11007;
				else
					A[i][j] = 3.1001;
		return A;
	}	
	
	static bool sqrt1(double norma)
	{
		return eps * 0.01;
	}
};

class Simpson {
public:
	static double f(double x) //исходная функция
	{
		double f = (x * x * x + 1);
		return f;
	}

	//linear
	static double methodSimpson(double a, double b)
	{
		double steps = 100;
		double Sresult, S1result1;
		int Scount = 0;
		double accurasy = 0.00001;
		double step = (b - a) / steps;
		Sresult = S1result1 = 0;
		double t = omp_get_wtime();
		for (int i = 1; i <= steps; ++i)
			Sresult += f(a + (i - 1) * step) + 4 * f(a + (i - 0.5) * step) + f(a + i * step);
		Sresult *= (step / 6);
		Scount++;
		while (abs(Sresult - S1result1) > accurasy)
		{
			S1result1 = Sresult;
			step = step / 2;
			steps = (int)((b - a) / step);
			for (int i = 1; i <= steps; ++i)
				Sresult += f(a + (i - 1) * step) + 4 * f(a + (i - 0.5) * step) + f(a + i * step);
			Sresult *= (step / 6);
			Scount++;
		}
		double t1 = omp_get_wtime();
		cout << endl << "Linear time = " << t1 - t << endl;

		return Sresult;
	}

	static double methodSimpson1(double a, double b)
	{
		double steps = 100;
		double Sresult, S1result1;
		int Scount = 0;
		double accurasy = 0.00001;
		double step = (b - a) / steps;
		Sresult = S1result1 = 0;
		double t = omp_get_wtime();
		for (int i = 1; i <= steps; ++i)
			Sresult += f(a + (i - 1) * step) + 4 * f(a + (i - 0.5) * step) + f(a + i * step);
		Sresult *= (step / 6);
		Scount++;
		while (abs(Sresult - S1result1) > accurasy)
		{
			S1result1 = Sresult;
			step = step / 2;
			steps = (int)((b - a) / step);
			for (int i = 1; i <= steps; ++i)
				Sresult += f(a + (i - 1) * step) + 4 * f(a + (i - 0.5) * step) + f(a + i * step);
			Sresult *= (step / 6);
			Scount++;
		}
		double t1 = omp_get_wtime();
		//cout << endl << "Linear time = " << t1 - t << endl;

		return Sresult;
	}

	static double methodSimpsonParalell(double a, double b)
	{
		double t = omp_get_wtime();
		double sum = 0;
		int k = 4;
#pragma omp parallel num_threads(k) shared(sum)
		{
			double kol = (b - a) / k; //0-25 26-50 21-75 76-100
			int cur = omp_get_thread_num();
			double cursum = methodSimpson1(kol * cur + a, kol * (cur + 1) + a);
#pragma omp critical
			//cout << cursum << ' ' << kol * cur + a << ' ' << kol * (cur + 1) + a << endl;
			//for (int i = kol * cur; i < kol * (cur + 1); i += kol) {
			sum += cursum;
			//}
		}
		double t1 = omp_get_wtime();
		//#pragma omp single
		cout << endl << "Parallel time = " << t1 - t << endl;

		return sum;
	}
};

class Sotr{
public:
	// Последовательный алгоритм чет-нечетной перестановки 
	void OddEvenSort(double* pData, int Size)
	{
    		double temp;
    		int upper_bound;

    		if (Size % 2 == 0) 
		        upper_bound = Size / 2 - 1;
	    	else 
	        	upper_bound = Size / 2;

	    	for (int i = 0; i < Size; i++) {
		        if (i % 2 == 0)
	          	  // четная итерация 
	       	    	for (int j = 0; j < Size / 2; j++)
	            	{
	                	if (pData[2 * j] > pData[2 * j + 1]) {
	                    	temp = pData[2 * j];
	                    	pData[2 * j] = pData[2 * j + 1];
	                    	pData[2 * j + 1] = temp;
	                	}
	            	}
	        	else
	            	// нечетная итерация 
	            	for (int j = 0; j < upper_bound; j++)
	            	{
		                if (pData[2 * j + 1] > pData[2 * j + 2]) {
		                    temp = pData[2 * j + 1];
		                    pData[2 * j + 1] = pData[2 * j + 2];
		                    pData[2 * j + 2] = temp;
		                }
	        	}
    		}
	}

// Параллельный алгоритм чет-нечетной перестановки
void ParallelOddEvenSort(double* pData, int Size) {
    double temp;
    int upper_bound;

    if (Size % 2 == 0)
        upper_bound = Size / 2 - 1;
    else
        upper_bound = Size / 2;

    for (int i = 0; i < Size; i++) 
    {
        if (i % 2 == 0) // четная итерация
#pragma omp parallel for
            for (int j = 0; j < Size / 2; j++)
            {
                if (pData[2 * j] > pData[2 * j + 1]) {
                    temp = pData[2 * j];
                    pData[2 * j] = pData[2 * j + 1];
                    pData[2 * j + 1] = temp;
                }
            }
        else // нечетная итерация
#pragma omp parallel for
            for (int j = 0; j < upper_bound; j++)
            {
                if (pData[2 * j + 1] > pData[2 * j + 2]) {
                    temp = pData[2 * j + 1];
                    pData[2 * j + 1] = pData[2 * j + 2];
                    pData[2 * j + 2] = temp;
                }
            }
    }
}
	
	//--------------------Сортировка Шелла-----------------------

// Последовательный алгоритм сортировки Шелла 
void ShellSort(double* pData, int n)
{
    int incr = n / 2;
    int j;

    while (incr > 0)
    {
        for (int i = incr + 1; i < n; i++) {
            j = i - incr;
            while (j >= 0)
                if (pData[j] > pData[j + incr])
                {
                    swap(pData[j], pData[j + incr]);
                    j = j - incr;
                }
                else j = -1;
        }
        incr = incr / 2;
    }
}

int ThreadNum; // Количество потоков 
int ThreadID; // Номер потока 
int DimSize; // Размерность гиперкуба 

// Создадим локальные копии переменной ThreadID
#pragma omp threadprivate(ThreadID)

// Определим количество потоков ThreadNum и размерность виртуального
// гиперкуба DimSize, а также идентификатор потока ThreadID
void InitializeParallelSections()
{
#pragma omp parallel 
    {
        ThreadID = omp_get_thread_num();
#pragma omp single 
        ThreadNum = omp_get_num_threads(); 
    }
    DimSize = int(log10(double(ThreadNum)) / log10(2.0)) + 1;
}

// Функция для слияния отсортированных блоков 
void MergeBlocks(double* pData, int Index1, int BlockSize1, int Index2, int BlockSize2)
{
    double* pTempArray = new double[BlockSize1 + BlockSize2];
    int i1 = Index1, i2 = Index2, curr = 0;

    while ((i1 < Index1 + BlockSize1) && (i2 < Index2 + BlockSize2))
    {
        if (pData[i1] < pData[i2]) 
            pTempArray[curr++] = pData[i1++];
        else 
            pTempArray[curr++] = pData[i2++];
    }

    while (i1 < Index1 + BlockSize1) 
        pTempArray[curr++] = pData[i1++];

    while (i2 < Index2 + BlockSize2) 
        pTempArray[curr++] = pData[i2++];

    for (int i = 0; i < BlockSize1 + BlockSize2; i++)
        pData[Index1 + i] = pTempArray[i];

    delete[] pTempArray;
}

// Функция для проверки упорядоченности массива
bool IsSorted(double* pData, int Size) {
    bool res = true;

    for (int i = 1; (i < Size) && (res); i++) {
        if (pData[i] < pData[i - 1])
            res = false;
    }

    return res;
}

// Функция для вычисления номера блока в гиперкубе 
int GrayCode(int RingID, int DimSize)
{
    if ((RingID == 0) && (DimSize == 1))
        return 0;
    if ((RingID == 1) && (DimSize == 1))
        return 1;

    int res;

    if (RingID < (1 << (DimSize - 1))) 
        return res = GrayCode(RingID, DimSize - 1);
    else 
        return res = (1 << (DimSize - 1)) + GrayCode((1 << DimSize) - 1 - RingID, DimSize - 1);
}

// Функция для вычисления линейного номера блока 
int ReverseGrayCode(int CubeID, int DimSize)
{
    for (int i = 0; i < (1 << DimSize); i++)
    {
        if (CubeID == GrayCode(i, DimSize))
            return i;
    }
}

// Функция для определения пар блоков 
void SetBlockPairs(int* BlockPairs, int Iter)
{
    int PairNum = 0, FirstValue, SecondValue;
    bool Exist;

    for (int i = 0; i < 2 * ThreadNum; i++)
    {
        FirstValue = GrayCode(i, DimSize);
        Exist = false;

        for (int j = 0; (j < PairNum) && (!Exist); j++)
            if (BlockPairs[2 * j + 1] == FirstValue)
                Exist = true;

        if (!Exist) {
            SecondValue = FirstValue^(1 << (DimSize - Iter - 1));
            BlockPairs[2 * PairNum] = FirstValue;
            BlockPairs[2 * PairNum + 1] = SecondValue;
            PairNum++;
        }
    }
}

// Функция поиска парного блока для текущего потока 
int FindMyPair(int* BlockPairs, int ThreadID, int Iter)
{
    int BlockID = 0, index, result;
    for (int i = 0; i < ThreadNum; i++)
    {
        BlockID = BlockPairs[2 * i];
        if (Iter == 0) 
            index = BlockID % (1 << (DimSize - Iter - 1));

        if ((Iter > 0) && (Iter < DimSize - 1)) 
            index = ((BlockID >> (DimSize - Iter)) << (DimSize - Iter - 1)) | (BlockID % (1 << (DimSize - Iter - 1)));
        
        if (Iter == DimSize - 1) 
            index = BlockID >> 1;

        if (index == ThreadID) {
            result = i;
            break;
        }
    }
    return result;
}

void SerialQuickSort(double* pData, int first, int last);

// "Сравнить и разделить"
// Все элементы из двух массивов делим так, чтобы
// все элементы в первом блоке были меньше любого
// элемента второго блока.
void CompareSplitBlocks(double* pData, int FirstBlockBegin, int FirstBlockSize, int SecondBlockBegin, int SecondBlockSize)
{
    int TotalSize = FirstBlockSize + SecondBlockSize;
    double* pTempBlock = new double[TotalSize];

    for (int i = 0; i < FirstBlockSize; i++)
        pTempBlock[i] = pData[i + FirstBlockBegin];

    for (int i = FirstBlockSize; i < TotalSize; i++)
        pTempBlock[i] = pData[i - FirstBlockSize + SecondBlockBegin];

    double sum = 0;
    int count = 0;

    for (int i = 0; i < TotalSize; i++) {
        sum += pTempBlock[i];
        count++;
    }

    double average = sum / count;

    int Ind1 = 0, Ind2 = 0;

    for (int i = 0; i < TotalSize; i++)
    {
        // Если элемент больше среднего значения блока,
        // пробуем поместить его в первый блок.
        if (pTempBlock[i] < average) {
            // Если в первом блоке есть место, помещаем
            // элемент в первый блок.
            if (Ind1 < FirstBlockSize)
            {
                pData[FirstBlockBegin + Ind1] = pTempBlock[i];
                Ind1++;
            }
            // Иначе во второй.
            else
            {
                pData[SecondBlockBegin + Ind2] = pTempBlock[i];
                Ind2++;
            }
        }
        // Если больше, пробуем поместить во второй блок.
        else {
            // Если во втором блоке есть место, помещаем
            // элемент во второй блок.
            if (Ind2 < SecondBlockSize)
            {
                pData[SecondBlockBegin + Ind2] = pTempBlock[i];
                Ind2++;
            }
            // Иначе в первый.
            else
            {
                pData[FirstBlockBegin + Ind1] = pTempBlock[i];
                Ind1++;
            }
        }
    }
}

// Функция для параллельного алгоритма Шелла 
void ParallelShellSort(double* pData, int Size)
{
    InitializeParallelSections();

    // Массив индексов первых элемен-тов блоков данных.
    // Т.е. i-й блок данных начинается с элемента Index[i] 
    // исходного массива.
    int* Index = new int[2 * ThreadNum];

    // Массив размеров блоков данных
    int* BlockSize = new int[2 * ThreadNum];

    // Массив пар номеров блоков в структуре гиперкуба
    int* BlockPairs = new int[2 * ThreadNum];

    for (int i = 0; i < 2 * ThreadNum; i++)
    {
        Index[i] = int((i * Size) / double(2 * ThreadNum));
        if (i < 2 * ThreadNum - 1) 
            BlockSize[i] = int(((i + 1) * Size) / double(2 * ThreadNum)) - Index[i];
        else 
            BlockSize[i] = Size - Index[i];
    }

    // Итерации алгоритма Шелла 
   for (int Iter = 0; (Iter < DimSize) && (!IsSorted(pData, Size)); Iter++)
    {
        // Определение пар блоков 
        SetBlockPairs(BlockPairs, Iter);

        // Операция "Сравнить и разделить" 
#pragma omp parallel 
        {
            int MyPairNum = FindMyPair(BlockPairs, ThreadID, Iter);
            int FirstBlock = ReverseGrayCode(BlockPairs[2 * MyPairNum], DimSize);
            int SecondBlock = ReverseGrayCode(BlockPairs[2 * MyPairNum + 1], DimSize);

            CompareSplitBlocks(pData, Index[FirstBlock], BlockSize[FirstBlock], Index[SecondBlock], BlockSize[SecondBlock]);
        }
    }

    // Локальная сортировка блоков данных
#pragma omp parallel
    {
        int BlockID = ReverseGrayCode(ThreadNum + ThreadID, DimSize);
        SerialQuickSort(pData, Index[BlockID], Index[BlockID] + BlockSize[BlockID] - 1);
        BlockID = ReverseGrayCode(ThreadID, DimSize);
        SerialQuickSort(pData, Index[BlockID], Index[BlockID] + BlockSize[BlockID] - 1);
    }

    // Чет-нечетная перестановка 
    int Iter = 1;
    while (!IsSorted(pData, Size))
    {
#pragma omp parallel 
        {
            if (Iter % 2 == 0) {
                // четная итерация 
                MergeBlocks(pData, Index[2 * ThreadID], BlockSize[2 * ThreadID], Index[2 * ThreadID + 1], BlockSize[2 * ThreadID + 1]);
            }
            else {
                // нечетная итерация 
                if (ThreadID < ThreadNum - 1)
                    MergeBlocks(pData, Index[2 * ThreadID + 1], BlockSize[2 * ThreadID + 1], Index[2 * ThreadID + 2], BlockSize[2 * ThreadID + 2]);
            }
        }
        Iter++;
    }
    delete[] Index;
    delete[] BlockSize;
    delete[] BlockPairs;
}
//-----------------------------------------------------------

	//--------------------Быстрая сортировка---------------------

// Последовательный алгоритм быстрой сортировки
void SerialQuickSort(double* pData, int first, int last) 
{
    while (first < last) 
    {
        int PivotPos = first;
        double Pivot = pData[first];
        for (int i = first + 1; i <= last; i++) 
        {
            if (pData[i] < Pivot) 
            {
                if (i != PivotPos + 1)
                    swap(pData[i], pData[PivotPos + 1]);
                PivotPos++;
            }
        }
        swap(pData[first], pData[PivotPos]);

        if (PivotPos - first < last - PivotPos) {
            SerialQuickSort(pData, first, PivotPos - 1);
            first = PivotPos + 1;
        }
        else {
            SerialQuickSort(pData, PivotPos + 1, last);
            last = PivotPos - 1;
        }
    }
}

// Функция для операции "Сравнить и разделить" 
void qCompareSplitBlocks(double* pFirstBlock, int& FirstBlockSize, double* pSecondBlock, int& SecondBlockSize, double Pivot)
{
    int TotalSize = FirstBlockSize + SecondBlockSize;
    double* pTempBlock = new double[TotalSize];
    int LastMin = 0, FirstMax = TotalSize - 1;

    for (int i = 0; i < FirstBlockSize; i++) 
    {
        if (pFirstBlock[i] < Pivot) 
            pTempBlock[LastMin++] = pFirstBlock[i];
        else 
            pTempBlock[FirstMax--] = pFirstBlock[i];
    }
    
    for (int i = 0; i < SecondBlockSize; i++) {
        if (pSecondBlock[i] < Pivot) 
            pTempBlock[LastMin++] = pSecondBlock[i];
        else 
            pTempBlock[FirstMax--] = pSecondBlock[i];
    }

    FirstBlockSize = LastMin;
    SecondBlockSize = TotalSize - LastMin;

    for (int i = 0; i < FirstBlockSize; i++) 
        pFirstBlock[i] = pTempBlock[i];

    for (int i = 0; i < SecondBlockSize; i++) 
        pSecondBlock[i] = pTempBlock[FirstBlockSize + i];
      
    delete[] pTempBlock;
}

// Функция для определения пар блоков 
void qSetBlockPairs(int* BlockPairs, int Iter)
{
    int PairNum = 0, FirstValue, SecondValue;
    bool Exist;

    for (int i = 0; i < 2 * ThreadNum; i++)
    {
        FirstValue = i;
        Exist = false;

        for (int j = 0; (j < PairNum) && (!Exist); j++)
            if (BlockPairs[2 * j + 1] == FirstValue) 
                Exist = true;

        if (!Exist) {
            SecondValue = FirstValue^(1 << (DimSize - Iter - 1));
            BlockPairs[2 * PairNum] = FirstValue;
            BlockPairs[2 * PairNum + 1] = SecondValue;
            PairNum++;
        }
    }
}

double MaxElementOfArray(double* pData, int Size);

double MinElementOfArray(double* pData, int Size);

// Параллельный алгоритм быстрой сортировки
void ParallelQuickSort(double* pData, int Size) 
{
    InitializeParallelSections();
    double** pTempData = new double* [2 * ThreadNum]; // Система буферов
    int* BlockSize = new int[2 * ThreadNum];
    double* Pivots = new double[ThreadNum];
    int* BlockPairs = new int[2 * ThreadNum];

    double AvailableThreadNum = 2 * ThreadNum;
    double CurrentSize = Size;

    for (int i = 0; i < 2 * ThreadNum; i++)
    {
        pTempData[i] = new double[Size];

        BlockSize[i] = ceil(CurrentSize / AvailableThreadNum);

        CurrentSize = CurrentSize - BlockSize[i];
        AvailableThreadNum--;
    }

    int ind = 0;
    for (int i = 0; i < 2 * ThreadNum; i++)
        for (int j = 0; j < BlockSize[i]; j++)
            pTempData[i][j] = pData[ind++];

    double MaxValue = MaxElementOfArray(pData, Size);
    double MinValue = MinElementOfArray(pData, Size);

    // Итерации быстрой сортировки 
    for (int i = 0; i < DimSize; i++) {
        // Определение ведущих значений 
        for (int j = 0; j < ThreadNum; j++)
        {
            Pivots[j] = (MaxValue + MinValue) / 2;
        }

        for (int iter = 1; iter <= i; iter++)
            for (int j = 0; j < ThreadNum; j++)
            {
                Pivots[j] = Pivots[j] - pow(-1.0f, j / ((2 * ThreadNum) >> (iter + 1))) * (MaxValue - MinValue) / (2 << iter);
            }

        // Определение пар блоков 
        qSetBlockPairs(BlockPairs, i);

#pragma omp parallel 
        {
            int MyPair = FindMyPair(BlockPairs, ThreadID, i);
            int FirstBlock = BlockPairs[2 * MyPair];
            int SecondBlock = BlockPairs[2 * MyPair + 1];

            qCompareSplitBlocks(pTempData[FirstBlock], BlockSize[FirstBlock], pTempData[SecondBlock], BlockSize[SecondBlock], Pivots[ThreadID]);
        }
    }
    
    // Локальная сортировка 
#pragma omp parallel 
    {
        if (BlockSize[2 * ThreadID] > 0)
            SerialQuickSort(pTempData[2 * ThreadID], 0, BlockSize[2 * ThreadID] - 1);
        if (BlockSize[2 * ThreadID + 1] > 0)
            SerialQuickSort(pTempData[2 * ThreadID + 1], 0, BlockSize[2 * ThreadID + 1] - 1);
    }

    ind = 0;
    for (int i = 0; i < 2 * ThreadNum; i++)
        for (int j = 0; (j < BlockSize[i]) && (ind < Size); j++)
            pData[ind++] = pTempData[i][j];
    
    for (int i = 0; i < ThreadNum; i++)
        delete[] pTempData[i];

    delete[] pTempData;
    delete[] BlockSize;
    delete[] Pivots;
    delete[] BlockPairs;
}
//-----------------------------------------------------------

double MaxElementOfArray(double* pData, int Size)
{
    double Max = pData[0];

    for ( int i = 0; i < Size; i++)
        if (pData[i] > Max) Max = pData[i];

    return Max;
}

double MinElementOfArray(double* pData, int Size)
{
    double Min = pData[0];

    for (int i = 0; i < Size; i++)
        if (pData[i] < Min) Min = pData[i];

    return Min;
}

void PrintArray(double* pData, int Size)
{
    for (int i = 0; i < Size; i++)
        cout << pData[i] << " ";
    cout << endl;
}

void CopyArray(double* A, double* B, int n)
{
    for (int i = 0; i < n; i++)
        B[i] = A[i];
}
	
}

void main()
{
	// Matrixi
	/*int** A = Matrixes::matr(siz, siz, 2);
	int** B = Matrixes::matr(siz, siz, 2);
	Matrixes::linear(A, B, siz, siz, siz); 
	Matrixes::tape(A, B, siz, siz, siz);
	Matrixes::BlockAr(A, B);*/
	
	// Jakobi
	//int n = 8;
	//double** A = JakobiMethod::initMatr(n);
	////Matrixes::print(A, n, n);
	//double* F = JakobiMethod::initVector(n, -23.6653);
	//
	//double* X = JakobiMethod::initVector(n, 10029046732);
	//JakobiMethod::JacobiLinear(n, A, F, X);
	//JakobiMethod::JacobiParallel(n, A, F, X);

	//double** A = Matrixes::ReadMatrFile("matr.txt");
	// matr 4x4 file for yakobi
	/*F[0] = 6;
	F[1] = -9;
	F[2] = 5;
	F[3] = 2;*/
	
	// matr 8x8 file for yakobi
	/*F[0] = 6;
	F[1] = -9;
	F[2] = 5;
	F[3] = 2;
	F[4] = 6;
	F[5] = -9;
	F[6] = 5;
	F[7] = 2;*/

	
	// simpson
	cout << Simpson::methodSimpson(-3.5, 3.5) << endl;
	cout << Simpson::methodSimpsonParalell(-3.5, 3.5) << endl;

int arrSize = 10000;
double* arr = initArr(arrSize);
double* arrCopied = copyArr(arr, arrSize)

OddEvenSort(arr, arrSize);
ParallelOddEvenSort(arr, arrSize);
	system("pause");

}

double* initArr (int arrSize)
{
double* newArr = new double [arrSize];
for (int i = 0; i < arrSize; i++) 
    newArr[i] = rand();
return newArr;
} 

double* copyArr (double* arr, int arrSize)
{
double* newArr = new double [arrSize];
for (int i = 0; i < arrSize; i++) 
    newArr[i] = arr[i];
return newArr;
}

/*
	// создаем объект класса, чтобы можно было обращаться к его методам
	// Matrixes matrix;

	// Ленточное и линейное умножение в массивах
	cout << omp_get_max_threads() << endl;
	// Обращаяемся к статическим методам класса Matrixes


	/*vector<vector<double>> A(3, vector<double>(3, 0.0));
	A[0][0] = 8.0;
	A[0][1] = 1.0;
	A[0][2] = -4.0;
	A[1][0] = 2.0;
	A[1][1] = -6.0;
	A[1][2] = 1.0;
	A[2][0] = -1.0;
	A[2][1] = 1.0;
	A[2][2] = 4.0;


	vector<double> F(3, 0.0);
	F[0] = 6.0;
	F[1] = -9.0;
	F[2] = 5.0;
	vector<double> X (3, 0.0);

double F[] = { 6.0, -9.0, 5.0 };

double* X = new double[3];
X[0] = 0.0;
X[1] = 0.0;
X[2] = 0.0;

double** A = Matrixes::ReadMatrFile("inputMatr.txt");

for (int i = 0; i < siz; i++) {
	for (int j = 0; j < siz; j++)
		cout << A[i][j] << " ";
	cout << endl;
}


JakobiMethod::JacobiLinear(siz, A, F, X);

//JakobiMethod::JacobiParallel(3, A, F, X);

// Matrixes::print(A, size, size);

//tape(A, B, size, size, size);

//// Блочное умножение в векторах
///*vector<vector<int>> matr1 = matrInit(size);
//vector<vector<int>> matr2 = matrInit(size);
//BlockV(matr1, matr2);
////matrOut(matr1, size);

//linear(A, B, size, size, size);

//BlockAr(A, B);
*/

// A
// 8 1 -4
// 2 -6 1
// -1 1 4

// F
// 6 -9 5

// ответ
// 1.0216, 2.0225, 0.9912
