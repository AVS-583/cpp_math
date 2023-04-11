#ifndef MATRIX_HPP
#define MATRIX_HPP
/*!
\defgroup Matrix_ Класс матрица
\file
\brief Заголовочный файл для класса матрица. Включает объявление класса и методов.
 Здесь так же находятся исходные коды конструкторов и деструкторов класса.
 @{
*/

/// Объявление класса Matrix
class Matrix {
private:
    int rows, cols;                                 ///< Строки, столбцы матрицы
    double** matrix;
public:
    /// Конструктор класса, создающий динамический массив - матрицу. При инициализации матрица заполняется нулями
    Matrix(int rows, int cols)
    {
        //cout << "Вызван конструктор " << this << endl;
        this->rows = rows;
        this->cols = cols;
        matrix = new double* [rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new double[cols];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    /// Конструктор копирования
    Matrix(const Matrix& other)
    {
        //cout << "Вызван конструктор копирования " << this << endl;
        this->rows = other.rows;
        this->cols = other.cols;
        matrix = new double* [rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new double[cols];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    /// Деструктор класса, освобождающий память
    ~Matrix()
    {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        //cout << "Вызван деструктор " << this << endl;
    }

    Matrix& operator= (const Matrix& other);        ///<  Метод реализации присваивания через глубокое копирование

    double& operator() (int row, int col);          ///<  Метод доступа к элементу матрицы
    /*!
    * Методы сложения (вычитания) матриц, умножения матрицы на матрицу и матрицы на скаляр 
    * реализуются через перегрузку операторов +(-) и * соответсвенно 
    * не изменяют исходную матрицу, а возвращают новую
    */
    Matrix operator+ (const Matrix& other);         ///<  Метод сложения матриц
    Matrix operator- (const Matrix& other);         ///<  Метод вычитания матриц
    Matrix operator* (const Matrix& other);         ///<  Метод умножения матриц
    Matrix operator* (const double scalar);         ///<  Метод умножения матрицы на число
    /*!
    * Методы умножения матрицы на матрицу и матрицы на скаляр дублируются перегруженным методом multiply
    * В отличие от оператора *, multiply изменяет исходную матрицу
    */
    void multiply(const Matrix& other);             ///<  Метод умножения матриц с изменением исходной матрицы
    void multiply(const double scalar);             ///<  Метод умножения матрицы на число с изменением исходной матрицы
    /*!
    * Методы для прочих вычислений с матрицей
    */
    Matrix transpose() const;                       ///<  Метод транспонирования  
    double det();                                   ///<  Метод вычисления определителя матрицы
    Matrix minor(int row, int col);                 ///<  Метод вычисления минора матрицы
    Matrix inverse();                               ///<  Метод вычисления обратной матрицы
    /*!
    * Другие методы
    */
    void identity();                                ///<  Метод создания единичной матрицы
    void print(const std::string name = "") const;  ///<  Метод вывода матрицы в консоль
};
#endif // !MATRIX_HPP
/*! @} */