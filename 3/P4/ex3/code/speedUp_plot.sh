fDAT="speedUp_best_3.dat"
gnuplot << END_GNUPLOT
set title "SpeedUp vs Matrix size"
set ylabel "SpeedUp"
set xlabel "Size"
set key right bottom
set grid
set term png
set output "SpeedUp.png"
plot "$fDAT" using 2:3 with lines lw 2 title "SpeedUp",

replot
quit
END_GNUPLOT