#include "reader.decl.h"

#include "reader.h"
#include "main.decl.h"


extern /* readonly */ CProxy_Main mainProxy;
extern /* readonly */ std::string filename;
extern /* readonly */ size_t numPartitions;
extern /* readonly */ size_t fileSize;

Reader::Reader() { }

Reader::Reader(CkMigrateMessage *msg) { }


void Reader ::readFile(int from) {
  size_t result;
  char * buffer;
  std::string file_path = "./testfilefolder" + std::to_string(thisIndex) + "/" + filename + std::to_string(thisIndex);
  size_t buffer_size = fileSize / numPartitions;
  // size_t buffer_size = 0;
  CkPrintf("File_path from %d, %s, reading %zu bytes\n", thisIndex, file_path.c_str(), buffer_size);
  FILE* fp = fopen(file_path.c_str(), "r");
  if (fp == NULL) {
    CkPrintf("How did this happen??");
    CkExit();
  }
  fseek(fp , 0 , SEEK_SET);
  rewind(fp);
  buffer = (char*) malloc(sizeof(char) * buffer_size);
  if (buffer == NULL) {
    CkPrintf("buffer is NULL, exiting");
    CkExit();
  }
  double read_time = CkWallTimer();
  // CkPrintf("Init time from %d, %f\n", thisIndex, read_time);
  result = fread(buffer, 1, buffer_size, fp);
  read_time = CkWallTimer() - read_time;
  CkPrintf("Read time from %d: %f\n", thisIndex, read_time);
  fclose(fp);
  free(buffer);
  if (result != buffer_size) {
    CkPrintf("read failed, exiting");
    CkExit();
  }
  mainProxy.done();
}

#include "reader.def.h"
