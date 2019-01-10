#pragma once
#include <glm/gtc/constants.hpp>

static const float PI = glm::pi<float>();
static const float EPS = glm::epsilon<float>();
static const float EPS2 = EPS * EPS;
static const float EPS3 = EPS2 * EPS;

static const glm::vec3 XAXIS(1, 0, 0);
static const glm::vec3 YAXIS(0, 1, 0);
static const glm::vec3 ZAXIS(0, 0, 1);

static const std::string SHADER_DIR = "./Shaders/";
static const std::string TEXTURE_DIR = "./Textures/";