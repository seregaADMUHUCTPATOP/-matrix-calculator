#include <iostream>
#include <vector>
int main {
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
        cout << "Ââåäèòå ýëåìåíòû ìàòðèöû (" << rows << "x" << cols << "):" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double val;
                while (!(cin >> val)) {
                    cout << "Îøèáêà ââîäà. Ïîâòîðèòå: ";
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
            throw runtime_error("Íåñîâìåñòèìûå ðàçìåðû ìàòðèö äëÿ óìíîæåíèÿ.");
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
            throw runtime_error("Îïðåäåëèòåëü ìîæíî âû÷èñëèòü òîëüêî äëÿ êâàäðàòíûõ ìàòðèö.");
        }
        if (rows == 1) return data[0][0];
        if (rows == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];

        //  For larger matrices, a more sophisticated determinant calculation is needed (e.g., LU decomposition).
        throw runtime_error("Âû÷èñëåíèå îïðåäåëèòåëÿ ïîääåðæèâàåòñÿ òîëüêî äëÿ ìàòðèö 2x2.");


    }

    void checkDimensions(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw runtime_error("Ìàòðèöû äîëæíû èìåòü îäèíàêîâûå ðàçìåðû äëÿ ýòîé îïåðàöèè.");
        }
    }
};
=======
using namespace std;
vector<vector<int>> inputMatrix(int rows, int cols) {
    setlocale(LC_ALL, "Russian");
    vector<vector<int>> matrix(rows, vector<int>(cols));
    cout << "Ââåäèòå ýëåìåíòû ìàòðèöû:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}
}
