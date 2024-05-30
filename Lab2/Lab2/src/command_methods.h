#pragma once

#include <memory>
#include <cstring>

class Commands{
public:
    Commands() = default;
    bool is_SETTIM(std::string command);
    bool is_SETPWM(std::string command);
    double get_SETTIM_param(std::string command);
    double get_SETPWM_param(std::string command);
public:
    double str_to_double(std::string snum);
    std::string double_to_str(double dnum, int precision);
private:
    bool isValidNumber(const std::string& s);
    bool validate_command_structure(std::string command, std::string expected_keyword);
    double exrtact_argument(std::string command, std::string expected_keyword);
};