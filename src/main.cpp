#include "renderer/renderer.h"
#include "settings.h"

#include <iostream>

int main(int argc, char** argv)
{
	try
	{
		auto settings = cg::settings::parse_settings(argc, argv);
		auto renderer = cg::renderer::make_renderer(settings);

		renderer->init();

		renderer->render();

        renderer->set_model_scale(0.5, 0.5, 0.5);

//        renderer->render();

        renderer->set_model_rotation(45.f, 0.f, 0.f);

        renderer->render();

		renderer->destroy();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}