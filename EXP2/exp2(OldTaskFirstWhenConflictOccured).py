# -*- coding: utf-8 -*-
# @Author: Leif
# @Date:   2017-05-19 13:00:24
# @Last Modified by:   Leif
# @Last Modified time: 2017-05-19 20:23:23
import Queue
import matplotlib.pyplot as plt


#we define task is a triple [name, arrive_time, service time]
class Task:

	def __init__(self, name, arriveTime, serviceTime):
		self.name = name
		self.arriveTime = arriveTime
		self.leftTime = serviceTime

class Simulator:

	def __init__(self,  taskList, timeSlice =  float("inf")):
		self.__taskList = taskList # a list of tasks
		self.__taskCount = len(taskList)
		self.__clock = 0
		self.__queue = Queue.Queue(-1)
		self.__log = {}
		self.__timeSlice = timeSlice
		self.__countDown = 0
		self.__taskOngoing = None
		self.__nextPid = 1

	def process(self):
		while self.__taskCount > 0:
			#if there is new task arrived, append it to queue
			for task in self.__taskList: 
				if(task.arriveTime == self.__clock):
					self.__queue.put(task)
					#append the time to arrive of new task to log
					self.__log[task.name] = (self.__nextPid,[self.__clock])
					self.__nextPid += 1

			#if the last task ran out of its execution time and the queue
			#is not empty, we admit the task in the front of the queue 
			if (self.__taskOngoing == None) and (not self.__queue.empty()):
				self.__taskOngoing = self.__queue.get()
			#append time point the task started to be executed
				self.__log[self.__taskOngoing.name][1].append(self.__clock)
			#reset the count down
				self.__countDown = min(self.__taskOngoing.leftTime, self.__timeSlice)
			#else either the last task ran out its execution time or the queue
			#is empty. If situation is the first, we continue to execute the last
			#task, else we do nothing
			self.__clock += 1
			if self.__taskOngoing != None:
				self.__countDown -= 1
				self.__taskOngoing.leftTime -= 1
				if(self.__countDown == 0):
					#if the ongoing task is still unfinished, append to the rear of queue
					if(self.__taskOngoing.leftTime != 0):
						self.__queue.put(self.__taskOngoing)
					else:
						self.__taskCount -= 1
					self.__log[self.__taskOngoing.name][1].append(self.__clock)
					self.__taskOngoing = None
			


	def showLog(self):
		for name in self.__log:
			print name, self.__log[name]

	def plot(self):
		plt.figure(figsize = (8,4))
		plt.xlabel("Time")
		plt.ylabel("PID")
		plt.ylim(0, self.__nextPid)
		for name in self.__log:
			for i in range(len(self.__log[name][1])-1):
				x = [self.__log[name][1][i], self.__log[name][1][i+1]]
				y = [self.__log[name][0], self.__log[name][0]]
				if(i%2 == 0):
					plt.plot(x, y, "b:", linewidth = 2)
				else:
					plt.plot(x, y, "r-", linewidth = 2)

		plt.show()




taskList = [Task('A', 0, 3), Task('B', 2, 6), Task('C', 4, 4),
Task('D', 6, 5), Task('E', 8, 2)]

simulator = Simulator(taskList,1)
simulator.process()
simulator.showLog()
simulator.plot()






