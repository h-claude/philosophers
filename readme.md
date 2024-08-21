Fonction qui parse argv :
- recup nombre de philo
- recup temps pour crever en milliseconds
- recup temps pour manger en milliseconds
- recup temps pour dormir en milliseconds
- recup si il y a nombre de fois qu'un philo doit manger

Eviter race condition pour les valeurs importantes 

fonction : pthread_mutex_lock prend la structure mutex et empeche tous les autres threads "d'avancer" tant qu'on a pas pthread_mutex_unlock

Note : Ne pas en abuser car il n'y aura plus d'interet a faire du multi thread
pour check longueur si plus de 10 chiffres ca degage et sinon faire un strncmp de intmax vs le nombre donne et si il renvoie un chiffre positif c'est que nombre donne est superieur au int max donc ca degage.


LEAKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK
