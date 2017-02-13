#include "engine.h"

int main()
{
  Engine eng;
  eng.addEntity(std::make_shared<Entity>());
  eng.addEntity(std::make_shared<Entity>());

  return 0;
}


//#include <iostream>

//using namespace std;

//#include <set>
//#include <map>
//#include <string>
//#include <memory>

//template<typename T>
//struct Observer
//{
//  std::set<T> handlers;
//  void add(T &handler) { handlers.insert(handler); }
//  void remove(T &handler) { handlers.erase(handler); }
//  //Handle??
//};

//struct Component
//{
//};

//int main(int /*argc*/, char */*argv*/[])
//{
//  cout << "Hello World!" << endl;
//  return 0;
//}
