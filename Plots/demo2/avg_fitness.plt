set terminal png size 1980,1080 

set tics font ',19'
set key font ",19"
set xlabel font ",19"
set ylabel font ",19"
set title font ",19"

set title "Average Fitness per Generation"
set xlabel "Generation Count"
set ylabel "Average Fitness"

plot "avg_fitness.txt" index 0 with lines linewidth 2 title 'Average Fitness'
     
     
set term png
set output "avg_fitness.png"
replot
