import time

def foo(x = 1):
	return x ** 2 - x ** 2 + 4 * x - x * 5 + x + x

while 1:
	n = input('Enter n: ')

	try:
		n = int(n)
	except:
		print('n should be an natural digit')
		exit()

	iter_time = time.time()

	for _ in range(n):
		foo()

	iter_time = time.time() - iter_time
	print(f'Done: {n} iterations: {iter_time}')

	retry = input('Do you want to retry? Type \'q\' to quit. ')
	if retry == 'q':
		break
