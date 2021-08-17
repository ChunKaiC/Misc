#!/bin/bash

function display_score {

	if test -f /mnt/c/Users/Kai/Desktop/csc_209/$1/feedback.txt; then
		grade=`tail -1 /mnt/c/Users/Kai/Desktop/csc_209/$1/feedback.txt | tr -d [:blank:]`

		IFS='/' read -ra grArray <<< "$grade"
		score=${grArray[0]}
		max=${grArray[1]}
	
		total_score=$total_score+score
		total_max=$total_max+max

		echo "$1: $score / $max"
	else
		echo "$1: - / -"
	fi
}
declare -i total_score=0
declare -i total_max=0

for d in a1 a2 a3 a4; do
	display_score $d
done

assign_score=$total_score
assign_max=$total_score

total_score=0
total_max=0

for d in t01 t02 t03 t04 t05 t06 t07 t08 t09 t10 t11; do
	display_score $d
done

tut_score=$total_score
tut_max=$total_max

echo "Assignment Total: $assign_score / $assign_max"
echo "Tutorial Total: $tut_score / $tut_max" 
