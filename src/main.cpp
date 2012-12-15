#include <allegro5/allegro.h>
#include "Application.h"

int main(int argc, char **argv) {
    
    ApplicationPtr app = Application::GetInstance();
    app->init(argc, argv, "data/config.ini");
    app->run();
    
    return 0;
    
}