#include "screen.hpp"

image::image() {}
image::image(double _x, double _y, const char* name, int res_x, int res_y) {
    tx.loadFromFile(name);
    sp.setTexture(tx);
    sp.setScale(res_x, res_y);
    x = _x;
    y = _y;
    sp.setPosition(x, y);
}
sf::Sprite image::get_sp() { return sp; }

text::text() {}
text::text(double _x, double _y, const char* tx, float scale_x, float scale_y) {
    x = _x;
    y = _y;
    font.loadFromFile("font.ttf");
    txt.setPosition(x, y);
    txt.setFont(font);
    txt.setString(tx);
    txt.setScale(scale_x, scale_y);

}

void text::set_color(sf::Color c) { txt.setColor(c); }

sf::Text text::get_txt() { return txt; }


void screen::add_image(image* im) { im_list.push_back(im); }
void screen::add_text(text* txt) { tx_list.push_back(txt); }
void screen::add_s_text(text* txt) { s_tx_list.push_back(txt); }
int screen::im_size() { return im_list.size(); }
int screen::t_size() { return tx_list.size(); }
int screen::s_t_size() { return s_tx_list.size(); }

int screen::handle_selection() {
    for (int i = 0; i < s_tx_list.size(); i++) {
        s_tx_list[i]->set_color(sf::Color::White);
    }
    s_tx_list[select_index]->set_color(sf::Color::Black);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        selector++;//Mark
        if (selector > 10) {//Mark
            if (select_index > 0) { select_index--; }
            selector = 0;
        }

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        selector++;
        if (selector > 10) {
            if (select_index < s_tx_list.size() - 1) { select_index++; }
            selector = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        return select_index;
    }
    return -1;

}

image* screen::get_image(int index) { return im_list[index]; }
text* screen::get_txt(int index) { return tx_list[index]; }
text* screen::get_s_txt(int index) { return s_tx_list[index]; }

bool screen::get_active() { return active; }
void screen::set_active(bool c) { active = c; }

void screen::print_texts(sf::RenderWindow* win) {
    for (int i = 0; i < tx_list.size(); i++) {
        win->draw(tx_list[i]->get_txt());
    }
}

void screen::print_selectable_texts(sf::RenderWindow* win) {
    for (int i = 0; i < s_tx_list.size(); i++) {
        win->draw(s_tx_list[i]->get_txt());
    }
}

void screen::print_images(sf::RenderWindow* win) {
    for (int i = 0; i < im_list.size(); i++) {
        win->draw(im_list[i]->get_sp());
    }
}
