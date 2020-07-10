#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

enum class CameraMoveDirection
{
	FORWARD,
	BACK,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FOCUS
};

class MyCamera
{
public:
	MyCamera(glm::vec3 pos, glm::vec3 worldUp, glm::vec3 target);
	MyCamera(glm::vec3 pos, glm::vec3 worldUp, float pitch, float yaw = -90.f, float moveSpeed = 1.f,
		float Sensitivity = 0.1f);
	~MyCamera();

private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_WorldUp;
	glm::vec3 m_Forward;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	float m_Pitch;
	float m_Yaw;
	float m_FOV;

	bool IsFirstInGame;
	float m_MouseX;
	float m_MouseY;
	float m_MovementSpeed;
	float m_Sensitivity;

public:
	glm::mat4 GetViewMatrix();

	inline const glm::vec3& GetCameraPos() const { return m_CameraPos; }

	void MouseInput(double x, double y);
	void ProcessKeyboard(CameraMoveDirection direction, float deltaTime);
	void IncSensitivity();
	void DescSensitivity();

	const glm::vec3& GetForward() const { return m_Forward; }
	void SetMoveSpeed(float val) { m_MovementSpeed = val; }
private:

	void UpdateCamera();
};

