#include "command_methods.h"

bool Commands::is_SETTIM(std::string command) {
    std::string keyword = "SETTIM";
    return validate_command_structure(command, keyword);
}

bool Commands::is_SETPWM(std::string command) {
    std::string keyword = "SETPWM";
    return validate_command_structure(command, keyword);
}

double Commands::get_SETTIM_param(std::string command) {
    return exrtact_argument(command, "SETTIM");
}

double Commands::get_SETPWM_param(std::string command) {
    return exrtact_argument(command, "SETPWM");
}

bool Commands::isValidNumber(const std::string& s) {
    bool decimalPointEncountered = false;
    for (char c : s) {
        if (!std::isdigit(c)) {
            if (c == '.' && !decimalPointEncountered) {
                decimalPointEncountered = true; // First decimal point is allowed
            } else {
                return false; // Invalid character or second decimal point encountered
            }
        }
    }
    return true;
}

bool Commands::validate_command_structure(std::string command, std::string expected_keyword){
    size_t pos = command.find(expected_keyword);
    if (pos == std::string::npos) return false;
    pos += expected_keyword.length();
    while (pos < command.size() && command[pos] == ' ') pos++; // Skip whitespace
    if (pos == command.size()) return false; // No parameter provided
    size_t start = pos;
    while (pos < command.size() && (std::isdigit(command[pos]) || command[pos] == '.')) pos++;
    std::string number = command.substr(start, pos - start);
    if (!isValidNumber(number)) return false;
    while (pos < command.size() && command[pos] == ' ') pos++; // Skip trailing whitespace
    return pos == command.size(); // True if no extra characters after number
}

double Commands::exrtact_argument(std::string command, std::string expected_keyword){
    size_t pos = command.find(expected_keyword) + expected_keyword.length();
    while (pos < command.size() && command[pos] == ' ') pos++; // Skip whitespace
    size_t start = pos;
    while (pos < command.size() && (std::isdigit(command[pos]) || command[pos] == '.')) pos++;
    return str_to_double(command.substr(start, pos - start));
}

double Commands::str_to_double(std::string snum){
    double dnum_intg = 0;
    uint8_t i = 0;
    for (; i < snum.length() && snum[i] != '.'; i++){
        dnum_intg *= 10;
        dnum_intg += (snum[i]-48);
    }

    double dnum_fract = 0;
    for (int j = snum.length()-1; j > i; j--){
        dnum_fract += (snum[j]-48);
        dnum_fract /= 10;
    }

    return dnum_intg + dnum_fract;
}

std::string Commands::double_to_str(double dnum, int precision){
    int dnum_intg = (int)dnum;
    double dnum_fract = dnum - dnum_intg;

    char snum[20];
    uint8_t len = 1;
    snum[0] = '.';
    for (int i = 0; i < precision && dnum_fract > 0.0; i++)
    {
        dnum_fract *= 10;
        snum[len++] = (char)((int)dnum_fract+48);
        dnum_fract -= (int)dnum_fract;
    }

    do {
        std::memcpy(&snum[1], &snum[0], len*sizeof(char));
        snum[0] = (char)(dnum_intg%10+48);
        len = len + 1;
        dnum_intg /= 10;
    } while (dnum_intg > 0);

    snum[len] = '\0';
    std::string s(snum);
    return s;
}
