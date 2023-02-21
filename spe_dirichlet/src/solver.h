#pragma once
#include "lib.h"
#include "constants.h"
#include "Matrix.h"
#include "read_file.h"


void get_SLAY(Matrix &A, double b[nx * ny],
              std::vector<double> &kx,
              std::vector<double> &ky)
            
{
    std::vector<int> ai;
    std::vector<int> aj;
    std::vector<double> a;

    std::cout << "\nStart creating matrix A and vector b" << std::endl;
    double Tau0, Tau1, Tau2, Tau3, Tau4;
    for (int i = 0; i < nx * ny; ++i)
    {
        b[i] = 0;

        if (i < nx)
        {
            b[i] += -2 * ky[i] / (hy * hy) * up;
            Tau2 = 2 * ky[i] / (hy * hy);
        }
        else
        {
            Tau2 = 2 * ky[i] * ky[i - nx] / ((hy * hy) * (ky[i] + ky[i - nx]));
            A.insert(i, i - nx, Tau2);
            // if (Tau2!=0)
            // {
            //     ai.push_back(i);
            //     aj.push_back(i - nx);
            //     a.push_back(Tau2);
            // }
        }
        if (i % nx == 0)
        {
            b[i] += -2 * kx[i] / (hx * hx) * left;
            Tau3 = 2 * kx[i] / (hx * hx);
        }
        else
        {
            Tau3 = 2 * kx[i] * kx[i - 1] / ((hx * hx) * (kx[i] + kx[i - 1]));
            A.insert(i, i - 1, Tau3);
            // if (Tau3 != 0)
            // {
            //     ai.push_back(i);
            //     aj.push_back(i-1);
            //     a.push_back(Tau3);
            // }
        }
        if ((i + 1) % nx == 0)
        {
            b[i] += -2 * kx[i] / (hx * hx) * right;
            Tau1 = 2 * kx[i] / (hx * hx);
        }
        else
        {
            Tau1 = 2 * kx[i] * kx[i + 1] / ((hx * hx) * (kx[i] + kx[i + 1]));
            A.insert(i, i + 1, Tau1);
            // if (Tau1 != 0)
            // {
            //     ai.push_back(i);
            //     aj.push_back(i + 1);
            //     a.push_back(Tau1);
            // }


        }
        if (nx * (ny - 1) <= i)
        {
            b[i] += -2 * ky[i] / (hy * hy) * bottom;
            Tau4 = 2 * ky[i] / (hy * hy);
        }
        else
        {
            Tau4 = 2 * ky[i] * ky[i + nx] / ((hy * hy) * (ky[i] + ky[i +nx]));
            A.insert(i,i + nx,Tau4);
            // if (Tau4 != 0)
            // {
            //     ai.push_back(i);
            //     aj.push_back(i + nx);
            //     a.push_back(Tau4);
            // }

        }
        
        Tau0 = Tau1 + Tau2 + Tau3 + Tau4;
        //std::cout<<-Tau0<<" "<<Tau1<<" "<<Tau2<<" "<<Tau3<<" "<<Tau4<<std::endl;
        
        // ai.push_back(i);
        // aj.push_back(i);
        // a.push_back(Tau0);
        A.insert(i, i, -Tau0);
        // std::cout << i << std::endl;
    }
    std::cout << "\n matrix A done" << std::endl;

    // std::ofstream output_file;

    // output_file.open("A.txt");

    for (int i = 0; i < nx * ny; ++i)
    {
        for (int j = 0; j < nx * ny; ++j)
        {
            if (A(i, j) !=0)
            {
                ai.push_back(i);
                aj.push_back(j);
                a.push_back(A(i, j));
            }
        }
    //     output_file << std::endl;
    }
    // output_file.close();

    A.write_to_mtx(ai,aj,a);
    std::ofstream output_file;
    output_file.open("../data/b.txt");
    output_file << nx*ny << std::endl;
    for (int i = 0; i < nx * ny; ++i)
    {
        output_file << b[i]<< " "<< std::endl;
    }
    
    output_file.close();
    std::cout<<"all writes completed"<<std::endl;

}