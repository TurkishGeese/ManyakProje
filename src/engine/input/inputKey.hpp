#pragma once

#include "manyakSDL.hpp"

enum InputKey {
	INVALID = -1,
	// Mouse
	LEFT_CLICK = 0,
	RIGHT_CLICK = 1,
	MIDDLE_CLICK = 2,

	// Controller Buttons
	CONTROLLER_A,
	CONTROLLER_B,
	CONTROLLER_X,
	CONTROLLER_Y,
	CONTROLLER_BACK,
	CONTROLLER_GUIDE,
	CONTROLLER_START,
	CONTROLLER_LEFTSTICK,
	CONTROLLER_RIGHTSTICK,
	CONTROLLER_LEFTSHOULDER,
	CONTROLLER_RIGHTSHOULDER,
	CONTROLLER_DPAD_UP,
	CONTROLLER_DPAD_DOWN,
	CONTROLLER_DPAD_LEFT,
	CONTROLLER_DPAD_RIGHT,

	// Controller Axis
	CONTROLLER_AXIS_LEFTX,
	CONTROLLER_AXIS_LEFTY,
	CONTROLLER_AXIS_RIGHTX,
	CONTROLLER_AXIS_RIGHTY,
	CONTROLLER_AXIS_TRIGGERLEFT,
	CONTROLLER_AXIS_TRIGGERRIGHT,

	// Keyboard buttons
	KEY_RETURN,
	KEY_ESCAPE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_SPACE,
	KEY_EXCLAIM,
	KEY_QUOTEDBL,
	KEY_HASH,
	KEY_PERCENT,
	KEY_DOLLAR,
	KEY_AMPERSAND,
	KEY_QUOTE,
	KEY_LEFTPAREN,
	KEY_RIGHTPAREN,
	KEY_ASTERISK,
	KEY_PLUS,
	KEY_COMMA,
	KEY_MINUS,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_COLON,
	KEY_SEMICOLON,
	KEY_LESS,
	KEY_EQUALS,
	KEY_GREATER,
	KEY_QUESTION,
	KEY_AT,
	KEY_LEFTBRACKET,
	KEY_BACKSLASH,
	KEY_RIGHTBRACKET,
	KEY_CARET,
	KEY_UNDERSCORE,
	KEY_BACKQUOTE,
	KEY_a,
	KEY_b,
	KEY_c,
	KEY_d,
	KEY_e,
	KEY_f,
	KEY_g,
	KEY_h,
	KEY_i,
	KEY_j,
	KEY_k,
	KEY_l,
	KEY_m,
	KEY_n,
	KEY_o,
	KEY_p,
	KEY_q,
	KEY_r,
	KEY_s,
	KEY_t,
	KEY_u,
	KEY_v,
	KEY_w,
	KEY_x,
	KEY_y,
	KEY_z,
	KEY_CAPSLOCK,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,

	KEY_LAST
};

// TODO there must be a smarter way of doing this.
InputKey inline getInputKeyFromMouseButton(SDL_MouseButtonEvent& e) {
	if (e.button == SDL_BUTTON_LEFT) {
		return LEFT_CLICK;
	}
	else if (e.button == SDL_BUTTON_MIDDLE) {
		return MIDDLE_CLICK;
	}
	else if (e.button == SDL_BUTTON_RIGHT) {
		return RIGHT_CLICK;
	}
	exit(1);
}

InputKey inline getInputKeyFromControllerButton(Uint8 controllerButton) {
	switch (controllerButton) {
	case SDL_CONTROLLER_BUTTON_A:
		return CONTROLLER_A;
	case SDL_CONTROLLER_BUTTON_B:
		return CONTROLLER_B;
	case SDL_CONTROLLER_BUTTON_X:
		return CONTROLLER_X;
	case SDL_CONTROLLER_BUTTON_Y:
		return CONTROLLER_Y;
	case SDL_CONTROLLER_BUTTON_BACK:
		return CONTROLLER_BACK;
	case SDL_CONTROLLER_BUTTON_GUIDE:
		return CONTROLLER_GUIDE;
	case SDL_CONTROLLER_BUTTON_START:
		return CONTROLLER_START;
	case SDL_CONTROLLER_BUTTON_LEFTSTICK:
		return CONTROLLER_LEFTSTICK;
	case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
		return CONTROLLER_RIGHTSTICK;
	case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
		return CONTROLLER_LEFTSHOULDER;
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		return CONTROLLER_RIGHTSHOULDER;
	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		return CONTROLLER_DPAD_UP;
	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		return CONTROLLER_DPAD_DOWN;
	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		return CONTROLLER_DPAD_LEFT;
	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		return CONTROLLER_DPAD_RIGHT;
	default:
		break;
	}
	exit(1);
}

