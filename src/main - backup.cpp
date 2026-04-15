//
// Created by Earth_Studio on 2026/4/12.
//

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <iostream>
#include <filesystem>

// 辅助函数：跨平台寻找可用的中文字体
std::string FindChineseFont() {
    // Windows 下的微软雅黑
    if (std::filesystem::exists("C:\\Windows\\Fonts\\msyh.ttc")) return "C:\\Windows\\Fonts\\msyh.ttc";
    if (std::filesystem::exists("C:\\Windows\\Fonts\\msyh.ttf")) return "C:\\Windows\\Fonts\\msyh.ttf";
    // Arch Linux 下常见的思源黑体
    if (std::filesystem::exists("/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc")) return "/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc";
    if (std::filesystem::exists("/usr/share/fonts/wqy-microhei/wqy-microhei.ttc")) return "/usr/share/fonts/wqy-microhei/wqy-microhei.ttc";
    return "";
}

// 核心拦截器：专门拦截多行文本框的“回车换行”符
static int FilterEnterCallback(ImGuiInputTextCallbackData* data) {
    if (data->EventChar == '\n' || data->EventChar == '\r') {
        return 1; // 1 表示拦截/丢弃该字符
    }
    return 0; // 0 表示允许通过
}

int main() {
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* hidden_window = glfwCreateWindow(1, 1, "Hidden", nullptr, nullptr);
    if (!hidden_window) { glfwTerminate(); return -1; }

    glfwMakeContextCurrent(hidden_window);
    glfwSwapInterval(1);

    if (!gladLoadGL(glfwGetProcAddress)) return -1;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigViewportsNoAutoMerge = true;
    io.IniFilename = nullptr;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(hidden_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // =========================================================================
    // 终极修复一：加载中文字体，解决显示 "??" 和乱码的问题
    // =========================================================================
    std::string fontPath = FindChineseFont();
    if (!fontPath.empty()) {
        ImFontConfig fontConfig;
        // 开启过采样，让字体在显示器上更平滑清晰
        fontConfig.OversampleH = 2;
        fontConfig.OversampleV = 2;
        // 这里的 GetGlyphRangesChineseFull() 包含了绝大多数中文、日文和全角标点
        io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 18.0f, &fontConfig, io.Fonts->GetGlyphRangesChineseFull());
    } else {
        std::cerr << "[Warning] No Chinese font found! Fallback to default." << std::endl;
        io.Fonts->AddFontDefault();
    }
    // =========================================================================

    bool is_open = true;
    char input_buffer[256] = "在这里输入中文测试 IME..."; // 测试 IME 的文本缓冲区

    while (!glfwWindowShouldClose(hidden_window) && is_open) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
        if (ImGui::Begin("CMaterial - 字体与输入法测试", &is_open, flags)) {
            ImGui::Text("Hello, Material Design 3!");
            ImGui::Text("当前帧耗时: %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            ImGui::Separator();

            // =========================================================================
            // 终极修复二：Fcitx5 异步吞字终极解决方案 (伪装单行大法)
            // =========================================================================
            ImGui::Text("输入法 (IME) 测试区域：");

            // 1. 获取标准单行输入框的高度
            ImVec2 single_line_size = ImVec2(0, ImGui::GetFrameHeight());

            // 2. 召唤伪装成单行的 Multiline 文本框
            // 加上 CallbackCharFilter 标志，并传入我们刚刚写的拦截器
            ImGui::InputTextMultiline("##ime_test",
                                      input_buffer,
                                      IM_ARRAYSIZE(input_buffer),
                                      single_line_size,
                                      ImGuiInputTextFlags_CallbackCharFilter,
                                      FilterEnterCallback);

            ImGui::Text("你输入的内容: %s", input_buffer);
            // =========================================================================

            if (ImGui::Button("退出引擎")) {
                is_open = false;
            }
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_context);
        }

        glfwSwapBuffers(hidden_window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(hidden_window);
    glfwTerminate();

    return 0;
}