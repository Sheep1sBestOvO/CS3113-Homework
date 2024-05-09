#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 25
#define LEVEL_HEIGHT 19

unsigned int LEVELA_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 6, 2, 2, 2, 2, 2, 2, 2, 2, 7, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0,11, 2, 2, 2, 2, 2, 2, 2, 2,12, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 1, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 3, 0, 5,
    0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5,
    0, 5, 0, 0, 0, 5, 0, 6, 2, 2, 2, 3, 0, 0, 0, 6, 2, 2, 7, 0, 5, 0, 0, 0, 5,
    0, 5, 2, 2, 2,12, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0,11, 2, 2, 2, 5,
    0, 5, 2, 2, 2, 7, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 6, 2, 2, 2, 5,
    0, 5, 0, 0, 0, 5, 0, 5, 0, 1, 2, 7, 0, 0, 0, 5, 0, 0, 5, 0, 5, 0, 0, 0, 5,
    0, 5, 0, 0, 0, 5, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 5, 0, 5, 0, 0, 0, 5,
    0, 5, 0, 1, 2,12, 0,11, 2, 2, 2,12, 0, 0, 0,11, 2, 2,12, 0,11, 2, 3, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,2, 2, 2, 3, 0, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 5, 0, 0, 1, 2, 2, 3,0,0, 0, 1, 2, 2, 3, 0, 0, 0, 1, 2, 2, 3, 0, 0, 5,
    0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    0, 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 12,
};

  


LevelA::~LevelA()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    
    Mix_FreeChunk(m_state.collect_sfx1);
    
    Mix_FreeMusic(m_state.bgm);
}


