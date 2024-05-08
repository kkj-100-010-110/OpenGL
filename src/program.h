#ifndef __PROGRAM_H__
#define __PROGRAM_H__
/**
 * @file program.h
 * @author GYEONG JU KIM
 * @brief pipeline program linked by shaders(vs, fs)
 * @version 0.1
 * @date 2024-03-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.h"
#include "shader.h"

CLASS_PTR(Program)
class Program
{
public:
    static ProgramUPtr Create( const std::vector<ShaderPtr> &shaders);

    ~Program();
    uint32_t Get() const { return m_program; }
    void Use() const;

private:
    Program() {}
    bool Link( const std::vector<ShaderPtr> &shaders);
    uint32_t m_program{0};
};
#endif // __PROGRAM_H__