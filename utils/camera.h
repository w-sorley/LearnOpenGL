#ifndef CAMERA_H
#define CAMERA_H

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define DEFAULT_YAW  -90.0f
#define DEFAULT_PATCH  0.0f

#define DEFAULT_SPEED 2.5f
#define DEFAULT_SENSITIVITY 0.1f
#define DEFAULT_ZOOM 45.0f

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

class Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 WorldUp;
        glm::vec3 Right;

        float Yaw;
        float Patch;

        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

    
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = DEFAULT_YAW, float patch = DEFAULT_PATCH ) :  Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(DEFAULT_SPEED),
            MouseSensitivity(DEFAULT_SENSITIVITY), Zoom(DEFAULT_ZOOM) {
                Position = position;
                WorldUp = worldUp;
                Yaw = yaw;
                Patch = patch;
                updateCameraVectors();
        }

        glm::mat4 GetViewMatrix() {
            return glm::lookAt(Position, Position + Front, Up);
        }

        void ProcessKeyboard(Camera_Movement direction, float deltatime) {
            float velocity = MovementSpeed * deltatime;
            switch (direction)
            {
            case FORWARD:
                Position += Front * velocity;
                break;
            case BACKWARD:
                Position -= Front * velocity;
                break;
            case LEFT:
                Position -= Right * velocity;
                break;
            case RIGHT:
                Position += Right * velocity;
                break;
            default:
                break;
            }
        }

        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;
            Yaw   += xoffset;
            Patch += yoffset;
            if(Yaw > 89.0f) Yaw = 89.0f;
            if(Patch < -89.0f) Patch = -89.0f;

            updateCameraVectors();   
        }

        void ProcessMouseScroll(float yoffset) {
            if(Zoom >=1.0f && Zoom <= 45.0f)
                Zoom -= yoffset;
            
            if(Zoom < 1.0)
                Zoom = 1.0f;
            if (Zoom > 45.0f)
                Zoom = 45.0f;
        }

    private:
        void updateCameraVectors() {
            glm::vec3 front = glm::vec3(0.0f);
            // 这里是默认起始位置指向x轴的正方向（1，0，0）
            front.x = cos(glm::radians(Patch)) * cos(glm::radians(Yaw));
            front.y = sin(glm::radians(Patch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Patch));
            Front   = glm::normalize(front);

            Right = glm::normalize(glm::cross(Front, WorldUp));
            Up    = glm::normalize(glm::cross(Right, Front));
        }
};

#endif