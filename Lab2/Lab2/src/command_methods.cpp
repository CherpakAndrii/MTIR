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

// bool is_SETTIM(std::string command) {
//     std::string keyword = "SETTIM";
//     return validate_command_structure(command, keyword);
// }

// bool is_SETPWM(std::string command) {
//     std::string keyword = "SETPWM";
//     return validate_command_structure(command, keyword);
// }

// double get_SETTIM_param(std::string command) {
//     return exrtact_argument(command, "SETTIM");
// }

// double get_SETPWM_param(std::string command) {
//     return exrtact_argument(command, "SETPWM");
// }

// bool isValidNumber(const std::string& s) {
//     bool decimalPointEncountered = false;
//     for (char c : s) {
//         if (!std::isdigit(c)) {
//             if (c == '.' && !decimalPointEncountered) {
//                 decimalPointEncountered = true; // First decimal point is allowed
//             } else {
//                 return false; // Invalid character or second decimal point encountered
//             }
//         }
//     }
//     return true;
// }

// bool validate_command_structure(std::string command, std::string expected_keyword){
//     size_t pos = command.find(expected_keyword);
//     if (pos == std::string::npos) return false;
//     pos += expected_keyword.length();
//     while (pos < command.size() && command[pos] == ' ') pos++; // Skip whitespace
//     if (pos == command.size()) return false; // No parameter provided
//     size_t start = pos;
//     while (pos < command.size() && (std::isdigit(command[pos]) || command[pos] == '.')) pos++;
//     std::string number = command.substr(start, pos - start);
//     if (!isValidNumber(number)) return false;
//     while (pos < command.size() && command[pos] == ' ') pos++; // Skip trailing whitespace
//     return pos == command.size(); // True if no extra characters after number
// }

// bool exrtact_argument(std::string command, std::string expected_keyword){
//     size_t pos = command.find(expected_keyword) + expected_keyword.length();
//     while (pos < command.size() && command[pos] == ' ') pos++; // Skip whitespace
//     size_t start = pos;
//     while (pos < command.size() && (std::isdigit(command[pos]) || command[pos] == '.')) pos++;
//     return std::stod(command.substr(start, pos - start));
// }