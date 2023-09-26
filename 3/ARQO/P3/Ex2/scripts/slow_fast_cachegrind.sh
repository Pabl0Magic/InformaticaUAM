#!/bin/bash

# initialize variables
P=10 # (13 mod 7) + 4 = 6 + 4 = 10
Ninicio=10 # $((2000+512*P))
Npaso=64
Nfinal=100 # $((2000+512*(P+1) )) 
_8MB=$((8 * 1024 * 1024)) # 8MB = 8388608 bytes

# Temporary file to dump valgrind data
TMPFILE=$(mktemp -p .)
trap 'rm -f "$TMPFILE"' EXIT

echo "Running slow and fast..."
# for each cache size...
for SIZE in 1024 2048 4096 8192
do
	# ...execute from Ninicio to Nfinal
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo "N: $N / $Nfinal..."
		valgrind --tool=cachegrind --I1=$SIZE,1,64 --D1=$SIZE,1,64 --LL=$_8MB,1,64 --cachegrind-out-file=$TMPFILE ./slow $N
		slowCacheD1mr=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $5}')
        slowCacheD1mw=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $8}')
		valgrind --tool=cachegrind --I1=$SIZE,1,64 --D1=$SIZE,1,64 --LL=$_8MB,1,64 --cachegrind-out-file=$TMPFILE ./fast $N
		fastCacheD1mr=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $5}')
        fastCacheD1mw=$(cg_annotate $TMPFILE | head -n 30 | grep 'PROGRAM TOTALS' | awk '{print $8}')
		
		# Data file structure:
		# <N> <D1mr “slow”> <D1mw “slow”> <D1mr “fast”> <D1mw “fast”>

		echo "$N	$slowCacheD1mr	$slowCacheD1mw	$fastCacheD1mr	$fastCacheD1mw" >> $SIZE.dat
	done
    # Cleanup from cg_annotate which potentially gives you ','
    sed -i 's/,//g' $SIZE.dat
done

echo "Generating plots..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Slow-Fast Cache Read Misses"
set ylabel "Number of Misses"
set xlabel "Cache Size"
set key right bottom
set grid
set term png
set yrange [0:*]
set output "cache_lectura.png"
plot "1024.dat" using 1:2 with lines lw 3 title "slow - 1kB", \
     "2048.dat" using 1:2 with lines lw 3 title "slow - 2kB", \
     "4096.dat" using 1:2 with lines lw 3 title "slow - 4kB", \
     "8192.dat" using 1:2 with lines lw 3 title "slow - 8kB", \
     "1024.dat" using 1:4 with lines lw 3 title "fast - 1kB", \
     "2048.dat" using 1:4 with lines lw 3 title "fast - 2kB", \
     "4096.dat" using 1:4 with lines lw 3 title "fast - 4kB", \
     "8192.dat" using 1:4 with lines lw 3 title "fast - 8kB"
replot
quit
END_GNUPLOT
echo "Second plot"
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Slow Cache Write Misses"
set ylabel "Number of Misses"
set xlabel "Cache Size"
set key right bottom
set grid
set term png
set yrange [0:*]
set output "cache_escritura.png"
plot "1024.dat" using 1:3 with lines lw 3 title "slow - 1kB", \
     "2048.dat" using 1:3 with lines lw 3 title "slow - 2kB", \
     "4096.dat" using 1:3 with lines lw 3 title "slow - 4kB", \
     "8192.dat" using 1:3 with lines lw 3 title "slow - 8kB", \
     "1024.dat" using 1:5 with lines lw 3 title "fast - 1kB", \
     "2048.dat" using 1:5 with lines lw 3 title "fast - 2kB", \
     "4096.dat" using 1:5 with lines lw 3 title "fast - 4kB", \
     "8192.dat" using 1:5 with lines lw 3 title "fast - 8kB"
replot
quit
END_GNUPLOT
