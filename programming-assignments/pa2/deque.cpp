//TODO: Error with resizing in pushpopL, either doesn't when it should,
// or doens't when it shouldn't... can't tell from the test output...
// more likely is that i'm not resizing early enough



/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque()
{

    data = vector<T>();
    n1 = 0;
    n2 = 0;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T retItem = data.at(n1);
    n1++;

    if ((n2 - n1) <= n1)
    {
        vector<T> resizedData = vector<T>();
        for (int i = n1; i < n2; i++)
        {
            resizedData.push_back(data.at(i));
        }
        data = resizedData;
        n1 = 0;
        n2 = data.size();
    }

    return retItem;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T retItem = data.at(n2 - 1);
    data.pop_back();
    n2--;

    if ((n2 - n1) <=  n1)
    {
        vector<T> resizedData = vector<T>();
        for (int i = n1; i < n2; i++)
        {
            resizedData.push_back(data.at(i));
        }
        data = resizedData;
        n1 = 0;
        n2 = data.size();
    }

    return retItem;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data.at(n1);
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data.at(n2 - 1);
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return (n1 == n2);
}
