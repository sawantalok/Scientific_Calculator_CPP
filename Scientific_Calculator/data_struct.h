#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include<cstdio>
#include<cstdlib>


#define array_size 10
#define max_num_len 10
#define array_increment_size array_size
template <typename T>
class Vector
{
    private: 
        T *data;
        char length;
        char currentIndex;

    public: 
        Vector(); 
        ~Vector();
        char push(T value);         // To add new elements in data structure (array)
        char pop();                 // To delete element from array
        char size();                // returns number of elements in the array
        char resize(char size = 0); // resize the array 
        T* at(int index);            //returns address of element
};

template <typename T>
Vector<T>::Vector():currentIndex(0)
{
    data = (T*)malloc(array_size * sizeof(T));
    if(!data)
        length = 0;
    else
        length = array_size;
}

template<typename T>
Vector<T>::~Vector()
{
    free(data);
}

template<typename T>
char Vector<T>::push(T value)
{
    if (currentIndex >= length)
    {
        if(!resize(length + array_increment_size))
            return 0;
    }
    data[currentIndex] = value;
    return ++currentIndex;
}

template<typename T>
char Vector<T>::pop()
{
    if(currentIndex > 0)
    {
        return --currentIndex;
    }
    return 0;
}


template<typename T>
char Vector<T>::size()
{
    return currentIndex;
}

template<typename T>
char Vector<T>::resize(char size)
{
    if(!data) //to check if array exist
    {
        data = (T *)malloc(size * sizeof(T));
    }
    else
    {
        data = (T *)realloc(data, size * sizeof(T)); // if array exist then using realloc
    }

    if(!data)
    {
        length = 0;
        return 0;
    }
    else
    {
        length = size;
        return size;
    }
}

template<typename T>
T* Vector<T>::at(int index)
{
    if(index < 0 || index >= length)
    {
        return NULL;
    }
    return &data[index];
}
#endif
