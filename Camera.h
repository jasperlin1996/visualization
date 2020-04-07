#include "glm/glm.hpp"

class Camera{
public:
    Camera();
    Camera(float, float);
    void shift_pos(glm::vec4);
    glm::vec3 get_position();
    glm::vec3 get_direction();
    glm::vec3 get_up();
    void update_zoom(float);
    void update_yaw(float);
    void update_pitch(float);
    void update_far(float);
    void update_camera_direction();
    float left, right, top, bottom, near, far;

private:
    glm::vec3 center;
    // glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    float camera_radius;
    float zoom;
    float yaw;
    float pitch;
};