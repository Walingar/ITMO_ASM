#!/usr/bin/python3

import sys
import subprocess
from subprocess import Popen
from random import randrange

def print_green(string):
	print("\033[92m {}\033[00m" .format(string))

def print_red(string):
	print("\033[91m {}\033[00m" .format(string))

def execute(args):
	proc = Popen(args, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	output = proc.stdout.readlines()
	err = proc.stderr.readlines()

	if err == []:
		print("Compile: ", args," OK")
	else:
		print('\n'.join(map(lambda x: x.decode("utf-8"), err)).strip())
		exit(1)

def test(program, times=100):
	for i in range(times):
		a_rand = randrange(0, 10**100)
		b_rand = randrange(0, 10**100)
		a = max(a_rand, b_rand)
		b = min(a_rand, b_rand)
		excepted = str(a - b)
		proc = Popen("./" + program, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		
		proc.stdin.write((str(a) + "\n").encode("utf-8"))
		proc.stdin.write((str(b) + "\n").encode("utf-8"))

		out, err = map(lambda x: x.decode("utf-8"), proc.communicate())

		output = out.strip()
		if err != '':
			print("Execution fails: ", program)
			print(err.strip())
			exit(1)
		
		print("{:15s}".format("First arg: ") + str(a))
		print("{:15s}".format("Second arg: ") + str(b))
		print("{:15s}".format("Excepted: ") + excepted)
		print("{:15s}".format("Found: ") + output)
		if (excepted == output):
			print_green("[OK]")
		else:
			print_red("[WA]")
		print()


file_name = "sub"

asm_file = "%s.asm" % file_name
obj_file = "%s.o"   % file_name
out_file = "%s"     % file_name
utils = ["../utils/read_write.o"]

command = "nasm -f elf64 -g -F dwarf {} -o {}".format(asm_file, obj_file)
execute(command)

command = "ld {} {} -o {}".format(obj_file, ' '.join(utils), out_file)
execute(command)

test(out_file)

command = "rm -rf " + ' '.join([obj_file, out_file])
execute(command)