//
// Created by ianpo on 14/07/2023.
//

#pragma once
#include "Voxymore/Core/Core.hpp"
#include "Voxymore/Core/Window.hpp"
#define GLFW_INCLUDE_NONE 1
#include "GLFW/glfw3.h"

namespace Voxymore::Core {

    class DefaultWindow : public Voxymore::Core::Window {
    public:
        DefaultWindow(const WindowProps& props);
        virtual ~DefaultWindow();

        virtual void OnUpdate() override;

        virtual inline unsigned int GetWidth() const override { return m_Data.Width; }
        virtual inline unsigned int GetHeight() const override { return m_Data.Height; }


        virtual inline void SetEventCallback(const EventCallBackFn& callback) override { m_Data.EventCallback = callback; }
        virtual void SetVSync(bool enabled) override;
        virtual bool IsVSync() const override;
        virtual bool IsMinify() const override;
        virtual inline void* GetNativeWindow() override {
            return m_Window;
        }
        virtual void SetCursorState(CursorState cursorState) override;
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;
        struct DefaultData
        {
            std::string Title;
            uint32_t Width, Height;
            bool Minified;
            bool VSync;

            EventCallBackFn  EventCallback;
        };
        DefaultData m_Data;
        CursorState m_CursorState;
    };

} // Core
