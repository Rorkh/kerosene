#include <iostream>
#include <chrono>
#include <thread>

#include <windows.h>
#include <WinUser.h>

int main()
{
    using namespace std::chrono_literals;
    std::cout << "Written for Lord of Panckaes by Solaire :)\nPress C to make mouse click.\n";

    bool pressed = false;

    while (true)
    {
        SHORT c_pressed = GetAsyncKeyState(0x43);
        if ((1 << 15) & c_pressed)
        {
            POINT pos_cursor;
            GetCursorPos(&pos_cursor);
            HWND window = WindowFromPoint(pos_cursor);

            SendMessage(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
            std::this_thread::sleep_for(5ms);

            pressed = true;
        }
        else
        {
            if (pressed)
            {
                POINT pos_cursor;
                GetCursorPos(&pos_cursor);
                HWND window = WindowFromPoint(pos_cursor);

                SendMessage(window, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
                pressed = false;
            }
        }
    }
}