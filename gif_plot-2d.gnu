reset

set term gif animate delay 1 size 1000,1000
set output "plot-2d.gif"

rang = 10000000

set xrange [-rang:rang]
set yrange [-rang:rang]


frames = 1000

do for [i=1:frames] {

  plot 'dados.dat' index (100*i) using ($3):($4) with points pt 7 ps 2 lc 7 title 'Estrela'

}
