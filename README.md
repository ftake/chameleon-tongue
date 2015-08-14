# Chameleon Tongue: An extensible input method launcher

## How to Customize Input Method to Start

### User-level preference:

    $ im-settings select ibus

or

    $ mkdir ~/.config/input-method
    $ cd ~/.config/input-method
    $ ln -s /usr/lib/input-method/profile.d/ibus target

### System-level preference

This settings are used for all the users who does not have
user-level preference above.

    $ mkdir /etc/xdg/input-method
    $ cd /etc/xdg/input-method
    $ ln -s /usr/lib/input-method/profile.d/ibus target

### Option arguments for IM startup scripts

#### Force LibreOffice GNOME for better IM support

    $ im-settings config --set global.ooo_force_desktop_gnome ture

## Input method framework specific feature

### IBus

If the current desktop environment is KDE and an Kimpanel applet is placed on the desktop, the launch script included in this launcher enables IBus Kimpanel panel application. Otherwise, the script selects ibus-ui-gtk3.

If you want to force ibus-ui-gtk3, run the follwoing command:

    $ im-settings config --set ibus.panel=/usr/lib64/ibus/ibus-ui-gtk3

Note that the path to ibus-ui-gtk3 might be different in your environment.