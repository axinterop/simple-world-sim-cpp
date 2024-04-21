#include "Plant.h"
#include "World.h"

void Plant::Action(World &W) {
    if (chunk->seeded_this_turn)
        return;

    if (type == GRASS) {
        if (rand() % 150 == 0) {
            chunk->seeded_this_turn = true;
            W.CreatePlantOffspring(*this);
        }
    } else if (type == SONCHUS) {
        for (int tr = 0; tr < 3; tr++) {
            if (rand() % 150 == 0) {
                chunk->seeded_this_turn = true;
                W.CreatePlantOffspring(*this);
                break;
            }
        }
    } else if (type == GUARANA) {
        if (rand() % 500 == 0) {
            chunk->seeded_this_turn = true;
            W.CreatePlantOffspring(*this);
        }
    } else if (type == BELLADONNA || type == H_SOSNOWSKYI) {
        if (rand() % 700 == 0) {
            chunk->seeded_this_turn = true;
            W.CreatePlantOffspring(*this);
        }
    }
}

COLLISION_STATUS Plant::Collision(Organism &other) {
    return STAY;
}

void Plant::setChunk(PlantChunk *pc) {
    chunk = pc;
}
