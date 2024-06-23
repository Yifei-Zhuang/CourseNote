sub = input()
sub = sub.split(',')
res = ""
for i in sub:
	temp = '.fill #' + str(i)
	res = res + temp + '\n'
print(res)

