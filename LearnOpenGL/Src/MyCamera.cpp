#include "MyCamera.h"
#include <iostream>
#include <GLFW/glfw3.h>
MyCamera::MyCamera(glm::vec3 pos, glm::vec3 worldUp, glm::vec3 target)
	:m_CameraPos(pos)
	,m_WorldUp(worldUp)
	,m_Pitch(0.f)
	,m_Yaw(-90.f)
	,IsFirstInGame(true)
	,m_MouseX(0.f)
	,m_MouseY(0.f)
{
	m_Forward	= glm::normalize(target - m_CameraPos);
	m_Right		= glm::normalize(glm::cross(m_Forward, m_WorldUp));
	m_Up		= glm::normalize(glm::cross(m_Right, m_Forward));
}

MyCamera::MyCamera(glm::vec3 pos, glm::vec3 worldUp, float pitch, float yaw, float moveSpeed, float Sensitivity)
	:m_CameraPos(pos)
	,m_WorldUp(worldUp)
	, m_Pitch(pitch)
	,m_Yaw(yaw)
	,IsFirstInGame(true)
	,m_MouseX(0.f)
	,m_MouseY(0.f)
	,m_MovementSpeed(moveSpeed)
	,m_Sensitivity(Sensitivity)
{
	UpdateCamera();
}

MyCamera::~MyCamera()
{
}

glm::mat4 MyCamera::GetViewMatrix()
{
	return glm::lookAt(m_CameraPos, m_CameraPos + m_Forward, m_Up);
}

void MyCamera::MouseInput(double x, double y)
{
	if (IsFirstInGame)
	{
		m_MouseX = x;
		m_MouseY = y;
		IsFirstInGame = false;
	}

	float delX = (x - m_MouseX) * m_Sensitivity;
	float delY = (y - m_MouseY) * m_Sensitivity;
	m_MouseX = x;
	m_MouseY = y;
	m_Yaw += delX;
	m_Pitch -= delY;
	if (m_Pitch > 60)
	{
		m_Pitch = 60;
	}
	else if (m_Pitch < -60)
	{
		m_Pitch = -60;
	}
	/*if (m_Yaw > 45)
	{
		m_Yaw = 45;
	}
	else if (m_Yaw < -45)
	{
		m_Yaw = -45;
	}*/

	UpdateCamera();
}

void MyCamera::ProcessKeyboard(CameraMoveDirection direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;

	if (direction == CameraMoveDirection::FORWARD)
		m_CameraPos += m_Forward * velocity;
	if (direction == CameraMoveDirection::BACK)
		m_CameraPos -= m_Forward * velocity;
	if (direction == CameraMoveDirection::LEFT)
		m_CameraPos -= m_Right * velocity;
	if (direction == CameraMoveDirection::RIGHT)
		m_CameraPos += m_Right * velocity;
	if (direction == CameraMoveDirection::UP)
		m_CameraPos += m_Up * velocity;
	if (direction == CameraMoveDirection::DOWN)
		m_CameraPos -= m_Up * velocity;
	if (direction == CameraMoveDirection::FOCUS)
	{
		m_CameraPos = glm::vec3(0.f, 0.f, 3.f);
		m_Yaw = -90.f;
		m_Pitch = 0.f;
	}

	UpdateCamera();
}

void MyCamera::IncSensitivity()
{
	m_Sensitivity += 0.001;
	if (m_Sensitivity > 1)
	{
		m_Sensitivity = 1;
	}
}

void MyCamera::DescSensitivity()
{
	m_Sensitivity -= 0.001;
	if (m_Sensitivity <= 0)
	{
		m_Sensitivity = 0.001;
	}
}

void MyCamera::UpdateCamera()
{
	glm::vec3 forward;
	forward.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	forward.y = glm::sin(glm::radians(m_Pitch));
	forward.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	m_Forward = glm::normalize(forward);

	m_Right = glm::normalize(glm::cross(m_Forward, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}
