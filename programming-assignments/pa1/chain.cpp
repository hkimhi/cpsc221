#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
/* YOUR CODE HERE */
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    Node *newNode = new Node(ndata);
    newNode->next = head_;
    walk(head_, length_)->next = newNode;
    length_ += 1;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    if(i == j) return;

    if(j < i) {
        //ensure i is always the smaller index
        int temp = i;
        i = j;
        j = temp;
    }

    Node *node1prev = walk(head_, i-1);
    Node *node2prev = walk(node1prev, j-i-1);

    //node1prev is the node BEFORE i
    //node2prev is the node BEFORE j
    Node *nodeI = node1prev->next;
    Node *nodeJ = node2prev->next;

    Node *temp = nodeI->next;
    nodeI->next = nodeJ->next;
    nodeJ->next = temp;

    node1prev->next = nodeJ;
    node2prev->next = nodeI;
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    Node *curr = head_->next;
    Node *prev = nullptr;
    Node *next = nullptr;

    while(curr != head_) {
        next = curr->next;
        curr->next = prev;
        
        prev = curr;
        curr = next;
    }

    head_->next = prev;
}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
/* YOUR CODE HERE */
}

/**
 * Destroys ALL dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    Node *toDelete = head_;
    Node *currDelete = nullptr;

    while(toDelete->next != nullptr) {
        currDelete = toDelete;
        toDelete = toDelete->next;

        delete currDelete;
        currDelete = nullptr;
    }
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    length_ = 0;
    height_ = other.height_;
    width_ = other.width_;

    head_ = new Node(other.head_->data);
    head_->next = head_;

    Node *otherCurr = other.head_->next;

    while(otherCurr != other.head_) {
        insertBack(otherCurr->data);
        otherCurr = otherCurr->next;
    }
}
