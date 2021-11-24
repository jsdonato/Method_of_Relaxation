#ifndef lattice_h
#define lattice_h
#include <vector>
#include "point.h"

class Lattice{
public:
   Lattice() {};

   Lattice(size_t SIZE, double V_left, double V_right, double V_top, double V_bottom): SIZE(SIZE) {
        for (int i = 0; i <= SIZE; i++){
            for (int j = 0; j<= SIZE; j++){
                if (j == 0){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_left);
                }
		else if (j == SIZE){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_right);
                }
                else if (i == SIZE){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_top);
                }
		else if (i == 0){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_bottom);
                } 
                else{
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), 0);
                }
            }
        }
    }
    
    Lattice(size_t SIZE, double V_left, double V_right, double V_top, double V_bottom, double guess) : SIZE(SIZE) {
        for (int i = 0; i <= SIZE; i++){
            for (int j = 0; j<= SIZE; j++){
                if (j == 0){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_left);
                }
		else if (j == SIZE){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_right);
                }
                else if (i == SIZE){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_top);
                }
		else if (i == 0){
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), V_bottom);
                } 
		else{
                    lattice.emplace_back(j * (1.0 / SIZE), i * (1.0 / SIZE), guess);
                }
            }
        }
    }
    
    Point& at(int index){
        return lattice[index];
    }
    
    Point& R(int index){
        return lattice[index + 1];
    }
    
    Point& L(int index){
        return lattice[index - 1];
    }
    
    Point& U(int index){
        return lattice[index - (SIZE + 1)];
    }
    
    Point& D(int index){
        return lattice[index + (SIZE + 1)];
    }
    
private:
    std::vector<Point> lattice;
    size_t SIZE;
};

#endif
