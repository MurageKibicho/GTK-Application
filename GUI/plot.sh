stats 'test.txt' using 1 nooutput
records1 = STATS_records
mean1 = STATS_mean
sum1 = STATS_sum
sumSquare1 = STATS_sumsq 
stats 'test.txt' using 2 nooutput
records2 = STATS_records
mean2 = STATS_mean
sum2 = STATS_sum
sumSquare2 = STATS_sumsq
stats 'test.txt' using 3 nooutput
records3 = STATS_records
mean3 = STATS_mean
sum3 = STATS_sum
sumSquare3 = STATS_sumsq
totalSum = sum1 + sum2 + sum3
totalRecords = records1 + records2 + records3
totalMean = mean1 + mean2 + mean3
totalSumSq = sumSquare1 + sumSquare2 + sumSquare3
grandMean = (totalSum) / totalRecords
sumNmeanGrand1 = records1 * (mean1 - grandMean) * (mean1 - grandMean) 
sumNmeanGrand2 = records1 * (mean2 - grandMean) * (mean2 - grandMean) 
sumNmeanGrand3 = records1 * (mean3 - grandMean) * (mean3 - grandMean) 
totalSumNmeanGrand = sumNmeanGrand1 + sumNmeanGrand2 + sumNmeanGrand3
degreeOfFreedomw = totalRecords - 3
degreeOfFreedomb = 3 - 1
Mssb = totalSumNmeanGrand / (degreeOfFreedomb)
Mssw = (totalSumSq)/(degreeOfFreedomw)
Ftest = Mssb / Mssw
print Ftest


set term wxt title 'Area Comparison'
set ylabel "Area (micrometer squared)"
set xlabel "Treatment Conditions"
set style fill solid 0.25 border -1 
set style boxplot outliers pointtype 7
set style data boxplot
set xtics ("TGFB : A1"1, "CGP53353: B1"2, "CGP53353: C1"3)
plot for [i=1:3] 'test.txt' using (i):i notitle 
