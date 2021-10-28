#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

#include <windows.h>
#include <WinUser.h>

int main()
{
    HKL currentKBL = GetKeyboardLayout(0);

    std::cout << "Press first key (it will be alias for MOUSE1)\n"; 
    char first = _getch();
    SHORT firstKeyCode = VkKeyScanEx(first, currentKBL);

    std::cout << "Captured!\n";

    std::cout << "Press second key (it will be alias for MOUSE2) or press ENTER to skip\n";
    char second = _getch();
    SHORT secondKeyCode = VkKeyScanEx(second, currentKBL);

    bool skipSecond = secondKeyCode == 13;

    std::ofstream fS;
    fS.open("config.json");
    fS << "{\n\t\"firstKey\": " << firstKeyCode << (skipSecond ? "\n}" : std::string(",\n\t\"secondKey\": ") + std::to_string(secondKeyCode) + "\n}");
    fS.close();

    return 0;
}