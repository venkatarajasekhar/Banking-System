#cd ..

for j in $(ls ./tests/input)
do
	for i in $(ls ./tests/input/$j)
	do
		echo "running test $i"
		./bin/system.exe < ./tests/input/$j/$i > ./tests/output/actual/$j/$i
	done
done
