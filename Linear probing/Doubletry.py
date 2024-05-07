# -*- coding: utf-8 -*-
"""
Created on Fri Feb 23 19:58:57 2024

@author: PC
"""

from record import Record

class doubleHashTable:
    def __init__(self):
        self.size = int(input("Enter the Size of the hash table: "))
        self.table = list(None for _ in range(self.size))
        self.elementCount = 0
        self.comparisons = 0

    def isFull(self):
        return self.elementCount == self.size

    def h1(self, element):
        return element % self.size

    def h2(self, element):
        return 5 - (element % 5)

    def insert(self, record):
        if self.isFull():
            print("Hash Table Full")
            return False
        position = self.h1(record.get_number())
        if self.table[position] == None:
            self.table[position] = record
            self.elementCount += 1
        else:
            i = 0
            print("Collision has occurred")
            while self.table[position] != None and i <= self.size:
                position = (self.h1(record.get_number()) + i * self.h2(record.get_number())) % self.size
                i += 1
            self.table[position] = record
            self.elementCount += 1
        return True

    def search(self, record):
        position = self.h1(record.get_number())
        if self.table[position] != None:
            self.comparisons += 1
            if (self.table[position].get_name() == record.get_name() 
                    and self.table[position].get_number() == record.get_number()):
                print("Phone number found at position {} and total comparisons are 1".format(position))
                return position
            else:
                i = 1
                while i <= self.size:
                    position = (self.h1(record.get_number()) + i * self.h2(record.get_number())) % self.size
                    if self.table[position] != None:
                        self.comparisons += 1
                        if (self.table[position].get_name() == record.get_name() 
                                and self.table[position].get_number() == record.get_number()):
                            print("Phone number found at position {}".format(position))
                            return position
                        else:
                            i += 1
                print("Record not Found")
                return False

    def display(self):
        print("\n")
        for i in range(self.size):
            print("Hash Value: {} \t\t {}".format(i, self.table[i]))
        print("The number of phonebook records in the Table are : {}".format(self.elementCount))
