# -*- coding: utf-8 -*-
"""
Created on Fri Feb 23 19:58:23 2024

@author: PC
"""

from record import Record

class hashTable:
    def __init__(self):
        self.size = int(input("Enter the Size of the hash table: "))
        self.table = list(None for _ in range(self.size))
        self.elementCount = 0
        self.comparisons = 0

    def isFull(self):
        return self.elementCount == self.size

    def hashFunction(self, element):
        return element % self.size

    def insert(self, record):
        if self.isFull():
            print("Hash Table Full")
            return False
        num = record.get_number()
        position = self.hashFunction(num)
        if self.table[position] == None:
            self.table[position] = record
            self.elementCount += 1
        else:
            while self.table[position] != None:
                position = (position + 1) % self.size
            self.table[position] = record
            self.elementCount += 1
        return True

    def search(self, record):
        position = self.hashFunction(record.get_number())
        if self.table[position] != None:
            if (self.table[position].get_name() == record.get_name() 
                    and self.table[position].get_number() == record.get_number()):
                print("Phone number found at position {} and total comparisons are 1".format(position))
                return position
            while self.table[position] != None or self.comparisons <= self.size:
                if (self.table[position].get_name() == record.get_name() 
                        and self.table[position].get_number() == record.get_number()):
                    i = self.comparisons + 1
                    print("Number found at position {} and total comparisons are {}".format(position, i))
                    return position
                position = (position + 1) % self.size
                self.comparisons += 1
        print("Record not found")
        return False

    def display(self):
        print("\n")
        for i in range(self.size):
            print("Hash Value: {} \t\t {}".format(i, self.table[i]))
