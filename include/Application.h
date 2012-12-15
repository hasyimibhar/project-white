//
//  Application.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/11/12.
//
//

#ifndef project_white_Application_h
#define project_white_Application_h

#include <string>
#include <memory>

struct ALLEGRO_DISPLAY;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;

class IGameStateManager;
typedef std::shared_ptr<IGameStateManager> GameStateManagerPtr;

class InputHandler;
typedef std::shared_ptr<InputHandler> InputHandlerPtr;

class Application;
typedef std::shared_ptr<Application> ApplicationPtr;

class Application {
    
private:
    ALLEGRO_DISPLAY         *display;
    ALLEGRO_EVENT_QUEUE     *eventQueue;
    ALLEGRO_TIMER           *timer;
    GameStateManagerPtr     gameStateManager;
    InputHandlerPtr         inputHandler;

public:
    static const std::string DefaultWindowTitle;
    static const int DefaultWindowWidth;
    static const int DefaultWindowHeight;
    static const float FPS;
    
    Application(int argc, char **argv, const std::string &configFilename = "");
    ~Application();
    
    int run();
};

#endif
