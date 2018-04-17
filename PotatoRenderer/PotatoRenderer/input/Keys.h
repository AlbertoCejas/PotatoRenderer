#ifndef _KEYS_H_
#define _KEYS_H_

#include <cstdint>

// GLFW
#include <GLFW/glfw3.h>

enum class Key : int32_t
{
	KEY_A = GLFW_KEY_A,
	KEY_S = GLFW_KEY_S,
	KEY_D = GLFW_KEY_D,
	KEY_W = GLFW_KEY_W
};

#endif