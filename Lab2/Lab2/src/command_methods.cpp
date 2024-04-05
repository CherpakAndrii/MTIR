#include "command_methods.h"

bool is_SETTIM(std::string command){
    return false;
}

bool is_SETPWM(std::string command){
    return false;
}

double get_SETTIM_param(std::string command){
    return 1;
}

double get_SETPWM_param(std::string command){
    return 0.25;
}
