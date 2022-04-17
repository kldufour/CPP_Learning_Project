# Projet tower_control DUFOUR Kelly

Les réponses aux différentes questions ont été faites dans les fichiers TASK_#.md

## Architecture du programme
Je n'ai pas été ammené a faire d'autres choix que ceux prévu par le sujet

## Point bloquant

L'appel Airport::update → get_reguired_fuel → is_low_on_fuel lève une erreur de segementation. Cette erreur vient du fait de l'appel au champs fuel. Je n'ai pas trouve de solution à cette errer. Neanmoins afin d'avoir un programme qui compile et de finir la TASK_2, je ne recalcule pas ordered_fuel en utilisant le minimum entre get_reguired_fuel et 5000. Le champs ordered_fuel faut 5000


## Appréciation

J'ai eu du mal avec le fait de repartir sur une base de projet s'est avéré être problèmatique, Ainsi que le fait d'avoir des taches guidées en effet je n'ai pas compris le but/l'objectif final du projet
