# Connect4 

Bienvenue dans **Connect4 Terminal Game**, un jeu de puissance 4 en ligne de commande développé en C. Ce projet permet à deux joueurs de s'affronter dans une partie de puissance 4, soit sur le même terminal, soit en réseau via un serveur local. Le projet utilise la programmation réseau pour permettre une interaction en temps réel entre les joueurs, sans nécessiter la démonisation du serveur.

## Fonctionnalités

- **Mode Joueur vs Joueur local** : Jouez à deux sur le même terminal.
- **Mode Réseau** : Connectez-vous à un serveur local pour jouer contre un autre joueur distant.
- **Interface Terminal** : Jeu entièrement jouable en ligne de commande avec une interface minimaliste.

## Prérequis

- Un compilateur C (GCC recommandé)
- Système d'exploitation basé sur Unix (Linux, macOS)
- Accès à un terminal
- Sockets pour la communication réseau (standard POSIX)

## Installation

1. **Clonez le dépôt** :
    ```bash
    git clone https://github.com/votre_nom/connect4_terminal_game.git
    cd connect4_terminal_game
    ```

2. **Compilez le projet** :
    ```bash
    gcc -o connect4 client.c server.c game.c -lpthread
    ```

3. **Démarrez le serveur** :
    ```bash
    ./connect4 server
    ```

4. **Démarrez le client** :
    ```bash
    ./connect4 client <adresse_ip_du_serveur>
    ```

## Utilisation

### Mode Local

1. Lancez le jeu avec la commande suivante :
    ```bash
    ./connect4
    ```

2. Suivez les instructions affichées dans le terminal pour jouer. Les joueurs entrent tour à tour le numéro de la colonne où ils souhaitent jouer.

### Mode Réseau

1. **Démarrez le serveur** :
    ```bash
    ./connect4 server
    ```
    Le serveur attendra une connexion d'un client pour démarrer la partie.

2. **Démarrez un client sur une autre machine** :
    ```bash
    ./connect4 client <adresse_ip_du_serveur>
    ```
    Remplacez `<adresse_ip_du_serveur>` par l'adresse IP de la machine hébergeant le serveur.

3. Une fois connecté, le jeu se déroulera comme en mode local, mais avec les deux joueurs sur des machines différentes.

## Fichiers du Projet

- **client.c** : Gère la connexion réseau et les interactions côté client.
- **server.c** : Implémente le serveur de jeu qui coordonne les parties en réseau.
- **game.c** : Contient la logique du jeu (affichage, vérification des conditions de victoire, etc.).
- **game.h** : En-tête avec les définitions et les prototypes des fonctions de jeu.
- **README.md** : Documentation du projet.

## Contributions

Les contributions sont les bienvenues ! Veuillez suivre ces étapes pour contribuer :

1. **Fork** le projet.
2. Créez votre branche de fonctionnalité (`git checkout -b feature/AmazingFeature`).
3. Effectuez vos modifications (`git commit -m 'Add some AmazingFeature'`).
4. Poussez sur la branche (`git push origin feature/AmazingFeature`).
5. Ouvrez une **Pull Request**.

## License

Ce projet est sous licence MIT. Veuillez consulter le fichier `LICENSE` pour plus d'informations.

## Auteurs

- **Mathéo Petry (Leyllio)** - *Développeur Principal* - [Votre Profil GitHub](https://github.com/Leyllio)
- **Clement Jonglas** - *Développeur Principal* - [Votre Profil GitHub](https://github.com/H4de421)

---