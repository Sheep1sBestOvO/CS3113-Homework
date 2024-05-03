#include "Scene.h"

class Menu : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    
    // ————— CONSTRUCTOR ————— //
    ~Menu();
    
    // ————— METHODS ————— //
    void initialise(int thing) override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
