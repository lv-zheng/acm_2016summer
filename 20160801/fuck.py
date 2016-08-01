import random

N = 3
Q = 3

print N, Q
for i in range(2, N + 1):
	print random.randint(1, i - 1),
print

for i in range(Q):
	if random.randint(0, 1) == 1:
		print "M", random.randint(1, N)
	else:
		print "Q", random.randint(1, N)
print 0, 0
