#cd ..

for j in $(ls ./tests/output/expected)
do
	for i in $(ls ./tests/input/$j)
	do
		echo "diffing test $i"
		diff ./tests/output/actual/$j/$i ./tests/output/expected/$j/$i > ./tests/output/diff/$j/$i
	done
done
