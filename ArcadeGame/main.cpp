#include <cstdio>
#include <FL/Fl.h>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Button.H>
#include "GreetingWindowHeader.hpp"

class MainWindow : public Fl_Window {
public:
    MainWindow(int w, int h, char const* title) : Fl_Window(w, h, title), m_counter(-20) {
        // Создаём кнопку
        m_button = new Fl_Button(34, 34, 133, 56, "i++");
        // Присваиваем обработчик кнопки, при этом пробрасываем текущее окно
        m_button->callback(button_click, this);
        // Создаём надпись-счётчик
        m_label = new Fl_Box(34, 177, 133, 56);
        // Выставляем размер шрифта
        m_label->labelsize(50);
        // Сразу обновляем текст счётчика
        update_label();
        // Заканчиваем добавлять виджеты
        end();
    }

protected:
    void update_label() {
        // Преобразуем число в строку
        std::snprintf(m_label_text, sizeof(m_label_text), "%d", m_counter);
        m_label->label(m_label_text);
    }

    static void button_click(Fl_Widget* w, void* data) {
        // Получаем окно, которое передали обработчику
        MainWindow* mw = static_cast<MainWindow*>(data);
        // Увеличиваем счётчик
        mw->m_counter++;
        // Обновляем надпись
        mw->update_label();
    }
private:
    Fl_Box* m_label;
    Fl_Button* m_button;
    char m_label_text[16];
    int m_counter;
};

int main(void) {
    // Задаём тему для виджетов (none, base, plastic, gtk+, gleam)
    //Fl::scheme("gleam");

    // Создаём окно
    MainWindow* window = new MainWindow(200, 300, "i++");
    GreetingWindow* window2 = new GreetingWindow(300, 300, "hui");
    window2->show();
    // Показываем окно
    //window->show();
    // Запускаем event loop
    return Fl::run();
}