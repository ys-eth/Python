#!/bin/bash

rm -f /tmp/length.dat /tmp/maxvalues.dat /tmp/histogram.dat /tmp/hisort.dat

make clean && make collatz	# Rebuild the sincos executable.
./collatz > /tmp/collatz.dat	# Place the data points into a file.

## Sequence Lengths Graph
for (( n = 2; n <= 10000; n++ )); do echo -n $n " " >> /tmp/length.dat
	./collatz -n $n | wc -l >> /tmp/length.dat;
done


## Max Values Graph
for (( n = 2; n <= 10000; n++ )); do echo -n $n " " >> /tmp/maxvalues.dat
	./collatz -n $n | sort -n | tail -n 1  >> /tmp/maxvalues.dat;
done


## Histogram Graph
for (( n = 2; n <= 10000; n++ )); do echo -n " " >> /tmp/histogram.dat
	./collatz -n $n | wc -l >> /tmp/histogram.dat;
done

cat /tmp/histogram.dat | sort -n | uniq -c >> /tmp/hisort.dat;


# This is the heredoc that is sent to gnuplot.
gnuplot <<END
    set terminal pdf
    set output "length.pdf"
    set title "Collatz Sequence Lengths"
    set xlabel "n"
    set ylabel "length"
    set zeroaxis
    plot "/tmp/length.dat" with dots title ""
END

gnuplot <<END
    set terminal pdf
    set output "maxvalues.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set yrange [0:100000]
    plot "/tmp/maxvalues.dat" with dots title ""
END

gnuplot <<END
     set terminal pdf
     set output "histogram.pdf"
     set title "Collatz Sequence Length Histogram"
     set xlabel "length"
     set ylabel "frequency"
     set xrange [0:225]
     set xtics 25
     plot "/tmp/hisort.dat" using 2:1 with impulses title "" 
END
