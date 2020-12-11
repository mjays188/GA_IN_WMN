set terminal png size 1980,1080 

set tics font ',19'
set key font ",19"
set xlabel font ",19"
set ylabel font ",19"
set title font ",19"

set title "Evolution of Best Route In Terms Of Fitness"
set xlabel "Generation Count"
set ylabel "Best Route Fitness"

plot "best_route_fitness.txt" index 0 with lines linewidth 2 title 'Best Route Fitness'
     
     
set term png
set output "best_route_fitness.png"
replot
