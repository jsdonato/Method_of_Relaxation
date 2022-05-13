#include <memory>
#include <iostream>
#include <getopt.h>
#include "methods.h"


class relaxation{
public:
    relaxation(int argc, char **argv) { 
        get_options(argc, argv); 
        if (method_name == "gauss") {
            method = std::make_unique<GaussSeitel>(&file_name, &guess, &V_left, &V_right,
			                           &V_top, &V_bottom, &SIZE, &iterations);
	}
        else if (method_name == "jacobi") {
            method = std::make_unique<Jacobi>(&file_name, &guess, &V_left, &V_right,
			                      &V_top, &V_bottom, &SIZE, &iterations);
	}
        else {
            std::cout << "ERROR: Invalid option inputted for method\n";
	    exit(1);
	}
    }

    void Run() {
        method->Run(); 
    }

    void Print() {
        method->Print();
    }
    
private: 
    std::unique_ptr<Method> method = nullptr;
    std::string file_name;
    std::string method_name;
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
                                    {"method", required_argument, nullptr, 'm'},
                                    {"guess", required_argument, nullptr, 'g'},
                                    {"left", required_argument, nullptr, 'l'},
                                    {"right", required_argument, nullptr, 'r'},
                                    {"top", required_argument, nullptr, 't'},
                                    {"bottom", required_argument, nullptr, 'b'},
				    {"size", required_argument, nullptr, 's'},
                                    {"iterations", required_argument, nullptr, 'i'},
				    { nullptr, 0, nullptr, '\0'}};
        while ((option = getopt_long(argc, argv, "f:g:l:r:t:b:s:i:m:", longOpts, &option_index)) != -1){
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
		case 'm': {
                    std::string str_m(optarg);
		    method_name = str_m;
		    break;
		}
		default:
                    exit(1);
            }
        }
        if (!file_opt || !size_opt || !iter_opt) {
	    std::cout << "ERROR: The (-f,--file), (-s,--size), and (-i,--iterations) options are all required.\n";
	    exit(1);
        } 
    }
};

int main(int argc, char **argv){
    
    relaxation r(argc, argv);
    r.Run();
    r.Print();
    
    return 0;
    
    
}
