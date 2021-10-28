#include <iostream>
#include <sstream>
#include <fstream>

#include <chrono>
#include <thread>
#include <filesystem>

#include <windows.h>
#include <WinUser.h>

#include "picojson.h"

int main()
{
    using namespace std::chrono_literals;
    std::cout << "Written for Lord of Panckaes by Solaire :)\nPress C to make mouse click (or configured keys).\n";

    SHORT first_key = 0x43;
    SHORT second_key = 0x56;

    if (std::filesystem::exists("config.json")) 
    {
        std::ifstream file;
        std::stringstream ss;

        file.open("config.json", std::ifstream::binary);
        ss << file.rdbuf();
        file.close();

        picojson::value v;
        ss >> v;

        std::string err = picojson::get_last_error();
        if (!err.empty()) {
            std::cerr << err << std::endl;
            return -1;
        }

        picojson::object config = v.get<picojson::object>();

        if (!config["firstKey"].is<picojson::null>()) first_key = config["firstKey"].get<double>();
        if (!config["secondKey"].is<picojson::null>()) second_key = config["secondKey"].get<double>();
    }

    bool first_pressed = false;
    bool second_pressed = false;

    while (true)
    {
        SHORT pressed = GetAsyncKeyState(first_key);
        if ((1 << 15) & pressed)
        {
            POINT pos_cursor;
            GetCursorPos(&pos_cursor);
            HWND window = WindowFromPoint(pos_cursor);

            SendMessage(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
            std::this_thread::sleep_for(5ms);

            first_pressed = true;
        }
        else
        {
            if (first_pressed)
            {
                POINT pos_cursor;
                GetCursorPos(&pos_cursor);
                HWND window = WindowFromPoint(pos_cursor);

                SendMessage(window, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
                first_pressed = false;
            }
        }

        pressed = GetAsyncKeyState(second_key);
        if ((1 << 15) & pressed)
        {
            POINT pos_cursor;
            GetCursorPos(&pos_cursor);
            HWND window = WindowFromPoint(pos_cursor);

            SendMessage(window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
            std::this_thread::sleep_for(5ms);

            second_pressed = true;
        }
        else
        {
            if (second_pressed)
            {
                POINT pos_cursor;
                GetCursorPos(&pos_cursor);
                HWND window = WindowFromPoint(pos_cursor);

                SendMessage(window, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
                second_pressed = false;
            }
        }
    }

    //return 0;
}