#!/bin/bash

# Tests de algoritmo greedy determinista

# cambiar al directorio del script
# para poder acceder a la carpeta de problemas
cd "$(dirname "$0")"

dataset_dir="n100_m200_l15_a4"
output_file="det_tests.csv"

# eliminar arvhivo csv si ya existe
[ -e "$output_file" ] && rm "$output_file"

# correr tests para cada caso
for problem in $dataset_dir/*.txt
do
    # obtener el numero del problema
    problem_number="${problem%.*}"; problem_number="${problem_number##*_}"
    # obtener costo del problema
    cost=$(./det.out -i $problem)
    # escribir en formato csv
    printf "%d,%d\n" "$problem_number" "$cost" >> "$output_file"
done