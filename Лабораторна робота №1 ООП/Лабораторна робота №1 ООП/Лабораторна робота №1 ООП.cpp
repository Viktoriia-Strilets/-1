
#include <iostream>

class Matrix
{
private:
    int row;
    int column;
    int** array;

public:

    Matrix();
    Matrix(int , int );
    Matrix(int** , int , int );
    Matrix(const Matrix& );

    Matrix AddMatrix(const Matrix& );
    Matrix MultTwoMatrixs(const Matrix& );
    Matrix MultMatrixToNumber(int num);
    Matrix MatrixTransposition();

    void InputMatrix();
    void PrintMatrix() const;

    bool Equal(Matrix) const;

    ~Matrix();
};

Matrix::Matrix() : row(0), column(0) {
    array = new int* [2];
    array[0] = new int[2] {0, 0};
    array[1] = new int[2] {0, 0};
}
    
Matrix::Matrix(int r, int c) : row(r), column(c) {

    if (r <= 0 || c <= 0) abort();
    array = new int* [row];
    for (int i = 0; i < row; i++) {
        array[i] = new int[column];
        for (int j = 0; j < column; j++) {
            array[i][j] = 0;
        }
    }
}

Matrix::Matrix(int** A, int r, int c) : row(r), column(c) {

    if (r <= 0 || c <= 0) abort();
    array = new int* [r];

    for (int i = 0; i < row; i++) {
        array[i] = new int[c];
        for (int j = 0; j < column; j++) {
            array[i][j] = A[i][j];
        }
    }
}
    
Matrix::Matrix(const Matrix& B) : row(B.row), column(B.column) {

    array = new int* [row];
    for (int i = 0; i < row; ++i) {
        array[i] = new int[column];
        for (int j = 0; j < column; ++j) {
            array[i][j] = B.array[i][j];
        }
    }
}
 
Matrix  Matrix::AddMatrix(const Matrix& B) {
    Matrix C(this->row, this->column);

    if (this->row != B.row || this->column != B.column) {
        abort();
    }
    else {

        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->column; j++) {
                C.array[i][j] = this->array[i][j] + B.array[i][j];
            }
        }
    }
    return C;
}

Matrix  Matrix::MultTwoMatrixs(const Matrix& B) {
    Matrix C(this->row, B.column);

    if (this->column != B.row) {
        abort();
    }
    else {
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < B.column; j++) {
                C.array[i][j] = 0;
                for (int t = 0; t < this->column; t++) {
                    C.array[i][j] += this->array[i][t] * B.array[t][j];
                }
            }
        }
    }
    return C;
}

Matrix  Matrix::MultMatrixToNumber(int num) {
    Matrix C(this->row, this->column);

    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            C.array[i][j] = this->array[i][j] * num;
        }
    }
    return C;
}

Matrix  Matrix::MatrixTransposition() {
    Matrix C(this->column, this->row);

    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->column; ++j) {
            C.array[j][i] = this->array[i][j];
        }
    }
    return C;
}

void Matrix::InputMatrix() {
    int num;
    std::cout << "Number of matrix rows : " << std::endl;
    std::cin >> row;
    std::cout << "Number of matrix columns : " << std::endl;
    std::cin >> column;
    std::cout << "Input elements of matrix : " << std::endl;

    array = new int* [row];
    for (int i = 0; i < row; i++) {
        array[i] = new int[column];
        for (int j = 0; j < column; j++) {
            std::cin >> num;
            array[i][j] = num;
        }
    }
}

void Matrix::PrintMatrix() const {

    if (array == nullptr) {
        std::cout << "Matrix is empty" << std::endl;
        return;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Matrix::Equal(Matrix B) const {
    if (row != B.row || column != B.column) {
        return false;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (array[i][j] == B.array[i][j]) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

Matrix:: ~Matrix() {

    if (array != nullptr) {
        for (int i = 0; i < row; i++) {
            delete[] array[i];
        }
        delete[] array;
    }
}


int main()
{
    int** ArrayA = new int* [3] { new int[3] {1, 2, 3}, new int[3] {3, 4, 5}, new int[3] {1, 4, 5} };    
    
    Matrix A(ArrayA, 2, 2);
    std::cout << "Matrix A: " << std::endl;
    A.PrintMatrix();

    Matrix B;
    B.InputMatrix();
    std::cout << "Matrix B: " << std::endl;
    B.PrintMatrix();

    std::cout << "Transposition Matrix A: " << std::endl;
    Matrix C(A.MatrixTransposition());
    C.PrintMatrix();

    std::cout << "Add Matrix A+B: " << std::endl;
    Matrix D(A.AddMatrix(B));
    D.PrintMatrix();

    std::cout << "MultMatrix 2*A: " << std::endl;
    Matrix E( A.MultMatrixToNumber(2));
    E.PrintMatrix();

    std::cout << "Mult Matrix A*B: " << std::endl;
    Matrix F(A.MultTwoMatrixs(B));
    F.PrintMatrix();

    std::cout << A.Equal(B) << std::endl;

    for (int i = 0; i < 2; i++) {
        delete[] ArrayA[i];
    }
    delete[] ArrayA;
    
    return 0;
    
}

