# 2023-2024-4GP_MANENT_ZUPPELLI
--- 
## Sommaire
   - [I) Contexte et objectifs du projet](#I-Contexteetobjectifsduprojet)
   - [II) Capteur à jauge de contrainte à base de crayon graphite](#II-Capteuràjaugedecontrainteàbasedecrayongraphite)
   - [III) Partie Analogique](#III-PartieAnalogique)
     
---
  
## I) Contexte et objectifs du projet

L'objectif de ce projet est de réaliser un capteur low-tech à base de graphite. Les recherches ont démontré les nombreux avantages du carbone graphite. L’électronique à base de papier gagne en popularité parmi les ingénieur(e)s grâce à sa facilité d’approvisionnement, sa simplicité de fabrication et son faible coût.<br>
Nous avons dû réaliser tous les processus de fabrication d'un shield PCB. Nous l'avons ensuite connecté à une plaque Arduino UNO.<br>
Notre shield contient 6 composants différents : une jauge de contrainte, un flex sensor, un écran oled, un encodeur rotatoire, un potentiomètre digital et un module Bluetooth.<br>
Par ailleurs, la carte Arduino fonctionne avec un code.<br>
Nous avons ensuite réalisé une application mobile connectée au module bluetooth.<br>
Nous avons évalué le capteur sur un banc de test.<br>
Puis nous avons fini par réaliser la datasheet du capteur de contrainte.<br>

## II) Capteur à jauge de contrainte à base de crayon graphite

Ce capteur low-tech utilise la théorie de la percolation au sein d’un système granulaire constitué de nanoparticules de graphite.<br>
Nous déposons une fine couche de graphite sur la feuille de papier ce qui présente un réseau percolé caractéristique. Dans ce réseau, le transport des électrons entre les nanoparticules est basé sur le mécanisme de l’effet tunnel.<br>
Lors de l'application d'une tension, le réseau percolé se trouve directement étendu. Cette déformation entraîne une augmentation de la distance effective entre les particules de graphite au sein du réseau. Une partie des chemins de percolation sont par conséquent rompus. Ainsi, la conduction du matériau diminue, donc la résistance de la couche de graphite augmente.<br>
Inversement, lors de l’application de déformations en compression, le réseau percolé se trouve directement comprimé. Cette déformation entraîne une diminution de la distance effective entre les particules.<br> Ainsi, de nouveaux chemins de percolation sont créés, la conduction du matériau augmente, soit la résistance de la couche de graphite diminue.

Une jauge de contrainte est un circuit résistif dont la résistance varie en fonction de sa déformation. Donc en mesurant les variations de résistance de la jauge, nous en avons déduit la contrainte et la déformation appliquées.<br>
Notre jauge de contrainte est alimentée par une tension régulée de 5V d'une carte Arduino UNO.
<br>
Ci-dessous, les 4 différentes jauges de contrainte que nous avons utilisé dans ce projet.

<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/capteur_%C3%A0_jauge_de_contrainte.PNG" alt="Figure 1 - Capteur à jauge de contrainte à base de crayon graphite">
<br>
<i>Capteur à jauge de contrainte à base de crayon graphite</i>
</p>

## III) Partie Analogique
