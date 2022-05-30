#include "renderer/rasterizer/rasterizer.h"
#include "renderer/renderer.h"
#include "resource.h"


namespace cg::renderer
{
	class rasterization_renderer : public renderer
	{
	public:
		virtual void init();
		virtual void destroy();

		virtual void update();
		virtual void render();

        virtual void set_model_scale(float x_scale = 1.f, float y_scale = 1.f, float z_scale = 1.f);
        virtual void set_model_rotation(float x_angle = 0.f, float y_scale = 1.f, float z_scale = 1.f);

	protected:
		std::shared_ptr<cg::resource<cg::unsigned_color>> render_target;
		std::shared_ptr<cg::resource<float>> depth_buffer;

		std::shared_ptr<cg::renderer::rasterizer<cg::vertex, cg::unsigned_color>> rasterizer;
	};
}// namespace cg::renderer