Uint8 inline getControllerButtonFromInputKey(InputKey inputKey) {
	switch (inputKey) {
	case CONTROLLER_A:
		return SDL_CONTROLLER_BUTTON_A;
	case CONTROLLER_B:
		return SDL_CONTROLLER_BUTTON_B;
	case CONTROLLER_X:
		return SDL_CONTROLLER_BUTTON_X;
	case CONTROLLER_Y:
		return SDL_CONTROLLER_BUTTON_Y;
	case CONTROLLER_BACK:
		return SDL_CONTROLLER_BUTTON_BACK;
	case CONTROLLER_GUIDE:
		return SDL_CONTROLLER_BUTTON_GUIDE;
	case CONTROLLER_START:
		return SDL_CONTROLLER_BUTTON_START;
	case CONTROLLER_LEFTSTICK:
		return SDL_CONTROLLER_BUTTON_LEFTSTICK;
	case CONTROLLER_RIGHTSTICK:
		return SDL_CONTROLLER_BUTTON_RIGHTSTICK;
	case CONTROLLER_LEFTSHOULDER:
		return SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
	case CONTROLLER_RIGHTSHOULDER:
		return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
	case CONTROLLER_DPAD_UP:
		return SDL_CONTROLLER_BUTTON_DPAD_UP;
	case CONTROLLER_DPAD_DOWN:
		return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	case CONTROLLER_DPAD_LEFT:
		return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	case CONTROLLER_DPAD_RIGHT:
		return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
	default:
		break;
	}
	exit(1);
}

InputKey inline getInputKeyFromControllerAxis(Uint8 controllerAxis) {
	switch (controllerAxis) {
	case SDL_CONTROLLER_AXIS_LEFTX:
		return CONTROLLER_AXIS_LEFTX;
	case SDL_CONTROLLER_AXIS_LEFTY:
		return CONTROLLER_AXIS_LEFTY;
	case SDL_CONTROLLER_AXIS_RIGHTX:
		return CONTROLLER_AXIS_RIGHTX;
	case SDL_CONTROLLER_AXIS_RIGHTY:
		return CONTROLLER_AXIS_RIGHTY;
	case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		return CONTROLLER_AXIS_TRIGGERLEFT;
	case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		return CONTROLLER_AXIS_TRIGGERRIGHT;
	default:
		break;
	}
	exit(1);
}

