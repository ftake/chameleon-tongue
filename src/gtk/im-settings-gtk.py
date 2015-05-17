#!/bin/env python

from gi.repository import Gtk


if __name__ == "__main__":
    builder = Gtk.Builder()
    builder.add_from_file("gtk-config.glade")

    dialog = builder.get_object("winIMSettingsGtk")
    handlers = {
        "onDeleteWindow": Gtk.main_quit,
        "onCancelClicked": Gtk.main_quit
    }
    builder.connect_signals(handlers)
    dialog.show_all()
    Gtk.main()
