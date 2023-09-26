#!/bin/bash

# Task 1
#####################################################
# This script will (roughly) execute the			#
# following sequence:								#
# ./slow N1											#
# ./slow N2											#
# ./slow ...										#
# ./slow Nfinal										#
# ./fast N1											#
# ./fast N2											#
# ./fast ...										#
# ./fast Nfinal										#
#####################################################

# Initialize variables
P=10 # (13 mod 7) + 4 = 6 + 4 = 10
Ninicio=$((10000 + 1024*P))
Npaso=64
Nfinal=$((10000 + 1024*(P+1) ))
fDAT=slow_fast_time.dat
fPNG=slow_fast_time.png
ntimes=15 # how many times to call the programs, to later compute the average

# These two will be useful later
slow="slow"
fast="fast"
# needed to do dynamically created variables
# to compute the average of various executions
declare -A fastTotal=()
declare -A slowTotal=()

# remove data file and png file
rm -f $fDAT $fPNG

# generate an empty data file
touch $fDAT

# Initialize the dynamically created accumulators
# so we can add them up to later compute the average
# If we don't initialize them, we would have done:
# " + 0.24124" for example, which yields a syntax error
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	slowTotal[$N]="0"
	fastTotal[$N]="0"
done

echo "Running slow and fast $ntimes times..."
for ((i = 1; i <= ntimes; i += 1));
do
	echo "Iteration: $i"
	# Compute the times for slow as told by the
	# practice task description:
	# ./slow N1, ./slow N2, ./slow N3...
	echo "Executing Slow..."
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo "Slow | N: $N / $Nfinal..."
		slowTime=$(./slow $N | grep 'time' | awk '{print $3}')
		echo "Time: $slowTime"
		slowTotal[$N]=$(echo "${slowTotal[$N]} $slowTime" | awk '{print $1+$2}')
		echo "Total for $N: ${slowTotal[$N]}"
	done
	echo "Executing Fast..."
	# Do the same for fast:
	# ./fast N1, ./fast N2, ./fast N3...
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo "Fast | N: $N / $Nfinal..."
		fastTime=$(./fast $N | grep 'time' | awk '{print $3}')
		echo "Time: $fastTime"
		fastTotal[$N]=$(echo "${fastTotal[$N]} $fastTime" | awk '{print $1+$2}')
		echo "Total for $N: ${fastTotal[$N]}"
	done
done
echo "Generating the DAT file..."
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	slowAvg=$(echo "${slowTotal[$N]} $ntimes" | awk '{print $1/$2}')
	fastAvg=$(echo "${fastTotal[$N]} $ntimes" | awk '{print $1/$2}')
	
	echo "$N	$slowAvg	$fastAvg" >> $fDAT
done

echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Slow-Fast Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG"
plot "$fDAT" using 1:2 with lines lw 2 title "slow", \
     "$fDAT" using 1:3 with lines lw 2 title "fast", 
replot
quit
END_GNUPLOT