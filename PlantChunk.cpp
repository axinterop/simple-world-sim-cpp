#include "PlantChunk.h"

int PlantChunk::free_id = 0;

int PlantChunk::getSize() {
    return plantIDS.size();
}

int PlantChunk::getRandomPlantID() {
    return plantIDS[rand() % plantIDS.size()];
}

void PlantChunk::addPlantID(int value) {
    for (auto p: plantIDS)
        if (p == value)
            return;
    plantIDS.push_back(value);
}

bool PlantChunk::isEmpty() {
    return plantIDS.empty();
}
