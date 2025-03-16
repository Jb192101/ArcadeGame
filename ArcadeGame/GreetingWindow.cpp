#include "GreetingWindowHeader.hpp"


GreetingWindow::GreetingWindow(int w, int h, char const* title) : Fl_Window(w, h, title), m_label_text("") {

    m_title_label = new Fl_Box(105, 10, 100, 30);
    m_title_label->labelsize(25);
    m_title_label->label("Welcome to the Dino game!");

    m_play_button = new Fl_Button(100, 45, 135, 55, "Start game");
    m_play_button->callback(play_button_click, this);

    m_author_button = new Fl_Button(100, 105, 135, 55, "About author");
    m_author_button->callback(author_button_click, this);

    m_about_game_button = new Fl_Button(100, 165, 135, 55, "About this game");
    m_about_game_button->callback(about_game_button_click, this);

    m_exit_button = new Fl_Button(100, 225, 135, 55, "Exit");
    m_exit_button->callback(exit_button_click, this);


    m_label = new Fl_Box(34, 290, 270, 200);
    m_label->labelsize(15);

    end();
}

void GreetingWindow::update_label(const char* new_text) {
    std::snprintf(m_label_text, sizeof(m_label_text), "%s", new_text);
    m_label->label(m_label_text);
}

void GreetingWindow::play_button_click(Fl_Widget* w, void* data) {
    GreetingWindow* mw = static_cast<GreetingWindow*>(data);
    const char start_msg[20] = "Starting the game";
    mw->update_label(start_msg);
    mw->~GreetingWindow();
}

void GreetingWindow::author_button_click(Fl_Widget* w, void* data) {
    GreetingWindow* mw = static_cast<GreetingWindow*>(data);
    const char about_author[258] = "The author of this game\nis Derevyanko Ivan,\ngroup 3413.";
    mw->update_label(about_author);
}


void GreetingWindow::about_game_button_click(Fl_Widget* w, void* data) {
    GreetingWindow* mw = static_cast<GreetingWindow*>(data);
    const char about_game[258] = "This game is a copy\nof the famous dinosaur\nfrom Google Chrome.\nIt is written in C++ and the FLTK library.\nThe game code uses only\nobject-oriented programming.\nThe game was created\nwithin the framework\nof the subject\nobject-oriented programming,\nRSREU, 2025.";
    mw->update_label(about_game);
}

void GreetingWindow::exit_button_click(Fl_Widget* w, void* data) {
    GreetingWindow* mw = static_cast<GreetingWindow*>(data);
    mw->~GreetingWindow();
}

GreetingWindow::~GreetingWindow() = default;
