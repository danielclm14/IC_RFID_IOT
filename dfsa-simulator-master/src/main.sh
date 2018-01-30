#!/bin/bash

g++ main.cpp -std=c++11 -o bin/main.exe
./bin/main.exe < input/in

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Tags"
  set ylabel "Slots"
  set title "Total Number of Slots used for each Estimator"
  set style line 1 pt 1
  set style line 2 pt 2
  set term png
  set output "graphs/slots.png"
  plot "output/slots.csv" u 1:2 pt 1 title "LowerBound" w linespoints, "output/slots.csv" u 1:3 title "Eom Lee" w linespoints, "output/slots.csv" u 1:4 title "DS-MAP" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Tags"
  set ylabel "Empty Slots"
  set title "Total Number of Empty Slots left for each Estimator"
  set term png
  set output "graphs/empties.png"
  plot "output/empties.csv" u 1:2 title "LowerBound" w linespoints, "output/empties.csv" u 1:3 title "Eom Lee" w linespoints, "output/empties.csv" u 1:4 title "DS-MAP" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Tags"
  set ylabel "Collisions"
  set title "Total Number of Collisions ocurred for each Estimator"
  set term png
  set output "graphs/collisions.png"
  plot "output/collisions.csv" u 1:2 title "LowerBound" w linespoints, "output/collisions.csv" u 1:3 title "Eom Lee" w linespoints, "output/collisions.csv" u 1:4 title "DS-MAP" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Tags"
  set ylabel "Runtime in Microseconds"
  set title "Total Simulation Runtime in Microseconds"
  set term png
  set output "graphs/time.png"
  plot "output/time.csv" u 1:2 title "LowerBound" w linespoints, "output/time.csv" u 1:3 title "Eom Lee" w linespoints, "output/time.csv" u 1:4 title "DS-MAP" w linespoints
EOF

gnuplot <<- EOF
  set grid layerdefault linewidth 1
  set xlabel "Tags"
  set ylabel "Througtput"
  set title "Total Throughtput"
  set term png
  set output "graphs/flow.png"
  plot "output/flow.csv" u 1:2 title "LowerBound" w linespoints, "output/flow.csv" u 1:3 title "Eom Lee" w linespoints, "output/flow.csv" u 1:4 title "DS-MAP" w linespoints
EOF

