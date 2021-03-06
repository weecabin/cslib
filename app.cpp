//#define DEBUG
// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)

#include "CircularBuffer2.h"
#include "CircularBuffer.h"
#include "CommandParser.h"
#include "Scheduler.h"
#include "MyStrings.h"
#include "PIDCtrl.h"
#include "Stats.h"
#include "LinkedList.h"
#include "Navigation.h"
#include "Map2.h"
#include "MyDefines.h"
#include <vector>
#include <cstdlib>
#include <cmath>

void CircularBufferTest2();
void CircularBufferTest();
void CommandParserTest();
void SchedulerTest();
void PidCtrlTest();
void DataToolsTest();
void LinkedListTest();
void NavigationTest();
void MapTest();

int main() 
{
  MapTest();
  //NavigationTest();
  //LinkedListTest();
  //DataToolsTest();
  //PidCtrlTest();
  //SchedulerTest();
  //CommandParserTest();
  //CircularBufferTest();
  //CircularBufferTest2();
  return 0;
}

void CircularBufferTest2()
{
  println("\n******** CircularBufferTest2 ********");
  CircularBuffer2<float> cb(5);
  println("buffer size set to 5");
  println("Add one and print it out");
  cb.Push(1);
  cb.Print();
  println("Add 10 more (2-11) and print the buffer out");
  for (int i=0;i<10;i++)
    cb.Push(2+i);
  cb.Print();
  println("print head");
  println(cb.Head());
  println("print tail");
  println(cb.Tail());
  println("insert 99 at 2");
  cb.Insert(2,99);
  cb.Print();
  println("delete value at 2");
  cb.Delete(2);
  cb.Print();
  println("delete value at 3");
  cb.Delete(3);
  cb.Print();
  println("delete value at 0");
  cb.Delete(0);
  cb.Print();
  println("insert 99 at 0");
  cb.Insert(0,99);
  cb.Print();
  println("pop head");
  println(cb.PopHead());
  println("list the buffer after the pop");
  cb.Print();
  
  println("pop tail");
  println(cb.PopTail());
  println("list the buffer after the pop");
  cb.Print();
  
  println("clear");
  cb.Clear();
  println("try to access the empty list");
  try
    {
      println(cb[1]);
    }
  catch (...)
    {
      println("oops, caught an exception");
    }
  println("print the empty list cb.Print()");
  cb.Print();
  println("add 1-5");
  for (int i = 1;i<6;i++)
    cb.Push(i);
  cb.Print();
  println("retrieve an index >= size, it should wrap");
  print("cb[5]=");println(cb[5]);
  print("cb[6]=");println(cb[6]);
  print("cb[7]=");println(cb[7]);
  
  println("pop head");
  println(cb.PopHead());
  println("list the buffer after the pop");
  cb.Print();
  
  println("pop tail");
  println(cb.PopTail());
  println("list the buffer after the pop");
  cb.Print();
}

// Map keys...
const char key1[] = "k1";
const char key2[] = "k2";
const char key3[] = "k3";
const char key4[] = "k4";
const char key5[] = "k5";
void ListCallback(const char* key,float value)
{
  print("key:");print(key);print("=");println(value);
}
void MapTest()
{
  println("\n******** MapTest ********");
  println("Add (key1,100),(key2,200),(key3,300)");
  Map2<const char*,float> m;
  m.Add(key1,100);
  println("Get a key value with only one in the map");
  print("key1: ");println(m.Value(key1));
  println("Add two more, then get them all");
  m.Add(key2,200);
  m.Add(key3,300);
  print("key1/key2: ");println(m.Value(key1)/m.Value(key2));
  println("m.Print()");
  m.Print();
  println("clear the map, then add 5 with AddSorted in the following order...");
  println("key5,key4,key3,key2,key1");
  m.Clear();
  println("m.Clear() completed");
  m.AddSorted(key5,500);
  m.AddSorted(key4,400);
  m.AddSorted(key3,300);
  m.AddSorted(key2,200);
  m.AddSorted(key1,100);
  println("m.Print()");
  m.Print();
  println("m.List");
  m.List(ListCallback);

  println("clear the map, then add 5 with AddSorted in the following order...");
  println("key1,key4,key3,key2,key5");
  m.Clear();
  println("m.Clear() completed");
  m.AddSorted(key1,100);
  m.AddSorted(key4,400);
  m.AddSorted(key3,300);
  m.AddSorted(key2,200);
  m.AddSorted(key5,500);
  println("m.Print()");
  m.Print();
  println("m.List");
  m.List(ListCallback);
  
  println("m.GetValue(2)");
  println(m.GetValue(2));
  println("m.GetValue(0)");
  println(m.GetValue(0));

  println("create a map with a vector as the value");
  Map2<float,vector<float>> mf;
  vector<float> v{1.1,2.2,3.3};
  mf.Add(.1,v);
  println(mf[.1][0]);

  println("Create a map with a size limit of 5 and add 10 elements");
  Map2<int,float> ml(5);
  for (int i=0;i<10;i++)
  {
    ml.AddSorted(i,i*1.1);
  }
  ml.Print();
}

