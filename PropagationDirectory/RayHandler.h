//
// Created by Christos on 4/7/2025.
//

#ifndef PWEOPTIMIZATION_RAYHANDLER_H
#define PWEOPTIMIZATION_RAYHANDLER_H


#include "../GraphDirectory/Graph.h"
#include "SystemState.h"
#include "ModeHandler.h"

class RayHandler {


private:
    Graph* graph;
    std::vector<Ray> newRays;
    SystemState systemState;
    ModeHandler modeHandler;
    double threshold;
    const double C = 299792458;

public:

    RayHandler(Graph& graph){

        this->graph = &graph;
        modeHandler = ModeHandler(graph, 1);
        threshold = pow(10,-12);

    }

    void propagate();

    void reflectRay(Ray& ray);

    void estimateSignal();

    void restoreSystem();


};


#endif //PWEOPTIMIZATION_RAYHANDLER_H
