#!/bin/bash

# Make the binaries
make pescalar_par_input
make pescalar_serie_input
declare -A times=()
declare -A serial=()
fDAT="time.dat"

# Delete the file
rm -rf $fDAT
touch $fDAT
N_FROM="1000"
N_STEP="1000"
N_TO="300000"
ntimes=5

for ((N = N_FROM ; N <= N_TO ; N += N_STEP)); do
	serial[$N]='0'
	for THR in 1 2 3 4 5 6 7 8
	do
		aux="$N-$THR"
		times[$aux]='0'
	done
done

for ((i = 1 ; i <= $ntimes ; i++)); do
	for ((N = N_FROM ; N <= N_TO ; N += N_STEP)); do
	echo "Size: $N | Serial"
	time=$(./pescalar_serie_input $N | grep 'Tiempo' | awk '{print $2}')
	serial[$N]=$(echo "${serial[$N]} $time" | awk '{print $1 + $2}')
		for THR in 1 2 3 4 5 6 7 8
		do
			echo "Size: $N | Threads: $THR"
			aux="$N-$THR"
			time=$(./pescalar_par_input $N $THR | awk '{print $2}')
			times[$aux]=$(echo "${times[$aux]} $time" | awk '{print $1 + $2}')
		done
	done
done

for ((N = N_FROM ; N <= N_TO ; N += N_STEP));do
	serial=$(echo "${serial[$N]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-1"
	time1=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-2"
	time2=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-3"
	time3=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-4"
	time4=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-5"
	time5=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-6"
	time6=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-7"
	time7=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	aux="$N-8"
	time8=$(echo "${times[$aux]} $ntimes" | awk '{print $1 / $2}')
	
	echo "$N	$serial	$time1	$time2	$time3	$time4	$time5	$time6	$time7	$time8" >> $fDAT
done

