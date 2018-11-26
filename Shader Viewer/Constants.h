#pragma once
#include <glm/gtc/constants.hpp>

// Functions and consts for vertex and index buffer lengths 
static const int VBLEN_PLANE = 4;
static const int VBLEN_CUBE = 24;
inline int VBLEN_SPHERE(int slices, int stacks) {
	return (slices + 1) * (stacks + 1);
}

static const int IBLEN_PLANE = 6;
static const int IBLEN_CUBE = 36;
inline int IBLEN_SPHERE(int slices, int stacks) {
	return slices * stacks * 6;
}

static const double PI = glm::pi<double>();
static const double EPS = glm::epsilon<double>();
static const double EPS2 = EPS * EPS;
static const double EPS3 = EPS2 * EPS;