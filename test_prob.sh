#!/bin/bash

# Tests de algoritmo greedy probabilistico

# cambiar al directorio del script
# para poder acceder a la carpeta de problemas
cd "$(dirname "$0")"

dataset_dir="n100_m200_l15_a4"
output_file="prob_tests.csv"

# eliminar arvhivo csv si ya existe
[ -e "$output_file" ] && rm "$output_file"

# correr tests para cada caso
for problem in $dataset_dir/*.txt
do
    # obtener el numero del problema
    problem_number="${problem%.*}"; problem_number="${problem_number##*_}"
    for config in {0..100..5}
    do
        # obtener costo del problema
        cost=$(./prob.out -i $problem $config )
        # escribir en formato csv
        printf "%d,%d,%d\n" "$problem_number" "$config" "$cost" >> "$output_file"
    done
done