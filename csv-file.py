#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This code does the following:
    1. opens a csv file
    2. goes through each and every line of it and removes all lines that start with alphabets
    3. Converts the 'string' type text of csv file to float
    4. writes it to a new file
"""

import csv

file=input('filename=')                                                         #provide filename
csvI=open(file,'r')                                                             #open csv file in read mode
csvO=open(file+str('stripped'),'w',newline='')                                  #writer object to write csv
csvR=csv.reader(csvI,delimiter=',')                                             #csv reader object with set delimiter: ,
csvW=csv.writer(csvO)
for row in csvR:
    for column in row:
        ###This block of code tests/tries to make the column value into float. Remember even numbers in a csv file
        ###is of type string. If the column value has digits then they can be made float, otherwise it returns an error
        try:
            float(column)
            csvW.writerow(row)
        except ValueError:                                                      #ValueError represents the error
            continue                                                            # Means do nothing
        ###Try block ends here
csvO.close()                                                                    #closes and saves the writer file
    
    

