#ifndef __APP_H__
#define __APP_H__

#include <gtkmm.h>

class HelloWin : public Gtk::Window
{
public:
    //void on_button_clicked(Glib::ustring data)
    void on_button_clicked();

    static void show_app();
};

#endif // __APP_H__
