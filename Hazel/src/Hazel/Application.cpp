#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// Just messing around with some stuff
		WindowProps testwindow = WindowProps("Super Awesome Game!", 1920, 1080);

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() { }

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		//dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMousePressed));
		//dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseReleased));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, .5, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnMousePressed(MouseButtonPressedEvent& e)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		return true;
	}

	bool Application::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
		glClearColor(1, .5, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		return true;
	}
}