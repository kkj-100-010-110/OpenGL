#include "context.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void OnCharEvent(GLFWwindow* window, unsigned int ch)
{
    ImGui_ImplGlfw_CharCallback(window, ch);
}

void OnScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

// window에서 키 이벤트 발생 시 호출하기 위한 콜백 정의
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    SPDLOG_INFO(
        "key: {}, scancode: {}, action: {}, mods: {}{}{}", key, scancode,
        action == GLFW_PRESS ? "Pressed"
        : action == GLFW_RELEASE ? "Released"
        : action == GLFW_REPEAT  ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C"
        : "-", mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// window의 프레임 버퍼 크기가 변경되었을 때 호출하기 위한 콜백 정의
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height)
{
    // SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    // glViewport(0, 0, width, height);
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    auto context = reinterpret_cast<Context*>(glfwGetWindowUserPointer(window));
    context->Reshape(width, height);
}

void OnCursorPos(GLFWwindow* window, double x, double y)
{
    auto context = (Context*)glfwGetWindowUserPointer(window);
    context->MouseMove(x, y);
}

void OnMouseButton(GLFWwindow* window, int button, int action, int modifier)
{
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, modifier);
    auto context = (Context*)glfwGetWindowUserPointer(window);
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    context->MouseButton(button, action, x, y);
}

int main(int argc, char* argv[])
{
    SPDLOG_INFO("Start the program");
    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("error: failed to initialize glfw: {}", description);
        return -1;
    }
    // glfwWindowHint을 통해서 아래의 인자 값으로 환경 설정하라고 알려준다.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
                                   nullptr, nullptr);
    if (!window) {
        SPDLOG_ERROR("error: failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    // 창 생성 후 이 창이 현재 스레드에서 메인 context라고 glfw에 알려준다.
    glfwMakeContextCurrent(window);
    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("error: failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    auto glVersion = (char*)glGetString(GL_VERSION);

    // create imgui context
    auto imguiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(imguiContext);
    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplOpenGL3_CreateFontsTexture();
    ImGui_ImplOpenGL3_CreateDeviceObjects();

    auto context = Context::Create();
    if (!context) {
        SPDLOG_ERROR("error: failed to create context");
        glfwTerminate();
        return -1;
    }
    // 전역 변수 사용 대신 glfw에 context 포인터를 설정하여 사용하기 위한 함수
    glfwSetWindowUserPointer(window, context.get());

    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    // glfw에게 프레임 버퍼 사이즈 변경 시 현재 컨텍스트에서 'OnFramebufferSizeChange' 콜백 요청
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    // glfw에게 키 이벤트 발생 시 현재 컨텍스트에서 'OnKeyEvent' 콜백 요청
    glfwSetKeyCallback(window, OnKeyEvent);

    glfwSetCharCallback(window, OnCharEvent);

    // glfw에게 마우스 커서의 움직임에 따른 'OnCursorPos' 콜백 요청
    glfwSetCursorPosCallback(window, OnCursorPos);
    // glfw에게 마우스 버튼이 클릭이 되어있을 때 'OnMouseButton' 콜백 요청
    glfwSetMouseButtonCallback(window, OnMouseButton);

    glfwSetScrollCallback(window, OnScroll);

    SPDLOG_INFO("OpenGL context version: {}", glVersion);
    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        context->ProcessInput(window);
        context->Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    context.reset(); // or context = nullptr;

    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_DestroyDeviceObjects();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(imguiContext);

    glfwTerminate();
    return 0;
}