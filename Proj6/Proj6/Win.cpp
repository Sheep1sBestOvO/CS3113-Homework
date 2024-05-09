#include "Win.h"
#include "Utility.h"


#define WIN_WIDTH 20
#define WIN_HEIGHT 8




unsigned int WIN_DATA[] =
{
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

Win::~Win()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;

    Mix_FreeMusic(m_state.bgm);
}

void Win::initialise(int lives)
{
    GLuint map_texture_id = Utility::load_texture("assets/tilesset.png");
    m_state.map = new Map(WIN_WIDTH, WIN_HEIGHT, WIN_DATA, map_texture_id, 1.0f, 25, 24);
    
    m_state.next_scene_id = -1;
    
    
    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(8.0f, -11.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    
    
    // Walking
    
    m_state.player->m_walking[m_state.player->RIGHT] = new int[11] {1, 2,3,4,5,6,7,8,9,10,11};
    m_state.player->m_walking[m_state.player->LEFT] = new int[1]{0};
    
    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 11;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 12;
    m_state.player->m_animation_rows   = 1;
    m_state.player->set_height(0.7f);
    m_state.player->set_width(0.7f);
    
}

void Win::update(float delta_time)
{
    
    
        
    
}


void Win::render(ShaderProgram *program)
{
    
    GLuint text_texture_id = Utility::load_texture("assets/font1.png");
    Utility::draw_text(program, text_texture_id, "YOU WIN ! ", 1.0f, -0.1f,glm::vec3(10.0f, -10.0f, 0.0f));
   
}

