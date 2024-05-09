#ifndef __COMMON_H__
#define __COMMON_H__
/**
 * @file common.h
 * @author GYEONG JU KIM
 * @brief common functions for other classes
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// macro for aliasing class pointers
#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__