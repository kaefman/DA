#pragma once

#include <vector>
#include <string>

std::vector<int> CalculateSP(std::vector<int> &z, std::vector<std::string> &pat);
std::vector<int> ZFunction(std::vector<std::string> &pat);
std::vector<int> FailFunction(std::vector<std::string> &pattern);
void KMP(std::vector<std::string> &pat);