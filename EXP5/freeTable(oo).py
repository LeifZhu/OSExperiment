# -*- coding: utf-8 -*-
# @Author: Leif
# @Date:   2017-06-04 16:54:06
# @Last Modified by:   Leif
# @Last Modified time: 2017-06-04 17:42:52

import random
import math

class FileManagement(object):
	def __init__(self, diskSize, blockSize):
		self.diskSize = diskSize
		self.disk = [[0,diskSize]]
		self.blockSize = float(blockSize)
		self.fileDirectory = []

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


	def recycle(self,firstBlock, space):
		blocks = int(math.ceil(space/self.blockSize))
		i = 0
		while self.disk[i][0] < firstBlock and i < len(self.disk):
			i += 1
		self.disk.insert(i, [firstBlock, blocks])
		if i > 0 and firstBlock == self.disk[i-1][0] + self.disk[i-1][1]:
			self.disk[i-1][1] += self.disk[i][1]
			del self.disk[i]
			i = i-1
		if i < len(self.disk)-1 and firstBlock + blocks == self.disk[i+1][0]:
			self.disk[i][1] += self.disk[i+1][1]
			del self.disk[i+1]

	def createFile(self, fileName, fileSize):
		self.fileDirectory.append((fileName,self.allocate(fileSize),fileSize))

	def deleteFile(self, fileName):
		for i in range(len(self.fileDirectory)):
			if self.fileDirectory[i][0] == fileName:
				self.recycle(self.fileDirectory[i][1], self.fileDirectory[i][2])
				del self.fileDirectory[i]
				break

	def showDisk(self):
		print 'free sections in disk:'
		print 'format: <first block number> <number of blocks>'
		for fbn, nob in self.disk:
			print fbn, nob

	def showDirectory(self):
		print 'files in disk:'
		print 'format: <file name> <first block number> <file size>(kb)'
		for fn, fbn, fs in self.fileDirectory:
			print fn, fbn, fs


simulator = FileManagement(500,2)

for i in range(50):
	fileName = str(i+1)+'.txt'
	fileSize = random.randint(2,10)
	simulator.createFile(fileName,fileSize)
print 'after 50 files created:'
simulator.showDirectory()
simulator.showDisk()
print '====================================================='


for i in [2*k + 1 for k in range(25)]:
	fileName = str(i) + '.txt'
	simulator.deleteFile(fileName)
print 'after some files deleted:'
simulator.showDirectory()
simulator.showDisk()
print '===================================================='

for fileName, fileSize in [('A.txt',7), ('B.txt',5), ('C.txt',2), ('D.txt',9), ('E.txt',3.5)]:
	simulator.createFile(fileName,fileSize)
print 'after five new files created:'
simulator.showDirectory()
simulator.showDisk()
print '===================================================='
