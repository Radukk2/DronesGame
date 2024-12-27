#pragma once

#include "components/simple_scene.h"
#include "lab_m1/DroneMiniGames/droneCamera.h"


namespace m1
{
    struct ViewportArea
    {
        ViewportArea() : x(0), y(0), width(1), height(1) {}
        ViewportArea(int x, int y, int width, int height)
            : x(x), y(y), width(width), height(height) {}
        int x;
        int y;
        int width;
        int height;
    };
    class DronesGame : public gfxc::SimpleScene
    {
    public:
        DronesGame();
        ~DronesGame();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void RenderDrone();
        void RenderTree(float x, float y, float z);
        void RenderPropeller(float angle, glm::mat4 modelMatrix);
        void RenderArrow();
        void generate_trees(float deltaTimeSeconds);
        void RenderPackage(glm::mat4 modelMatrix);
        bool CheckCollision();
        void ReinitializeMap();
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::DroneCamera* camera, *camera_above;
        glm::mat4 projectionMatrix, projectionMatrix_1;
        bool renderCameraTarget;
        float fov;
        float aspect;
        float zNear;
        float zFar;
        float left;
        float right;
        float bottom;
        float top;
        float angle_offset;
        float drone_rotation_angle;
        float tilt_forward;
        float tilt_right;
        float acceleration,  verticalAcceleration;
        float verticalSpeed;
        bool stabilize;
        bool once_generated, picked, inDropZone;
        ViewportArea miniViewportArea;
        std::vector<std::pair<float, float>> trees, centers;
        int random1, random2, score;
        float x, time1;
        // TODO(student): If you need any other class variables, define them here.

    };

    
}   // namespace m1
