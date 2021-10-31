#include <unistd.h>
#include <string>

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

	void LeftMouseDown();
	void LeftMouseUp();

	void RightMouseDown();
	void RightMouseUp();
}