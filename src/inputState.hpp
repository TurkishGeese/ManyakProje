#pragma once

enum class InputState {
	NONE = 0,
	PRESSED = 1,
	HELD = 2,
	RELEASED = 4
};

inline int operator|(InputState a, InputState b) {
	return static_cast<int>(a) | static_cast<int>(b);
}

inline int operator|(int a, InputState b) {
	return a | static_cast<int>(b);
}

inline int operator|(InputState a, int b) {
	return static_cast<int>(a) | b;
}

inline int operator&(InputState a, InputState b) {
	return static_cast<int>(a) & static_cast<int>(b);
}

inline int operator&(int a, InputState b) {
	return a & static_cast<int>(b);
}

inline int operator&(InputState a, int b) {
	return static_cast<int>(a) & b;
}
