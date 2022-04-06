#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<cmath>
#include<cstdio>
#include<cstdlib>

float calculate(const char* eq, char start, char end, const float* vars = nullptr);

char* reverseString(const char* string, char length);
#endif

