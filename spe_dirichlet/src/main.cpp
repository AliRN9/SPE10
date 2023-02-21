#include "lib.h"
#include "constants.h"
#include "Matrix.h"
#include "read_file.h"
#include "solver.h"


int main()
{

    std::ifstream fperm;
    fperm.open("../data/spe_perm.dat");

    if (fperm.fail())
    {
        std::cout << "SPE10 data files not found." << std::endl;
        std::cout << "Expecting spe_perm.dat." << std::endl;
        return false;
    }
    else
    {
        std::vector<double> Kx;
        std::vector<double> Ky;
        std::vector<double> Kz;
        read_dataset(fperm, Kx, Ky, Kz);
        fperm.close();


        saveToVTK(Kx,Ky,Kz,nx,ny,nz,"../data/output.vtk");
        std::vector<double> Kx_s;
        std::vector<double> Ky_s;
        std::vector<double> Kz_s;
        slice(Kx,Ky,Kz,Kx_s,Ky_s,Kz_s);
        Matrix A(nx*ny,nx*ny);
        double b[nx * ny];
        get_SLAY(A,b,Kx_s,Ky_s);
        
    }
    
    // std::cout<<"reached last point"<<std::endl;

    std::cout << "solution rendering" << std::endl;
    system("python3 ../src/Matrix.py  image");

    return 0;
}
