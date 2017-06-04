import matplotlib.pyplot as plt

def SSTF(start, blockSeq):
	record = []
	tag = [0 for x in range(len(blockSeq))]
	time = 0
	record.append((start, time))
	for i in range(len(blockSeq)):
		nextIndex = -1
		sst = float("inf")
		for j in range(len(blockSeq)):
			seekTime = abs(blockSeq[j] - record[-1][0])
			if seekTime < sst and tag[j] == 0:
				nextIndex = j
				sst = seekTime
		tag[nextIndex] = 1
		time += sst
		record.append((blockSeq[nextIndex],time))
	for x in record:
		print x
	plt.figure(figsize = (10,10))
	plt.title("Disk Scheduling Diagram")
	plt.xlabel("block number")
	plt.ylabel("time")
	x = [t[0] for t in record]
	y = [t[1] for t in record]
	plt.plot(x, y, "bo-",label="SSTF", linewidth = 2)
	flag = 1 #avoid label overlapping
	for _x, _y in zip(x, y):
		if flag:
			plt.text(_x, _y,("(%d,%d)"%(_x, _y)),fontsize = 15, ha="right")
		else:
			plt.text(_x, _y,("(%d,%d)"%(_x, _y)),fontsize = 15, ha="left")
		flag = not flag
	plt.legend(loc="upper left");
	plt.show()


start = 53
blockSeq = [98, 183, 37, 122, 14, 124, 65, 67]
SSTF(start, blockSeq)

		
