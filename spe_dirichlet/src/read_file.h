#pragma once
#include "lib.h"
#include "constants.h"


void saveToVTK(std::vector<double> &kx,
               std::vector<double> &ky,
               std::vector<double> &kz,
               int Nx,
               int Ny,
               int Nz,
               std::string name = "../data/output.vtk")
{
    std::ofstream output_file;

    output_file.open(name);
    output_file << "# vtk DataFile Version 3.0" << std::endl;
    output_file << "written by Ali" << std::endl;
    output_file << "ASCII" << std::endl;
    output_file << "DATASET STRUCTURED_GRID" << std::endl;
    output_file << "DIMENSIONS " << (Nx + 1) << " " << (Ny + 1) << " " << (Nz + 1) << std::endl;
    output_file << "POINTS " << (Nx + 1) * (Ny + 1) * (Nz + 1) << " double" << std::endl;

    for (int z = 0; z < Nz + 1; ++z)
        for (int y = 0; y < Ny + 1; ++y)
            for (int x = 0; x < Nx + 1; ++x)
            {
                output_file << x << " " << y << " " << z << std::endl;
            }

    output_file << "POINT_DATA " << (Nx + 1) * (Ny + 1) * (Nz + 1) << std::endl;

    output_file << "CELL_DATA " << Nx * Ny * Nz << std::endl;
    output_file << "SCALARS k double 3" << std::endl;
    output_file << "LOOKUP_TABLE default" << std::endl;

    for (int i = 0; i < Nx * Ny * Nz; ++i)

        output_file << kx[i] << " " << ky[i] << " " << kz[i] << std::endl;

    output_file.close();

    std::cout << " VTK file is ready !" << std::endl;

}

void slice(std::vector<double> &kx,
           std::vector<double> &ky,
           std::vector<double> &kz,
           std::vector<double> &Kx_s,
           std::vector<double> &Ky_s,
           std::vector<double> &Kz_s)
{

    int z = 50;
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            Kx_s.push_back(kx[i + j * ny + z * nx * ny]);
            Ky_s.push_back(ky[i + j * ny + z * nx * ny]);
            Kz_s.push_back(kz[i + j * ny + z * nx * ny]);
        }
    }

    saveToVTK(Kx_s, Ky_s, Kz_s, 60, 220, 1, "../data/output50.vtk");
    std::cout << " VTK slice  is ready !" << std::endl;


}



void read_dataset(std::ifstream &file,
                  std::vector<double> &Kx, std::vector<double> &Ky, std::vector<double> &Kz)
{
    std::string x, y, z;
    for (int i = 0; i < nx; ++i)
    {
        for (int j = 0; j < ny; ++j)
        {
            for (int k = 0; k < nz; ++k)
            {
                file >> x;
                Kx.push_back(std::stod(x));
            }
        }
    }

    for (int i = 0; i < nx; ++i)
    {
        for (int j = 0; j < ny; ++j)
        {
            for (int k = 0; k < nz; ++k)
            {
                file >> y;
                Ky.push_back(std::stod(y));
            }
        }
    }

    for (int i = 0; i < nx; ++i)
    {
        for (int j = 0; j < ny; ++j)
        {
            for (int k = 0; k < nz; ++k)
            {
                file >> z;
                Kz.push_back(std::stod(z));
            }
        }
    }
    std::cout << "data read !" << std::endl;

}
