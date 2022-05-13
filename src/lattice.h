#ifndef lattice_h
#define lattice_h
#include <vector>

class Lattice{
public:
   Lattice() : SIZE(nullptr) {};

   Lattice(const size_t * const SIZE, const double * const V_left, const double * const V_right, 
	   const double * const V_top, const double * const V_bottom, const double guess = 0.0) : SIZE(SIZE) {
        for (int i = 0; i <= *SIZE; i++){
            for (int j = 0; j<= *SIZE; j++){
                if (j == 0){
                    lattice.emplace_back(*V_left);
                }
		else if (j == *SIZE){
                    lattice.emplace_back(*V_right);
                }
                else if (i == *SIZE){
                    lattice.emplace_back(*V_top);
                }
		else if (i == 0){
                    lattice.emplace_back(*V_bottom);
                } 
		else{
                    lattice.emplace_back(guess);
                }
            }
        }
    }
    
    const double X(const int index) const {
        return (double)(index % (*SIZE + 1)) / (double)*SIZE; 
    }

    const double Y(const int index) const {
        return (double)(index /  (*SIZE + 1)) / (double)*SIZE;
    }

    void set(const int index, const double value) {
        lattice[index] = value;
    }
    
    const double& at(const int index) const {
        return lattice[index];
    }
    
    const double& R(const int index) const {
        return lattice[index + 1];
    }
    
    const double& L(const int index) const {
        return lattice[index - 1];
    }
    
    const double& U(const int index) const {
        return lattice[index - (*SIZE + 1)];
    }
    
    const double& D(const int index) const {
        return lattice[index + (*SIZE + 1)];
    }
    
private:
    std::vector<double> lattice;
    const size_t * const SIZE;
};

#endif
