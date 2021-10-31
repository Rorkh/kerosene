#include <iostream>
#include <fstream>
#include <string>

#include "misc/consts.h"
#include "misc/utils.h"
  
int main()
{
 
    std::cout << "Press first key (it will be alias for MOUSE1)\n"; 
    int firstKeyCode = utils::GetKey();
 
    std::cout << "Captured!\n";
 
    std::cout << "Press second key (it will be alias for MOUSE2) or press ENTER to skip\n";
    int secondKeyCode = utils::GetKey();
 
    bool skipSecond = secondKeyCode == constant::KEY_ENTER;
 
    std::ofstream fS;
    fS.open("config.json");
    fS << "{\n\t\"firstKey\": " << std::to_string(firstKeyCode) << (skipSecond ? "\n}" : std::string(",\n\t\"secondKey\": ") + std::to_string(secondKeyCode) + "\n}");
    fS.close();
 
    return 0;
}