#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 1e-10;

bool isZeroRow(const vector<double> &row)
{
    for (double val : row)
    {
        if (abs(val) > EPSILON)
            return false;
    }
    return true;
}

int rankOfMatrix(vector<vector<double>> &matrix)
{
    int row = matrix.size();
    int col = matrix[0].size();
    int rank = 0;

    vector<bool> usedRows(row, false);

    for (int c = 0; c < col; c++)
    {
        int pivot_row = -1;

        double max_val = EPSILON;
        for (int r = 0; r < row; r++)
        {
            if (!usedRows[r] && abs(matrix[r][c]) > max_val)
            {
                max_val = abs(matrix[r][c]);
                pivot_row = r;
            }
        }

        if (pivot_row != -1)
        {
            usedRows[pivot_row] = true;
            rank++;

            double pivot = matrix[pivot_row][c];
            for (int j = c; j < col; j++)
            {
                matrix[pivot_row][j] /= pivot;
            }

            for (int r = 0; r < row; r++)
            {
                if (r != pivot_row && !isZeroRow(matrix[r]))
                {
                    double factor = matrix[r][c];
                    for (int j = c; j < col; j++)
                    {
                        matrix[r][j] -= factor * matrix[pivot_row][j];
                    }
                }
            }
        }
    }

    return rank;
}

void printMatrix(const vector<vector<double>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (double val : row)
        {
            cout << val << "\t";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<double>> matrix = {
        {1, 1, 1, 0}, // [0,1,2]
        {1, 0, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 1, 0} // [0,2,3]
        // {1, 1, 1, 1}  // [0,1,2,3]
    };

    cout << "Original matrix:" << endl;
    printMatrix(matrix);

    int rank = rankOfMatrix(matrix);
    cout << "\nAfter Gaussian elimination:" << endl;
    printMatrix(matrix);
    cout << "\nThe rank of the matrix is: " << rank << endl;

    return 0;
}