#pragma once

#include <memory>

bool is_SETTIM(std::string command);
bool is_SETPWM(std::string command);
double get_SETTIM_param(std::string command);
double get_SETPWM_param(std::string command);

// bool isValidNumber(const std::string& s);
// bool validate_command_structure(std::string command, std::string expected_keyword);
// bool exrtact_argument(std::string command, std::string expected_keyword);
