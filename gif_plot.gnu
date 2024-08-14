reset

set term gif animate delay 1 size 1000,1000
set output "plot.gif"

rang = 50000

frames = 4000
rot = 0

do for [i=1:frames] {

  splot 'dados.dat' index (i) using ($3):($4):($5) with points pt 7 ps 2 lc 7 notitle
  
  if(rot >= 360){rot = rot - 360}
  set view 60, rot
  rot = rot + 0.2

  set xrange [-(2000000+1*700):(2000000+1*700)]
  set yrange [-(2000000+1*700):(2000000+1*700)]
  set zrange [-(2000000+1*700):(2000000+1*700)]

}
