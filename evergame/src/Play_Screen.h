#ifndef PLAY_SCREEN
#define PLAY_SCREEN

#include <SFML/Graphics.hpp>
#include <vector>

#include "Cinematic_Manager.h"
#include "Collision_Engine.h"
#include "Platform_Map.h"
#include "Text.h"
#include "Character.h"
#include "Generic_Map.h"
#include "Screen.h"
#include "Renderer.h"
#include "Trigger.h"

class Play_Screen : public Screen
{
private:
    bool player_dying;
    bool player_dead;
    bool player_won;
    bool trigger_on;
    Trigger active_trigger;
    std::vector<Trigger> triggers;
    std::string next_screen_s;
    std::string name_tag;
private:
    Drawable_Static interaction_board;
    Animation_Manager explosion_animation_manager;
    Platform_Map platform_map;
    Generic_Map background_map;
    Character player;
    Cinematic_Manager cinematic_manager;
private:
    void handle_drawing(Renderer &renderer);
    void handle_input();
    void handle_triggers();
    void handle_action(const std::string &action);
    void handle_active_tiles();
    void reset(const Screen_Configuration &config);
public:
    Play_Screen(const Screen_Configuration &config);
public:
    void handle_frame(Renderer &renderer) override;
    std::string next_screen() override;
};
#endif 
