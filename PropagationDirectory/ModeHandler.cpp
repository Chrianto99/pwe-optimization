//
// Created by Christos on 3/18/2025.
//

#include "ModeHandler.h"


#include "ModeHandler.h"
#include <iostream>
#include <numeric>  // for std::accumulate


void ModeHandler::aliasMethod() {
    int numTiles = graph->getNumTiles();

    for (int i = 0; i < numTiles; ++i) {
        int numModes = graph->getNumModes(i);

        std::vector<int> &counts = tileDistributions[i];  // Current tile's counts
        int total = std::accumulate(counts.begin(), counts.end(), 0);  // Sum of counts

        if (total == 0) continue;  // Avoid division by zero

        std::vector<double> prob(numModes);
        std::vector<int> small, large;

        // Normalize probabilities
        for (int j = 0; j < numModes; ++j) {
            prob[j] = (counts[j] * numModes) / static_cast<double>(total);
            if (prob[j] < 1.0) small.push_back(j);
            else large.push_back(j);
        }

        // Build alias tables
        while (!small.empty() && !large.empty()) {
            int smallIdx = small.back();
            small.pop_back();
            int largeIdx = large.back();

            probabilities[i][smallIdx] = prob[smallIdx];
            aliases[i][smallIdx] = largeIdx;

            prob[largeIdx] = (prob[largeIdx] + prob[smallIdx]) - 1.0;
            if (prob[largeIdx] < 1.0) {
                small.push_back(largeIdx);
                large.pop_back();
            }
        }

        // Assign remaining values
        while (!large.empty()) {
            probabilities[i][large.back()] = 1.0;
            large.pop_back();
        }
        while (!small.empty()) {
            probabilities[i][small.back()] = 1.0;
            small.pop_back();
        }
    }
}

    int ModeHandler::chooseMode(int tileId) {

        std::uniform_int_distribution<int> dist(0, graph->getNumModes(tileId) - 1);
        int r = dist(randGen);
        std::uniform_real_distribution<double> realDist(0.0, 1.0);
        double u = realDist(randGen);

        // Step 3: Use the alias method to decide which mode to pick
        if (u < probabilities[tileId][r]) {
            // Choose the current mode
            return r;
        } else {
            // Choose the alias for the mode
            return aliases[tileId][r];
        }

    }

