# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
```
la touche 'C' permet d'ajouter un avion
```

Comment faire pour quitter le programme ?
```
Pour quitter on peut utiliser la touche 'Q' ou la touche 'X'
```

A quoi sert la touche 'F' ?
```
Elle sert à mettre en plein ecran
```

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
```
atterissage sur la piste
recupère des passagers
quitte le terminal
quitte la piste
```

Quelles informations s'affichent dans la console ?
```
AY7405 is now landing...
now servicing AY7405...
done servicing AY7405
AY7405 lift off
```

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?
```
trois des avions font sur la piste et sont mis en service, le dernier vole autour en attendant qu'un terminal ce libère
```

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.


## AircraftType : 
```md
permet d'initialiser un tableau contenant les 3 type d'avion possible, avec leurs vitesse(au sol, dans les aires) et leurs accélérations respectives
```

## Aircraft : 
```md
permet la gestion d'un avion 
```

## AirportType : 
```md
permet la gestion des informations d'un aéroport
```

### Airport : 
```md
permet la gestion d'un aéroport
``` 

## Runway : 
```md
permet de donnée la position des pistes par rapport à la position de l'aéroport
```

## Terminal : 
```md
permet de représenter les terminaux et permet aux avions de récupérer des passagers
``` 

## TowerSimulation : 
```md
permet la gestion de toutes la simulation ainsi que les actions de l'utilisateur
```

## Tower : 
```md
permet de représenter les tours de contrôle
```

## Waypoint : 
```md
permet de représenter un point sur le chemin d'un avion
```

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.


## Tower :
### WaypointQueue get_instructions(Aircraft& aircraft) 
```md
Permet de donner des instructions au avions. 
Tout d'abord si l'avion n'est pas a un terminal, on teste s'il est proche de l'aéroport\
si ce n'est pas le cas alors il est guidé jusqu'à l'aéroport. Ensuite si un terminal est\
disponible il est reservé pour l'avion sinon l'avion tourne autour de l'aéroport.\
Sinon l'avion est mis en service au terminal, une fois la mise en service terminé\
l'avion est prêt à partir.

```

### void arrived_at_terminal(consr Aircraft& aircraft)
```md
permet d'assigner un terminal à l'avion
```

## Aicraft :
### const st::string& get_flight_num() const
```md
permet d'avoir accès au champ flight_number
```
### float distance_to(const Point3D& p) const
```md
permet d'avoir la distance entre le champ pos et le position p
```
### void display() const override
```md
permet d'afficher un avion, dans cet méthode on récupère la texture (GL::Texture2D)\
 à partir du type de l'avion qui nous permet ensuite de le render à la bonne position
```
### void move() override
```md
permet de mettre en mouvement un aircraft
```

## Airport :
### Tower& get_tower()
```md
permet d'avoir accés au champ tower
```
### void display() const override
```md
permet d'afficher l'aéroport
```
### void move() override
```md
pour chacun des terminales appartenant à la liste de teminals, on fait appel à leur fonction move
```

## Terminal :
### bool in_use() const
```md
teste si le champ current_aircraft est assigné
```
### bool is_servicing() const
```md
teste si un avion est mis en service
```
### void assign_craft(const Aircraft& aircraft)
```md
assigne aicraft au champs current_aircraft
```
### void start_service(const Aircraft& aircraft)
```md 
met aicraft en service et affiche le message correspondant
```
### void finish_service()
```md
met fin au service et affiche le message correspondant
```
### void move() override
```md
incrémentent le champs service_progress
```

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.
```
Les vitesses maximales et accélération de chaque avion sont définies dans la classe AicraftType
```
2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.

```md
La variable ticks_per_sec permet de contrôler le framrate de la simulation.\
 On trouve cette variable dans le fichier opengl_interface.hpp
```
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.
```md
La variable SERVICES_CYCLES du fichier config.hpp permet de contrôler le temps de débarquement des avions.
```

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

```
On peut savoir, où l'avion doit être supprimer en utilisant des breakpoint sur les return de la fonction Tower::get_instructions
On pourrais le faire dans la fonction timer de opengl_interface.cpp
On modifie le type de retour de la première fonction en bool ce qui permet de tester dans la seconde fonction
```

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

```
Il n'est pas pertinent de faire de même pour DynamicObject car c'est une classe polymorphe
```

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
