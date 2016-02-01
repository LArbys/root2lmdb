#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "lmdb.h"
#include "caffe/common.hpp"
#include "caffe/proto/caffe.pb.h" // datum definition
#include "caffe/util/format.hpp"

#include "TFile.h"
#include "TChain.h"

void parse_inputlist( std::string filename, std::vector< std::string >& inputlist ) {

  std::ifstream infile( filename.c_str() );
  char buffer[5120];
  std::string fname;
  std::string lastname = "";
  while ( !infile.eof() ) {
    infile >> buffer;
    fname = buffer;
    if ( fname!="" && fname!=lastname ) {
      inputlist.push_back( fname );
      lastname = fname;
    }
  }
  
}

int main( int narg, char** argv ) {

  std::string infile = argv[1];
  std::string outdb = argv[2];

  std::vector<std::string> inputlist;
  parse_inputlist( infile, inputlist );


  // For each event we do a few things: 
  // (1) Calculate mean of all images
  // (2) put data into datum object
  // (3) store that object into an lmdb database
  // (4) make the training list with labels

  // Load ROOT Tree
  std::cout << "[LOAD TREE]" << std::endl;
  TChain* bbtree = new TChain("yolo/bbtree");
  int nfiles = 0;
  for ( std::vector<std::string>::iterator it=inputlist.begin(); it!=inputlist.end(); it++ ) {
    bbtree->Add( (*it).c_str() );
    std::cout << " " << nfiles << ": " << (*it) << std::endl;
    nfiles++;
  }
  
  char label[100];
  bbtree->SetBranchAddress("label",label);

  int entry = 0;
  unsigned long bytes = bbtree->GetEntry(entry);
  while ( bytes!=0 ) {
    std::cout << "Entry " << entry << ": " << label << std::endl;
    entry++;
    bytes = bbtree->GetEntry(entry);
    if ( entry>100 )
      break;
  }


  return 0;
}
