# -*- coding: utf-8 -*-
# @Author: Leif
# @Date:   2017-06-04 16:54:06
# @Last Modified by:   Leif
# @Last Modified time: 2017-06-25 18:31:43

import random
import math

class FileManagement(object):
	#接收磁盘大小，磁盘块大小，进行初始化
	def __init__(self, diskSize, blockSize):
		self.diskSize = diskSize
		self.disk = [[0,diskSize]]
		self.blockSize = float(blockSize)
		self.fileDirectory = []

	#分配磁盘空间的函数，采用首次适应法
	def allocate(self,space):
		blocks = int(math.ceil(space/self.blockSize))
		for section in self.disk:
			if section[1] >= blocks:
				firstBlock = section[0]
				section[1] -= blocks
				section[0] += blocks
				if section[1] == 0:
					self.disk.remove(section)
				return firstBlock
		return -1

	#回收磁盘空间的函数，注意如果与前后块邻接需要将空闲区域合并
	def recycle(self,firstBlock, space):
		blocks = int(math.ceil(space/self.blockSize))
		i = 0
		while self.disk[i][0] < firstBlock and i < len(self.disk):
			i += 1
		self.disk.insert(i, [firstBlock, blocks])
		#如果与前一个空闲区邻接，合并
		if i > 0 and firstBlock == self.disk[i-1][0] + self.disk[i-1][1]:
			self.disk[i-1][1] += self.disk[i][1]
			del self.disk[i]
			i = i-1
		#如果与后一个空闲区邻接，合并
		if i < len(self.disk)-1 and firstBlock + blocks == self.disk[i+1][0]:
			self.disk[i][1] += self.disk[i+1][1]
			del self.disk[i+1]

	#创建名为fileName,大小为fileSize的文件，分配其需要的空间
	def createFile(self, fileName, fileSize):
		self.fileDirectory.append((fileName,self.allocate(fileSize),fileSize))

	#删除名为fileName的文件，回收其占用的磁盘
	def deleteFile(self, fileName):
		for i in range(len(self.fileDirectory)):
			if self.fileDirectory[i][0] == fileName:
				self.recycle(self.fileDirectory[i][1], self.fileDirectory[i][2])
				del self.fileDirectory[i]
				break
	#显示磁盘状态
	def showDisk(self):
		print 'free sections in disk:'
		print 'format: <first block number> <number of blocks>'
		for fbn, nob in self.disk:
			print fbn, nob

	#显示文件目录
	def showDirectory(self):
		print 'files in disk:'
		print 'format: <file name> <first block number> <file size>(kb)'
		for fn, fbn, fs in self.fileDirectory:
			print fn, fbn, fs

#按照题目要求，磁盘有500块，每块2kB
simulator = FileManagement(500,2)

#创建50个文件后显示文件目录和磁盘状态
for i in range(50):
	fileName = str(i+1)+'.txt'
	fileSize = random.randint(2,10)
	simulator.createFile(fileName,fileSize)
print 'after 50 files created:'
simulator.showDirectory()
simulator.showDisk()
print '====================================================='

#删除部分文件后显示文件目录和磁盘状态
for i in [2*k + 1 for k in range(25)]:
	fileName = str(i) + '.txt'
	simulator.deleteFile(fileName)
print 'after some files deleted:'
simulator.showDirectory()
simulator.showDisk()
print '===================================================='

#新建5个文件并显示文件目录和磁盘状态
for fileName, fileSize in [('A.txt',7), ('B.txt',5), ('C.txt',2), ('D.txt',9), ('E.txt',3.5)]:
	simulator.createFile(fileName,fileSize)
print 'after five new files created:'
simulator.showDirectory()
simulator.showDisk()
print '===================================================='
