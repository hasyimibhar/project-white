//
//  Application.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/11/12.
//
//

#include "Application.h"
#include "Elves.h"
#include <allegro5/allegro.h>
#include <stdexcept>

const std::string   Application::DefaultWindowTitle     = "project-white";
const int           Application::DefaultWindowWidth     = 640;
const int           Application::DefaultWindowHeight    = 480;

Application::Application(int                argc,
                         char               **argv,
                         const std::string  &configFilename) {
    
    al_init();
    
    std::string windowTitle;
    int windowWidth, windowHeight;
    
    // Use default values by default (duh)
    windowTitle     = DefaultWindowTitle;
    windowWidth     = DefaultWindowWidth;
    windowHeight    = DefaultWindowHeight;
    
    if (!configFilename.empty()) {
        
        ALLEGRO_CONFIG *configFile = al_load_config_file(configFilename.c_str());
        
        if (configFile == NULL) {
            throw std::runtime_error("Config file is missing!");
        } else {
        
            if (al_get_config_value(configFile, "window", "title")) {
                windowTitle = std::string(al_get_config_value(configFile, "window", "title"));
            } else {
            }
            
            if (al_get_config_value(configFile, "window", "width") &&
                al_get_config_value(configFile, "window", "height")) {
                windowWidth = from_string<int>(std::string(al_get_config_value(configFile, "window", "width")));
                windowHeight = from_string<int>(std::string(al_get_config_value(configFile, "window", "height")));
            }
            
            al_destroy_config(configFile);
            
        }
    }
    
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_new_display_option(ALLEGRO_SWAP_METHOD, 2, ALLEGRO_REQUIRE);
    display = al_create_display(windowWidth, windowHeight);
    
    if (display == NULL) {
        throw std::runtime_error("Unable to initialize display!");
    } else {
        al_set_window_title(display, windowTitle.c_str());
    }
    
    if (!al_install_mouse() || !al_install_keyboard()) {
        throw std::runtime_error("Unable to initialize mouse and keyboard!");
    }
    
    eventQueue = al_create_event_queue();
    
    if (eventQueue == NULL) {
        throw std::runtime_error("Unable to initialize event queue!");
    } else {
        al_register_event_source(eventQueue, al_get_display_event_source(display));
        al_register_event_source(eventQueue, al_get_keyboard_event_source());
        al_register_event_source(eventQueue, al_get_mouse_event_source());
    }
}

Application::~Application() {
    
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    al_uninstall_system();
    
}

int Application::run() {
    
    bool shouldExit = false;
    
    while (!shouldExit) {
        
        //////////////////////////////////////////////////
        // Process all events
        ALLEGRO_EVENT event;

        while (al_get_next_event(eventQueue, &event)) {
            
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    shouldExit = true;
                    break;
                    
                case ALLEGRO_EVENT_KEY_DOWN:
                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                        shouldExit = true;
                    }
                    
                default:
                    break;
            }
            
        }
        
    }
    
    return 0;
}
