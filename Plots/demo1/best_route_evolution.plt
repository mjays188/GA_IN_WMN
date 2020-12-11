set terminal png size 1980,1080
set title "Best Rout Evolution (Route 8 in this case)"
set xlabel "Generation Count"
set ylabel "Best route's evolution Time (ms)"
plot "best_route_evolution.txt" index 0 with lines title 'Best Rout Evolution (ms)' 
     
     
set term png
set output "best_route_evolution.png"
replot
