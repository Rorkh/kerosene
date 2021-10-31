#ifndef CONSTS_H
#define CONSTS_H

namespace constant {
	#ifdef _WIN32
	inline constexpr int KEY_ENTER = 13;
	inline constexpr int PRIMARY_KEY = 0x43;
	#elif defined(__linux__)
	inline constexpr int KEY_ENTER = 10;
	inline constexpr int PRIMARY_KEY = 0x0063;
	#endif
}

#endif