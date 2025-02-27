#include "fumo_engine/global_state.hpp"
#include "fumo_engine/sprite_manager/sprite_and_animation_systems.hpp"
#include "objects/components.hpp"
#include "objects/player_systems/player_general_systems.hpp"
#include "objects/systems.hpp"
#include "raylib.h"

extern std::unique_ptr<GlobalState> global;

void PlayerInputHandler::handle_input() {
    const auto body_movement_ptr = global->ECS->get_system<BodyMovement>();
    const auto& player_id = global->player_id;
    auto& player_body = global->ECS->get_component<Body>(player_id);
    auto& player_animation = global->ECS->get_component<AnimationInfo>(player_id);

    const auto& animation_player = global->ECS->get_system<AnimationPlayer>();

    bool idle = true;

    if (IsKeyDown(KEY_SPACE)) {
        if (player_body.touching_ground) {
            // animation_player->play(player_animation, "jump");
            // animation_player->queue(player_animation, "land");
            body_movement_ptr->jump(player_body);
            idle = false;
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        body_movement_ptr->move_vertically(player_body, -1.0f);
        idle = false;
    }
    if (IsKeyDown(KEY_UP)) {
        body_movement_ptr->move_vertically(player_body, 1.0f);
        idle = false;
    }
    if (IsKeyDown(KEY_LEFT)) {
        animation_player->play(player_animation, "sprint");
        body_movement_ptr->move_horizontally(player_body, -1.0f);
        idle = false;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        animation_player->play(player_animation, "sprint");
        body_movement_ptr->move_horizontally(player_body, 1.0f);
        idle = false;
    }

    if (idle) {
        animation_player->play(player_animation, "idle");
    }
    body_movement_ptr->update_position(player_body);
}
