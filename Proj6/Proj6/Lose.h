
#include "Scene.h"

class Lose : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    
    // ————— CONSTRUCTOR ————— //
    ~Lose();
    int ENEMY_COUNT = 4;
    // ————— METHODS ————— //
    void initialise(int lives) override;
    void update(float delta_time) ;
    void render(ShaderProgram *program) override;
};

