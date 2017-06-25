# -*- coding: utf-8 -*-
# @Author: Leif
# @Date:   2017-06-24 22:02:33
# @Last Modified by:   Leif
# @Last Modified time: 2017-06-25 17:06:18
import matplotlib.pyplot as plt

def SCAN(start, blockSeq):
	record = []
	alias = blockSeq[:]
	alias.sort() #对寻道请求排序
	partition = 0
	#找到第一个比当前位置大的磁道
	while partition < len(alias) and alias[partition] < start:
		partition += 1
	time = 0
	#将(初始位置,初始时刻)写入记录
	record.append((start, time))
	#自里向外扫描磁道
	i = partition
	while i < len(alias):
		seekTime = alias[i] - record[-1][0]
		time += seekTime
		record.append((alias[i],time))
		i += 1
	#自外向里扫描
	i = partition - 1
	while i >= 0:
		seekTime = record[-1][0] - alias[i]
		time += seekTime
		record.append((alias[i],time))
		i -= 1
	#打印移臂记录
	for x in record:
		print x
	#绘图
	plt.figure(figsize = (10,10))
	plt.title("Disk Scheduling Diagram")
	plt.xlabel("block number")
	plt.ylabel("time")
	x = [t[0] for t in record]
	y = [t[1] for t in record]
	plt.plot(x, y, "ro-",label="SCAN", linewidth = 2)
	flag = 1 #avoid overlap
	for _x, _y in zip(x, y):
		if flag:
			plt.text(_x, _y,("(%d,%d)"%(_x, _y)),fontsize = 15, ha="right")
		else:
			plt.text(_x, _y,("(%d,%d)"%(_x, _y)),fontsize = 15, ha="left")
		flag = not flag
	plt.legend(loc="upper right");
	plt.show()

#输入数据
start = 53
blockSeq = [98, 183, 37, 122, 14, 124, 65, 67]
#调用SCAN算法模拟程序
SCAN(start, blockSeq)
		
