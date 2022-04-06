/**************************************************************************
 *
 *       Program         :   main.cpp
 *       Purpose         :
 *       Author          :   Alok Sawant
 *       Creation Date   :   26-10-2021
 *       Last Modified   :   Tue 26 Oct 16:04:44 2021
 *
 **************************************************************************/
#include "calculator.h"
#include "data_struct.h"
#include <iostream>
#include <string>
#include <algorithm>

int main() {

    std::string input;

    float ans = std::nanf("");
    while (1) {
        //std::cin >> input;
        std::cout << "Enter you expression here: " << std::endl;
        std::getline(std::cin >> std::ws, input); // read input sting with white spaces
        input.erase(remove(input.begin(), input.end(), ' '), input.end());;              // remove all white spaces from the equation

        // std::cout << input;
        ans = calculate(input.c_str(), 0, input.length(),&ans);
        std::cout <<"Solution for "<< input <<"\t=>" << ans << "\n\n";
    }
}
