#include <math.h>
#include <fstream>
#include <array>
#include "lattice.h"


class Method {
public:
  Method() : SIZE(nullptr), iterations(nullptr), file_name(nullptr) {}

  Method(const std::string * const file_name_, const size_t * const SIZE_, const size_t * const iterations_) :
	 file_name(file_name_), SIZE(SIZE_), iterations(iterations_) {}

  virtual void Run() = 0;

  virtual void Print() const = 0;

  virtual ~Method() = default;

protected: 
  const size_t * const SIZE;
  const size_t * const iterations;
  const std::string * const file_name;

};

class GaussSeitel : public Method {
public:
    GaussSeitel(const std::string * const file_name_, const double * const guess_, 
		const double * const V_left_, const double * const V_right_,
	        const double * const V_top_, const double * const V_bottom_,
		const size_t * const SIZE_, const size_t * const iterations_) :
	        Method(file_name_, SIZE_, iterations_),
		lattice(SIZE, V_left_, V_right_, V_top_, V_bottom_) {}

    void Run() {
        for (int i = 0; i < *iterations; i++){ 
            for (int j = *SIZE + 2; j < ((*SIZE + 1) * (*SIZE + 1) - 1) - (*SIZE + 1); j++){
                if ((j + 1) % (*SIZE + 1) != 0 && j % (*SIZE + 1) != 0){ 
		    lattice.set(j, (1.0 / 4.0) * (lattice.R(j) + lattice.L(j) + lattice.U(j) + lattice.D(j))); 
                }
            } 
        }
    }

    void Print() const {
        std::ofstream out;
	out.open(*file_name);	
	for (int i = 0; i < (*SIZE + 1) * (*SIZE + 1); i++){ 
            out << lattice.X(i) << " " 
	        << lattice.Y(i) << " " 
	        << lattice.at(i) << "\n";
        }
    }

private:
    Lattice lattice;
};

class Jacobi : public Method {
public:
    Jacobi(const std::string * const file_name_, const double* guess_,
	   const double * const V_left_, const double * const V_right_,
	   const double * const V_top_, const double * const V_bottom_,
	   const size_t * const SIZE_, const size_t * const iterations_) :
	   Method(file_name_, SIZE_, iterations_),
           lattices(std::array<Lattice, 2>{Lattice(SIZE_, V_left_, V_right_, V_top_, V_bottom_),
                                           Lattice(SIZE, V_left_, V_right_, V_top_, V_bottom_, *guess_)}) {}

    void Run() {
        for (int i = 0; i < *iterations; i++){ 
            for (int j = *SIZE + 2; j < ((*SIZE + 1) * (*SIZE + 1) - 1) - (*SIZE + 1); j++){
                if ((j + 1) % (*SIZE + 1) != 0 && j % (*SIZE + 1) != 0){ 
		    lattices[i % 2].set(j, (1.0 / 4.0) * (lattices[(i + 1) % 2].R(j) + lattices[(i + 1) % 2].L(j) + lattices[(i + 1) % 2].U(j) + lattices[(i + 1) % 2].D(j))); 
                }
            } 
        }
    }

    void Print() const {
        std::ofstream out;
	out.open(*file_name);	
	for (int i = 0; i < (*SIZE + 1) * (*SIZE + 1); i++){ 
            out << lattices[(*iterations + 1) % 2].X(i) << " " 
	        << lattices[(*iterations + 1) % 2].Y(i) << " " 
	        << lattices[(*iterations + 1) % 2].at(i) << "\n";
        }
    }

private:
    std::array<Lattice, 2> lattices;
};
