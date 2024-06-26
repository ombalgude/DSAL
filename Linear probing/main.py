# -*- coding: utf-8 -*-
"""
Created on Fri Feb 23 19:56:45 2024

@author: PC
"""

from LinearProbing import hashTable
from record import Record
from Doubletry import doubleHashTable

def input_record():
    record = Record()
    name = input("Enter Name:")
    number = int(input("Enter Number:"))
    record.set_name(name)
    record.set_number(number)
    return record

def menu():
    print("************************")
    print("1. Linear Probing      *")
    print("2. Double Hashing      *")
    print("3. Exit                *")
    print("************************")

def inner_menu():
    print("************************")
    print("1. Insert              *")
    print("2. Search              *")
    print("3. Display             *")
    print("4. Back                *")
    print("************************")

choice1 = 0
while choice1 != 3:
    menu()
    choice1 = int(input("Enter Choice"))
    if choice1 > 3:
        print("Please Enter Valid Choice")

    if choice1 == 1:
        h1 = hashTable()
        choice2 = 0
        while choice2 != 4:
            inner_menu()
            choice2 = int(input("Enter Choice"))
            if choice2 > 4:
                print("Please Enter Valid Choice")

            if choice2 == 1:
                record = input_record()
                h1.insert(record)

            elif choice2 == 2:
                record = input_record()
                position = h1.search(record)

            elif choice2 == 3:
                h1.display()
            
    elif choice1 == 2:
        h2 = doubleHashTable()
        choice2 = 0
        while choice2 != 4:
            inner_menu()
            choice2 = int(input("Enter Choice"))
            if choice2 > 4:
                print("Please Enter Valid Choice")

            if choice2 == 1:
                record = input_record()
                h2.insert(record)

            elif choice2 == 2:
                record = input_record()
                position = h2.search(record)

            elif choice2 == 3:
                h2.display()
