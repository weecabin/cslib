#include "PIDCtrl.h"

#define print(x)(std::cout<<x)
#define println(x)(std::cout<<x<<"\n")

PIDCtrl::PIDCtrl (float kp,float ki,float kd,int bufferSize)
{
  buffer.SetSize(bufferSize);
  do
    buffer.Push(0);
  while(!buffer.Full());
  sum=0;

  this->kp=kp;
  this->ki=ki;
  this->kd=kd;
}

void PIDCtrl::SetCoefficients(float kp, float ki, float kd)
{
  this->kp=kp;
  this->ki=ki;
  this->kd=kd;
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
  return Correction();
}

float PIDCtrl::Add(float value)
{
  float newEntry = value-target;
  // add a new value and subtract the one to be removed from the buffer
  sum+=newEntry-buffer.Tail();
  buffer.Push(newEntry);
  return Correction();
}

float PIDCtrl::Correction()
{
  return kp*(buffer.Head())+
         ki*sum+
         kd*(buffer.operator[](1)-buffer.Head());
}

float PIDCtrl::Integral()
{
  return ki*sum;
}

  