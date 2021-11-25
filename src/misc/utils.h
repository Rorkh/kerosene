#include <unistd.h>

#include <string>
#include <sstream>
#include <fstream>

#include "../thirdparty/picojson.h"

#ifdef _WIN32
#include <windows.h>
#include <WinUser.h>
#elif defined(__linux__)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#endif

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <WinUser.h>
#elif defined(__linux__)
#include <termios.h>
#include <cstring>
#endif


#ifdef _WIN32
void SimulateMousePress(UINT Msg, WPARAM wParam);
#endif

namespace utils {
	int GetKey();

	bool IsKeyPressed(int key);
	bool IsFileExists(const std::string& name);


	#ifdef _WIN32
		HWND FindOsu();

		void LeftMouseDown(HWND window);
		void LeftMouseUp(HWND window);

		void RightMouseDown(HWND window);
		void RightMouseUp(HWND window);
	#elif defined(__linux)
		void LeftMouseDown();
		void LeftMouseUp();

		void RightMouseDown();
		void RightMouseUp();
	#endif

	void ReadConfig(int *first_key, int *second_key);
}