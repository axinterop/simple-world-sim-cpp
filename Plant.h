#ifndef PR1_PLANT_H
#define PR1_PLANT_H

#include "Organism.h"
#include "PlantChunk.h"

class Plant : public Organism {
private:
    PlantChunk *chunk;
public:
    using Organism::Organism;
    void Action(World &W) override;
    COLLISION_STATUS Collision(Organism &other) override;
    std::string className() override = 0;
    void setChunk(PlantChunk *pc);
    int getRandomChunkPlantID() { return chunk->getRandomPlantID(); };
    PlantChunk *getChunk() { return chunk; };
    int getChunkID() { return chunk->getId(); };
};

#endif //PR1_PLANT_H
