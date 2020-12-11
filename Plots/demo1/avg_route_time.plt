set terminal png size 1980,1080
set title "Average Route Time"
set xlabel "Generation Count"
set ylabel "Average Route Time (ms)"
plot "avg_route_time.txt" index 0 with lines title 'avg route time' 
     
     
set term png
set output "avg_route_time.png"
replot
