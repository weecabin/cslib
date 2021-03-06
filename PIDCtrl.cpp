#include "PIDCtrl.h"
#include <cmath>

#include "MyDefines.h"

PIDCtrl::PIDCtrl (float kp,float ki,float kd,float ts, int bufferSize)
{
  this->bufferSize=bufferSize;
  buffer.SetSize(bufferSize);
  do
    buffer.Push(0);
  while(!buffer.Full());
  sum=0;
  dataIn=0;

  this->kp=kp;
  this->ki=ki;
  this->kd=kd;
  this->ts=ts;
}

void PIDCtrl::SetCoefficients(float kp, float ki, float kd)
{
  this->kp=kp;
  this->ki=ki;
  this->kd=kd;
  do
    buffer.Push(0);
  while(!buffer.Full());
  sum=0;
  dataIn=0;
}

void PIDCtrl::SetSampleInterval(float ts)
{
  this->ts=ts; 
}

float PIDCtrl::GetKp()
{
  return kp;
}
float PIDCtrl::GetKi()
{
  return ki;
}
float PIDCtrl::GetKd()
{
  return kd;
}
float PIDCtrl::GetTs()
{
  return ts;
}

bool PIDCtrl::BufferIsFull()
{
  //std::cout<<"dataIn:"<<dataIn<<"bufferSize:"<<bufferSize<<"\n";
  return dataIn>=bufferSize;
}

void PIDCtrl::Print()
{
  for (int index=0;index<buffer.ValuesIn();index++)
  {
    print(buffer.operator[](index));
    print(" ");
  }
  println("");
}

void PIDCtrl::Target(float target)
{
  this->target=target;
}

float PIDCtrl::NextError(float error)
{
  sum+=error-buffer.Tail();
  buffer.Push(error);
  dataIn++;
  return Correction();
}

float PIDCtrl::DeltaError()
{
  float max=0;
  for (int i=0;i<buffer.ValuesIn();i++)
    for (int j=i+1;j<buffer.ValuesIn()-1;j++)
    {
      float test = std::abs(buffer[i]-buffer[j]);
      if (test>max)
        max=test;
    }
  return max;
}

float PIDCtrl::Add(float value)
{
  float newEntry = value-target;
  // add a new value and subtract the one to be removed from the buffer
  sum+=newEntry-buffer.Tail();
  buffer.Push(newEntry);
  dataIn++;
  return Correction();
}

float PIDCtrl::Correction()
{
  return kp*(buffer.Head())+
         ki*sum*ts+
         kd*(buffer.operator[](1)-buffer.Head()/ts);
}

float PIDCtrl::Integral()
{
  return ki*sum*ts;
}

  