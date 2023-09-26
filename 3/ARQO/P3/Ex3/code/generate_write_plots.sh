gnuplot << END_GNUPLOT
set title "Normal-Transpose Write Cache Misses"
set ylabel "Number of Misses"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "mult_cache_write.png"
plot "mult.dat" using 1:4 with lines lw 2 title "normal write miss", \
	 "mult.dat" using 1:7 with lines lw 2 title "transpose write miss",
replot
quit
END_GNUPLOT