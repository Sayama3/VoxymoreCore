//
// Created by ianpo on 30/07/2023.
//

#pragma once

#include "Voxymore/Core/Core.hpp"
#include "Voxymore/Core/KeyCodes.hpp"
#include "Voxymore/Core/TimeStep.hpp"
#include "Voxymore/Layers/Layer.hpp"
#include "Voxymore/Events/Event.hpp"
#include "Voxymore/Events/ApplicationEvent.hpp"
#include "Voxymore/Events/KeyEvent.hpp"
#include "Voxymore/Events/MouseEvent.hpp"
#include "Voxymore/Renderer/PerspectiveCamera.hpp"

namespace Voxymore::Core {
    class PerspectiveCameraController : public Layer {
    public:
        PerspectiveCameraController(float width, float height);

        virtual void OnUpdate(TimeStep ts) override;
        virtual void OnEvent(Event& e) override;

        inline PerspectiveCamera& GetCamera() { return m_Camera; }
        inline const PerspectiveCamera& GetCamera() const { return m_Camera; }

    public:
        inline bool IsEnable() const { return m_Enable; }
        void SetEnable(bool isEnable);

        inline float GetWidth() const { return m_Width; }
        inline float GetHeight() const { return m_Height; }

        void SetWidth(uint32_t width);
        void SetHeight(uint32_t height);
        void SetSize(uint32_t width, uint32_t height);

        inline float GetFOV() const { return m_FOV; }
        inline void SetFOV(float fOV) { m_FOV = fOV; m_UpdateProjectionMatrix = true; }

        inline float GetNearClip() const { return m_NearClip; }
        inline void SetNearClip(float nearClip) { m_NearClip = nearClip; m_UpdateProjectionMatrix = true; }

        inline float GetFarClip() const { return m_FarClip; }
        inline void SetFarClip(float farClip) { m_FarClip = farClip; m_UpdateProjectionMatrix = true; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

        void UpdateMovement();
        void UpdateRotation();
    private:
        bool m_Enable = true;
        bool m_UpdateViewMatrix = false;
        bool m_UpdateProjectionMatrix = false;
    private:
        const float c_ScrollStep = 0.5f;
        const float c_TranslationSpeed = 5.0f;
        const float c_RotationSpeed = 0.5f;
        float m_Width;
        float m_Height;
        float m_FOV = 45.0f;
        float m_NearClip = 0.01f;
        float m_FarClip = 1000.0f;

        glm::vec3 m_Position = glm::zero<glm::vec3>();
        glm::quat m_Rotation = glm::identity<glm::quat>();
    private:
        bool m_HasSetMouse = false;
        glm::vec3 m_Movement = glm::zero<glm::vec3>();
        float m_MouseX, m_MouseY;
        float m_Sensitivity = 1.0f;
    private:
		Key m_ForwardKey = Key::W;
		Key m_BackwardKey = Key::S;
		Key m_RightKey = Key::D;
		Key m_LeftKey = Key::A;
		Key m_UpKey = Key::E;
		Key m_DownKey = Key::Q;
    private:
        PerspectiveCamera m_Camera;
    };

} // Core