void LevelA::initialise(int lives)
{

    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/tilesset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1, 5, 3);
    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    
    // Existing
    
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
    GLuint enemy1_texture = Utility::load_texture("assets/BIRD.png");
    GLuint enemy2_texture = Utility::load_texture("assets/whitebird.png");
    GLuint coin_texture = Utility::load_texture("assets/GoldCoinSpinning.png");
   
    if(lives == 3){
        m_state.enemies = new Entity[200];
        
    }
   
   
    ENEMY_COUNT = 4;

    cur = 0;
    dot_count = 0;
    
    /* top part */
    for(int i = 0; i < 10; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+8, -2, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    /*left part*/
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+2, -6, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+2, -7, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+2, -10, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+2, -11, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+8, -11, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    
    
    
    /*right part*/
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+21, -6, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+21, -7, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+21, -10, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 3; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+21, -11, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    
    for(int i = 0; i < 10; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+8, -13, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    /*bottom*/
    for(int i = 0; i < 4; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+4, -17, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 4; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+11, -17, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    for(int i = 0; i < 4; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+18, -17, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    
    for(int i = 0; i < 10; i++){
        m_state.enemies[i+cur].m_texture_id = coin_texture;
        m_state.enemies[i+cur].set_ai_type(GOLD);
        m_state.enemies[i+cur].set_position(glm::vec3(i+8, -15, 0.0f));
        m_state.enemies[i+cur].m_walking[Entity::LEFT]  = new int[24] {0,1,2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        m_state.enemies[i+cur].m_animation_indices = m_state.enemies[i+cur].m_walking[Entity::LEFT];
        
        m_state.enemies[i+cur].m_animation_frames = 24;
        m_state.enemies[i+cur].m_animation_index  = 0;
        m_state.enemies[i+cur].m_animation_time   = 0.0f;
        m_state.enemies[i+cur].m_animation_cols   = 24;
        m_state.enemies[i+cur].m_animation_rows   = 1;
        dot_count++;
    }
    cur += dot_count;
    dot_count = 0;
    
    
    
    ENEMY_COUNT += cur;
    for(int i = 4; i < ENEMY_COUNT; i++){
        
        m_state.enemies[i].set_width(0.6f);
        m_state.enemies[i].set_height(0.6f);
    }
    for(int i = cur; i < ENEMY_COUNT; i++){
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(WALKER);
        m_state.enemies[i].set_ai_state(GO_LEFT);
        
        m_state.enemies[i].set_position(glm::vec3((ENEMY_COUNT-i)+10, -9.0f, 0.0f));
        m_state.enemies[i].set_speed(2.0f);
        
        
        m_state.enemies[i].m_walking[Entity::LEFT]  = new int[4] {8, 9, 10, 11};
        m_state.enemies[i].m_walking[Entity::RIGHT] = new int[4] {4, 5, 6, 7};
        m_state.enemies[i].m_walking[Entity::UP]    = new int[4] {12, 13, 14, 15};
        m_state.enemies[i].m_walking[Entity::DOWN]  = new int[4] {0, 1, 2, 3};
        m_state.enemies[i].m_animation_indices = m_state.enemies[i].m_walking[Entity::LEFT];
        
        m_state.enemies[i].m_animation_frames = 4;
        m_state.enemies[i].m_animation_index  = 0;
        m_state.enemies[i].m_animation_time   = 0.0f;
        m_state.enemies[i].m_animation_cols   = 4;
        m_state.enemies[i].m_animation_rows   = 13;
        m_state.enemies[i].set_width(0.7f);
        m_state.enemies[i].set_height(0.7f);
        
    }
    m_state.enemies[cur].m_texture_id = enemy1_texture;
    m_state.enemies[cur+1].m_texture_id = enemy1_texture;
    m_state.enemies[cur+2].m_texture_id = enemy2_texture;
    m_state.enemies[cur+3].m_texture_id = enemy2_texture;
    m_state.player->dot_count = cur;
    
    for(int i = 0; i < ENEMY_COUNT; i++){
        if(!m_state.enemies[i].is_active()){
            m_state.player->dot_count -=1;
        }
    }
    m_state.lives = new Entity [3];
    GLuint lives_texture = Utility::load_texture("assets/heart.png");
    for(int i = 0; i < 3; i++){
        m_state.lives[i].set_entity_type(LIVES);
        m_state.lives[i].set_width(1.0f);
        m_state.lives[i].set_height(1.0f);
        m_state.lives[i].m_scale = glm::vec3(1.0f, 1.0f,0.0f);
        m_state.lives[i].set_position(glm::vec3(1.0f+i, -19.0f, 0.0f));
        m_state.lives[i].m_texture_id = lives_texture;
    }
    for(int i = lives; i < 3; i++){
        m_state.lives[i].deactivate();
    }

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/lookintovoid.mp3");
    
    Mix_PlayMusic(m_state.bgm, -1);
    
    
    Mix_ResumeMusic();
    m_state.collect_sfx1 = Mix_LoadWAV("assets/coin-sound.mp3");
    
    m_state.death_noise = Mix_LoadWAV("assets/eat_ghost.wav");
    
    
}

void LevelA::update(float delta_time)
{
       
       cur_time += delta_time;
       
       m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
       for (int i = 0; i < ENEMY_COUNT; i++) m_state.enemies[i].update(delta_time, m_state.player, NULL, 0, m_state.map);
       if (m_state.player->dot_count == 0){
           m_state.next_scene_id = 2;
       }
       if(m_state.player->eat){
           
               m_state.player->eat= false;
               Mix_PlayChannel(1, m_state.collect_sfx1, 0);
               Mix_Volume(1, 10);
           }
    

    if(m_state.player->lives < 3){
        m_state.lives[m_state.player->lives].deactivate();
    }
    if(m_state.player->lives == 0) {
        m_state.next_scene_id = 3;
    }
       
       for (int i = 0; i < 3; i++) m_state.lives[i].update(delta_time, m_state.player, NULL, 0, m_state.map);
       

}

void LevelA::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++){
        if(m_state.enemies[i].is_active()){
            m_state.enemies[i].render(program);
        }
            
    }
    
    for (int i = 0; i < 3; i++){
        if(m_state.lives[i].is_active()){
            m_state.lives[i].render(program);
        }
    }
}
