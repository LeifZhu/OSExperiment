# -*- coding: utf-8 -*-
# @Author: Leif
# @Date:   2017-06-25 17:13:44
# @Last Modified by:   Leif
# @Last Modified time: 2017-06-25 17:15:04
import matplotlib.pyplot as plt

def SSTF(start, blockSeq):
	record = []
	#list是可变对象，为使函数内部的排序不影响blockSeq，将其完整切片付给alias
	#函数内部只对alias进行操作
	alias = blockSeq[:]
	alias.sort()
	#找到第一个大于起始位置start的磁道
	high = 0
	while high < len(alias) and alias[high] < start:
		high += 1
	low = high - 1
	#初始化time,并将当前位置和时刻写入记录
	time = 0
	record.append((start, time))
	#距离当前位置最近的只可能是alias[low]和alias[high]其中之一
	for i in range(len(alias)):
		if low >= 0:
			seekTimeLow = record[-1][0] - alias[low]
		else:
			seekTimeLow = float("inf")
		if high < len(alias):
			seekTimeHigh = alias[high] - record[-1][0]
		else:
			seekTimeHigh = float("inf")
		if seekTimeHigh < seekTimeLow:
			time += seekTimeHigh
			record.append((alias[high],time))
			high += 1
		else:
			time += seekTimeLow
			record.append((alias[low],time))
			low -= 1
	#打印移臂记录
	for x in record:
		print x
	#绘制图像
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

		
