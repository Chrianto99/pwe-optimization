//
// Created by Christos on 4/7/2025.
//

#include <cmath>
#include "RayHandler.h"

void RayHandler::propagate() {

    std::vector<Ray> currentRaysCopy = graph->getInputRays();
    std::vector<Ray> currentRays = currentRaysCopy;
    while (!currentRays.empty()) {
        //cout << "New Ray Set of Size:  " << currentRays.size() << endl;

        for (Ray &ray: currentRays) {

            reflectRay(ray);
        }

        currentRays.clear();
        currentRays = newRays;
        newRays.clear();
    }

    estimateSignal();
    restoreSystem();
    //systemState.print();




}

void RayHandler::reflectRay(Ray &ray) {
    Node &currentNode = graph->getNode(ray.getCurrentNodeId());
    Edge &currentEdge = graph->getEdge(ray.getLastEdgeId());

    if (!currentNode.isActive()) {
        int modeChosen = modeHandler.chooseMode(currentNode.getId());
        currentNode.setActiveMode(modeChosen);
        currentNode.setActive(true);
        std::pair<int, int> nodeModePair{currentNode.getId(), modeChosen};
        systemState.addActiveMode(nodeModePair);
    }

    string key = to_string(currentEdge.getId()) + " " + to_string(currentNode.getActiveMode());

    const vector<double> &outputDist = currentNode.getDistFromRoutingTable(key);
    //cout << currentNode.getId()  << " " << currentEdge.getId() << endl;

    //cout << "Next Ray: "  << endl;
   // for (const double &value: outputDist)        cout << "value: " << value;

    for (const double &value: outputDist) {
        int outputEdgeId = (int) floor(value);
        Edge &newEdge = graph->getEdge(outputEdgeId);
        Node &destNode = graph->getNode(newEdge.getDestNodeId());

        double gain = value - outputEdgeId;
        double pathLoss = newEdge.getPathLoss();
        double totalLength = ray.getLength() + newEdge.getLength();
        double totalPower = ray.getPower() * pathLoss * gain;
        //cout << "Total Power : " << totalPower << endl;

        if (totalPower < threshold) {
            //cout << "Ray Discarded" << endl;
            continue;
        }

        if (destNode.getType() == "Rx") {
            //cout << "Ray Reached Receiver" << endl;
            destNode.addToRays(ray);
            continue;
        }

        ray.addEdge(outputEdgeId);
        newRays.emplace_back(totalPower, totalLength, destNode.getId(), ray.getEdges());

    }
}

void RayHandler::estimateSignal() {

    auto &receivers = graph->getReceivers();

    for (Node *nodePtr: receivers) {

        Node receiver = *nodePtr;
        //cout << " receiver rays:" << receiver.getRays().size() << endl;
        int numRays = 0;
        double power = 0, delaySpread = 0;
        double mean_delay = 0, mean_delay_sq = 0;
        double a = 0, d = 0;
        double time = 0;
        for (const Ray &ray: receiver.getRays()) {
            power += ray.getPower();
            time = ray.getLength() / C;


            a += ray.getPower() * time;
            d += ray.getPower() * time * time;
            numRays++;
        }
        mean_delay = a / power;
        mean_delay_sq = d / power;
        delaySpread = sqrt(mean_delay_sq - (mean_delay * mean_delay));
        double tolerance = 1e-14;  // Adjust the tolerance as necessary
        if (abs(delaySpread) < tolerance) delaySpread = 0;

        systemState.addToDelaySpreads(delaySpread);
        systemState.addToPowers(power);
        systemState.addToRayCounts(numRays);
        systemState.setMaxDelaySpread();
        systemState.setMinPower();



    }



}

void RayHandler::restoreSystem() {

    auto &receivers = graph->getReceivers();

    for (Node *receiver : receivers ){
        receiver->clearRays();
    }
    auto &allNodes = graph->getAllNodes();

    for (Node &node : allNodes){
        node.setActive(false);
    }
}




