# $1: file neme, $2: node num
echo "num of node = $2"
/usr/local/openmpi-2.0.1/bin/mpirun --mca btl ^openib --hostfile ~/hostfile -np $2 ./$1
