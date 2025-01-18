#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define DEG_TO_RAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)

// Carte (1 = mur, 0 = vide)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

// Position et direction du joueur
double playerX = 4.0;
double playerY = 4.0;
double dirAngle = 270.0; // Angle en degrés

// Plan de la caméra
double planeX;
double planeY;

// Initialisation des directions en fonction de l'angle du joueur
void initializePlayerDirection() {
    double dirX = cos(DEG_TO_RAD(dirAngle));
    double dirY = sin(DEG_TO_RAD(dirAngle));
    double fov = 66.0; // Champ de vision en degrés

    planeX = cos(DEG_TO_RAD(dirAngle + 90)) * tan(DEG_TO_RAD(fov / 2));
    planeY = sin(DEG_TO_RAD(dirAngle + 90)) * tan(DEG_TO_RAD(fov / 2));

    printf("Player direction: dirX=%f, dirY=%f, planeX=%f, planeY=%f\n", dirX, dirY, planeX, planeY);
}

// Traiter un seul rayon
void processRay(int x, int screenWidth, double dirX, double dirY) {
    // Calcul de la position et de la direction du rayon
    double cameraX = 2 * x / (double)screenWidth - 1;
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;

    // Coordonnées de la case où se trouve le joueur
    int mapX = (int)playerX;
    int mapY = (int)playerY;

    // Longueur du rayon vers la prochaine case (DDA)
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    // Calcul du pas et de la distance initiale jusqu'au premier point d'intersection
    int stepX, stepY;
    double sideDistX, sideDistY;

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (playerX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (playerY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
    }

    // Exécution de l'algorithme DDA
    bool hit = false;
    int side;

    while (!hit) {
        // Déplacer dans la direction X ou Y
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        // Vérifier si un mur est atteint
        if (map[mapY][mapX] == 1) hit = true;
    }

    // Calcul de la distance projetée sur la caméra
    double perpWallDist;
    if (side == 0) {
        perpWallDist = (mapX - playerX + (1 - stepX) / 2) / rayDirX;
    } else {
        perpWallDist = (mapY - playerY + (1 - stepY) / 2) / rayDirY;
    }

    // Affichage des résultats pour chaque rayon
    printf("Ray %d: Wall hit at map[%d][%d], Distance: %f\n", x, mapX, mapY, perpWallDist);
}

// Fonction de raycasting
void raycast(int screenWidth) {
    double dirX = cos(DEG_TO_RAD(dirAngle));
    double dirY = sin(DEG_TO_RAD(dirAngle));

    for (int x = 0; x < screenWidth; x++) {
        processRay(x, screenWidth, dirX, dirY);
    }
}

int main() {
    int screenWidth = 640; // Largeur de l'écran
    initializePlayerDirection();
    raycast(screenWidth);
    return 0;
}
