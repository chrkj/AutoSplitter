#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "MenuLayer.h"

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "AutoSplitter";
	spec.Width = 300;
	spec.Height = 400;

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<MenuLayer>();
	return app;
}