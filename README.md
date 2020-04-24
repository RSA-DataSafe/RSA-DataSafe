![RSA-Database](features/rsa_logo.png)

![GitHub top language](https://img.shields.io/github/languages/top/RSA-Datasafe/RSA-Datasafe)

# Projet RSA

Le but de ce projet est d'implémenter RSA. Nous auront la possibilité de signer et de vérifier un fichier pour s'assurer de l'identiter de l'envoyeur (afin d'éviter l'attaque de l'homme du milieu). 

# Installation - Déployement du produit 

## ⚒ Compiler le projet

make

## ▶ Executer le projet

make run

## ℹ Le code source

Il se trouve dans le répertoire `src/`.

`cd src/`

# Module de notre projet

## Interface

Ce module gère la communication entre le programme, l'utilisateur et les autres module.

## Génération des clés

Génère les clés pour chiffrer et déchiffrer un message.

## Chiffrement

Chiffre un message.

## Signature

Il a deux principale fonctionnalité :
<ul>
	<li>générer une signature</li>
	<li>verifier une signature</li>
</ul>
Ce module utilise une fonction de hashage. On a choisi d'utiliser sha3.

## Déchiffrement

Déchiffre un message.

## Gestion de fichier

Gére la connection à l'application ainsi que la sauvegarde des clés de l'utilisateur et de ces messages.
