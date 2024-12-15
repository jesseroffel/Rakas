#pragma once
#include "event.hpp"

#include <glm/glm.hpp>
#include <sstream>

namespace Sampo
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const glm::vec2& aPosition) : m_MousePosition(aPosition) {}

		const glm::vec2& GetMousePosition() const { return m_MousePosition; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoved Event: " << m_MousePosition.x << ", " << m_MousePosition.y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventMouse | EventInput)
	private:
		glm::vec2 m_MousePosition;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float aXOffset, float aYOffset) : m_OffsetX(aXOffset), m_OffsetY(aYOffset) {}

		float GetXOffset() const { return m_OffsetX; }
		float GetYOffset() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolled Event: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventMouse | EventInput)
	private:
		float m_OffsetX, m_OffsetY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventMouse | EventInput)
	protected:
		MouseButtonEvent(int aButton) : m_Button(aButton) {}
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int aButton) : MouseButtonEvent(aButton) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed Event: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int aButton) : MouseButtonEvent(aButton) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased Event: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}