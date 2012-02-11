import os

for j in range(1, 6):
	print 'Script: Weekly script day %d' % j
	os.system("python Daily-java.py weekly-java/day" + str(j) + "/test1 weekly-java/day" + str(j) + "/test2 weekly-java/day" + str(j) + "/test3")
	f = open("system/account/master_bank_account.mba", "r")
	g = open("weekly-java/day" +  str(j) + "/master_bank_account.mba", "w")
	g.write(f.read())
	f.close()
	g.close()
	
print 'Script: Weekly script complete.'
