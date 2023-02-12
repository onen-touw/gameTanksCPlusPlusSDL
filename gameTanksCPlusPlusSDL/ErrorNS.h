#pragma once

#include<iostream>

enum ErrorsCodes : uint8_t
{
	OK, 
	IMG_LOADING_ERROR = 100, 
	MAP_LOADING_ERROR,
	FONT_OPEN_ERROR,
};

namespace errors {
	extern uint8_t errorStatus;
}

