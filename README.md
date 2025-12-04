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
- Fréquence de commutation choisie : 20 kHz (PSC = 0, ARR = 4250-1) 
- Temps mort configuré : 400 ns (68 dans le registe). On a calculé (en partant de la datasheet) pour avoir une marge en prenant 200ns puis on a mis le double pour rien cramer car ce temps reste négligeable devant la période de PWM.
  <img width="590" height="220" alt="image" src="https://github.com/user-attachments/assets/00c0a349-37d4-4a38-af86-444972949c18" />
- Duty cycle initial : 60 %

<img width="249" height="154" alt="image" src="https://github.com/user-attachments/assets/1c45c52d-2fba-4ae3-88c3-620a46d05313" />


## 4. Premiers Tests :
- On branche le moteur en 48V avec une limitation de 12A.




