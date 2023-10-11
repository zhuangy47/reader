#ifndef __MAIN_H__
#define __MAIN_H__

#include <string>
#include <sstream>


class Main : public CBase_Main {
 private:
  int doneCount;

 public:
  Main(CkArgMsg* msg);
  Main(CkMigrateMessage* msg);

  void done();
};


#endif //__MAIN_H__
