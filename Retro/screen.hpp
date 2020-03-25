#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED
#include <SFML/Graphics.hpp>

//There was a whole button class here, but then i figured that retro games didn't realy have mouse buttons....


class image {//Basically a wrapper around sf::Sprite
    sf::Sprite sp;
    sf::Texture tx;
    double x;
    double y;
public:
    image();
    image(double _x, double _y, const char* name, int res_x, int res_y);
    sf::Sprite get_sp();
};

class text {//Again wrapper around sf::Text
    double x;
    double y;
    sf::Text txt;
    sf::Font font;
public:
    text();
    text(double _x, double _y, const char* txt, float scale_x = 1, float scale_y = 1);
    void set_color(sf::Color c);
    sf::Text get_txt();

};

class screen {//A screen is basically a setting that will be displayed at certain points (must be static screens)
    //Ex: the welcome screen, the game over screen etc...
    //It does not support any kind of graphics
    //Only Text and selectable text
    //Selectable text is basically text that can act as a button(more or less)
    std::vector <image*> im_list;//Image vector
    std::vector <text*> tx_list;//Text vector
    std::vector <text*> s_tx_list;//Selectable text vector
    int select_index = 0;//Indicates what setting is currently selected
    bool active = true;
    int selector = 0;//Used for proper use of key press
    //Acts as lower bound for key press detection
    //10 frames must pass while a key is pressed to detect it as a key press(see mark at screen.cpp)
public:
    void add_image(image* im);//Since every screen has different properties, i can add as many text, images etc... at every screen
    //Also since the coordinates of those are defined in the coresponding classes
    //I don't need to relocate them inside here, they are already relocated in their own classes
    //That's why i made wrappers around sf::Sprite and sf::Text instead of directly using those classes
    //(if you were wondering)
    void add_text(text* txt);
    void add_s_text(text* txt);
    int im_size();
    int l_size();
    int t_size();
    int s_t_size();
    int handle_selection();
    image* get_image(int index);
    text* get_txt(int index);
    text* get_s_txt(int index);
    bool get_active();
    void set_active(bool c);
    void print_texts(sf::RenderWindow* win);
    void print_selectable_texts(sf::RenderWindow* win);
    void print_images(sf::RenderWindow* win);
};


#endif // SCREEN_HPP_INCLUDED
