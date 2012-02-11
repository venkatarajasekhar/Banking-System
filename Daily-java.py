import os, sys;

# Correct usage?
if len(sys.argv) != 4:
	print 'Usage: python Daily.py <trans1> <trans2> <trans3>'
	sys.exit()
	
# Run the front end
for i in range(1, 4):
	print 'Script: Running transaction stream %d' % i
	os.system("java -cp ./bin FrontEnd < " + sys.argv[i])
	
# Merge the transaction files
f = open("./system/transaction/merged_transactions.tra", "a")
for r,d,fi in os.walk("./system/transaction"):
		for files in fi:
			if files.startswith("transaction"):
				print files
				g=open(os.path.join(r,files))
				f.write(g.read())
				g.close()
f.close()

# Run the back end
print 'Script: Running back end'
os.system("./bin/Back.exe")

#Clean up
print 'Script: Removing transaction files'
for r,d,fi in os.walk("./system/transaction"):
	for files in fi:
		os.remove(os.path.join(r, files))
print 'Script: Rewriting transaction counter'
h = open("./system/transaction/trans_counter.txt", "a")
h.write("00001")
print 'Script: Daily script complete'
