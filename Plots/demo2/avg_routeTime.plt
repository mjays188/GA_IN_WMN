set terminal png size 1980,1080 

set tics font ',19'
set key font ",19"
set xlabel font ",19"
set ylabel font ",19"
set title font ",19"

set title "Average Route Time per Generation"
set xlabel "Generation Count"
set ylabel "Average Route Time (ms)"

plot "avg_routeTime.txt" index 0 with lines linewidth 2 title 'Average Route Time'
     
     
set term png
set output "avg_routeTime.png"
replot
