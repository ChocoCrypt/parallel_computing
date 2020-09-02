#!/bin/bash
for (( i = 1; i < 10000000 ; i=i+100000  )); do
    ./paralelo "$i" >>paralelos.dat
    ./serial "$i" >> seriales.dat
done

echo "terminado"
