#cd ..

for j in $(ls ./tests/test-transactions/)
do
	echo "diffing test $j"
	diff ./tests/test-transactions/$j ./system/transaction/$j > ./tests/test-transactions/diff/$j
done
