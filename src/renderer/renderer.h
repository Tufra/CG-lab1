#pragma once

#include "settings.h"
#include "world/camera.h"
#include "world/light.h"
#include "world/model.h"


namespace cg::renderer
{
	class renderer
	{
	public:
		void set_settings(std::shared_ptr<cg::settings> in_settings);

		unsigned get_height();
		unsigned get_width();

		virtual void init() = 0;
		virtual void destroy() = 0;

		virtual void update() = 0;
		virtual void render() = 0;

		void move_forward(float delta = 0.01f);
		void move_backward(float delta = 0.01f);
		void move_left(float delta = 0.01f);
		void move_right(float delta = 0.01f);
		void move_yaw(float delta = 0.f);
		void move_pitch(float delta = 0.f);

//        virtual void set_model_scale(float3 scale) = 0;
//        virtual void set_model_rotation(float3 angle) = 0;
//
//        virtual void set_light_position(float3 in_position) = 0;
//        virtual void set_light_direction(float theta, float phi) = 0;

	protected:
		std::shared_ptr<cg::settings> settings;

		std::shared_ptr<cg::world::camera> camera;
		std::shared_ptr<cg::world::model> model;
        std::shared_ptr<cg::world::light> light;

		std::chrono::time_point<std::chrono::high_resolution_clock> current_time =
				std::chrono::high_resolution_clock::now();
		float frame_duration = 1.f;
	};


	extern std::shared_ptr<renderer> make_renderer(std::shared_ptr<cg::settings> settings);
}// namespace cg::renderer