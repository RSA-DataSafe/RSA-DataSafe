#!/bin/bash

lowercase(){
    echo "$1" | sed "y/ABCDEFGHIJKLMNOPQRSTUVWXYZ/abcdefghijklmnopqrstuvwxyz/"
}

OS=`lowercase \`uname\``
KERNEL=`uname -r`
MACH=`uname -m`

if [ "{$OS}" == "windowsnt" ] ; then
    echo "Windows"
elif [ "{$OS}" == "darwin" ] ; then
    echo "Mac OS"
elif [ `uname` = "Linux" ] ; then
    if [ -f /etc/debian_version ] ; then
        echo "Debian"
    elif [ -f /etc/arch-version ] ; then
        echo "Arch"
    else
        echo "Système d'exploitation Linux inconnu"
        echo "Impossible d'installer les dépendances"
    fi
else
    echo "Système d'exploitation inconnu"
    echo "Impossible d'installer les dépendances"
fi