InputKey inline getInputKeyFromSdlKey(Uint8 key) {

	// Don't handle SDLK_UNKNOWN
	switch (key) {
	case SDLK_RETURN:
		return KEY_RETURN;
	case SDLK_ESCAPE:
		return KEY_ESCAPE;
	case SDLK_BACKSPACE:
		return KEY_BACKSPACE;
	case SDLK_TAB:
		return KEY_TAB;
	case SDLK_SPACE:
		return KEY_SPACE;
	case SDLK_EXCLAIM:
		return KEY_EXCLAIM;
	case SDLK_QUOTEDBL:
		return KEY_QUOTEDBL;
	case SDLK_HASH:
		return KEY_HASH;
	case SDLK_PERCENT:
		return KEY_PERCENT;
	case SDLK_DOLLAR:
		return KEY_DOLLAR;
	case SDLK_AMPERSAND:
		return KEY_AMPERSAND;
	case SDLK_QUOTE:
		return KEY_QUOTE;
	case SDLK_LEFTPAREN:
		return KEY_LEFTPAREN;
	case SDLK_RIGHTPAREN:
		return KEY_RIGHTPAREN;
	case SDLK_ASTERISK:
		return KEY_ASTERISK;
	case SDLK_PLUS:
		return KEY_PLUS;
	case SDLK_COMMA:
		return KEY_COMMA;
	case SDLK_MINUS:
		return KEY_MINUS;
	case SDLK_PERIOD:
		return KEY_PERIOD;
	case SDLK_SLASH:
		return KEY_SLASH;
	case SDLK_0:
		return KEY_0;
	case SDLK_1:
		return KEY_1;
	case SDLK_2:
		return KEY_2;
	case SDLK_3:
		return KEY_3;
	case SDLK_4:
		return KEY_4;
	case SDLK_5:
		return KEY_5;
	case SDLK_6:
		return KEY_6;
	case SDLK_7:
		return KEY_7;
	case SDLK_8:
		return KEY_8;
	case SDLK_9:
		return KEY_9;
	case SDLK_COLON:
		return KEY_COLON;
	case SDLK_SEMICOLON:
		return KEY_SEMICOLON;
	case SDLK_LESS:
		return KEY_LESS;
	case SDLK_EQUALS:
		return KEY_EQUALS;
	case SDLK_GREATER:
		return KEY_GREATER;
	case SDLK_QUESTION:
		return KEY_QUESTION;
	case SDLK_AT:
		return KEY_AT;
	case SDLK_LEFTBRACKET:
		return KEY_LEFTBRACKET;
	case SDLK_BACKSLASH:
		return KEY_BACKSLASH;
	case SDLK_RIGHTBRACKET:
		return KEY_RIGHTBRACKET;
	case SDLK_CARET:
		return KEY_CARET;
	case SDLK_UNDERSCORE:
		return KEY_UNDERSCORE;
	case SDLK_BACKQUOTE:
		return KEY_BACKQUOTE;
	case SDLK_a:
		return KEY_a;
	case SDLK_b:
		return KEY_b;
	case SDLK_c:
		return KEY_c;
	case SDLK_d:
		return KEY_d;
	case SDLK_e:
		return KEY_e;
	case SDLK_f:
		return KEY_f;
	case SDLK_g:
		return KEY_g;
	case SDLK_h:
		return KEY_h;
	case SDLK_i:
		return KEY_i;
	case SDLK_j:
		return KEY_j;
	case SDLK_k:
		return KEY_k;
	case SDLK_l:
		return KEY_l;
	case SDLK_m:
		return KEY_m;
	case SDLK_n:
		return KEY_n;
	case SDLK_o:
		return KEY_o;
	case SDLK_p:
		return KEY_p;
	case SDLK_q:
		return KEY_q;
	case SDLK_r:
		return KEY_r;
	case SDLK_s:
		return KEY_s;
	case SDLK_t:
		return KEY_t;
	case SDLK_u:
		return KEY_u;
	case SDLK_v:
		return KEY_v;
	case SDLK_w:
		return KEY_w;
	case SDLK_x:
		return KEY_x;
	case SDLK_y:
		return KEY_y;
	case SDLK_z:
		return KEY_z;
	case SDLK_CAPSLOCK:
		return KEY_CAPSLOCK;
	case SDLK_F1:
		return KEY_F1;
	case SDLK_F2:
		return KEY_F2;
	case SDLK_F3:
		return KEY_F3;
	case SDLK_F4:
		return KEY_F4;
	case SDLK_F5:
		return KEY_F5;
	case SDLK_F6:
		return KEY_F6;
	case SDLK_F7:
		return KEY_F7;
	case SDLK_F8:
		return KEY_F8;
	case SDLK_F9:
		return KEY_F9;
	case SDLK_F10:
		return KEY_F10;
	case SDLK_F11:
		return KEY_F11;
	case SDLK_F12:
		return KEY_F12;
	default:
		return INVALID;
	}
}

