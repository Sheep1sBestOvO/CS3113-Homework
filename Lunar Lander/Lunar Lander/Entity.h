class Entity
{
private:
    int * m_animation_right = NULL,
        * m_animation_left  = NULL,
        * m_animation_up    = NULL,
        * m_animation_down  = NULL;

    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;

    float     m_speed;
    glm::vec3 m_movement;
    glm::mat4 m_model_matrix;
    glm::vec3 init_scale = glm::vec3(1.0f,1.0f,0.0f);
    
    bool m_is_win;
    bool m_is_lose;

    int m_width  = 1,
        m_height = 1;
public:
    static const int SECONDS_PER_FRAME = 4;
    static const int LEFT  = 0,
                     RIGHT = 1,
                     UP    = 2,
                     DOWN  = 3;

    int** m_walking = new int* [4]
        {
            m_animation_left,
            m_animation_right,
            m_animation_up,
            m_animation_down
        };

    int m_animation_frames = 0,
        m_animation_index  = 0,
        m_animation_cols   = 0,
        m_animation_rows   = 0;

    int* m_animation_indices = NULL;
    float m_animation_time = 0.0f;

    GLuint    m_texture_id;

    // ————— METHODS ————— //
    Entity();
    ~Entity();

    void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);
    bool const check_collision(Entity* other) const;

    void update(float delta_time, Entity* collidable_entities, int collidable_entity_count);
    void render(ShaderProgram* program);
    
    void move_left()  {m_acceleration.x += -0.8f;};
    void move_right() {m_acceleration.x += 0.8f;};


    // ————— GETTERS ————— //
    glm::vec3 const get_position()     const { return m_position; };
    glm::vec3 const get_velocity()     const { return m_velocity; };
    glm::vec3 const get_acceleration() const { return m_acceleration; };
    glm::vec3 const get_movement()     const { return m_movement; };
    float     const get_speed()        const { return m_speed; };
    bool      const get_win_state()    const { return m_is_win;}
    bool      const get_lose_state()   const { return m_is_lose;}

    // ————— SETTERS ————— //
    void const set_position(glm::vec3 new_position) { m_position = new_position; };
    void const set_velocity(glm::vec3 new_velocity) { m_velocity = new_velocity; };
    void const set_acceleration(glm::vec3 new_position) { m_acceleration = new_position; };
    void const set_movement(glm::vec3 new_movement) { m_movement = new_movement; };
    void const set_speed(float new_speed) { m_speed = new_speed; };
    void const set_scale(glm::vec3 scale){(init_scale = scale);};
    
    
    void const not_moving() {
        if (m_acceleration.x < 0.0f){
            m_acceleration.x += 0.5f;
        }else if (m_acceleration.x > 0.0f){
            m_acceleration.x -= 0.5f;
        }
    }
    
};
