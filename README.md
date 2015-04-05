# Chameleon Tongue: An extensible input method launcher

## How to Customize Input Method to Start

### User-level preference:

    $ mkdir ~/.config/input-method
    $ cd ~/.config/input-method
    $ ln -s target /usr/lib/input-method/profile.d/ibus

### System-level preference

This settings are used for all users without user-level preference above.

    $ mkdir ~/.config/input-method
    $ cd ~/.config/input-method
    $ ln -s target /usr/lib/input-method/profile.d/ibus

### Option arguments for IM startup scripts

TBD.

    $ mkdir ~/.config/input-method
    $ cd ~/.config/input-method
    $ vi optargs

## Input method framework specific feature

### IBus

If the current desktop environment is KDE and an Kimpanel applet is placed on the desktop, the launch script included in this launcher enables IBus Kimpanel panel application. Otherwise, the script selects ibus-ui-gtk3.

If you want to force ibus-ui-gtk3, add the following declaration in ~/.config/input-method/optargs:

    IBUS_PANEL=/usr/lib64/ibus/ibus-ui-gtk3

Note that the path to ibus-ui-gtk3 might be different in your environment.