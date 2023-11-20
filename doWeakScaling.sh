if test -f "a.out"; then
    rm a.out
fi
echo "Doing Weak Scaling"
for i in {1..5}
do
    echo "- $i -------------------"
    echo "Serial Code"
    gcc-7.5.0 ./src/main.c ./src/ex1.c -DCOMPILATION_NOTES="\"WEAK_SCALING;SERIAL_CODE\"" -DN=32 -DPRINT
    ./a.out
    echo "-------------------"
    echo ""
    for i in 1 2 4 8 16 32 64
    do  
        echo "Parallel Code with $i threads"
        echo "-------------------"
        dim=$((32*i))
        gcc-7.5.0 ./src/main.c ./src/ex1.c -DCOMPILATION_NOTES="\"WEAK_SCALING;$i\"" -fopenmp -DN="$dim" -DPRINT
        export OMP_NUM_THREADS=$i
        ./a.out
        echo "-------------------"
        echo ""
    done
done

source pytonWeakScalingCharts.sh
echo "Done Weak Scaling"
echo "-------------------"