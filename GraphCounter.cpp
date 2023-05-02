//
// Created by adamp on 4/24/2023.
//

#include <queue>
#include <iostream>
#include <thread>
#include "GraphCounter.h"

GraphCounter::GraphCounter(std::vector<Node *> *component)
{
    this->Component = component;
    results = new int[Component->size()];

    for(int i = 0; i < Component->size(); i++)
    {
        results[i] = 0;
    }
}

GraphCounter::~GraphCounter()
{
    delete[] results;
}

void GraphCounter::Count()
{
    int * distances = new int[Component->size()];

    for(int i = 0; i < Component->size(); i++)
    {
        distances[i] = -1;
    }

    int eccentricity = BFSGetEccentricity(Component->at(0), distances);
    MaxEccentricity = eccentricity;
    MinEccentricity = eccentricity;

    for(int i = 1; i < Component->size(); i++)
    {
        for(int j = 0; j < Component->size(); j++)
        {
            distances[j] = -1;
        }

        eccentricity = BFSGetEccentricity(Component->at(i), distances);
        CheckMinAndMax(eccentricity);
        if(i % 100 == 0)
        {
            std::cout << i << std::endl;
        }
    }
}

int GraphCounter::BFSGetEccentricity(Node * root, int * distances)
{
    int highestDistance = -1;
    int tmp_size = Component->size();

    distances[root->GetIndex()] = 0;
    std::queue<Node *> queue;
    queue.push(root);

    while (!queue.empty())
    {
        Node * currentNode = queue.front();
        queue.pop();

        for(Node * searchedNode : *(currentNode->GetNeighbours()))
        {
            if(distances[searchedNode->GetIndex()] == -1)
            {
                int tmp_distance = distances[currentNode->GetIndex()] + 1;
                distances[searchedNode->GetIndex()] = tmp_distance;
                queue.push(searchedNode);
                if(highestDistance < tmp_distance)
                    highestDistance = tmp_distance;
            }
        }
    }
    //delete[] distances;
    return highestDistance;
}

void GraphCounter::CheckMinAndMax(int newValue)
{
    if(MaxEccentricity < newValue)
        MaxEccentricity = newValue;
    else if (MinEccentricity > newValue)
        MinEccentricity = newValue;
}

void GraphCounter::PrintResults()
{
    std::cout << "-------------------Counter Results-------------------" << std::endl;
    std::cout << "Radius: " << MaxEccentricity << std::endl;
    std::cout << "Diameter: " << MinEccentricity<< std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}

void GraphCounter::ThreadEccentricity(Node *root, GraphCounter * counter, int * distances)
{
    counter->results[root->GetIndex()] = counter->BFSGetEccentricity(root, distances);
}

void GraphCounter::MultiThreadCount()
{
    std::thread threads[NUM_OF_THREADS];
    int index = 0;
    int size_tmp = Component->size() * NUM_OF_THREADS;
    int * distances = new int[size_tmp];

    while(index < Component->size())
    {
        for(int i = 0; i < size_tmp; i++)
            distances[i] = -1;

        int numberOfCyclus = NUM_OF_THREADS;
        for(int i = 0; i < numberOfCyclus; i++)
        {
            if(index >= Component->size())
            {
                numberOfCyclus = i;
                break;
            }
            threads[i] = std::thread(ThreadEccentricity, Component->at(index), this, distances + i * Component->size());
            index++;
        }

        for(int i = 0; i < numberOfCyclus; i++)
        {
            threads[i].join();
        }

        std::cout << index << std::endl;
    }

    delete[] distances;

    MaxEccentricity = results[0];
    MinEccentricity = results[0];
    for(int i = 1; i < Component->size(); i++)
    {
        CheckMinAndMax(results[i]);
    }
}

