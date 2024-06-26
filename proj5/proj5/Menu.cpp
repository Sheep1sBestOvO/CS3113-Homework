#include "Menu.h"
#include "Utility.h"


#define LEVEL0_WIDTH 20
#define LEVEL0_HEIGHT 8




unsigned int LEVEL_0_DATA[] =
{
    1,  2,  2, 2,   2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1,  3,  3, 4,   4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

Menu::~Menu()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;

    Mix_FreeMusic(m_state.bgm);
}

void Menu::initialise()
{
    GLuint map_texture_id =  Utility::load_texture(MAP_TILESET_FILEPATH);
    m_state.map = new Map(LEVEL0_WIDTH, LEVEL0_HEIGHT, LEVEL_0_DATA, map_texture_id, 1.0f, 5, 3);

    m_state.player = new Entity();
       m_state.player->set_entity_type(PLAYER);
       m_state.player->set_position(glm::vec3(5.0f, 0.0f, 0.0f));
       m_state.player->m_origin_position = glm::vec3(5.0f, 0.0f, 0.0f);
       m_state.player->set_movement(glm::vec3(0.0f));
       m_state.player->set_speed(2.5f);
       m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
       m_state.player->m_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);
       
       // Walking
       m_state.player->m_walking[m_state.player->LEFT]  = new int[4] { 8, 9, 10, 11 };
       m_state.player->m_walking[m_state.player->RIGHT] = new int[4] { 28, 29, 30, 31 };
       

       m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
       m_state.player->m_animation_frames = 4;
       m_state.player->m_animation_index  = 0;
       m_state.player->m_animation_time   = 0.0f;
       m_state.player->m_animation_cols   = 4;
       m_state.player->m_animation_rows   = 4;
       m_state.player->set_height(0.8f);
       m_state.player->set_width(0.8f);
       
       // Jumping
       m_state.player->m_jumping_power = 5.0f;
       
       /**
        Enemies' stuff */
       GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);
       
       m_state.enemies = new Entity[ENEMY_COUNT];
       m_state.enemies[0].set_entity_type(ENEMY);
       m_state.enemies[0].set_ai_type(GUARD);
       m_state.enemies[0].set_ai_state(IDLE);
       m_state.enemies[0].m_texture_id = enemy_texture_id;
       m_state.enemies[0].set_position(glm::vec3(8.0f, 0.0f, 0.0f));
       m_state.enemies[0].set_movement(glm::vec3(0.0f));
       m_state.enemies[0].set_speed(1.0f);
       m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
       
       

    
    

    }


void Menu::update(float delta_time, int player_lives)
{
    
    if (delta_time == -1) {
        m_state.next_scene_id = 1;
    }
        
    
}


void Menu::render(ShaderProgram *program)
{
    m_state.map->render(program);
    GLuint text_texture_id = Utility::load_texture(TEXT_FILEPATH);
    
    Utility::draw_text(program, text_texture_id, "PRESS ENTER TO START", 0.5f, -0.1f, glm::vec3(2.0f,-2.0f, 0.0f));
   
}
