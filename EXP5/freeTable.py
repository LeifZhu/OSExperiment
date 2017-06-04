# -*- coding: utf-8 -*-
# @Author: Leif
# @Date:   2017-06-04 15:47:07
# @Last Modified by:   Leif
# @Last Modified time: 2017-06-04 16:26:58
import random
import math

disk = [[0,500]]
directory = []

def allocate(space):
	blocks = int(math.ceil(space/2.0))
	for section in disk:
		if section[1] >= blocks:
			section[1] -= blocks
			firstBlock = section[0]
			section[0] += blocks
			if section[1] == 0:
				disk.remove(section)
			return firstBlock
	return -1


def recycle(firstBlock, space):
	blocks = int(math.ceil(space/2.0))
	i = 0
	while disk[i][0] < firstBlock and i < len(disk):
		i += 1
	disk.insert(i, [firstBlock, blocks])
	if i > 0 and firstBlock == disk[i-1][0] + disk[i-1][1]:
		disk[i-1][1] += disk[i][1]
		del disk[i]
		i = i-1
	if i < len(disk)-1 and firstBlock + blocks == disk[i+1][0]:
		disk[i][1] += disk[i+1][1]
		del disk[i+1]

for i in range(50):
	fileName = str(i+1)+'.txt'
	fileSize = random.randint(2,10)
	directory.append((fileName,allocate(fileSize),fileSize))
print 'after 50 files created:'
print 'file directory:',directory
print 'free sections in disk:',disk
print '====================================================='


for i in [2*k + 1 for k in range(25)]:
	for j in range(len(directory)):
		if directory[j][0] == str(i)+'.txt':
			recycle(directory[j][1], directory[j][2])
			del directory[j]
			break
print 'after some files deleted:'
print 'file directory:',directory
print 'free sections in disk:',disk
print '===================================================='

for newFile in [('A.txt',7), ('B.txt',5), ('C.txt',2), ('D.txt',9), ('E.txt',3.5)]:
	directory.append((newFile[0], allocate(newFile[1]), newFile[1]))

print 'after five new files created:'
print 'file directory:',directory
print 'free sections in disk:',disk
print '===================================================='


	

