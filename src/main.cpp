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

        renderer->set_light_position(float3 {0.f, 0.f, 0.f});
        renderer->set_light_direction(-160.f, 100.f);

        renderer->set_model_scale(float3 {0.03, 0.03, 0.03});

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