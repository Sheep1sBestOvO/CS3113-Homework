/**
* Author: [Yang Zou]
* Assignment: Pong Clone
* Date due: 2024-03-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/


#define GL_GLEXT_PROTOTYPES 1
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#define LOG(argument) std::cout << argument << '\n'

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "stb_image.h"

#include <ctime>
#include "cmath"


const int WINDOW_WIDTH  = 640,
          WINDOW_HEIGHT = 480;

const float BG_RED = 0.9608f,
            BG_BLUE = 0.9608f,
            BG_GREEN = 0.9608f,
            BG_OPACITY = 1.0f;

const int VIEWPORT_X      = 0,
          VIEWPORT_Y      = 0,
          VIEWPORT_WIDTH  = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;


const char  V_SHADER_PATH[]    = "shaders/vertex_textured.glsl",
            F_SHADER_PATH[]    = "shaders/fragment_textured.glsl",
            BALL_FILE_PATH[]   = "assets/soph.png",
            PADDLE_FILE_PATH[] = "assets/paddle.jpg",
            PLAYER_1_WIN_FILE_PATH[]   = "assets/winner-1.png",
            PLAYER_2_WIN_FILE_PATH[]   = "assets/winner-2.png";

const float MILLISECONDS_IN_SECOND     = 1000.0;
const float MINIMUM_COLLISION_DISTANCE = 1.0f;


const int   NUMBER_OF_TEXTURES = 1;
const GLint LEVEL_OF_DETAIL    = 0;
const GLint TEXTURE_BORDER     = 0;

const int FONTBANK_SIZE        = 8;


SDL_Window* g_display_window;
bool  g_game_is_running = true;
float g_previous_ticks  = 0.0f;


ShaderProgram g_shader_program;
glm::mat4     g_view_matrix,
              g_projection_matrix,
              g_ball_matrix,
              g_paddle_1_matrix,
              g_paddle_2_matrix,
              g_player_1_win_matrix,
              g_player_2_win_matrix;

float g_paddle_speed = 5.0f;
float g_ball_speed = 2.0f;



bool g_paddle_can_move = true;
bool g_player_1_win = false;
bool g_player_2_win = false;
bool g_player_2_up = true;
              
GLuint g_ball_texture_id,
       g_paddle_texture_id,
       g_player_1_win_texture_id,
       g_player_2_win_texture_id;
       





glm::vec3 g_paddle_1_position = glm::vec3(-4.5f, 0.0f, 0.0f);
glm::vec3 g_paddle_1_movement = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 g_paddle_2_position = glm::vec3(4.5f, 0.0f, 0.0f);
glm::vec3 g_paddle_2_movement = glm::vec3(0.0f, 0.0f, 0.0f);


glm::vec3 g_ball_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 g_ball_movement = glm::vec3(-0.5f, -1.0f, 0.0f);



 
bool check_collision(glm::vec3 &position_a, glm::vec3 &position_b)
{
    
    float x_distance = fabs(position_a.x - position_b.x) - ((2.0f) / 2.0f);
    float y_distance = fabs(position_a.y - position_b.y) - ((2.0f) / 2.0f);
    
    if (x_distance < 0 && y_distance <= 0){
        return true;
    }
    else{
        return false;
    }
}


void ball_direction()
{
    if (g_ball_position.y < -3.25f){

        g_ball_movement.y = 1.0f;
    }else if (g_ball_position.y > 3.25f){
        g_ball_movement.y = -1.0f;
    }
    
    if(g_ball_position.x < -4.5f){
        g_ball_movement = glm::vec3(0.0f);
        g_player_2_win = true;
        return;
    }else if (g_ball_position.x > 4.5f){
        g_ball_movement = glm::vec3(0.0f);
        g_player_1_win = true;
        return;
        
    }
    
    if (check_collision(g_paddle_1_position, g_ball_position)){
        g_ball_movement.x = 1.0f;
    }else if (check_collision(g_paddle_2_position, g_ball_position)){
        g_ball_movement.x = -1.0f;
    }
    
    if (glm::length(g_ball_movement) > 1.0f)
    {
        g_ball_movement = glm::normalize(g_ball_movement);
    }
}




GLuint load_texture(const char* filepath)
{
    int width, height, number_of_components;
    unsigned char* image = stbi_load(filepath, &width, &height, &number_of_components, STBI_rgb_alpha);
    
    if (image == NULL)
    {
        LOG("Unable to load image. Make sure the path is correct.");
        assert(false);
    }
    
    GLuint textureID;
    glGenTextures(NUMBER_OF_TEXTURES, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, LEVEL_OF_DETAIL, GL_RGBA, width, height, TEXTURE_BORDER, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(image);
    
    return textureID;
}



void initialise()
{
    SDL_Init(SDL_INIT_VIDEO);
    g_display_window = SDL_CreateWindow("Pong Clone!",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    
    g_ball_matrix        = glm::mat4(1.0f);
    g_paddle_1_matrix    = glm::mat4(1.0f);
    g_paddle_2_matrix    = glm::mat4(1.0f);
    
    
    g_view_matrix       = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    
    g_ball_texture_id         = load_texture(BALL_FILE_PATH);
    g_paddle_texture_id       = load_texture(PADDLE_FILE_PATH);
    g_player_1_win_texture_id = load_texture(PLAYER_1_WIN_FILE_PATH);
    g_player_2_win_texture_id = load_texture(PLAYER_2_WIN_FILE_PATH);
    
    
    g_player_1_win_matrix = glm::mat4(1.0f);
    g_player_1_win_matrix =  glm::scale(g_player_1_win_matrix, glm::vec3(3.0f));
      
    g_player_2_win_matrix = glm::mat4(1.0f);
    g_player_2_win_matrix =  glm::scale(g_player_2_win_matrix, glm::vec3(3.0f));
    
    
    
    glUseProgram(g_shader_program.get_program_id());
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void process_input()
{
    
    g_paddle_1_movement = glm::vec3(0.0f);
    g_paddle_2_movement = glm::vec3(0.0f);
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_game_is_running = false;
                break;
                                                                             
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                   
                    case SDLK_q:
                        g_game_is_running = false;
                        break;
                    
                    case SDLK_t:
                        g_paddle_can_move = !g_paddle_can_move;
                
                    default:
                        break;
                }
                                                                 
            default:
                break;
        }
    }
                                                                     
  
                                                                             
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    if (!g_player_1_win && !g_player_2_win){
        if (key_state[SDL_SCANCODE_W] && g_paddle_1_position.y < 3.25f)
        {
            g_paddle_1_movement.y = 1.0f;
        }
        else if (key_state[SDL_SCANCODE_S] &&  g_paddle_1_position.y > -3.25f)
        {
            g_paddle_1_movement.y = -1.0f;
        }
        
        if (key_state[SDL_SCANCODE_UP] && g_paddle_can_move && g_paddle_2_position.y < 3.25f )
        {
            g_paddle_2_movement.y = 1.0f;
        }
        else if (key_state[SDL_SCANCODE_DOWN] && g_paddle_can_move && g_paddle_2_position.y > -3.25f)
        {
            g_paddle_2_movement.y = -1.0f;
        }
        
        if(!g_paddle_can_move){
            if (g_paddle_2_position.y > 3.25f){
                g_player_2_up = !g_player_2_up;
            }
            if (g_paddle_2_position.y < -3.25f){
                g_player_2_up = !g_player_2_up;
            }
            if (g_player_2_up )
            {
                g_paddle_2_movement.y = 1.0f;
            }else if ( !g_player_2_up ){
                g_paddle_2_movement.y = -1.0f;
            }
        }
    }
    
//    if (glm::length(g_paddle_1_movement) > 1.0f)
//    {
//        g_paddle_1_movement = glm::normalize(g_paddle_1_movement);
//    }
//    
//    if (glm::length(g_paddle_2_movement) > 1.0f)
//    {
//        g_paddle_2_movement = glm::normalize(g_paddle_2_movement);
//    }
}



void update()
{
    float ticks = (float) SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    g_paddle_1_position += g_paddle_1_movement * g_paddle_speed * delta_time;
                                                                                
    g_paddle_1_matrix = glm::mat4(1.0f);
    g_paddle_1_matrix = glm::translate(g_paddle_1_matrix, g_paddle_1_position);
    
    g_paddle_2_position += g_paddle_2_movement * g_paddle_speed * delta_time;
                                                                                
    g_paddle_2_matrix = glm::mat4(1.0f);
    g_paddle_2_matrix = glm::translate(g_paddle_2_matrix, g_paddle_2_position);
    
    ball_direction();
    g_ball_position += g_ball_movement * g_ball_speed * delta_time;
    g_ball_matrix = glm::mat4(1.0f);
    g_ball_matrix = glm::translate(g_ball_matrix, g_ball_position);
    
    
    
}

void draw_object(glm::mat4 &object_model_matrix, GLuint &object_texture_id)
{
    g_shader_program.set_model_matrix(object_model_matrix);
    glBindTexture(GL_TEXTURE_2D, object_texture_id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
}



void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f
    };

    float texture_coordinates[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    };
    
    glVertexAttribPointer(g_shader_program.get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(g_shader_program.get_position_attribute());
    
    glVertexAttribPointer(g_shader_program.get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texture_coordinates);
    glEnableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());
    
    draw_object(g_paddle_1_matrix, g_paddle_texture_id);
    draw_object(g_paddle_2_matrix, g_paddle_texture_id);
    draw_object(g_ball_matrix, g_ball_texture_id);
    
    if (g_player_1_win){
        draw_object(g_player_1_win_matrix, g_player_1_win_texture_id);
    }else if (g_player_2_win){
        draw_object(g_player_2_win_matrix, g_player_2_win_texture_id);
    }
    
    glDisableVertexAttribArray(g_shader_program.get_position_attribute());
    glDisableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());
    
    SDL_GL_SwapWindow(g_display_window);
}

void shutdown() { SDL_Quit(); }


int main(int argc, char* argv[])
{
    initialise();
    
    while (g_game_is_running)
    {
        process_input();
        update();
        render();
    }
    
    shutdown();
    return 0;
}
