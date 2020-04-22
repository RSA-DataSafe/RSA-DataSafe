#!/bin/bash
declare -a tableau_fichier=( 
"bin" 
"obj" 
"obj/gestion_fichier" 
"obj/generation" 
"obj/interface" 
"obj/chiffrement" 
"obj/dechiffrement" 
"obj/signature" 
"obj/calcul" 
)

mkdir ${tableau_fichier[@]} 2> /dev/null 

unset tableau[@]
