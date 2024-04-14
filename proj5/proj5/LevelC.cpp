#include "LevelC.h"
#include "Utility.h"


#define LEVEL3_WIDTH 20
#define LEVEL3_HEIGHT 8



const char  SPRITESHEET_FILEPATH[]  = "assets/loose sprites.jpg",
            MAP_TILESET_FILEPATH[]  = "assets/oak_woods_tileset.png",
            BGM_FILEPATH[]          = "assets/Ancient Mystery Waltz Presto.mp3",
            ENEMY_FILEPATH[]        = "assets/jump.png",
            DEATH_FILEPATH[]        = "assets/Goblin Death.wav",
            TEXT_FILEPATH[]         = "assets/font1.png";


unsigned int LEVEL_3_DATA[] =
{
    26,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    26,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    26,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    26,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    26,  0,  0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    26,  1,  0, 0,   0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0,
    26, 26, 1, 1,   1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    26, 26, 26, 26, 0, 26, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

LevelC::~LevelC()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelC::initialise()
{
    // ————— MAP SET-UP ————— //
    GLuint map_texture_id =  Utility::load_texture(MAP_TILESET_FILEPATH);
    m_state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, LEVEL_3_DATA, map_texture_id, 1.0f, 25, 24);

    

    
    // ————— GEORGE SET-UP ————— //
    // Existing
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
   m_state.player->m_animation_rows   = 8;
   m_state.player->set_height(0.8f);
   m_state.player->set_width(0.8f);
   
   // Jumping
   m_state.player->m_jumping_power = 7.0f;
   
   /**
    Enemies' stuff */
   GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);
   
   m_state.enemies = new Entity[ENEMY_COUNT];
   m_state.enemies[0].set_entity_type(ENEMY);
   m_state.enemies[0].set_ai_type(GUARD);
   m_state.enemies[0].set_ai_state(IDLE);
   m_state.enemies[0].m_texture_id = enemy_texture_id;
   m_state.enemies[0].set_position(glm::vec3(12.0f, 0.0f, 0.0f));
   m_state.enemies[0].set_movement(glm::vec3(0.0f));
   m_state.enemies[0].set_speed(1.0f);
   m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
   
       

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 16.0f);
    
    m_state.jump_sfx = Mix_LoadWAV(DEATH_FILEPATH);

    }


void LevelC::update(float delta_time,int player_lives)
{
    m_state.player->m_player_lives = player_lives;
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
   
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].update(delta_time, m_state.player, NULL, NULL, m_state.map);
    }
    
}


void LevelC::render(ShaderProgram *program)
{
    m_state.player->render(program);
    
    m_state.map->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++){
            m_state.enemies[i].render(program);
        }
}
