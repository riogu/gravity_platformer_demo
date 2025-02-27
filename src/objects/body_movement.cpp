// clang-format off
#include "fumo_engine/event_manager.hpp"
#include "fumo_engine/global_state.hpp"
#include "objects/components.hpp"
#include "raylib.h"
#include "systems.hpp"
#include "raymath.h"
#include <cerrno>
// clang-format on

extern std::unique_ptr<GlobalState> global;

const static float movement_scaling = 15000.0f;
const static float jump_scaling = 25000.0f;

void BodyMovement::move_towards(Body& body, Body& target) {
    Vector2 direction = Vector2Normalize(target.position - body.position);
    float sqr_distance = Vector2DistanceSqr(target.position, body.position);
    body.velocity = direction * sqr_distance * global->frametime;
}

void BodyMovement::move_towards_position(Body& body, Vector2 position) {
    Vector2 direction = Vector2Normalize(position - body.position);
    float sqr_distance = Vector2DistanceSqr(position, body.position);
    body.velocity = direction * sqr_distance * global->frametime;
}
void BodyMovement::update_position(Body& body) {
    body.position += body.velocity * global->frametime;
}

void BodyMovement::reset_velocity(Body& body) { body.velocity = {0.0f, 0.0f}; }

// NOTE: moves the body in a fixed way, regardless of
// the velocity it had before this update
// if you want it to interact with the world, use the non fixed method
void BodyMovement::move_vertically(Body& body, float amount) {
    body.velocity -=
        body.gravity_direction * amount * movement_scaling * global->frametime;
}
void BodyMovement::move_horizontally(Body& body, float amount) {
    Vector2 x_direction = {body.gravity_direction.y, -body.gravity_direction.x};
    body.velocity += x_direction * amount * movement_scaling * global->frametime;
}
void BodyMovement::jump(Body& body) {

    // TODO:
    // Bonus Air Time
    // Peak control
    // Fast Falling
    // Lerp the jump movement

    // body.velocity = Vector2Negate(body.gravity_direction * 2000.0f);

    body.velocity +=
        Vector2Negate(body.gravity_direction) * jump_scaling * global->frametime;
    body.jumping = true;
    body.going_up = true;

    // NOTE: finally need the system awake thing naisu
}
// void JumpBufferHandler::update_jump_buffer() {
//     // now we want to slowly remove the velocity every frame
//     Vector2 y_velocity =
//         entity_body.gravity_direction *
//         Vector2DotProduct(entity_body.velocity, entity_body.gravity_direction);
//     if (Vector2Equals(y_velocity, Vector2Zero())) {
//         entity_body.jumping = false;
//     }
//
//     entity_body.velocity += entity_body.gravity_direction;
// }
// // unused atm
// void BodyMovement::move_vertically_fixed(Body& body, float amount) {
//     Vector2 new_vel = body.gravity_direction * amount * movement_scaling;
//     body.position -= new_vel * global->frametime;
// }
//
// void BodyMovement::move_horizontally_fixed(Body& body, float amount) {
//     Vector2 x_direction = {body.gravity_direction.y, -body.gravity_direction.x};
//     Vector2 new_vel = x_direction * amount * movement_scaling;
//     body.position += new_vel * global->frametime;
// }
