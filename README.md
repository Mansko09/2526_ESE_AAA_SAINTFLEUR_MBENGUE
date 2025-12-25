# 2526_ESE_AAA_SAINTFLEUR_MBENGUE
TP actionneurs - Kenny SAINT FLEUR et Mantoulaye MBENGUE -



## 1. Objectifs du TP

- Générer 4 PWM en complémentaire décalée pour contrôler en boucle ouverte le moteur en respectant le cahier des charges  
- Inclure le temps mort (dead-time)  
- Vérifier les signaux de commande à l’oscilloscope  
- Prendre en main le hacheur  
- Faire un premier essai de commande moteur  

## 2. Configuration matérielle utilisée

- Carte : NUCLEO-G474RE.  
- Moteur :  MP77S (MCC, 530W, 48V)  
- Pour le control de moteur, on utilise la ma

## 3. Génération des 4 PWM complémentaires avec temps mort

### 3.1 Paramétrage dans STM32CubeMX / CubeIDE
- Timer utilisé : Timer 1 CH1/CH1N,  CH2/CH2N.
- Mode : PWM complémentaire (center aligned 1) avec dead-time 
- Fréquence de commutation choisie : 20 kHz (PSC = 0, ARR = 4250-1) pour HCLK = 170MHz
- Temps mort configuré : 400 ns (68 dans le registre). On a calculé (en partant de la datasheet) pour avoir une marge en prenant 200ns puis on a mis le double pour rien cramer car ce temps reste négligeable devant la période de PWM.
  <img width="590" height="220" alt="image" src="https://github.com/user-attachments/assets/00c0a349-37d4-4a38-af86-444972949c18" />
- Duty cycle initial : 60 %

<img width="249" height="154" alt="image" src="https://github.com/user-attachments/assets/1c45c52d-2fba-4ae3-88c3-620a46d05313" />


## 4. Premiers Tests :
- On branche le moteur en 48V (qui seront hachés) avec une limitation de 12A.

<img width="2048" height="1536" alt="image" src="https://github.com/user-attachments/assets/ac6ca0e7-dfbc-48cb-8bb3-5d33134482ff" />

- Quand on monte le rapport cyclique brusquement, on a une montée brusque du courant. Donc on veut utiliser des rampes pour monter le rapport cyclique de façon progressive.
  On fait des pas de 100 sur le ARR (ARR_MAX = 4250) avec un temps d'interval de 5ms.

## 5. Shell sans freeRTOS :
Après quelques modifications, le shell fonctionne correctement.
On créer les différentes fonctionnalités dans la fonction d'initialisation.

<img width="908" height="253" alt="image" src="https://github.com/user-attachments/assets/9758c63b-b031-4cb5-8054-893589ea1603" />

## 6. Commande MCC Basique :
En faisant une installation de sondes pour détecter les PWM, on obtient ce montage : 
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/16b8a1d8-34e4-4e69-b695-15bb8165ccd6" />

Et l'oscillocsope affiche les signaux suivant :

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/d02af268-c744-4109-a7b6-465e12d8eeed" />


On arrive aussi a faire varier le rapport cyclique...

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/5baf9d6b-9d2e-4979-b5bb-26f9aecaa35b" />


## 7 - Commande en boucle ouverte, mesure de Vitesse et de courant
### 7.1. Commande de la vitesse
On a rajouté ces fonctionnalités :

<img width="277" height="72" alt="image" src="https://github.com/user-attachments/assets/3765f644-db5c-442b-96bb-5ef5f0896057" />

### 7.2. Mesure du courant
On mesure le courant uniquement dans la phase U car il s'agit d'une MCC

les pins utilisés sont les suivants : 

<img width="271" height="277" alt="image" src="https://github.com/user-attachments/assets/402a2e40-d038-4067-b83d-50605f8d1e7a" />

Voici la fonction liant la tension de mesure et le courant dans le GO10 SME : 

<img width="351" height="69" alt="image" src="https://github.com/user-attachments/assets/03e4cfde-fb8c-41f5-a3df-aad2dff0f667" />


On en déduit : 

<img width="218" height="51" alt="image" src="https://github.com/user-attachments/assets/de6c9c28-6fd7-49e6-bb2f-e2faf3735e12" />

On mesure une première valeur de courant avec l'ADC : 

<img width="387" height="516" alt="image" src="https://github.com/user-attachments/assets/66e867e0-845a-4a5e-ba23-0174e842667e" />


<img width="669" height="70" alt="image" src="https://github.com/user-attachments/assets/883b2fa0-a6d6-4dc7-871e-86cf0c44ffad" />



Mesure de Vitesse : 


<img width="516" height="292" alt="image" src="https://github.com/user-attachments/assets/581276a4-c5a2-4bf5-ad18-5903705d881f" />


