mpicxx -I/boost/include -L/boost/lib -o $1.o $1.cpp -lboost_mpi -lboost_serialization -DBOOST_MPI_HOMOGENIUS -std=c++11
