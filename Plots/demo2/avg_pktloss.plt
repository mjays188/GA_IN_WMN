set terminal png size 1980,1080 

set tics font ',19'
set key font ",19"
set xlabel font ",19"
set ylabel font ",19"
set title font ",19"

set title "Average PacketLoss per Generation"
set xlabel "Generation Count"
set ylabel "Average PacketLoss"

plot "avg_pktloss.txt" index 0 with lines linewidth 2 title 'Average PacketLoss'
     
     
set term png
set output "avg_pktloss.png"
replot
