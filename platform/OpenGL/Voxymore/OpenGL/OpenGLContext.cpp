//
// Created by ianpo on 19/07/2023.
//

#include "OpenGLContext.hpp"
#include "Voxymore/Core/Logger.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Voxymore {
    namespace Core {
        OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {

        }

        OpenGLContext::~OpenGLContext() {

        }

        void OpenGLContext::Init() {
            VXM_PROFILE_FUNCTION();
            glfwMakeContextCurrent(m_WindowHandle);
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            VXM_CORE_INFO("glad loading status: {0}", status);

            VXM_CORE_INFO("OpenGL Info:");
            VXM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
            VXM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
            VXM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
        }

        void OpenGLContext::SwapBuffers() {
            VXM_PROFILE_FUNCTION();
            glfwSwapBuffers(m_WindowHandle);
        }
    } // Voxymore
} // Core