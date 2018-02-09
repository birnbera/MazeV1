#ifndef event_hpp
#define event_hpp

#include <iostream>
#include <SDL2/SDL.h>

class Event {
public:
    Event();
    virtual ~Event();
    virtual void get_event(const SDL_Event &e);
    virtual void on_key_down(SDL_Keycode sym);
    virtual void on_key_up(SDL_Keycode sym);
    virtual void on_quit();
    virtual void on_mouse_move(int x, int y, int xrel, int yrel);
};

#endif /* event_hpp */
