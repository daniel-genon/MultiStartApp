# MultiStartApp
Application de séquençage de démarrage de logiciels

Pour la description précise du logiciel ouvrir le fichier doc-multistartapp.pdf présent dans le projet.

Installation.

    Ce logiciel est actuellement programmé avec la bibliothèque Qt version 6, mais pour les distributions n’incluant pas encore cette version 6, il est possible de le construire en utilisant la version Qt 5.15, laquelle provoquera quelques avertissements sans conséquences.

- Construction avec l’EDI QtCreator.

-- Version Qt 6 et ultérieures
Télécharger le projet Multistartapp présent dans le dépot github et ouvrir le projet en sélectionnant le fichier Cmakelists.txt. Utilisez les commandes de construction comme pour tout autre application basée sur Qt.

-- Version Qt5.15
Procéder comme pour la version Qt6 en modifiant la ligne commenteé du Cmakelists.txt


- Version Qt5.15 en ligne de commande.

Télécharger le projet Multistartapp515.zip présent dans le dépot github du projet MultiStartApp et décompresser ce fichier où vous le souhaiter.

- Utiliser avec Make ou CMake.

vérifier la présence ou installer les paquets gcc gcc-9 gcc-10 g++ g++-10 et libconfig++9v5
vérifier l’existence de : /usr/bin/gcc

Au préalable, puisque nous devrons utiliser les programmes cmake et ninja dans un terminal pour compiler et construire le logiciel, nous vérifions leurs présence dans le dossier /usr/bin où ils sont généralement stockés ; s’ils sont absents il nous suffit d’installer les paquets cmake et ninja-build.

Nous vérifions que les bibliothèques Qt nécessaires sont présentes en cherchant dans le dossier /usr/bin, Le mot <x86_64-linux-gnu>, utilisé ci-dessous, dépend de votre distribution, le paquet entre parenthèses et celui qu’il faut installer en cas d’absence :

--  le dossier : /usr/lib/<x86_64-linux-gnu>/cmake/Qt5 (s’il n’existe pas, il sera créé par le chargement d’un des paquets ci-dessous) ;
-- /usr/lib/<x86_64-linux-gnu>/cmake/Qt5Core ( paquet libqt5core5a )
-- /usr/lib/<x86_64-linux-gnu>/cmake/Qt5Gui ( paquet libqt5gui5 )
-- /usr/lib/<x86_64-linux-gnu>/cmake/Qt5Widgets ( paquet libqt5widgets5 )
S’il en manque, installez-les.

-- Pour construire le programme exécutable effectuez les opérations suivantes :

    extraire le dossier multistartapp515 dans le /home/chez vous
    ouvrir un terminal en utilisant la commande du menu ou alt+controle+t
    placez-vous dans le dossier multistartapp515 : cd multistartapp515
    créez le dossier release : mkdir release
    exécutez la commande : cmake -G Ninja -B release
    aller dans le dossier release : cd release
    exécuter la commande : ninja
Attendre la fin de compilation et, s’il n’y a pas d’erreurs (ne pas s’occuper des avertissements), lister le dossier et vérifier que le fichier multistartapp est présent. Déplacer ce fichier dans le dossier destiné aux programmes utilisateurs du système.

- Désinstaller le logiciel :

Pour désinstaller le logiciel et ces dépendances :
-- Supprimer le logiciel du répertoire où il se trouve. S’il est dans /usr/bin vous devrez avoir les droits "root"
-- Supprimer le dossier multiapp et tout ce qu’il contient. Mais avant l’opération, vérifiez bien que les fichiers que vous souhaitez garder soient bien sauvegardés.
-- Si vous avez créé des fichiers script vous pouvez aussi les effacer s'ils sont devenus inutiles.

Daniel Génon
