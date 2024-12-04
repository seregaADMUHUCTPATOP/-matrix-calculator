#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <algorithm>
using namespace std;
class Matrix {
public:
    vector<vector<double>> data;
    int rows, cols;
    Matrix(int rows, int cols) : rows(rows), cols(cols) { data.resize(rows, vector<double>(cols, 0.0)); }
    void inputMatrix() {
        cout << "Введите элементы матрицы (" << rows << "x" << cols << "):" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double val;
                while (!(cin >> val)) {
                    cout << "Ошибка ввода. Повторите ввод элемента [" << i + 1 << "][" << j + 1 << "]: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                data[i][j] = val;
            }
        }
    }
    void printMatrix() const {
        cout << fixed << setprecision(2);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
    Matrix operator+(const Matrix& other) const { return addSub(other, '+'); }
    Matrix operator-(const Matrix& other) const { return addSub(other, '-'); }
    Matrix operator*(const Matrix& other) const { return multiply(other); }
    Matrix transpose() const { return transposeMatrix(); }
    double determinant() const { return calculateDeterminant(); }
private:
    Matrix addSub(const Matrix& other, char op) const {
        checkDimensions(other);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = (op == '+') ? data[i][j] + other.data[i][j] : data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    Matrix multiply(const Matrix& other) const {
        if (cols != other.rows) {
            throw runtime_error("Несовместимые размеры матриц для умножения.");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
    Matrix transposeMatrix() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }
    double calculateDeterminant() const {
        if (rows != cols) {
            throw runtime_error("Определитель можно вычислить только для квадратных матриц.");
        }
        if (rows == 1) return data[0][0];
        if (rows == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        throw runtime_error("Вычисление определителя поддерживается только для матриц 1x1 и 2x2.");
    }
    void checkDimensions(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw runtime_error("Матрицы должны иметь одинаковые размеры для сложения/вычитания.");
        }
    }
};
int main() {
    setlocale(LC_ALL, "RUSSIAN");
    char operation;
    int rowsA, colsA, rowsB, colsB;
    cout << "Выберите операцию (+, -, *, t, d): ";
    cin >> operation;
    while (true) {
        cout << "Введите размеры матрицы A (строки столбцы, целые положительные числа): ";
        if (cin >> rowsA >> colsA && rowsA > 0 && colsA > 0) break;
        cout << "Ошибка ввода размеров. Повторите.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (true) {
        cout << "Введите размеры матрицы B (строки столбцы, целые положительные числа): ";
        if (cin >> rowsB >> colsB && rowsB > 0 && colsB > 0) break;
        cout << "Ошибка ввода размеров. Повторите.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    Matrix matrixA(rowsA, colsA);
    Matrix matrixB(rowsB, colsB);
    try {
        matrixA.inputMatrix();
        matrixB.inputMatrix();
        Matrix result(1,1); 
        if (operation == '+') {
            if (matrixA.rows != matrixB.rows || matrixA.cols != matrixB.cols) throw runtime_error("Матрицы должны иметь одинаковые размеры для сложения.");
            result = matrixA + matrixB;
        } else if (operation == '-') {
            if (matrixA.rows != matrixB.rows || matrixA.cols != matrixB.cols) throw runtime_error("Матрицы должны иметь одинаковые размеры для вычитания.");
            result = matrixA - matrixB;
        } else if (operation == '*') {
            if (matrixA.cols != matrixB.rows) throw runtime_error("Несовместимые размеры матриц для умножения.");
            result = matrixA * matrixB;
        } else if (operation == 't') {
            result = matrixA.transpose();
            cout << "Результат (транспонированная матрица A):" << endl;
            result.printMatrix();
            result = matrixB.transpose();
            cout << "Результат (транспонированная матрица B):" << endl;
            result.printMatrix();
            return 0;
        } else if (operation == 'd') {
            cout << "Определитель A: " << matrixA.determinant() << endl;
            cout << "Определитель B: " << matrixB.determinant() << endl;
            return 0;
        } else {
            cout << "Неверная операция." << endl;
            return 1;
        }
        cout << "Результат:" << endl;
        result.printMatrix();
    } catch (const runtime_error& error) {
        cerr << "Ошибка: " << error.what() << endl;
        return 1;
    }
    return 0;
}
