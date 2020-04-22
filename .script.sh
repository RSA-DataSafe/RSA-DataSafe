#!/bin/bash

if [ ! -d "bin/" ]; then 
    mkdir bin
fi

if [ ! -d "obj/" ]; then 
	mkdir obj
	mkdir obj/gestion_fichier
	mkdir obj/generation
	mkdir obj/interface
	mkdir obj/chiffrement
	mkdir obj/dechiffrement
	mkdir obj/signature
	mkdir obj/calcul
fi