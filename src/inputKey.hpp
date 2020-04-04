#ifndef __WTF__
#define __WTF__

enum InputKey {
	LEFT_CLICK = 0,
	RIGHT_CLICK = 1,
	MIDDLE_CLICK = 2
};

// TODO there must be a smarter way of doing this.
InputKey inline getInputKey(SDL_MouseButtonEvent& e) {
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

#endif