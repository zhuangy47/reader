#include "main.decl.h"

#include "main.h"
#include "reader.decl.h"


/* readonly */ CProxy_Main mainProxy;
/* readonly */ std::string filename;
/* readonly */ size_t numPartitions;
/* readonly */ size_t fileSize;

Main::Main(CkArgMsg* msg) {
  doneCount = 0;
  delete msg;

  filename = "file";
  if (msg->argc == 2) {
    numPartitions = atoi(msg->argv[1]);
    fileSize = 4294967296;
  } else if (msg->argc == 3) {
    numPartitions = atoi(msg->argv[1]);
    std::stringstream stream(msg->argv[2]);
    stream >> fileSize;
  } else {
    CkPrintf("./charmrun +p# ./reader <#> <total_file_size>\n");
    CkExit();
  }
  CkPrintf("Reading %zu in %zu parts\n", fileSize, numPartitions);
  mainProxy = thisProxy;


  CProxy_Reader readerArray = CProxy_Reader::ckNew(numPartitions);
  readerArray.readFile(-1);
}


Main::Main(CkMigrateMessage* msg) { }

void Main::done() {
  doneCount++;
  if (doneCount >= numPartitions){
    CkPrintf("Exiting\n");
    CkExit();
  }
}


#include "main.def.h"
