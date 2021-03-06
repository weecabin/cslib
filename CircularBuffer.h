
#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include "MyDefines.h"

/*
CircularBuffer
Implements a buffer with a maximum size of size elements.
from the outside, new elements appear to be added at the beginning of
the buffer, and older elements are pushed down. if the newest element 
exceeds the buffer size, the oldest will be removed.
the array operator [0] returns the most recent addition, or the Head of the buffer.
*/

template <class T> class CircularBuffer
{
  public:
  CircularBuffer()
  {
    SetSize(1);
  }
  CircularBuffer(int size)
  {
    SetSize(size);
  }
  ~CircularBuffer()
  {
    //std::cout<<"in ~CircularBuffer\n";
    if (buffer!=0)
      delete [] buffer;
  }
  void SetSize(int size)
  {
    if(buffer!=nullptr)delete []buffer;
    buffer=new T[size];
    Clear();
    end=&buffer[size-1];
    this->size=size;
    valuesIn=0;
  }
  void Clear()
  {
    valuesIn=0;
    current=buffer-1;
  }
  void Print()
  {
    if (valuesIn==0)
    {
      std::cout << "Empty\n";
      return;
    }
    for (int i=0;i<valuesIn;i++)
      { 
        std::cout << i;
        std::cout << ": ";
        std::cout << (*this)[i];
        std::cout << "\n";
      }
  }
  bool Empty()
  {
    return valuesIn==0;
  }
  bool Full()
  {
    return valuesIn>=size;
  }
  void Push(T value)
  {
    if (++valuesIn>size)
      valuesIn=size;
    if (current==end)
      current=buffer-1;
    *++current=value;
  }
  T Head()
  {
    return (*this)[0];
  }
  T Tail()
  {
    return (*this)[valuesIn-1];
  }
  int ValuesIn()
  {
    return valuesIn;
  }
  void Insert(int d,T value)
  {
    if (d==0)
    {
      Push(value);
      return;
    }
    if (d==valuesIn)return; // can't insert at the end
    for (int i=valuesIn==size?valuesIn-2:valuesIn-1;i>=d;i--)
    {
      //std::cout << *Ptr(i-1);
      //std::cout << "\n";
      *Ptr(i+1)=*Ptr(i);
    }
    *Ptr(d)=value;
    if (valuesIn==size)return;
    valuesIn++;
  }
  T Delete(int d)
  {
    T *temp=Ptr(d);
    for (int i=d;i<valuesIn-1;i++)
    {
      *Ptr(i)=*Ptr(i+1);
    }
    valuesIn--;
    return *temp;
  }
  T operator[](int i)
  {
    if (i>=size || valuesIn==0)
      return *invalid;
    return *Ptr(i);
  }
  private:
  T* Ptr(int i)
  {
    T *temp=current-i;
    if (temp>=buffer)
      return temp;
    temp=end-(buffer-temp)+1;
    return temp;
  }
  T *current=nullptr;
  T *buffer=nullptr;
  T *end=nullptr;
  T *invalid=nullptr; 
  int size;
  int valuesIn;
};
#endif