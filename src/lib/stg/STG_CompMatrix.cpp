// #ifndef __COMPRESSEDFORMAT_CPP__
// #define __COMPRESSEDFORMAT_CPP__

#include "STG_CompMatrix.hpp"

// ============= C++ ============= //
// ========= Реализации ========== //

STG::CMatrix::CMatrix() { }

STG::CMatrix::CMatrix(size_t N)
{
	this->N = N;
	CompressedMatrix.resize(N);
}

// Получить элемент на месте [i,j]
double STG::CMatrix::get_value(size_t i, size_t j) const 
{
	// Такой алгоритм быстрее чем 
	// return CompressedMatrix[i][j]; Не понятно почему
	auto fnd = CompressedMatrix[i].find(j);
	if (fnd == CompressedMatrix[i].end())
	{
		return 0;
	} 
	else
	{
		return fnd->second;
	}
}

// Добавить элемент (а) в матрицу на место [i,j] 
void STG::CMatrix::set_value(size_t i, size_t j, double a)
{
	if(a == 0) 
	{	
		// For constructions like:
		// Matrix.set_value(i, j, Matrix.GetValue(i, j) + a)
		// if *Matrix.GetValue(i, j) + a* == 0 need to clear element i,j
		CompressedMatrix[i].erase(j);
	} else
	{
		CompressedMatrix[i][j] = a;
	}
}

// Уможение разреженной матрицы на вектор
std::vector<double> STG::CMatrix::operator*(const std::vector<double> &Vector) const
{
	if (Vector.size() == ! N)
	{
		throw std::runtime_error("Dimensions of vector and matrix doesn't match");
	}
	
	// Вектор в который записывается результат
	std::vector<double> Result(N);
	for (size_t i = 0; i < N; i++)
	{	
		// Внутренняя сумма (*Скалярное произведение строки на вектор*)
		double Sum = 0;
		for (auto elem : CompressedMatrix[i])
		{
			Sum += Vector[elem.first] * elem.second;
		} // elem  	// Наиболее быстрый найденный вариант
					// Хоть и в геттере есть возвращение 0 на любой элемент матрицы если его нет в @CompressedMatrix
					// Пробег лишь по не нулевым элементам быстрее
		Result[i] = Sum;
	} // i
	return Result;
}

// Умножение матрицы на число
STG::CMatrix STG::CMatrix::operator*(const double a) const
{
	// Возвращается новая матрица
	CMatrix Result(N);
	for (size_t i = 0; i < N; i++)
	{
		for (auto elem : CompressedMatrix[i])
		{
			Result.set_value(i, elem.first, elem.second * a);
		} // elem 	// Наискорейший вариант
	} // i
	return Result;
}

// Умножение матриц разряженного типа
STG::CMatrix STG::CMatrix::operator*(CMatrix &Matrix) const
{
	// Возвращается новая матрица
	CMatrix Result(N);
	for (size_t i = 0; i < N; i++) 
	{			
		for (size_t j = 0; j < N; j++) 
		{
			// Внутренняя сумма
			double Sum = 0;
			for (auto elem : CompressedMatrix[i]) 
			{
				// ! Тут поменял
				Sum += elem.second * Matrix.get_value(elem.first, j);
			} // elem 
			if (Sum != 0)
			{
				Result.set_value(i,j, Sum);
			} //endif
		} // j
	} // i
	return Result;
}

// Перегрузка скобок, т.к. часто необходимо обращаться к строкам матрицы
// Так будет быстрее чем GetValue и удобней
std::map<size_t, double> STG::CMatrix::operator[](size_t i) const
{
	return CompressedMatrix[i];
}

// Перегрузка оператора = 
// Используется для конструкций CMatrix C = A * B
STG::CMatrix STG::CMatrix::operator=(CMatrix &Matrix_A)
{
	for (size_t i = 0; i < Matrix_A.size(); i++)
	{
		this->CompressedMatrix[i] = Matrix_A[i];
	}
	return *this;
}

// Возвращает нижне-треугольную матрицу разложения холецкого
STG::CMatrix STG::CMatrix::do_cholesky_decomp() const
{
	if (N == 3)
	{
		return do_cholesky_decomp_low_dim();
	}
	
	// Ход алгоритма для нахождения L(ower)
	CMatrix L(this->N);
	for (size_t i = 0; i < N; i++) 
	{
		for (size_t j = 0; j <= i; j++) 
		{
			double sum = 0;
			for (size_t k = 0; k < j; k++)
			{
				sum += L.get_value(i,k) * L.get_value(j,k);
			}
			if (i == j)
			{
				L.set_value(i,i, sqrt(this->get_value(i,i) - sum));
			}
			else
			{
				double Diff = this->get_value(i,j) - sum;
				if (Diff != 0)
				{
					L.set_value(i,j, (1.0 / L.get_value(j,j) * (Diff)));
				}
			}
		}
	}

	return L;
}

// Возвращает нижне-треугольную матрицу разложения холецкого
STG::CMatrix STG::CMatrix::do_cholesky_decomp_low_dim() const
{
	STG::CMatrix lower(3);

	lower.set_value(0, 0, sqrt(this->get_value(0,0)));
	lower.set_value(1, 0, this->get_value(1,0) / lower.get_value(0, 0));
	lower.set_value(1, 1, sqrt(this->get_value(1,1) - lower.get_value(1, 0) * lower.get_value(1, 0)));
	lower.set_value(2, 0, this->get_value(2,0) / lower.get_value(0, 0));
	lower.set_value(2, 1, (this->get_value(2,1) - lower.get_value(1,0) * lower.get_value(2,0)) / lower.get_value(1,1));
	lower.set_value(2, 2, sqrt(this->get_value(2,2) - lower.get_value(2, 0) * lower.get_value(2, 0) - lower.get_value(2, 1) * lower.get_value(2, 1)));

	return lower;
}

// Возвращает число строк матрицы
size_t STG::CMatrix::size() const
{
	return this->N;
}

void STG::CMatrix::resize(size_t N)
{
	CompressedMatrix.resize(N);
	this->N = N;
}

void STG::CMatrix::set_zero_row(size_t i)
{
	CompressedMatrix[i].clear();
}

STG::CMatrix::~CMatrix() { }

// #endif