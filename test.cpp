/*
  Test program for boost::mpi

  Compile command:
  mpicxx -I/boost/include -L/boost/lib -o mpi_test mpi_test.cpp -lboost_mpi -lboost_serialization -std=c++11
  Execuiton command:
  /usr/local/openmpi-2.0.1/bin/mpirun -np <num of slot> -mca btl ^openib ./mpi_test
*/

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/string.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>


namespace bmpi = boost::mpi;

int main(int argc, char** argv) {
  bmpi::environment env(argc, argv);
  bmpi::communicator world;
  int name_len = 6;
  char name[name_len];
  MPI_Get_processor_name(name, &name_len);
  printf("%s : rank = %d, size = %d\n", name, world.rank(), world.size());

  // gather
  usleep(300000);
  std::vector<std::string> testvec;
  if (world.rank() == 0) {
    std::cout << "===== test for bmpi::gather() =====" << std::endl;
    testvec.push_back("--- rank0 teststr ---");
  }
  std::string rankstr = std::to_string(world.rank());
  bmpi::gather(world, rankstr, testvec, 0);
  if (world.rank() == 0) {
    std::cout << "bmpi::gather() test result" << std::endl;
    for (std::string s : testvec) std::cout<< "  " << s;
    std::cout << std::endl;
  }

  // broadcast
  usleep(300000);
  std::string s;
  if (world.rank() == 0) {
    std::cout << "===== test for bmpi::broadcast() =====" << std::endl;
    std::cout << "input: test string = ";
    std::cin >> s;
  }
  bmpi::broadcast(world, s, 0);
  std::cout << "   rank = " << world.rank()
            << ", s = " << s << std::endl;

  return 0;
}
