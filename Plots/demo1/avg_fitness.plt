set terminal png size 1980,1080
set title "Average Fitness"
set xlabel "Generation Count"
set ylabel "Average Fitness"
plot "avg_fitness.txt" index 0 with lines title 'avg fitness value' 
     
     
set term png
set output "avg_fitness.png"
replot
