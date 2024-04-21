#ifndef PR1_PLANTCHUNK_H
#define PR1_PLANTCHUNK_H

#include "util.h"

class PlantChunk {
    int id;
    static int free_id;
    std::vector<int> plantIDS;
public:
    PlantChunk() { id = free_id++; }
    bool seeded_this_turn = false;
    int getSize();
    int getRandomPlantID();
    void addPlantID(int value);
    bool isEmpty();
    bool getId() { return id; };
};


#endif //PR1_PLANTCHUNK_H
