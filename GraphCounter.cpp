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
    MaxEccentricity = -1;
    MinEccentricity = -1;
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
    int eccentricity = 0;//BFSGetEccentricity(Component->at(0));
    MaxEccentricity = eccentricity;
    MinEccentricity = eccentricity;

    for(int i = 1; i < Component->size(); i++)
    {
        //eccentricity = BFSGetEccentricity(Component->at(i));
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
    int result = counter->results[root->GetIndex()];
}

void GraphCounter::MultiThreadCount()
{
    std::thread threads[1000];
    int index = 0;
    int size_tmp = Component->size() * 1000;
    int * distances = new int[size_tmp];

    while(index < Component->size())
    {
        for(int i = 0; i < size_tmp; i++)
            distances[i] = -1;

        int numberOfCyclus = 1000;
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
        if(MaxEccentricity < results[i])
            MaxEccentricity = results[i];
        if(MinEccentricity > results[i])
            MinEccentricity = results[i];
    }
}

