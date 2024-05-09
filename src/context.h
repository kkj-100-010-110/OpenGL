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
#include "image.h"
#include "texture.h"

CLASS_PTR(Context)
class Context {
  public:
    static ContextUPtr Create();
    void Render();
    void ProcessInput(GLFWwindow* window);
    void Reshape(int width, int height);
    void MouseMove(double x, double y);
    void MouseButton(int button, int action, double x, double y);

  private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;
    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
    TextureUPtr m_texture;
    TextureUPtr m_texture2;

    // camera parameters
    bool m_cameraControl{false};
    glm::vec2 m_prevMousePos{glm::vec2(0.0f)};

    float m_cameraPitch{0.0f};
    float m_cameraYaw{0.0f};

    glm::vec3 m_cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)};
    glm::vec3 m_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::vec3 m_cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)};

    int m_width{WINDOW_WIDTH};
    int m_height{WINDOW_HEIGHT};
};

#endif // __CONTEXT_H__