SDL_KeyCode inline getSdlKeyCodeFromInputKey(InputKey key) {

	// Don't handle SDLK_UNKNOWN
	switch (key) {
	case KEY_RETURN:
		return SDLK_RETURN;
	case KEY_ESCAPE:
		return SDLK_ESCAPE;
	case KEY_BACKSPACE:
		return SDLK_BACKSPACE;
	case KEY_TAB:
		return SDLK_TAB;
	case KEY_SPACE:
		return SDLK_SPACE;
	case KEY_EXCLAIM:
		return SDLK_EXCLAIM;
	case KEY_QUOTEDBL:
		return SDLK_QUOTEDBL;
	case KEY_HASH:
		return SDLK_HASH;
	case KEY_PERCENT:
		return SDLK_PERCENT;
	case KEY_DOLLAR:
		return SDLK_DOLLAR;
	case KEY_AMPERSAND:
		return SDLK_AMPERSAND;
	case KEY_QUOTE:
		return SDLK_QUOTE;
	case KEY_LEFTPAREN:
		return SDLK_LEFTPAREN;
	case KEY_RIGHTPAREN:
		return SDLK_RIGHTPAREN;
	case KEY_ASTERISK:
		return SDLK_ASTERISK;
	case KEY_PLUS:
		return SDLK_PLUS;
	case KEY_COMMA:
		return SDLK_COMMA;
	case KEY_MINUS:
		return SDLK_MINUS;
	case KEY_PERIOD:
		return SDLK_PERIOD;
	case KEY_SLASH:
		return SDLK_SLASH;
	case KEY_0:
		return SDLK_0;
	case KEY_1:
		return SDLK_1;
	case KEY_2:
		return SDLK_2;
	case KEY_3:
		return SDLK_3;
	case KEY_4:
		return SDLK_4;
	case KEY_5:
		return SDLK_5;
	case KEY_6:
		return SDLK_6;
	case KEY_7:
		return SDLK_7;
	case KEY_8:
		return SDLK_8;
	case KEY_9:
		return SDLK_9;
	case KEY_COLON:
		return SDLK_COLON;
	case KEY_SEMICOLON:
		return SDLK_SEMICOLON;
	case KEY_LESS:
		return SDLK_LESS;
	case KEY_EQUALS:
		return SDLK_EQUALS;
	case KEY_GREATER:
		return SDLK_GREATER;
	case KEY_QUESTION:
		return SDLK_QUESTION;
	case KEY_AT:
		return SDLK_AT;
	case KEY_LEFTBRACKET:
		return SDLK_LEFTBRACKET;
	case KEY_BACKSLASH:
		return SDLK_BACKSLASH;
	case KEY_RIGHTBRACKET:
		return SDLK_RIGHTBRACKET;
	case KEY_CARET:
		return SDLK_CARET;
	case KEY_UNDERSCORE:
		return SDLK_UNDERSCORE;
	case KEY_BACKQUOTE:
		return SDLK_BACKQUOTE;
	case KEY_a:
		return SDLK_a;
	case KEY_b:
		return SDLK_b;
	case KEY_c:
		return SDLK_c;
	case KEY_d:
		return SDLK_d;
	case KEY_e:
		return SDLK_e;
	case KEY_f:
		return SDLK_f;
	case KEY_g:
		return SDLK_g;
	case KEY_h:
		return SDLK_h;
	case KEY_i:
		return SDLK_i;
	case KEY_j:
		return SDLK_j;
	case KEY_k:
		return SDLK_k;
	case KEY_l:
		return SDLK_l;
	case KEY_m:
		return SDLK_m;
	case KEY_n:
		return SDLK_n;
	case KEY_o:
		return SDLK_o;
	case KEY_p:
		return SDLK_p;
	case KEY_q:
		return SDLK_q;
	case KEY_r:
		return SDLK_r;
	case KEY_s:
		return SDLK_s;
	case KEY_t:
		return SDLK_t;
	case KEY_u:
		return SDLK_u;
	case KEY_v:
		return SDLK_v;
	case KEY_w:
		return SDLK_w;
	case KEY_x:
		return SDLK_x;
	case KEY_y:
		return SDLK_y;
	case KEY_z:
		return SDLK_z;
	case KEY_CAPSLOCK:
		return SDLK_CAPSLOCK;
	case KEY_F1:
		return SDLK_F1;
	case KEY_F2:
		return SDLK_F2;
	case KEY_F3:
		return SDLK_F3;
	case KEY_F4:
		return SDLK_F4;
	case KEY_F5:
		return SDLK_F5;
	case KEY_F6:
		return SDLK_F6;
	case KEY_F7:
		return SDLK_F7;
	case KEY_F8:
		return SDLK_F8;
	case KEY_F9:
		return SDLK_F9;
	case KEY_F10:
		return SDLK_F10;
	case KEY_F11:
		return SDLK_F11;
	case KEY_F12:
		return SDLK_F12;
	default:
		return SDLK_UNKNOWN;
	}
	/* These are SDL Keycodes that haven't been mapped
	SDLK_PRINTSCREEN
	SDLK_SCROLLLOCK
	SDLK_PAUSE
	SDLK_INSERT
	SDLK_HOME
	SDLK_PAGEUP
	SDLK_DELETE = '\177',
	SDLK_END
	SDLK_PAGEDOWN
	SDLK_RIGHT
	SDLK_LEFT
	SDLK_DOWN
	SDLK_UP
	SDLK_NUMLOCKCLEAR
	SDLK_KP_DIVIDE
	SDLK_KP_MULTIPLY
	SDLK_KP_MINUS
	SDLK_KP_PLUS
	SDLK_KP_ENTER
	SDLK_KP_1
	SDLK_KP_2
	SDLK_KP_3
	SDLK_KP_4
	SDLK_KP_5
	SDLK_KP_6
	SDLK_KP_7
	SDLK_KP_8
	SDLK_KP_9
	SDLK_KP_0
	SDLK_KP_PERIOD
	SDLK_APPLICATION
	SDLK_POWER
	SDLK_KP_EQUALS
	SDLK_F13
	SDLK_F14
	SDLK_F15
	SDLK_F16
	SDLK_F17
	SDLK_F18
	SDLK_F19
	SDLK_F20
	SDLK_F21
	SDLK_F22
	SDLK_F23
	SDLK_F24
	SDLK_EXECUTE
	SDLK_HELP
	SDLK_MENU
	SDLK_SELECT
	SDLK_STOP
	SDLK_AGAIN
	SDLK_UNDO
	SDLK_CUT
	SDLK_COPY
	SDLK_PASTE
	SDLK_FIND
	SDLK_MUTE
	SDLK_VOLUMEUP
	SDLK_VOLUMEDOWN
	SDLK_KP_COMMA
	SDLK_KP_EQUALSAS400
	SDLK_ALTERASE
	SDLK_SYSREQ
	SDLK_CANCEL
	SDLK_CLEAR
	SDLK_PRIOR
	SDLK_RETURN2
	SDLK_SEPARATOR
	SDLK_OUT
	SDLK_OPER
	SDLK_CLEARAGAIN
	SDLK_CRSEL
	SDLK_EXSEL
	SDLK_KP_00
	SDLK_KP_000
	SDLK_THOUSANDSSEPARATOR
	SDLK_DECIMALSEPARATOR
	SDLK_CURRENCYUNIT
	SDLK_CURRENCYSUBUNIT
	SDLK_KP_LEFTPAREN
	SDLK_KP_RIGHTPAREN
	SDLK_KP_LEFTBRACE
	SDLK_KP_RIGHTBRACE
	SDLK_KP_TAB
	SDLK_KP_BACKSPACE
	SDLK_KP_A
	SDLK_KP_B
	SDLK_KP_C
	SDLK_KP_D
	SDLK_KP_E
	SDLK_KP_F
	SDLK_KP_XOR
	SDLK_KP_POWER
	SDLK_KP_PERCENT
	SDLK_KP_LESS
	SDLK_KP_GREATER
	SDLK_KP_AMPERSAND
	SDLK_KP_DBLAMPERSAND
	SDLK_KP_VERTICALBAR
	SDLK_KP_DBLVERTICALBAR
	SDLK_KP_COLON
	SDLK_KP_HASH
	SDLK_KP_SPACE
	SDLK_KP_AT
	SDLK_KP_EXCLAM
	SDLK_KP_MEMSTORE
	SDLK_KP_MEMRECALL
	SDLK_KP_MEMCLEAR
	SDLK_KP_MEMADD
	SDLK_KP_MEMSUBTRACT
	SDLK_KP_MEMMULTIPLY
	SDLK_KP_MEMDIVIDE
	SDLK_KP_PLUSMINUS
	SDLK_KP_CLEAR
	SDLK_KP_CLEARENTRY
	SDLK_KP_BINARY
	SDLK_KP_OCTAL
	SDLK_KP_DECIMAL
	SDLK_KP_HEXADECIMAL
	SDLK_LCTRL
	SDLK_LSHIFT
	SDLK_LALT
	SDLK_LGUI
	SDLK_RCTRL
	SDLK_RSHIFT
	SDLK_RALT
	SDLK_RGUI
	SDLK_MODE
	SDLK_AUDIONEXT
	SDLK_AUDIOPREV
	SDLK_AUDIOSTOP
	SDLK_AUDIOPLAY
	SDLK_AUDIOMUTE
	SDLK_MEDIASELECT
	SDLK_WWW
	SDLK_MAIL
	SDLK_CALCULATOR
	SDLK_COMPUTER
	SDLK_AC_SEARCH
	SDLK_AC_HOME
	SDLK_AC_BACK
	SDLK_AC_FORWARD
	SDLK_AC_STOP
	SDLK_AC_REFRESH
	SDLK_AC_BOOKMARKS
	SDLK_BRIGHTNESSDOWN
	SDLK_BRIGHTNESSUP
	SDLK_DISPLAYSWITCH
	SDLK_KBDILLUMTOGGLE
	SDLK_KBDILLUMDOWN
	SDLK_KBDILLUMUP
	SDLK_EJECT
	SDLK_SLEEP
	SDLK_APP1
	SDLK_APP2
	SDLK_AUDIOREWIND
	SDLK_AUDIOFASTFORWARD
	*/
}