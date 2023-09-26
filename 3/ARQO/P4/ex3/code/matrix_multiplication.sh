#!/bin/bash

# initialize variables
P=6 # (13 mod 8) + 1 = 5 + 1 = 6
Ninicio=$((512+P))
Npaso=64
Nfinal=$((1024+512+P))
ntimes=5 # how many times to call the programs

#initialize threads
Tinicio=1
Tpaso=1
Tfinal=4

# arrays to accumulate the data about the times
declare -A serial=()
declare -A times=()
declare -A avgSerie=()

for ((T=Tinicio ;  T <= Tfinal ; T += Tpaso)) do
	rm -rf multiplication_loop$T.dat speedUp_$T.dat
	touch multiplication_loop$T.dat
	touch speedUp_$T.dat
don
# initialize to 0
for ((N=Ninicio ;  N <= Nfinal ; N += Npaso)) do
	echo "Serial | Size $N..."
	sumSerie=0
	for ((i = 0 ; i < ntimes ; i++)) do
		timeSerie=$(./matrixMultiplicationSerie $N | grep 'time' | awk '{print $3}')
		sumSerie=$(echo "$sumSerie $timeSerie" | awk '{print $1 + $2}')
	done
	avgSerie[$N]=$(echo "$sumSerie $ntimes" | awk '{print $1 / $2}')
done

for ((T=Tinicio ;  T <= Tfinal ; T += Tpaso)) do
	echo "$T threads..."
	for ((N=Ninicio ;  N <= Nfinal ; N += Npaso)) do
		echo "Size $N..."

		sumLoop='0'

		for ((i = 0 ; i < ntimes ; i++)) do
			timeLoop=$(./matrixMultiplicationLoop3 $T $N | grep 'time' | awk '{print $3}')
			sumLoop=$(echo "$sumLoop $timeLoop" | awk '{print $1 + $2}')
		done
		avgLoop=$(echo "$sumLoop $ntimes" | awk '{print $1 / $2}')
		speedUp=$(echo "${avgSerie[$N]} $avgLoop" | awk '{print $1 / $2}')
		


		echo "$T $N ${avgSerie[$N]} $avgLoop" >> time_best_$T.dat
		echo "$T $N $speedUp" >> speedUp_best_$T.dat
	done
done
