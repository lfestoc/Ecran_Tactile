# Ecran_Tactile
Pour faire fonctionner ce code avec l'écran, importez le dans cubeIDE
Faites la configuration suivante : 
(voir également Pin_configuration.png)

PIN configuration :
XR : PA8
XL : PA1
YD : PA4, EXTI4
YU : PB10
VCC : 3V3
GND : GND
CS : PB6
RST : PC7
RS/A0 : PA9
SCL : PB3 
SDA : PA7 
SDO : PA6 
A : 3V3
K1 : GND
K2 : GND
K3 : GND
K4 : GND


Les fonctions d'affichage sont définies dans le fichier MY_ILI9341.c et les fonction de la partie tactile dans le fichier LCD_touch.c
Certaines fonctions faisaient déja partie de la libraire, d'autres ont étés ajoutées par nous même avec la compréhension actuelle que nous avons de ces librairies. 
Dans notre main nous utilisons l'état de l'écran tactile pour faire des actions et nous attendons une interuptions sur PA4 pour ne pas lire en continue un point. 
Cette méthode est plus lente que lal lecture en continue mais permet de consommer moins. 
Au moment où nous écrivons cela il y a encore des problèmes au niveau du retour de l'état de l'écran. (Par exemple l'état On_Down n'est pas toujours atteint au début d'un touché)
Nous avons donc tenté de regler ce problème à l'aide de FLAGS. 
Plusieurs fonctionnalités sont disponible comme la lecture de gif (il faut d'abord rentrer des image sous forme de matrice) (voir image.h).
Il y à également la possibilité de faire un swipe up, swipe left ou swipe right. 

link of the project on GITHUB : https://github.com/lfestoc/Ecran_Tactile.git
