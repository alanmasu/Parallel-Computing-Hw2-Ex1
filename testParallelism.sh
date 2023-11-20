if test -f "a.out"; then
    rm a.out
fi

gcc-7.5.0 ./src/main.c ./src/ex1.c -DN=512 -DPRINT -fopenmp 
export OMP_NUM_THREADS=1
./a.out
export OMP_NUM_THREADS=2
./a.out
export OMP_NUM_THREADS=4
./a.out