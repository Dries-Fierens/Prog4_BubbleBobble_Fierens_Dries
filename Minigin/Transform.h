#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec2& GetPosition() const { return m_position; }
		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);
	private:
		glm::vec2 m_position;
	};
}
