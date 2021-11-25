#include "utils.h"

#ifdef _WIN32
void SimulateMousePress(HWND window, UINT Msg, WPARAM wParam)
{
	POINT pos_cursor;
	GetCursorPos(&pos_cursor);
	SendMessage(window, Msg, wParam, MAKELPARAM(pos_cursor.x, pos_cursor.y));
}
#endif

namespace utils {	
	int GetKey()
	{
		#ifdef _WIN32
		HKL currentKBL = GetKeyboardLayout(0);
		char ch = _getch();
		return VkKeyScanEx(ch, currentKBL);
		#elif defined(__linux__)
		struct termios oldattr, newattr;
		int ch;
		tcgetattr( STDIN_FILENO, &oldattr );
		newattr = oldattr;
		newattr.c_lflag &= ~( ICANON | ECHO );
		tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
		ch = getchar();
		tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
		return ch;
		#endif
	}
	
	bool IsKeyPressed(int key)
	{
		#ifdef __linux__
		Display *dpy = XOpenDisplay(":0");
		char keys_return[32];
		XQueryKeymap(dpy, keys_return);
		KeyCode kc2 = XKeysymToKeycode(dpy, key);
		bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
		XCloseDisplay(dpy);
		return isPressed;
		#elif defined(_WIN32)
			SHORT pressed = GetAsyncKeyState(key);
			return (1 << 15) & pressed;
		#endif
	}

	bool IsFileExists(const std::string& name) 
	{
		if (FILE *file = fopen(name.c_str(), "r")) {
			fclose(file);
			return true;
		} else {
			return false;
		}   
	}

	#ifdef __linux__
		void LeftMouseDown()
		{
			Display *display = XOpenDisplay(NULL);
			XTestFakeButtonEvent(display, 1, true, 0);
			XFlush(display);
			XCloseDisplay(display);
		}

		void LeftMouseUp()
		{
			Display *display = XOpenDisplay(NULL);
			XTestFakeButtonEvent(display, 1, false, 0);
			XFlush(display);
			XCloseDisplay(display);
		}

		void RightMouseDown()
		{
			Display *display = XOpenDisplay(NULL);
			XTestFakeButtonEvent(display, 3, true, 0);
			XFlush(display);
			XCloseDisplay(display);
		}

		void RightMouseUp()
		{
			Display *display = XOpenDisplay(NULL);
			XTestFakeButtonEvent(display, 3, false, 0);
			XFlush(display);
			XCloseDisplay(display);
		}
	#elif defined(_WIN32)
		void LeftMouseDown(HWND window)
		{
			SimulateMousePress(window, WM_LBUTTONDOWN, MK_LBUTTON);
		}

		void LeftMouseUp(HWND window)
		{
			SimulateMousePress(window, WM_LBUTTONUP, 0);
		}

		void RightMouseDown(HWND window)
		{
			SimulateMousePress(window, WM_RBUTTONDOWN, MK_RBUTTON);
		}

		void RightMouseUp(HWND window)
		{
			SimulateMousePress(window, WM_RBUTTONUP, 0);
		}
	#endif

	void ReadConfig(int *first_key, int *second_key)
	{
		if (utils::IsFileExists("config.json")) 
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
			}

			picojson::object config = v.get<picojson::object>();

			if (!config["firstKey"].is<picojson::null>()) *first_key = config["firstKey"].get<double>();
			if (!config["secondKey"].is<picojson::null>()) *second_key = config["secondKey"].get<double>();
		}
	}

	#ifdef _WIN32
		HWND FindOsu()
		{
			std::cout << "Searching for \"osu!\" window\n";
			HWND OsuWindow = FindWindowA(nullptr, TEXT("osu!"));

			if (OsuWindow == nullptr) 
			{
				std::cout << "Please run osu!\n";
				while (OsuWindow == nullptr) 
				{
					OsuWindow = FindWindowA(nullptr, TEXT("osu!"));
					Sleep(100);
				}
			}

			std::cout << "Osu! founded\n";
			return OsuWindow;
		}
	#endif
}