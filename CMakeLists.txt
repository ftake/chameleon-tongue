project(chameleon-tongue)

cmake_minimum_required(VERSION 2.8)

add_subdirectory(src)

install(PROGRAMS bin/check-libreoffice-gnome bin/start-im
        DESTINATION lib/input-method)
install(DIRECTORY profile.d locale.d DESTINATION lib/input-method)
install(DIRECTORY etc/input-method DESTINATION /etc)
install(FILES xinitrc.d/input-method.sh DESTINATION /etc/X11/xinit/xinitrc.d)
install(FILES misc/input-method.desktop DESTINATION /etc/xdg/autostart)
