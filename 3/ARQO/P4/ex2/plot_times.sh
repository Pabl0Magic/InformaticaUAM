fDAT="time.dat"
rm -rf times.png
echo "Plotting time.dat..."
gnuplot << END_GNUPLOT
set title "Execution times for each approach vs vector size"
set ylabel "Execution time (s)"
set xlabel "Vector Size"
set key right bottom
set grid
set term png
set output "times.png"
plot "$fDAT" using 1:2 with lines lw 2 title "serial", \
	"$fDAT" using 1:3 with lines lw 2 title "1 thread", \
	"$fDAT" using 1:4 with lines lw 2 title "2 threads", \
	"$fDAT" using 1:5 with lines lw 2 title "3 threads", \
	"$fDAT" using 1:6 with lines lw 2 title "4 threads", \
	"$fDAT" using 1:7 with lines lw 2 title "5 threads", \
	"$fDAT" using 1:8 with lines lw 2 title "6 threads", \
	"$fDAT" using 1:9 with lines lw 2 title "7 threads", \
	"$fDAT" using 1:10 with lines lw 2 title "8 threads"
replot
quit
END_GNUPLOT
totalSerial=0
while IFS= read -r line
do
	cur=$(echo "$line" | awk '{print $2}')
	totalSerial=$(echo "$totalSerial $cur" | awk '{print $1 + $2}')
done < $fDAT

fSP="speedup.dat"
rm -rf $fSP
touch $fSP

echo "Generating Speedup data..."
while IFS= read -r line
do
	N=$(echo "$line" | awk '{print $1}')
	serial=$(echo "$line" | awk '{print $2}')
	# This could have been an array, with a nice
	# for. Just ignore please.
	time1thr=$(echo "$line" | awk '{print $3}')
	time2thr=$(echo "$line" | awk '{print $4}')
	time3thr=$(echo "$line" | awk '{print $5}')
	time4thr=$(echo "$line" | awk '{print $6}')
	time5thr=$(echo "$line" | awk '{print $7}')
	time6thr=$(echo "$line" | awk '{print $8}')
	time7thr=$(echo "$line" | awk '{print $9}')
	time8thr=$(echo "$line" | awk '{print $10}')
	sp1thr=$(echo "$time1thr $serial" | awk '{print $2 / $1}')
	sp2thr=$(echo "$time2thr $serial" | awk '{print $2 / $1}')
	sp3thr=$(echo "$time3thr $serial" | awk '{print $2 / $1}')
	sp4thr=$(echo "$time4thr $serial" | awk '{print $2 / $1}')
	sp5thr=$(echo "$time5thr $serial" | awk '{print $2 / $1}')
	sp6thr=$(echo "$time6thr $serial" | awk '{print $2 / $1}')
	sp7thr=$(echo "$time7thr $serial" | awk '{print $2 / $1}')
	sp8thr=$(echo "$time8thr $serial" | awk '{print $2 / $1}')
	echo "$N	$sp1thr	$sp2thr	$sp3thr	$sp4thr	$sp5thr	$sp6thr	$sp7thr	$sp8thr" >> $fSP
done < $fDAT

echo "Plotting speedups"
gnuplot << END_GNUPLOT
set title "Speedups"
set ylabel "Overall speedup"
set xlabel "Vector Size"
set key right bottom
set grid
set term png
set output "speedups.png"
plot "$fSP" using 1:2 with lines lw 2 title "1 thread", \
	"$fSP" using 1:3 with lines lw 2 title "2 threads", \
	"$fSP" using 1:4 with lines lw 2 title "3 threads", \
	"$fSP" using 1:5 with lines lw 2 title "4 threads", \
	"$fSP" using 1:6 with lines lw 2 title "5 threads", \
	"$fSP" using 1:7 with lines lw 2 title "6 threads", \
	"$fSP" using 1:8 with lines lw 2 title "7 threads", \
	"$fSP" using 1:9 with lines lw 2 title "8 threads"
replot
quit
END_GNUPLOT