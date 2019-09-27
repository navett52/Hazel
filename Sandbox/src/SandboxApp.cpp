#include <Hazel.h>

#define BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() : Layer("Exmple") {}

	void OnUpdate() override
	{
		// Muting this for now as it saturates the console...
		// HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override
	{
		// So OnEvent is basically the generic event callback, which will probably
		// normally hold en event dispatcher to appropriately disptach events to that
		// layer's event handlers.
		Hazel::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Hazel::MouseButtonPressedEvent>(BIND_EVENT_FN(OnMousePressed));

		// HZ_TRACE("{0}", event); // <- used this just to prove our layer was getting acknowledged.
	}
private:
	bool OnMousePressed(Hazel::MouseButtonPressedEvent& e);
};

bool ExampleLayer::OnMousePressed(Hazel::MouseButtonPressedEvent& e)
{
	HZ_TRACE("Mouse pressed!");
	return true;
}

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}