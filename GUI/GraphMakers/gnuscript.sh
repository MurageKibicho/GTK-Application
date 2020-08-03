set style fill solid 0.25 border -1 
set style boxplot outliers pointtype 7
set style data boxplot
set xtics ("1"1, "2"2)
plot for [i=1:2] 'orbital1.txt' using (i):i notitle 
