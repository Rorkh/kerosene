#include <iostream>
#include <sstream>
#include <fstream>

#include <chrono>
#include <thread>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <WinUser.h>
#elif defined(__linux__)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#endif

#ifdef _WIN32
#define LEFTMOUSE_DOWN POINT pos_cursor; \
                        GetCursorPos(&pos_cursor); \
                        HWND window = WindowFromPoint(pos_cursor); \
                        SendMessage(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
#define LEFTMOUSE_UP POINT pos_cursor; \
                        GetCursorPos(&pos_cursor); \
                        HWND window = WindowFromPoint(pos_cursor); \
                        SendMessage(window, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
#define RIGHTMOUSE_DOWN POINT pos_cursor; \
                        GetCursorPos(&pos_cursor); \
                        HWND window = WindowFromPoint(pos_cursor); \
                        SendMessage(window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
#define RIGHTMOUSE_UP POINT pos_cursor; \
                        GetCursorPos(&pos_cursor); \
                        HWND window = WindowFromPoint(pos_cursor); \
                        SendMessage(window, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
#elif defined(__linux__)
#define LEFTMOUSE_DOWN XTestFakeButtonEvent(display, 1, true, 0); \
                       XFlush(display);
#define LEFTMOUSE_UP XTestFakeButtonEvent(display, 1, false, 0); \
                     XFlush(display);  
#define RIGHTMOUSE_DOWN XTestFakeButtonEvent(display, 3, true, 0); \
                        XFlush(display);
#define RIGHTMOUSE_UP XTestFakeButtonEvent(display, 3, false, 0); \
                      XFlush(display);
#endif

#include "picojson.h"

int main()
{
    using namespace std::chrono_literals;
    std::cout << "Written for Lord of Panckaes by Solaire :)\nPress C to make mouse click (or configured keys).\n";

    SHORT first_key = 0x43;
    SHORT second_key = 0x00;
       
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

    #ifdef __linux__
    Display* display = XOpenDisplay(NULL);
    #endif

    while (true)
    {
        SHORT pressed = GetAsyncKeyState(first_key);
        if ((1 << 15) & pressed)
        {
            LEFTMOUSE_DOWN
            std::this_thread::sleep_for(5ms);

            first_pressed = true;
        }
        else
        {
            if (first_pressed)
            {
                LEFTMOUSE_UP
                first_pressed = false;
            }
        }

        if (second_key != 0x00) {
            pressed = GetAsyncKeyState(second_key);
            if ((1 << 15) & pressed)
            {
                RIGHTMOUSE_DOWN
                std::this_thread::sleep_for(5ms);

                second_pressed = true;
            }
            else
            {
                if (second_pressed)
                {
                    RIGHTMOUSE_UP
                    second_pressed = false;
                }
            }
        }
    }

    #ifdef __linux__
    XCloseDisplay(display);
    #endif
}