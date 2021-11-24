#include <math.h>
#include <fstream>
#include <array>
#include <iostream>
#include <getopt.h>
#include "lattice.h"
#include "point.h"

class relaxation{
public:
    relaxation(int argc, char **argv) { 
       get_options(argc, argv); 
       lattices = {Lattice(SIZE, V_left, V_right, V_top, V_bottom),
                   Lattice(SIZE, V_left, V_right, V_top, V_bottom, guess)}; 
    }

    void Run() {
        for (int i = 0; i < iterations; i++){ 
            for (int j = SIZE + 2; j < ((SIZE + 1) * (SIZE + 1) - 1) - (SIZE + 1); j++){
                if ((j + 1) % (SIZE + 1) != 0 && j % (SIZE + 1) != 0){ 
		    double num = (1.0 / 4.0) * (lattices[(i + 1) % 2].R(j).V() + lattices[(i + 1) % 2].L(j).V() + lattices[(i + 1) % 2].U(j).V() + lattices[(i + 1) % 2].D(j).V());
                    lattices[i % 2].at(j).set_V(num);
                }
            } 
        }
    }

    void Print() {
        std::ofstream out;
	out.open(file_name);
	for (int i = 0; i < (SIZE + 1) * (SIZE + 1); i++){
            double x = lattices[iterations % 2].at(i).X();
            double y = lattices[iterations % 2].at(i).Y();
            out << x << " " << y << " " << lattices[iterations % 2].at(i).V() << "\n";
        } 
    }
    
private:
    std::array<Lattice, 2> lattices;
    std::string file_name;
    double guess = 0.0;
    double V_left = 0.0;
    double V_right = 0.0;
    double V_top = 0.0;
    double V_bottom = 0.0;
    size_t SIZE;
    size_t iterations;

    void get_options(int argc, char **argv){
        int option_index = 0, option = 0;
	bool file_opt = false;
	bool size_opt = false;
	bool iter_opt = false;
        struct option longOpts[] = {{"file", required_argument, nullptr, 'f'},
                                    {"guess", required_argument, nullptr, 'g'},
                                    {"left", required_argument, nullptr, 'l'},
                                    {"right", required_argument, nullptr, 'r'},
                                    {"top", required_argument, nullptr, 't'},
                                    {"bottom", required_argument, nullptr, 'b'},
				    {"size", required_argument, nullptr, 's'},
                                    {"iterations", required_argument, nullptr, 'i'},
				    { nullptr, 0, nullptr, '\0'}};
        while ((option = getopt_long(argc, argv, "f:g:l:r:t:b:s:i:", longOpts, &option_index)) != -1){
            switch (option){
                case 'f': {
                    file_opt = true;
                    std::string str_f(optarg);
                    file_name = str_f;
                    break;
                }
                case 'g': {
                    std::string str_g(optarg);
                    guess = std::stod(str_g);
                    break;
                }
                case 'l': {
                    std::string str_l(optarg);
                    V_left = std::stod(str_l);
                    break;
                }
                case 'r': {
                    std::string str_r(optarg);
                    V_right = std::stod(str_r);
                    break;
                }
                case 't': {
                    std::string str_t(optarg);
                    V_top = std::stod(str_t);
                    break;
                }
		case 'b': {
                    std::string str_b(optarg);
                    V_bottom = std::stod(str_b);
                    break;
                }
                case 's': {
		    size_opt = true;
                    std::string str_s(optarg);
                    SIZE = std::stoi(str_s);
                    break;
                }
                case 'i': {
                    iter_opt = true;
                    std::string str_i(optarg);
                    iterations = std::stoi(str_i);
                    break;
                }
		default:
                    exit(1);
            }
        }
        if (!file_opt || !size_opt || !iter_opt) {
	    std::cout << "ERROR: The (-f,--file), (-s,--size), and (-i,--iterations) options are all required.\n";
	    exit(0);
        } 
    }
};

int main(int argc, char **argv){
    
    relaxation r(argc, argv);
    r.Run();
    r.Print();
    
    return 0;
    
    
}