void NavigationTest()
{
  println("\n******** NavigationTest ********");
  
  print("HeadingError(5.1,355.2) (target,current) = ");
  println(HeadingError(5.1,355.2));

  print("HeadingError(730,710) = ");
  println(HeadingError(730,710));

  print("HeadingError(710,730) = ");
  println(HeadingError(710,730));

  print("HeadingError(710,710) = ");
  println(HeadingError(710,710));

  print("FixHeading(0) = ");
  println(FixHeading(0));
  
  print("FixHeading(370) = ");
  println(FixHeading(370));
  
  print("FixHeading(-10) = ");
  println(FixHeading(-10));
  
  print("FixHeading(180) = ");
  println(FixHeading(180));

  print("FixHeading(730) = ");
  println(FixHeading(730));

  print("FixHeading(710) = ");
  println(FixHeading(710));
}

void LinkedListTest()
{
  println("\n******** LinkedListTest ********");
  LinkedList<float> ll;
  ll.Add(1.1);
  
  // make sure list works with only one value in
  println("GetNext(true)...");
  println(ll.GetNext(true));
  while(!ll.EndNext())
    println(ll.GetNext());
  
  println("GetPrev(true)...");
  println(ll.GetPrev(true));
  while(!ll.EndPrev())
    println(ll.GetPrev());

  println("Add two more terms");
  ll.Add(2.2);
  ll.Add(3.3);

  println("Traverse up...");
  // This resets the iterator, and returns the first value
  println(ll.GetNext(true));
  while(!ll.EndNext())
    println(ll.GetNext());
  
  println("Traverse down...");
  // This resets the iterator, and returns the last value
  println(ll.GetPrev(true));
  while(!ll.EndPrev())
    println(ll.GetPrev());

  for (float f=4.0;f<10;f+=.5)
    ll.Add(f);
  
  println("LinkedList.Print()");
  ll.Print();
  
  println("Iterator... up...");
  for(auto itr = ll.Head(); itr != ll.End(); ++itr)
    std::cout << *itr << std::endl;

  println("Iterator... down...");
  for(auto itr = ll.Tail(); itr != ll.End(); --itr)
    std::cout << *itr << std::endl;
  
  println("Remove a node ll.erase(itr)");
  auto itr = ll.Head();
  ++itr;
  ll.erase(itr);
  println("ll.Print(up)");
  ll.Print();
  println("ll.Print(down)");
  ll.Print(false);
  
  println("Insert 99 at 3.3");
  itr = ll.FindNext(3.3);
  ll.insert(itr,99);
  println("ll.Print(up)");
  ll.Print();
  println("ll.Print(down)");
  ll.Print(false);
  
  println("find ll.FindNext(99)");
  itr = ll.FindNext(99);
  if (itr!=ll.End())
  {
    print("found ");println(*itr);
  }

  println("Iterator... up...");
  for(auto itr = ll.Head(); itr != ll.End(); ++itr)
    std::cout << *itr << std::endl;
  
  println("Iterator... down...");
  for(auto itr = ll.Tail(); itr != ll.End(); --itr)
    std::cout << *itr << std::endl;

  println("From Head, *itr.next()...");
  itr = ll.Head();
  println(*itr.next());
  println("*itr.next(3)...");
  println(*itr.next(3));
  
  println("*itr.next(99), 0 indicates end...");
  println(*itr.next(99));
  println("*itr.prev()...");
  println(*itr.prev());
  println("*itr.findprev(6)...");
  println(*itr.findprev(6));
  println("*itr.findnext(9)...");
  println(*itr.findnext(9));

  println("list it before destructor executes");
  ll.Print();
}

