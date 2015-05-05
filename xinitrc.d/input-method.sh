#!/bin/sh

# to be sourced

# Set system environment
libexec_dir=/usr/lib
bin_dir=$libexec_dir/input-method
profile_dir=/usr/lib/input-method/profile.d

echo "Preparing input method"

# First, check personal input method
if [ -e $HOME/.config/input-method/target/env ]; then
   echo "Using personal input method" 1>&2
   env=$HOME/.config/input-method/target/env
# Then, check system input method
elif [ -e /etc/input-method/target/env ]; then
   echo "Using system input method" 1>&2
   env=/etc/input-method/target/env
fi

# Set environment variables for the selected input method
. $env
unset env

# Now the IM variable should refer to the selected input method

# Check desktop environment
if [ "$XDG_CURRENT_DESKTOP" = "GNOME" ]; then
   # workaround for bnc#853063
   # activate/deactivate g-s-d keyboard plugin depending on IM
   if [ "$IM" = "ibus" ]; then
      echo "GNOME session is detected. GNOME will start IBus" 1>&2
      gsettings set org.gnome.settings-daemon.plugins.keyboard active true
   else
      gsettings set org.gnome.settings-daemon.plugins.keyboard active false
   fi
fi

# Export variables
export IM
export GTK_IM_MODULE
export QT_IM_MODULE
export QT_IM_SWITCHER
export XMODIFIERS

echo "Prepared for $IM" 1>&2
