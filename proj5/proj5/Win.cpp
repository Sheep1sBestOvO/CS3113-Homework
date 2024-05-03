#include "Win.h"
#include "Utility.h"


#define LEVELwin_WIDTH 20
#define LEVELwin_HEIGHT 8


const char  SPRITESHEET_FILEPATH[]  = "assets/loose sprites.png",
            MAP_TILESET_FILEPATH[]  = "assets/oak_woods_tileset.png",
            BGM_FILEPATH[]          = "assets/Ancient Mystery Waltz Presto.mp3",
            ENEMY_FILEPATH[]        = "assets/jump.png",
            TEXT_FILEPATH[]         = "assets/font1.png";

unsigned int LEVEL_Win_DATA[] =
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

void Win::initialise()
{
    GLuint map_texture_id =  Utility::load_texture(MAP_TILESET_FILEPATH);
    m_state.map = new Map(LEVELwin_WIDTH, LEVELwin_HEIGHT, LEVEL_Win_DATA, map_texture_id, 1.0f, 25, 24);

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


void Win::update(float delta_time, int player_lives)
{
    
        
    
}


void Win::render(ShaderProgram *program)
{
    m_state.map->render(program);
    GLuint text_texture_id = Utility::load_texture(TEXT_FILEPATH);
    
    Utility::draw_text(program, text_texture_id, "You win!", 0.5f, -0.1f, glm::vec3(3.8f,-2.0f, 0.0f));
   
}
