# $1: file neme, $2: node num

echo "num of node = $2"
mpirun --hostfile hostfile -np $2 ./$1
