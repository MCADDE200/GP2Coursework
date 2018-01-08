#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct TheCamera
{
public:
	TheCamera()
	{
	}

	void initCamera(const glm::vec3& position, float fieldOfView, float aspect, float nearClip, float farClip)
	{
		this->position = position;
		this->forwards = glm::vec3(0.0f, 0.0f, 1.0f);
		this->upwards = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projectionMatrix = glm::perspective(fieldOfView, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projectionMatrix * glm::lookAt(position, position + forwards, upwards);
	}

	void MoveForward(float amt)
	{
		position += forwards * amt;
	}

	void MoveRight(float amt)
	{
		position += glm::cross(upwards, forwards) * amt;
	}

	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(upwards, forwards));

		forwards = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forwards, 0.0)));
		upwards = glm::normalize(glm::cross(forwards, right));
	}

	void RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forwards = glm::vec3(glm::normalize(rotation * glm::vec4(forwards, 0.0)));
		upwards = glm::vec3(glm::normalize(rotation * glm::vec4(upwards, 0.0)));
	}

	glm::vec3 GetCameraPosition()
	{
		return this->position;
	}

protected:
private:
	glm::mat4 projectionMatrix;
	glm::vec3 position;
	glm::vec3 forwards;
	glm::vec3 upwards;
};