void DataToolsTest()
{
  println("\n******** StatsTest ********");
  Stats stats;
  println("Adding 1-10");
  for (float f=1;f<=10;f+=1)
  {
    stats.Add(f);      
  }
  stats.Print();
  stats.Clear();

  println("\nAdding sin(0-PI)");
  for (float a=0;a<M_PI;a+=.1)
    stats.Add(sin(a));
  stats.Print();
  /*
  print("Min: ");println(stats.Min());
  print("Max: ");println(stats.Max());
  print("Delta: ");println(stats.Delta());
  print("Sum: ");println(stats.Sum());
  print("Mean: ");println(stats.Mean());
  print("Variance: ");println(stats.Variance());
  print("stdev: ");println(stats.Stdev());
  */
}

// PID testing
void PidCtrlTest()
{
  println("\n******** PidCtrlTest ********");
  println("buffer length set to 10, adding 15");
  PIDCtrl pid(1,1,0,1,10);
  println("Set target to 5");
  pid.Target(5);
  srand(2);
  float r = float(rand()%1000)/1000.0;
  for (int i=0;i<15;i++)
  {
    pid.Add(i*1.01);
    if (pid.BufferIsFull())
      println("buffer full");
    else
      println("buffer not full");
  }
  pid.Print();
  print("Correction: ");println(pid.Correction());
  print("delta: ");println(pid.DeltaError());
}

// Scheduler Testing
int count1=0;
void task1()
{
  cout<<"Task1: "<<++count1<<"\n";
}

int count2=0;
void task2()
{
  cout<<"\tTask2: "<<++count2<<"\n";
}

int count3=0;
void task3()
{
  cout<<"\t\tTask3: "<<++count3<<"\n";
}
int count4=0;
void task4()
{
  cout<<"\t\t\tTask4: "<<++count4<<"\n";
}
int idle=0;
void idleTask()
{
  print("idleTask: ");println(++idle);
  MyTime t;
  // don't want to fill the screen with idleTask
  do{}while(t.millis()<20);   
}
void SchedulerTest()
{
  std::cout<<"\n******** SchedulerTest ********\n";
  count1=count2=count3=count4=0;
  Scheduler s(5);
  // using FunctionTask as the idle task for convenience here
  // the runtime parameter won't be used, but it's needed
  s.IdleTask(new FunctionTask(idleTask,1));
  s.AddTask(new FunctionTask(task1,.1));
  s.AddTask(new FunctionTask(task2,.2));
  s.AddTask(new FunctionTask(task3,.3));
  s.AddTask(new FunctionTask(task4,.4));
  s.Run(5);
}

// CommandParser testing...
void GetHeading(char *paramstr)
{
  std::cout << "In GetHeading\n";
}

void SetHeading(char *paramstr)
{
  float floats[1]={0};
  ToFloat(paramstr,floats);
  
  int ints[1];
  ToInt(paramstr,ints);
  std::cout << "In SetHeading("<<floats[0]<<")\n";
  std::cout << "int param: "<<ints[0]<<"\n";
}
void SetPid(char *paramstr)
{
  float floats[3]={0,0,0};
  ToFloat(paramstr,floats);
  std::cout << "In SetPid("<<floats[0]<<","<<floats[1]<<","<<floats[2]<<")\n";
}

void CommandParserTest()
{
  std::cout<<"\n***** CommandParser Testing *****\n";

  //Iterator<const char *,CommandHandler*,LessChar,EqualChar> test(new Map1Node<const char *,CommandHandler*>);
  
  CommandParser p;
  p.Add(GetHeading,GETHEADING);
  p.Add(SetHeading,SETHEADING);
  p.Add(SetPid,SETPID);
  p.Print();
  char cmd1[] = "GetHeading()";
  p.Execute(cmd1);
  char cmd2[] = "SetHeading(60.1)";
  p.Execute(cmd2);
  char cmd3[]= "SetPid(1.1,2.2,3.3)";
  p.Execute(cmd3);
  char cmd4[]= "SetPid(1.1,2.2)";
  p.Execute(cmd4);
  char cmd5[]= "SetPid(1.1,2.2,5)";
  p.Execute(cmd5);
}

void CircularBufferTest()
{
  std::cout << "\n***** CircularBuffer Testing *****\n";
  std::cout << "Created buffer of 10 floats, then added more than 10\n";
  CircularBuffer<float> cb(10); 
  //cb.SetSize(10);
  for (float i=1.1;i<20;i+=1.1)
  {
    cb.Push(i);
    if (cb.Full())println("Buffer Is Full");
  }
  println("print the buffer with .Print()");
  cb.Print();
  std::cout <<"delete the third entry\n";
  cb.Delete(2);
  cb.Print();
}
