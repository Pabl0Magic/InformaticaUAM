fDAT="time_best_3.dat"
gnuplot << END_GNUPLOT
set title "Execution times for each approach vs Matrix size"
set ylabel "Execution time (s)"
set xlabel "Size"
set key right bottom
set grid
set term png
set output "best_time.png"
plot "$fDAT" using 2:3 with lines lw 2 title "Serial", \
     "$fDAT" using 2:4 with lines lw 2 title "Best parallel",

replot
quit
END_GNUPLOT