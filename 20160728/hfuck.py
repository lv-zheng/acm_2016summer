import random

T = 100

print T

def pa():
	N = random.randint(2, 5)
	M = random.randint(N, 30)

	K = random.randint(0, M - 1)
	r = range(2, M)
	random.shuffle(r)
	r = r[:K]
	r.sort()

	print N, M
	print K,
	for i in r:
		print i,
	print

	for i in range(N):
		for j in range(M):
			print float(random.randint(0, 10)) / 10,
		print

for i in range(T):
	pa()
