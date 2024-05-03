#include "Scene.h"

class LevelA : public Scene {
public:
    int ENEMY_COUNT = 4;
    
    ~LevelA();
    
    int cur = 0;
    int dot_count;
    void initialise(int lives) override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    
};
