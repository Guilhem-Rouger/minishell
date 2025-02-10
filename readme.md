# Minishell

Un shell minimaliste inspiré de bash, développé dans le cadre du projet 42.

## Description

Ce projet consiste en la création d'un shell simple capable de :
- Interpréter et exécuter des commandes
- Gérer les variables d'environnement
- Supporter les redirections et les pipes
- Gérer les quotes et les caractères spéciaux

## Fonctionnalités

- Prompt personnalisé avec le nom d'utilisateur
- Gestion de l'historique des commandes (readline)
- Exécution de commandes avec leurs arguments
- Gestion des variables d'environnement
- Support des opérateurs de redirection (`<`, `>`, `>>`)
- Support des pipes (`|`)
- Gestion des quotes simples et doubles
- Builtins implémentés

## Structure du Projet

### Fichiers Principaux
- `include/minishell.h` : Header contenant toutes les définitions et structures
- `libft/` : Bibliothèque de fonctions utilitaires
- `Makefile` : Pour la compilation du projet

### Structures de Données Principales

#### t_token
Structure pour le parsing des commandes :
- Gestion du texte et du type de token
- Support des quotes doubles et simples
- Gestion des chemins et arguments
- Liste chaînée pour les tokens

#### t_data
Structure principale du shell :
- Gestion de l'environnement
- Variables de contrôle
- Gestion des fichiers et pipes
- Stockage des commandes et arguments

## Compilation et Utilisation

```bash
make        # Pour compiler le projet
./minishell # Pour lancer le shell
```

## Dépendances
- readline
- Compilateur C
- Make

## Auteur
- grouger (@42)