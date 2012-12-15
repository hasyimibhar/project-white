#include <allegro5/allegro.h>
#include "Application.h"

int main(int argc, char **argv) {
    
    Application app (argc, argv, "data/config.ini");
    app.run();
    
    return 0;
    
}