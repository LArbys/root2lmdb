CXX = c++
CFLAGS = -g -fPIC `root-config --cflags`
LDFLAGS = 
LDLIBS = 

CAFFE_INCDIR = /home/taritree/software/caffe/include

CUDA_INCDIR = /usr/local/cuda-7.5/targets/x86_64-linux/include

LMDB_LIBDIR = /usr/lib/x86_64-linux-gnu
LMDB_INCDIR = /usr/include

PROTOBUF_LIBDIR = /usr/lib/x86_64-linux-gnu
PROTOBUF_INCDIR = /usr/include

ROOTLIBS = `root-config --libs`

CFLAGS += -I$(CAFFE_INCDIR) -I$(LMDB_INCDIR) -I$(PROTOBUF_INCDIR) -I$(CUDA_INCDIR)
LDLIBS += $(ROOTLIBS) -L$(LMDB_LIBDIR) -llmdb -L$(PROTOBUF_LIBDIR) -lprotobuf

all: root2lmdb

root2lmdb.o: root2lmdb.cc
	$(CXX) $(CFLAGS) -c root2lmdb.cc -o root2lmdb.o

root2lmdb: root2lmdb.o
	$(CXX) $(LDLIBS) -o root2lmdb root2lmdb.o $(LDLIBS)
	@rm root2lmdb.o

clean:
	@rm root2lmdb
