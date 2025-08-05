#include "SpriteComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Timer.h"

dae::SpriteComponent::SpriteComponent(const std::string& filename, GameObject* pOwner)
	: BaseComponent(pOwner)
{
	SetTexture(filename);
}

dae::SpriteComponent::SpriteComponent(std::shared_ptr<Texture2D> texture, GameObject* pOwner)
	: BaseComponent(pOwner)
{
	SetTexture(texture);
}

void dae::SpriteComponent::Update()
{
	m_position = GetOwner()->GetPosition();

	if (m_isAnimatingOnce)
	{
		m_currentTime += Timer::GetInstance().GetDeltaTime();

		if (m_currentTime >= m_animationTime)
		{
			++m_currentIndex;
			if (m_currentIndex >= m_endIndex)
			{
				if (m_isAnimatingOnce)
				{
					m_isAnimatingOnce = false;
					m_endIndex = m_endIndexOnce;
					m_animationTime = m_animationTimeOnce;
				}
				m_currentIndex = m_startIndex;
			}

			m_rect.x = (m_currentIndex % m_columns) * m_rect.w;
			m_rect.y = (m_currentIndex / m_columns) * m_rect.h;

			m_currentTime = 0.f;
		}
	}
}

void dae::SpriteComponent::Render() const
{
	if (m_texture)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, m_position.x + m_offset.x, m_position.y + m_offset.y, m_width, m_height, &m_rect);
	}
}

void dae::SpriteComponent::Animate(int rows, int columns, int frames, int startIndex, int endIndex)
{
	if (m_isAnimatingOnce)
	{
		m_isAnimatingOnce = false;
	}

	m_rows = rows;
	m_columns = columns;
	m_currentIndex = startIndex;
	m_startIndex = startIndex;
	m_endIndex = endIndex;
	m_animationTime = rows * columns / float(frames);
	m_currentTime = 0.f;

	m_rect.w = int(m_texture->GetSize().x) / m_columns;
	m_rect.h = int(m_texture->GetSize().y) / m_rows;
	m_rect.x = (m_currentIndex % m_columns) * m_rect.w;
	m_rect.y = (m_currentIndex / m_columns) * m_rect.h;

	m_width = float(m_rect.w);
	m_height = float(m_rect.h);
}

void dae::SpriteComponent::AnimateOnce(int rows, int columns, int frames, int startIndex, int endIndex)
{
	if (m_isAnimatingOnce)
	{
		m_endIndex = m_endIndexOnce;
		m_startIndex = m_startIndexOnce;
	}

	m_isAnimatingOnce = true;
	m_currentTime = 0.f;
	m_rows = rows;
	m_columns = columns;
	m_animationTimeOnce = m_animationTime;
	m_endIndexOnce = endIndex;
	m_currentIndex = startIndex;
	m_endIndex = endIndex;
	m_animationTime = m_rows * m_columns / float(frames);

	m_rect.x = (m_currentIndex % m_columns) * m_rect.w;
	m_rect.y = (m_currentIndex / m_columns) * m_rect.h;
}