#!/bin/bash
echo "$0 $1 $2 $3"
for (( c=0; c<3; c++ ))
do
    time ./kruskal.out $1 $2 $3 $4
    echo "Pulsa cualquier tecla para continuar: "
    read aux
done