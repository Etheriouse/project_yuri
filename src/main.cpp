#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Application.hpp"

// maybe commencer a faire la parti render lol
// et la parti move sur la map (case par case)

// doubler le jeu en fr en jp (si j'ai le niveau)

// intro en pov réel

// histoire a player dans la vrai vie allume son pc et lance un petit jeu indé qu'il a trouver sur internet
// il lance le jeu se fait une petite session et quand il veut quitter il se rend compte qu'il peu pas, tente de fermer la fenetre
// peu pas, tente gestionnaire des tache, redemarer le pc, et meme en debranchant la prise le pc reste allumer
// le player panique pas trop et se dit, je crois bien que je dois finir le jeu pour fermer se jeu

// encore reflechir a ce qui se passe quand tu fini le jeu classique
// et a se qu'il se passe si tu choisi de continuer la ou y'a rien qui était prevu (l'enver du decord)

// la cut scene pov réel de tente de fermer le jeu est faite la 1er fois que tu tente de quitter le jeu
// les autre fois c juste une mini cut scene du player qui se leve de son bureau et sort de chez lui
// intro du jeu quand deja lancer c le player qui rentre chez lui et qui se pose sur son bureau

// menu global avec tout ce qui est lier au jeu sur le pc et le reste en dehors ou jsp
// load reset delete (faudra faire un truc, pareil pour reset)
// le menu du jeu c les icon sur le bureau du pc (le bureau virtuel pas physique) // avec les menu dans les dossier lesp arametre dans parametre window etc
// ou tu peux choisir ta save, les credit, les succes ou c dans la chambre du player, genre son armoire ces bouqin etc

// Jeu classique fantasy, tu peux le finir sans savoie que qi une suite daction est effectuer tu arrive dans un endroit où t pas senser allez ( l'envers du decord ) ( possiblement tu récupère des ppuvoir plus puissants et tu te tappe avec dieux ou les principe celeste jsp)

// Gameplay
// Tour par tour mais une action par tour et les entity joue jusye apres toi, donner impression temps réel en tour par tour
// Niveau de difficultés en détaillant les action ( ex bouger dans l'inventaire = 1 action jusqua fin, niveau diff up => chaque mouvement dans l'inventaire = une action)
// Designe
// Assez dessiner main puis numeriser ou dessin numérique style crayon feutre
// content
// Dungeon a faire 3 pour ouvrir le final, petite énigme pour ouvrir les 3 dungeon et le dungeon principal sur une carte a la undertal deltarune, pas forcément de monde ouvert ( ca ma gaver )


// Game object is a save active
// Main objet with menu save gestionary etc needed

#define UNUSED(x) (void)(x)

int main(int argc, char const *argv[])
{

    UNUSED(argc);
    UNUSED(argv);

    return Application::newInstance().run();
    // create the map and save the map in file test_map01.map

    // Mob frog("Frog", 25, 2);
    // Mob frog2("Frog", 25, 2);
    // frog.x = 2;
    // frog.y = 1;
    // frog2.x = 6;
    // frog2.y = 0;
    // Mob bones("Bones", 45, 10);
    // bones.x = 5;
    // bones.y = 6;
    // Map m(8, 8, {&frog, &frog2, &bones});

    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         if (j < 2)
    //             *m(i, j) = {0, Tile::Grass};
    //         else if (j > 5)
    //             *m(i, j) = {0, Tile::Stone};
    //         else if (j > 1 && j < 6 && (i == 1 || i == 6))
    //             *m(i, j) = {0, Tile::WoodBridge};
    //         else
    //             *m(i, j) = {0, Tile::Air};
    //     }
    // }

    // m.debug_print();
    // Serializer s("test_map001.map", SERIALIZER_LOAD_MODE);
    // Map m("test_map001.map");
    // m.debug_print();
    // m.save(s);

    return 0;
}
