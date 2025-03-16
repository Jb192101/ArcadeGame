#pragma once

#include <cstdio>
#include <FL/Fl.h>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Button.H>

class GreetingWindow : public Fl_Window {
public:
    GreetingWindow(int w, int h, char const* title);

protected:
    void update_label(const char* new_text);

    static void play_button_click(Fl_Widget* w, void* data);

    static void author_button_click(Fl_Widget* w, void* data);

    static void about_game_button_click(Fl_Widget* w, void* data);

    static void exit_button_click(Fl_Widget* w, void* data);

    ~GreetingWindow();
private:
    Fl_Box* m_label;
    Fl_Box* m_title_label;
    Fl_Button* m_play_button;
    Fl_Button* m_author_button;
    Fl_Button* m_about_game_button;
    Fl_Button* m_exit_button;
    char m_label_text[260];
};