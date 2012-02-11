import os

for j in range(1, 6):
	print 'Script: Weekly script day %d' % j
	os.system("python Daily.py weekly/day" + str(j) + "/test1 weekly/day" + str(j) + "/test2 weekly/day" + str(j) + "/test3")
	f = open("system/account/master_bank_account.mba", "r")
	g = open("weekly/day" +  str(j) + "/master_bank_account.mba", "w")
	g.write(f.read())
	f.close()
	g.close()
	
print 'Script: Weekly script complete.'
