#!/bin/bash

g++ testGen.cpp -o testGen
g++ solution.cpp -o solution

for i in {1..20}
do
    inputFileName="cases/case$i.in"
    outputFileName="cases'case$i.out"
    ./solution inputFileName, outputFileName
done