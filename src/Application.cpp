//
//  Application.cpp
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/11/12.
//
//

#include "Application.h"
#include "Elves.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "InputHandler.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>

const std::string   Application::DefaultWindowTitle     = "project-white";
const int           Application::DefaultWindowWidth     = 640;
const int           Application::DefaultWindowHeight    = 480;
const float         Application::FPS                    = 60.0f;

Application::Application(int                argc,
                         char               **argv,
                         const std::string  &configFilename) {
    
    al_init();
    al_init_primitives_addon();
    
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
    
    timer = al_create_timer(1.0f / FPS);
    if (timer == NULL) {
        throw std::runtime_error("Unable to initialize timer!");
    } else {
        al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    }
    
    inputHandler = std::make_shared<InputHandler>();
    
    gameStateManager = std::make_shared<GameStateManager>();
    gameStateManager->changeState(PlayState::GetInstance());
}

Application::~Application() {
    
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    al_uninstall_system();
    
}

int Application::run() {
    
    bool shouldExit = false;
    al_start_timer(timer);
    
    while (!shouldExit && gameStateManager->getActiveStateCount() > 0) {
        
        //////////////////////////////////////////////////
        // Process all events
        ALLEGRO_EVENT event;

        while (al_get_next_event(eventQueue, &event)) {
            
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    shouldExit = true;
                    break;
                    
                ////////////////////////////////////////
                // Update
                case ALLEGRO_EVENT_TIMER:
                    ALLEGRO_KEYBOARD_STATE keyboardState;
                    al_get_keyboard_state(&keyboardState);
                    inputHandler->updateKeyboardState(&keyboardState);
                    
                    gameStateManager->handleInput(inputHandler);
                    gameStateManager->update(1.0f / FPS);
                    break;
                    
                default:
                    break;
            }
            
        }
        
        ////////////////////////////////////////////////
        // Draw 
        al_clear_to_color(al_map_rgb(255, 255, 255));
        gameStateManager->draw(display);
        al_flip_display();
    }
    
    al_stop_timer(timer);
    
    return 0;
}
