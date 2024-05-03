#include "Scene.h"

class Win : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    
    // ————— CONSTRUCTOR ————— //
    ~Win();
    
    // ————— METHODS ————— //
    void initialise(int lives) override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};

