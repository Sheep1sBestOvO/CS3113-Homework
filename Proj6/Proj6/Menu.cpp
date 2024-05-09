#include "Menu.h"
#include "Utility.h"


#define LEVEL0_WIDTH 20
#define LEVEL0_HEIGHT 8




unsigned int LEVEL_0_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

Menu::~Menu()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;

    Mix_FreeMusic(m_state.bgm);
}

void Menu::initialise(int thing)
{
    
    
    GLuint map_texture_id = Utility::load_texture("assets/tilesset.png");
    m_state.map = new Map(LEVEL0_WIDTH, LEVEL0_HEIGHT, LEVEL_0_DATA, map_texture_id, 1.0f, 25, 24);
    
    
    
    m_state.next_scene_id = -1;
    
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(12.0f, -11.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.0f);
    
    m_state.player->m_texture_id = Utility::load_texture("assets/player1.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[3] {6, 13, 20};
    m_state.player->m_walking[m_state.player->RIGHT] = new int[3] {2, 9, 16};
    m_state.player->m_walking[m_state.player->UP]    = new int[3] {0, 7, 14};
    m_state.player->m_walking[m_state.player->DOWN]  = new int[3] {4, 11, 18};
    
    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 3;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 7;
    m_state.player->m_animation_rows   = 3;
    m_state.player->set_height(0.7f);
    m_state.player->set_width(0.7f);
    
    /**
     Enemies' stuff */
    
    GLuint coin_texture = Utility::load_texture("assets/GoldCoinSpinning.png");
    
    m_state.enemies = new Entity[10];
    for(int i = 0; i < 10; i++){
        m_state.enemies[i].m_texture_id = coin_texture;
        m_state.enemies[i].set_ai_type(GOLD);
        m_state.enemies[i].set_position(glm::vec3(i+8, -2, 0.0f));
        m_state.enemies[i].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i].m_animation_indices = m_state.enemies[i].m_walking[Entity::LEFT];
        
        m_state.enemies[i].m_animation_frames = 24;
        m_state.enemies[i].m_animation_index  = 0;
        m_state.enemies[i].m_animation_time   = 0.0f;
        m_state.enemies[i].m_animation_cols   = 24;
        m_state.enemies[i].m_animation_rows   = 1;
        
    }
    
}


void Menu::update(float delta_time)
{

  
    if (delta_time == -1) {
           m_state.next_scene_id = 1;
       }
          
    
}


void Menu::render(ShaderProgram *program)
{
    
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    for (int i = 0; i < 10; i++){
        m_state.enemies[i].render(program);
    }
    Utility::draw_text(program, text_texture_id, "GOLD COLLECTOR",  1.0f, -0.1f,glm::vec3(6.0f, -10.0f, 0.0f));
    
    Utility::draw_text(program, text_texture_id, "PRESS ENTER TO START",  1.0f, -0.1f,glm::vec3(4.0f, -12.0f, 0.0f));
   
}

