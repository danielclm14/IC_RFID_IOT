#!/bin/bash

g++ -Wall -g main.cpp -std=c++11 -o bin/main.exe
./bin/main.exe < input/in

# toda esta parte comentada nao diz respeito ao algoritmo Q, mas aos outros tipos de estimadores.

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Slots"
#   set title "Numero total de Slots usados por cada estimador, iniciando em 64"
#   set style line 1 pt 1
#   set style line 2 pt 2
#   set term png
#   set output "graphs/slots.png"
#   plot "output/slots.csv" u 1:2 pt 1 title "LowerBound" w linespoints, "output/slots.csv" u 1:3 title "Eom Lee" w linespoints, "output/slots.csv" u 1:4 title "DS-MAP" w linespoints, "output/slots.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Slots"
#   set title "Numero total de Slots usados por cada estimador, iniciando em 128"
#   set style line 1 pt 1
#   set style line 2 pt 2
#   set term png
#   set output "graphs/slots128.png"
#   plot "output/slots128.csv" u 1:2 pt 1 title "LowerBound" w linespoints, "output/slots128.csv" u 1:3 title "Eom Lee" w linespoints, "output/slots128.csv" u 1:4 title "DS-MAP" w linespoints, "output/slots128.csv" u 1:5 title "Chen" w linespoints
# EOF

# #set yrange [inf:sup]

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Slots vazios"
#   set title "Numero total de Slots vazios para cada estimador"
#   set term png
#   set output "graphs/empties.png"
#   plot "output/empties.csv" u 1:2 title "LowerBound" w linespoints, "output/empties.csv" u 1:3 title "Eom Lee" w linespoints, "output/empties.csv" u 1:4 title "DS-MAP" w linespoints,  "output/empties.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Slots vazios"
#   set title "Numero total de Slots vazios para cada estimador - 128"
#   set term png
#   set output "graphs/empties128.png"
#   plot "output/empties128.csv" u 1:2 title "LowerBound" w linespoints, "output/empties128.csv" u 1:3 title "Eom Lee" w linespoints, "output/empties128.csv" u 1:4 title "DS-MAP" w linespoints,  "output/empties128.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "colisoes"
#   set title "Numero total de colisoes para cada estimador"
#   set term png
#   set output "graphs/collisions.png"
#   plot "output/collisions.csv" u 1:2 title "LowerBound" w linespoints, "output/collisions.csv" u 1:3 title "Eom Lee" w linespoints, "output/collisions.csv" u 1:4 title "DS-MAP" w linespoints, "output/collisions.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "colisoes"
#   set title "Numero total de colisoes para cada estimador - 128"
#   set term png
#   set output "graphs/collisions128.png"
#   plot "output/collisions128.csv" u 1:2 title "LowerBound" w linespoints, "output/collisions128.csv" u 1:3 title "Eom Lee" w linespoints, "output/collisions128.csv" u 1:4 title "DS-MAP" w linespoints, "output/collisions128.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Runtime in Microseconds"
#   set title "Total Simulation Runtime in Microseconds"
#   set term png
#   set output "graphs/time.png"
#   plot "output/time.csv" u 1:2 title "LowerBound" w linespoints, "output/time.csv" u 1:3 title "Eom Lee" w linespoints, "output/time.csv" u 1:4 title "DS-MAP" w linespoints, "output/time.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Runtime in Microseconds"
#   set title "Total Simulation Runtime in Microseconds - 128"
#   set term png
#   set output "graphs/time128.png"
#   plot "output/time128.csv" u 1:2 title "LowerBound" w linespoints, "output/time128.csv" u 1:3 title "Eom Lee" w linespoints, "output/time128.csv" u 1:4 title "DS-MAP" w linespoints, "output/time128.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Throughput"
#   set title "Total Throughput"
#   set term png
#   set output "graphs/flow.png"
#   plot "output/flow.csv" u 1:2 title "LowerBound" w linespoints, "output/flow.csv" u 1:3 title "Eom Lee" w linespoints, "output/flow.csv" u 1:4 title "DS-MAP" w linespoints, "output/flow.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Throughput"
#   set title "Total Throughput - 128"
#   set term png
#   set output "graphs/flow128.png"
#   plot "output/flow128.csv" u 1:2 title "LowerBound" w linespoints, "output/flow128.csv" u 1:3 title "Eom Lee" w linespoints, "output/flow128.csv" u 1:4 title "DS-MAP" w linespoints, "output/flow128.csv" u 1:5 title "Chen" w linespoints
# EOF

# gnuplot <<- EOF
#   set grid layerdefault linewidth 1
#   set xlabel "Etiquetas"
#   set ylabel "Efficiency"
#   set title "Efficiency for each Estimator"
#   set term png
#   set output "graphs/efficiency.png"
#   plot "output/efficiency.csv" u 1:2 title "LowerBound" w linespoints, "output/efficiency.csv" u 1:3 title "Eom Lee" w linespoints, "output/efficiency.csv" u 1:4 title "DS-MAP" w linespoints, "output/efficiency.csv" u 1:5 title "Chen" w linespoints
# EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Etiquetas"
  set ylabel "Slots"
  set title "Numero total de Slots usados por Q"
  set style line 1 pt 1
  set style line 2 pt 2
  set term png
  set output "graphs/Qnovo/QSlots.png"
  plot "output/QSlots.csv" u 1:2 pt 1 title "Algorythm Q" w linespoints, "output/QSlotso.csv" u 1:2 title "Otimo Q" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Etiquetas"
  set ylabel "Vazios"
  set title "Numero total de Slots vazios"
  set style line 1 pt 1
  set style line 2 pt 2
  set term png
  set output "graphs/Qnovo/Qempties.png"
  plot "output/Qempities.csv" u 1:2 pt 1 title "Algorythm Q" w linespoints, "output/Qempitieso.csv" u 1:2 title "Otimo Q" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Etiquetas"
  set ylabel "Efficiency"
  # set yrange [0.3:0.36]
  set title "Eficiencia de Q"
  set style line 1 pt 1
  set style line 2 pt 2
  set term png
  set output "graphs/Qnovo/Qefficience.png"
  plot "output/Qefficience.csv" u 1:2 pt 1 title "Algorythm Q" w linespoints, "output/Qefficienceo.csv" u 1:2 title "Otimo Q" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Etiquetas"
  set ylabel "collisions"
  set title "Numero total de colisoes ocorridas utilizando Q"
  set style line 1 pt 1
  set style line 2 pt 2
  set term png
  set output "graphs/Qnovo/QCollisions.png"
  plot "output/QCollision.csv" u 1:2 pt 1 title "Algorythm Q" w linespoints, "output/QCollisiono.csv" u 1:2 title "Otimo Q" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Etiquetas"
  set ylabel "Run time in microsseconds"
  set title "Total Simulation Runtime in Microseconds"
  set style line 1 pt 1
  set style line 2 pt 2
  set term png
  set output "graphs/Qnovo/Qtime.png"
  plot "output/QTime.csv" u 1:2 pt 1 title "Algorythm Q" w linespoints, "output/QTimeo.csv" u 1:2 title "Otimo Q" w linespoints
EOF