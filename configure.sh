#!/bin/bash

lowercase(){
    echo "$1" | sed "y/ABCDEFGHIJKLMNOPQRSTUVWXYZ/abcdefghijklmnopqrstuvwxyz/"
}

OS=`lowercase \`uname\``
KERNEL=`uname -r`
MACH=`uname -m`

if [ "$OS" = "windowsnt" ] ; then
    echo "Système d'exploitation Windows non supportés"
    echo "Impossible d'installer les dépendances"
elif [ "$OS" = "darwin" ] ; then
    echo "Système d'exploitation Mac OS non supportés"
    echo "Impossible d'installer les dépendances"
elif [ "$OS" = "linux" ] ; then
    if [ -f /etc/debian_version ] ; then
        echo "Mise à jour de la liste des paquets"
        sudo apt-get update
        echo "Installation des dépendances"
        sudo apt-get install libgmp3-dev libgtk2.0-dev libgtk-3-dev libgtk2.0-0 at-spi2-core
    else
        echo "Système d'exploitation Linux non supportés"
        echo "Impossible d'installer les dépendances"
    fi
else
    echo "Système d'exploitation inconnu"
    echo "Impossible d'installer les dépendances"
fi