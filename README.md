# 2023-2024-4GP_MANENT_ZUPPELLI
--- 
## Sommaire
   - [I) Contexte et objectifs du projet](#I-Contexteetobjectifsduprojet)
   - [II) Capteur à jauge de contrainte à base de crayon graphite](#II-Capteuràjaugedecontrainteàbasedecrayongraphite)
   - [III) Partie Analogique](#III-PartieAnalogique)
   - [IV) Code Arduino](#IV-CodeArduino)
     
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

Ce capteur graphite possède une résistance variable de l'ordre du GΩ. Le courant généré lorsque l'on applique une tension de 5V aux bornes du capteur est très faible.<br>
Pour obtenir un signal exploitable nous avons dû l'amplifier. Pour ce faire, nous avons utilisé un montage transimpédance constitué d'un amplificateur opérationnel.<br>
Pour cela nous avons dans un premier temps effectué une simulation électronique du capteur et de ce montage transimpédance sous LTSpice. Voici ci-dessous le montage réalisé sous LTSpice. Pour notre montage nous avons choisi l'AOP LTC1050 prenant en entrée un courant faible (de l'ordre d'une dizaine de picoampère).

<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/circuit_amplificateur.PNG" alt="Circuit amplificateur réalisé dans LTSpice">
<br>
<i>Circuit amplificateur réalisé dans LTSpice</i>
</p>
<br>
Ce circuit amplificateur contient également 3 filtres passe bas passifs, dont nous avons pu tester le bon fonctionnement alternativement.<br>
- Le premier étage a une fréquence de coupure de 16 Hz, il permet de filtrer les bruits du courant en entrée. Nous avons testé ce premier étage pour vérifier que la fréquence de coupure soit la bonne.





- Le second étage a une fréquence de coupure de 1,6 Hz. Il permet de filtrer la composante de bruit du réseau électrique: le bruit à 50 Hz.

- Le dernier étage a une fréquence de coupure à 1,6 kHz qui permet d'atténuer le bruit provenant lors du traitement électronique.


## IV) Code Arduino

Le code Arduino permet la réception des mesures faites par les deux capteurs (Graphites et Flex Sensor) et d'afficher ces valeurs sur l'OLED. 
Notre programme principal est composé de sous programmes associés à ces éléments:
<br>
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/capteur_%C3%A0_jauge_de_contrainte.PNG" alt="Figure 2 - Capteur à jauge de contrainte à base de crayon graphite">
<br>
<i>Capteur graphite</i>
<br>   
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/Flex%20Sensor.PNG"alt="Figure 3 - Flex Sensor">
<br>
<i>Flex Sensor</i>
<br>   
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/ecran%20oled.PNG"alt="Figure 4 - Ecran OLED">
<br>
<i>Ecran OLED</i>
<br>   
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/encodeur%20rotatoire.PNG"alt="Figure 5 - Encodeur rotatoire">
<br>
<i>Encodeur rotatoire</i>
<br>   
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/potar.PNG"alt="Figure 6 - Potentiomètre digital">
<br>
<i>Potentiomètre digital</i>


