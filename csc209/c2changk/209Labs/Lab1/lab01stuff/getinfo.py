#!/usr/local/bin/python3

import sys

# By default, print() writes to standard output

print("Please enter your name:")

# By default input() reads from standard input
stu_name = input()

print("Please enter your classes this term:")
classes = input()

if len(stu_name.strip()) == 0:
	# If an error occurs, we want to write to standard error
	print("Error: name cannot be empty", file=sys.stderr)

	# In this case we choose to terminate the program with a non-zero exit
	# value indicating that an error occurred.
	exit(1)
	
if len(classes.strip()) == 0:
	print("Error: you are at least taking one class", file=sys.stderr)
	exit(1)
else:
	data = classes.split(" ")
	

print("Hi ", stu_name, ", are you enjoying ", data[0], "?", sep="")
