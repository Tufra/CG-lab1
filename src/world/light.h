#define _USE_MATH_DEFINES

#include "linalg.h"

using namespace linalg::aliases;

namespace cg::world {
    class light {
    public:
        light();
        ~light();

        void set_position(float3 in_position);
        void set_theta(float in_theta);
        void set_phi(float in_phi);

        const float3 get_position() const;
        const float3 get_direction() const;
        const float get_theta() const;
        const float get_phi() const;

    protected:
        float3 position;
        float theta;
        float phi;

    };
}
