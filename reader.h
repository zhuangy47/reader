#ifndef __READER_H__
#define __READER_H__

#include <string>
#include <fstream>

class Reader : public CBase_Reader {
 public:
  Reader();
  Reader(CkMigrateMessage *msg);
  void readFile(int from);
};


#endif //__READER_H__
