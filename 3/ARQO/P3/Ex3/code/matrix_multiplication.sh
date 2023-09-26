#!/bin/bash

# initialize variables
P=10 # (13 mod 7) + 4 = 6 + 4 = 10
Ninicio=$((256+256*P))
Npaso=32
Nfinal=$(( 256+256*(P+1) ))
_8MB=$((8 * 1024 * 1024)) # 8MB = 8388608 bytes
fDAT=mult.dat
fPNGCACHE=mult_cache.png
fPNGTIME=mult_time.png
ntimes=5 # how many times to call the programs

# 4092 is an arbitrary number.
_8MB=$((8 * 1024 * 1024)) # 8MB = 8388608 bytes
SIZE=4096

# arrays to accumulate the data about the times
declare -A normalTimes=()
declare -A transposeTimes=()

# remove data file and png file
rm -f $fDAT $fPNG

# generate an empty data file
touch $fDAT

# Temporary file to dump valgrind data
TMPFILE=$(mktemp -p .)
trap 'rm -f "$TMPFILE"' EXIT

for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	normalTimes[$N]='0'
	transposeTimes[$N]='0'
done

echo -e "\033[1mRunning Matrix Multiplication programs: benchmarking execution time\033[0m"
echo -e "\e[37mPlease, be patient as this script takes a long time to finish.\033[0m"
for((i = 1; i < ntimes; i++)); do
	echo "Iteration: $i / $ntimes"
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo ">N: $N / $Nfinal..."
		normalTime=$(./matrixMultiplication $N | grep 'time' | awk '{print $3}')
		normalTimes[$N]=$(echo "${normalTimes[$N]} $normalTime" | awk '{print $1+$2}')
		transposeTime=$(./matrixMultiplication $N -t | grep 'time' | awk '{print $3}')
		transposeTimes[$N]=$(echo "${transposeTimes[$N]} $transposeTime" | awk '{print $1+$2}')
	done
done
echo -e "\033[1mRunning Matrix Multiplication Cachegrind with level 1 cache $SIZE and LL size $_8MB\033[0m"
echo -e "\e[37mPlease, be patient as this script takes a long time to finish.\033[0m"
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	valgrind --tool=cachegrind --I1=$SIZE,1,64 --D1=$SIZE,1,64 --LL=$_8MB,1,64 --cachegrind-out-file=$TMPFILE ./matrixMultiplication $N
	normalD1mr=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $5}')
	normalD1mw=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $8}')
	valgrind --tool=cachegrind --I1=$SIZE,1,64 --D1=$SIZE,1,64 --LL=$_8MB,1,64 --cachegrind-out-file=$TMPFILE ./matrixMultiplication $N -t
	transD1mr=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $5}')
	transD1mw=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $8}')
	# Data file format:
	# <N> <tiempo “normal”> <D1mr “normal”> <D1mw “normal”> <tiempo “trasp”> <D1mr “trasp”> <D1mw “trasp”>
	# Let's extract the accumulated time and divide it by ntimes (to get the average)
	normalTime=$(echo "${normalTimes[$N]} $ntimes" | awk '{print $1/$2}')
	transposeTime=$(echo "${transposeTimes[$N]} $ntimes" | awk '{print $1/$2}')
	echo "$N	$normalTime	$normalD1mr	$normalD1mw	$transposeTime	$transD1mr	$transD1mw" >> $fDAT
done
# Clean up the .dat file by removing the commas
sed -i 's/,//g' $fDAT
echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Normal-Transpose Cache Misses"
set ylabel "Number of Misses"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNGCACHE"
plot "$fDAT" using 1:3 with lines lw 2 title "normal read miss", \
	 "$fDAT" using 1:4 with lines lw 2 title "normal write miss", \
	 "$fDAT" using 1:6 with lines lw 2 title "transpose read miss", \
	 "$fDAT" using 1:7 with lines lw 2 title "transpose write miss",
replot
quit
END_GNUPLOT
gnuplot << END_GNUPLOT
set title "Normal-Transpose Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNGTIME"
plot "$fDAT" using 1:2 with lines lw 2 title "normal", \
	 "$fDAT" using 1:5 with lines lw 2 title "transpose"
replot
quit
END_GNUPLOT