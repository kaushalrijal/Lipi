#ifndef CODE_EXECUTER_H
#define CODE_EXECUTER_H

#include <string>

void generateCppFile(const std::string&, const std::string&);

bool compileCppFile(const std::string&, const std::string&);

std::string runBinary(const std::string&);

#endif