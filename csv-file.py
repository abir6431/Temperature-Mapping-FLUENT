#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This code does the following:
    1. opens a csv file
    2. removes rows that start with alphabets
    4. writes it to a new file
"""

import csv

file=input('filename=')                                                         #provide filename
csvI=open(file,'r')                                                             #open csv file in read mode
csvO=open(file+str('stripped'),'w',newline='')                                  #writer object to write csv
csvR=csv.reader(csvI,delimiter=',')                                             #csv reader object with set delimiter: ,
csvW=csv.writer(csvO)                                                           #csv writer object
###This function tries to make the s value into float type. If the s value has alphabets it returns an error thus the function
###will return False
def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False 
##############################################################################                                                          

for row in csvR:
    for column in row:
        if is_number(column)==True:                                             #returns True is column value is number
            csvW.writerow(row)                                                  #write this whole row down to the csv file
            break                                                               #return to the 'row' for loop
csvO.close()   
