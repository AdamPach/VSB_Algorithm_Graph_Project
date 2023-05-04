//
// Created by adamp on 4/23/2023.
//

#include "Node.h"


/**
 * @brief Construct a new Node:: Node object, Set node color to Undiscovered and IndexInComponent on -1 value
 * 
 * @param value Set value of node
 */
Node::Node(int value)
{
    this->value = value;
    this->nodeColor = NodeColor::Undiscovered;
    this->indexInComponent = -1;
}

/**
 * @brief Add new neighbour to the neighbours references
 * 
 * @param newNeighbour New neighbour reference
 */
void Node::CreateEdge(Node * newNeighbour)
{
    this->neighbours.push_back(newNeighbour);
}

/**
 * @brief Get value of the node
 * 
 * @return int Value of node 
 */
int Node::GetValue()
{
    return this->value;
}

/**
 * @brief Get reference to the neighbours vector
 * 
 * @return std::vector<Node *>* Neighbours vector
 */
std::vector<Node *> *Node::GetNeighbours()
{
    return &this->neighbours;
}

/**
 * @brief Returns Color of the node
 * 
 * @return Node::NodeColor 
 */
Node::NodeColor Node::GetColor()
{
    return this->nodeColor;
}

/**
 * @brief Set new color to the node
 * 
 * @param color New color
 */

void Node::SetColor(NodeColor color)
{
    this->nodeColor = color;
}

/**
 * @brief Set index, where is node store in the component
 * 
 * @param newIndex New index
 */

void Node::SetIndex(int newIndex)
{
    this->indexInComponent = newIndex;
}

/**
 * @brief Returns index
 * 
 * @return int Index
 */
int Node::GetIndex() {
    return indexInComponent;
}
