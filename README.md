# 2023-2024-4GP_MANENT_ZUPPELLI
--- 
## Sommaire
   - [I) Contexte et objectifs du projet](#I-Contexteetobjectifsduprojet)
   - [II) Capteur à jauge de contrainte à base de crayon graphite](#II-Capteuràjaugedecontrainteàbasedecrayongraphite)
   - [III) Partie Analogique](#III-PartieAnalogique)
   - [IV) Code Arduino](#IV-CodeArduino)
   - [V) Banc de tests](#V-Bancdetests)
     
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
<br>
- Le premier étage a une fréquence de coupure de 16 Hz, il permet de filtrer les bruits du courant en entrée. Nous avons testé ce premier étage pour vérifier que la fréquence de coupure soit la bonne.
<br>
</p>
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/diagramme_de_bode_%C3%A9tage_1.PNG" alt="Simulation de l'étage 1 dans LTSpice">
<br>
<i>Simulation de l'étage 1 dans LTSpice</i>
</p>
En effet la fréquence de coupure est la bonne.
<br>
- Le second étage a une fréquence de coupure de 1,6 Hz. Il permet de filtrer la composante de bruit du réseau électrique: le bruit à 50 Hz.
<br>
</p>
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/diagramme_de_bode_%C3%A9tage_2.PNG" alt="Simulation de l'étage 2 dans LTSpice">
<br>
<i>Simulation de l'étage 2 dans LTSpice</i>
</p>
En effet la fréquence de coupure est la bonne.
<br>
- Le dernier étage a une fréquence de coupure à 1,6 kHz qui permet d'atténuer le bruit provenant lors du traitement électronique.
<br>
</p>
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/diagramme_de_bode_%C3%A9tage_3.PNG" alt="Simulation de l'étage 3 dans LTSpice">
<br>
<i>Simulation de l'étage 3 dans LTSpice</i>
</p>
En effet la fréquence de coupure est la bonne.
<br> 
Conclusion : grâce à la simulation sur LTSpice, nous remarquons que notre signal de sortie atteindra les 1V, ce qui lui permet d'être récupéré et exploité par la carte arduino UNO.


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
<br>   
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/module%20bluetooth.PNG"alt="Figure 7 - Module Bluetooth">
<br>
<i>Module Bluetooth</i>

## V) Banc de tests

Nous avons relevé la variation de résistance de notre capteur en fonction de son angle de déformation. Pour cela, nous avons fabriqué un banc de test avec des disques en papiers ayant différents rayons de courbure:
<br> 
<p align="center">
<img src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP_MANENT_ZUPPELLI/blob/main/images_projet_capteur/banc%20de%20tests.png"alt="Figure 8 - Banc de tests">
<br> 
<i>Banc de tests</i>
<br>
Nous avons réalisé les mesures pour une déformation du capteur en traction et en compression. Nous avons testé plusieurs crayons graphites qui ont des duretés différentes: 2H, 2B, HB, 6B.
<br>

Voici les résultats obtenus: 
