#pragma once
#include "lib.h"
#include "constants.h"

class Matrix
{
private:
    int m; // стоолбцы
    int n; // строки
    double **A;

public:
    Matrix()
    {
        m = 0;
        n = 0;
        A = 0;
    }

    Matrix(int N, int M)
    {
        n = N;
        m = M;
        A = new double *[n];
        for (int i = 0; i < n; ++i)
        {
            A[i] = new double[m];
            for (int j = 0; j < m; ++j){
                A[i][j] = 0;
            }
        }
        std::cout<<"constructor done"<<std::endl;
    }

    void insert(int i, int j, double x)
    {
        A[i][j] = x;
    }

    double operator()(int i, int j)
    {
        return A[i][j];
    }

    void print_Matrx()
    {

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                std::cout << std::setw(5) << A[i][j];
            }
            std::cout << std::endl;
        }
    }


    void write_to_mtx(std::vector<int> &ai,
                    std::vector<int> &aj,
                    std::vector<double> &a)
    {
        std::string filename = "../data/A.mtx";
        std::ofstream file;
        file.open(filename);
        for (int i = 0; i < a.size(); ++i) {
            file<<ai[i]<<" "<<aj[i]<<" "<<a[i]<<std::endl;
        }
        file.close();
        std::cout<<"A.mtx done"<<std::endl;
    }

    ~Matrix()
    {
        for (int z = 0; z < m; z++)
            delete[] A[z];

        delete[] A;
    }
};
