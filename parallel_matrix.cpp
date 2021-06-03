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
#define eps 0.01

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
		cout << "Time of parallel Jakobi: " << t << endl;
		printVector(N, X);
		cout << "Sum parallel: " << sumVectorX(N, X) << endl;
		cout << endl;
	}

	static void JacobiLinear(int N, double** A, double* F, double* X)
	{
		double* TempX = initVector(siz, 0.0);
		double norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.
		double t = omp_get_wtime();
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
			//cout << "norma = " << norm << endl;
		} while (norm > eps);
		t = omp_get_wtime() - t;
		cout << "Time of linear Jakobi: " << t << endl;
		printVector(N, X);
		cout << "Sum linear: " << sumVectorX(N, X) << endl;
		cout << endl;
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
					A[i][j] = n + 20;
				else
					A[i][j] = 1;
		return A;
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
		double accurasy = 0.1;
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

	static double methodSimpsonParalell(double a, double b)
	{
		double t = omp_get_wtime();
		double sum = 0;
		int k = 4;
#pragma omp parallel num_threads(k) shared(sum)
		{
			double kol = (b - a) / k; //0-25 26-50 21-75 76-100
			int cur = omp_get_thread_num();
			double cursum = methodSimpson(kol * cur + a, kol * (cur + 1) + a);
#pragma omp critical
			cout << cursum << ' ' << kol * cur + a << ' ' << kol * (cur + 1) + a << endl;
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

void main()
{
	// Matrixi
	int** A = Matrixes::matr(siz, siz, 2);
	int** B = Matrixes::matr(siz, siz, 2);
	Matrixes::linear(A, B, siz, siz, siz); 
	Matrixes::tape(A, B, siz, siz, siz);
	Matrixes::BlockAr(A, B);

	// проверка работы метода заполнения матрицы
	/*double** At = JakobiMethod::initMatr(5);
	Matrixes::print(At, 5, 5);*/

	// Jakobi
	//int n = 12;
	//double** A = JakobiMethod::initMatr(n);
	//Matrixes::print(A, n, n);
	//double* F = JakobiMethod::initVector(n, 3);
	
	//double** A = Matrixes::ReadMatrFile("matr.txt");
	// matr 4x4 file
	/*F[0] = 6;
	F[1] = -9;
	F[2] = 5;
	F[3] = 2;*/
	
	// matr 8x8 file
	/*F[0] = 6;
	F[1] = -9;
	F[2] = 5;
	F[3] = 2;
	F[4] = 6;
	F[5] = -9;
	F[6] = 5;
	F[7] = 2;*/

	//double* X = JakobiMethod::initVector(n, 0);
	//JakobiMethod::JacobiLinear(n, A, F, X);
	//JakobiMethod::JacobiParallel(n, A, F, X);

	// simpson
	//cout << Simpson::methodSimpson(-3.5, 3.5) << endl;
	//cout << Simpson::methodSimpsonParalell(-3.5, 3.5) << endl;

	system("pause");
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
