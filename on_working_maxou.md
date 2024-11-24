# Prochaines etapes a faire

- Recuperer les paths des arguments, les envoyer pour l image, check si les paths sont valid, fd opens etc.
- dans le meme cas, check si path already use pour eviter doublons (2 NO ou SO par ex)
- Apres avoir check les premieres lignes (set les paths, ceiling and floor), decaler le pointers pour continuer a parser au bon endroit
- floodfill
- restorer la map (On remet tout en FLOOR, mais if status = 1 alors c est une porte fermee, donc on remet DOOR)
- return la map fini
-