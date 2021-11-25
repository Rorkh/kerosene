#include <iostream>

#include <chrono>
#include <thread>

#include "misc/consts.h"
#include "misc/utils.h"

#ifdef __WIN32
    #define LeftMouseDown() utils::LeftMouseDown(window);
    #define LeftMouseUp() utils::LeftMouseUp(window);
    #define RightMouseDown() utils::RightMouseDown(window);
    #define RightMouseUp() utils::RightMouseUp(window);
#elif defined(__linux__)
    #define LeftMouseDown() utils::LeftMouseDown();
    #define LeftMouseUp() utils::LeftMouseUp();
    #define RightMouseDown() utils::RightMouseDown();
    #define RightMouseUp() utils::RightMouseUp();
#endif

int main()
{
    using namespace std::chrono_literals;

    std::cout << "Written for Lord of Panckaes by Solaire ";

    #ifdef __WIN32
        std::cout << "\x03";
    #elif __linux__
        std::cout << "\xe2\x99\xa5";
    #endif

    std::cout << "\nIt's better one.\n\n";

    int first_key = constant::PRIMARY_KEY;
    int second_key = 0x00;

    utils::ReadConfig(&first_key, &second_key);

    bool first_pressed = false;
    bool second_pressed = false;

    #ifdef __WIN32
        HWND window = utils::FindOsu();
    #endif

    std::cout << "\nPress C to make mouse click (or configured keys).\n";

    while (true)
    {
        if (utils::IsKeyPressed(first_key)) {
            LeftMouseDown();
            std::this_thread::sleep_for(5ms);

            first_pressed = true;
        }
        else
        {
            if (first_pressed)
            {
                LeftMouseUp();
                first_pressed = false;
            }
        }

        if (second_key != 0x00) {
            if (utils::IsKeyPressed(second_key)) {
                RightMouseDown();
                std::this_thread::sleep_for(5ms);

                second_pressed = true;
            }
            else
            {
                if (second_pressed)
                {
                    RightMouseUp();
                    second_pressed = false;
                }
            }
        }
    }
}
