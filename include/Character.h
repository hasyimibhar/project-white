//
//  Character.h
//  project-white
//
//  Created by Hasyimi Bahrudin on 12/16/12.
//
//

#ifndef project_white_Character_h
#define project_white_Character_h

#include "Entity.h"

namespace AllegroFighters {
    class Character;
    typedef std::shared_ptr<Character> CharacterPtr;
    
    enum Direction {
        Left = -1,
        Right = 1
    };
    
    class Character : public BaseEntity {
    private:
        Vector2 velocity;
        bool isJumping;
        
    public:
        static const float JumpSpeed;
        static const float MoveSpeed;
        
        Character();
        ~Character();
        
        void update(float dt);
        void draw(ALLEGRO_DISPLAY *display, CameraPtr camera);
        
        void jump();
        void move(Direction direction);
        void stop();
    };
}

#endif
