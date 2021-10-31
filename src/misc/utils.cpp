#include "utils.h"

#ifdef _WIN32
void SimulateMousePress(UINT Msg, WPARAM wParam)
{
	POINT pos_cursor;
	GetCursorPos(&pos_cursor);
	HWND window = WindowFromPoint(pos_cursor);
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

	void LeftMouseDown()
	{
		#ifdef __linux__
		Display *display = XOpenDisplay(NULL);
		XTestFakeButtonEvent(display, 1, true, 0);
		XFlush(display);
		XCloseDisplay(display);
		#elif defined(_WIN32)
		SimulateMousePress(WM_LBUTTONDOWN, MK_LBUTTON);
		#endif
	}

	void LeftMouseUp()
	{
		#ifdef __linux__
		Display *display = XOpenDisplay(NULL);
		XTestFakeButtonEvent(display, 1, false, 0);
		XFlush(display);
		XCloseDisplay(display);
		#elif defined(_WIN32)
		SimulateMousePress(WM_LBUTTONUP, 0);
		#endif
	}

	void RightMouseDown()
	{
		#ifdef __linux__
		Display *display = XOpenDisplay(NULL);
		XTestFakeButtonEvent(display, 3, true, 0);
		XFlush(display);
		XCloseDisplay(display);
		#elif defined(_WIN32)
		SimulateMousePress(WM_RBUTTONDOWN, MK_RBUTTON);
		#endif
	}

	void RightMouseUp()
	{
		#ifdef __linux__
		Display *display = XOpenDisplay(NULL);
		XTestFakeButtonEvent(display, 3, false, 0);
		XFlush(display);
		XCloseDisplay(display);
		#elif defined(_WIN32)
		SimulateMousePress(WM_RBUTTONUP, 0);
		#endif
	}
}