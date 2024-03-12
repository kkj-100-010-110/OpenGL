#ifndef __SHADER_H__
#define __SHADER_H__
/**
 * @file shader.h
 * @author GYEONG JU KIM
 * @brief class to create shaders
 * @version 0.1
 * @date
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.h"

CLASS_PTR(Shader);
class Shader {
  public:
    static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);
    ~Shader();
    uint32_t Get() const { return m_shader; }

  private:
    Shader() {}
    bool LoadFile(const std::string& filename, GLenum shaderType);
    uint32_t m_shader{0};
};

#endif // __SHADER_H__