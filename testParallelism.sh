if test -f "a.out"; then
    rm a.out
fi

export OMP_NUM_THREADS=4
for dim in 128 512 1024 2048
do
    gcc-7.5.0 ./src/main.c ./src/ex1.c -DN=$dim -DPRINT -fopenmp -DCOMPILATION_NOTES="\"TEST_PARALLELISM;4\""
    ./a.out
done

source graphEnv/bin/activate
python3 ./src/pytonCharts.py
deactivate