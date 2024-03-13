#ifndef __CONTEXT_H__
#define __CONTEXT_H__
/**
 * @file context.h
 * @author GYEONG JU KIM
 * @brief Initialize GLFW/OpenGL context/GLAD, create openGL objects(shaders/programs), render and terminate GLFW/program
 * @version 0.1
 * @date
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.h"
#include "program.h"
#include "shader.h"
#include "buffer.h"
#include "vertex_layout.h"

CLASS_PTR(Context)
class Context {
  public:
    static ContextUPtr Create();
    void Render();

  private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;
    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
};

#endif // __CONTEXT_H__