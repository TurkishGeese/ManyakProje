#pragma once

enum InputKey {
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
    CONTROLLER_AXIS_TRIGGERRIGHT
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
    switch(controllerButton) {
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