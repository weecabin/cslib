#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <map>
#include <cstring>
#include <cstdlib>

using namespace std;

void ToFloat(char *params, float floats[])
{
  char *token = strtok(params,",");
  int i = 0;
  while (token != NULL)
    {
    floats[i++]=atof(token);
    token = strtok(NULL,",");
    }
}

class CommandHandler
{
  public:
  CommandHandler(void (*executer)(char *),const char* cmd)
  {
    this->executer=executer;
    this->cmd=cmd;
  }
  void Execute(char *cmdLine)
  {
    executer(cmdLine);
  }
  private:
  void (*executer)(char *);
  const char* cmd;
};

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcasecmp(a, b) < 0;
   }
};

class CommandParser
{
  public:
  CommandParser()
  {
  }
  ~CommandParser()
  {
    map<const char*,CommandHandler *>::iterator it;
    for (it = cmdMap.begin(); it != cmdMap.end(); it++)
    {
      delete it->second;
    }
  };
  void Add(void (*executer)(char *),const char* cmd)
  {
    CommandHandler *handler=new CommandHandler(executer,cmd);
    cmdMap.insert({cmd,handler});
  }
  bool Execute(char *cmdLine)
  {
    int openParen=0;
    int closeParen=0;
    int lineLen = strlen(cmdLine);
    // locate parens "command(param1,param2...)"
    // replace commas with 0, to facilitate param conversions
    for(int i=0;i<lineLen;i++)
    {
      if (cmdLine[i]==0)return false; // no cmd string
      if (cmdLine[i]=='(')
      {
        openParen=i;
        cmdLine[i]=0;
      }
      else if (cmdLine[i]==')')
      {
        cmdLine[i]=0;
        break;
      }
    }
    if (cmdMap.count(cmdLine)>0) // the key esists
    {
      if (openParen==0 || (openParen+1==closeParen))
      {
        // no parameters
        char nothing[]="";
        cmdMap[cmdLine]->Execute(nothing);
      }
      else
      {
        cmdMap[cmdLine]->Execute(&cmdLine[openParen+1]);
      }
      return true;
    } 
    else
    {
      //std::cout<<"key not found\n";
      //std:cout<<"size:";std::cout<<cmdMap.size();
      return false;
    }
  }
  private:
  map<const char*,CommandHandler *, cmp_str> cmdMap;
};

#endif