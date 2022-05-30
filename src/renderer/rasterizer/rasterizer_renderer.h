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

        virtual void set_model_scale(float3 scale);
        virtual void set_model_rotation(float3 angle);

        virtual void set_light_position(float3 in_position);
        virtual void set_light_direction(float theta, float phi);

	protected:
		std::shared_ptr<cg::resource<cg::unsigned_color>> render_target;
		std::shared_ptr<cg::resource<float>> depth_buffer;

		std::shared_ptr<cg::renderer::rasterizer<cg::vertex, cg::unsigned_color>> rasterizer;
	};
}// namespace cg::renderer