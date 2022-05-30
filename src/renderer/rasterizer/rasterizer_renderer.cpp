#define _USE_MATH_DEFINES

#include "rasterizer_renderer.h"

#include "utils/resource_utils.h"


void cg::renderer::rasterization_renderer::init()
{
	render_target = std::make_shared<cg::resource<cg::unsigned_color>>(settings->width, settings->height);

	rasterizer = std::make_shared<cg::renderer::rasterizer<cg::vertex, cg::unsigned_color>>();

	rasterizer->set_viewport(settings->width, settings->height);

	model = std::make_shared<cg::world::model>();
	model->load_obj(settings->model_path);
    model->set_scale();
    model->set_rotation();

	camera = std::make_shared<cg::world::camera>();
	camera->set_height(static_cast<float>(settings->height));
	camera->set_width(static_cast<float>(settings->width));
	camera->set_position(float3 {
			settings->camera_position[0],
			settings->camera_position[1],
			settings->camera_position[2]
	});
	camera->set_phi(settings->camera_phi);
	camera->set_theta(settings->camera_theta);
	camera->set_angle_of_view(settings->camera_angle_of_view);
	camera->set_z_near(settings->camera_z_near);
	camera->set_z_far(settings->camera_z_far);

    light = std::make_shared<cg::world::light>();

	depth_buffer = std::make_shared<cg::resource<float>>(settings->width, settings->height);
	rasterizer->set_render_target(render_target, depth_buffer);
	
}
void cg::renderer::rasterization_renderer::render()
{
	rasterizer->clear_render_target({254, 180, 180});

	float4x4 matrix = linalg::mul(
			camera->get_projection_matrix(),
			camera->get_view_matrix(),
            model->get_transform_matrix(),
			model->get_world_matrix()
	);

	rasterizer->vertex_shader = [&](float4 vertex, cg::vertex vertex_data) {
		auto processed = linalg::mul(matrix, vertex);
		return std::make_pair(processed, vertex_data);
	};

	rasterizer->pixel_shader = [&](cg::vertex vertex_data, float z) {

        float3 point_dir = float3 {
            -light->get_position().x,
            -light->get_position().y,
            -light->get_position().z
        };
        float3 vertex_normal = float3 {vertex_data.nx, vertex_data.ny, vertex_data.nz};
        float normal_len = linalg::length(vertex_normal);
        float dir_len = linalg::length(point_dir);
        float angle_diff = linalg::dot(-point_dir, vertex_normal) / (normal_len * dir_len);

		return cg::color {
			vertex_data.ambient_r * angle_diff,
			vertex_data.ambient_g * angle_diff,
			vertex_data.ambient_b * angle_diff
		};
	};

	for (size_t shape_id = 0; shape_id < model->get_index_buffers().size(); ++shape_id) {
		rasterizer->set_vertex_buffer(model->get_vertex_buffers()[shape_id]);
		rasterizer->set_index_buffer(model->get_index_buffers()[shape_id]);
		rasterizer->draw(model->get_index_buffers()[shape_id]->get_number_of_elements(), 0);
	}

	cg::utils::save_resource(*render_target, settings->result_path);

}

void cg::renderer::rasterization_renderer::set_model_scale(float3 scale) {
    model->set_scale(scale);
}

void cg::renderer::rasterization_renderer::set_model_rotation(float3 angle) {
    model->set_rotation(angle);
}

void cg::renderer::rasterization_renderer::set_light_position(float3 in_position) {
    light->set_position(in_position);
}

void cg::renderer::rasterization_renderer::set_light_direction(float theta, float phi) {
    light->set_theta(theta);
    light->set_phi(phi);
}

void cg::renderer::rasterization_renderer::destroy() {}

void cg::renderer::rasterization_renderer::update() {}