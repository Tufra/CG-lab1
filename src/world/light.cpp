#include "light.h"


cg::world::light::light() : theta(0.f), phi(0.f), position(float3 {0.f, 0.f, 0.f}) {}

cg::world::light::~light() {}

void cg::world::light::set_position(float3 in_position)
{
    position = in_position;
}

void cg::world::light::set_theta(float in_theta)
{
    theta = in_theta * static_cast<float>(M_PI) / 180.f;
}

void cg::world::light::set_phi(float in_phi)
{
    phi = in_phi * static_cast<float>(M_PI) / 180.f;
}

const float3 cg::world::light::get_position() const
{
    return position;
}

const float3 cg::world::light::get_direction() const
{
    return float3 {
            sin(theta) * cos(phi),
            sin(phi),
            -cos(theta) * cos(phi)
    };

}

const float cg::world::light::get_theta() const
{
    return theta;
}
const float cg::world::light::get_phi() const
{
    return phi;
}