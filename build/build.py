#!/usr/bin/env python3.10

import os
import shutil
import time
import sys

is_windows = sys.platform.startswith('win32') or sys.platform.startswith('cygwin')
is_linux = sys.platform.startswith('linux')
is_mac = sys.platform.startswith('darwin')

if is_windows:
	print("Detected Windows OS")
	pico_dir = 'D:\\'
elif is_linux:
	print("Detected linux OS")
	username = os.popen("whoami").read().strip() #username needed for linux copy path
	pico_dir = "/media/" + username + "/RPI-RP2/"
elif is_mac:
	print("Detected mac OS")
	pico_dir = "/Volumes/RPI-RP2/"
else:
	print("Unrecognized OS")

def error(message):
	print(message)
	exit()


def cmake():
	print("Python style CMake Build...")
	windows_command = 'cmake -G \"NMake Makefiles\" ..'
	linux_command = 'cmake ..'
	command = windows_command if is_windows else linux_command
	stream = os.popen(command)
	output = stream.read()
	cmake_success_string = "-- Build files have been written to:"
	if cmake_success_string not in output:
		error("CMAKE FAILED")

def nmake():
	print("Python style NMake Build...")
	windows_command = 'nmake'
	linux_command = 'make firefly'
	command = windows_command if is_windows else linux_command
	stream = os.popen(command)
	output = stream.read()
	nmake_success_string = "[100%] Built target firefly"
	if nmake_success_string not in output:
		error("nmake FAILED")
	elf_command = './elf2uf2/elf2uf2 firefly.elf firefly.uf2'
	stream = os.popen(elf_command)
	output = stream.read()
	print("elf2uf2: ", output)
	

def upload():
	print("Python waiting for Pico available at:\t", pico_dir)
	count = 0
	while not os.path.isdir(pico_dir):
		time.sleep(0.1)
		print(".", end="", flush=True)
		count += 1
		if count >= 600: #60 secs timeout
			print("\nTimeout...")
			exit()

	print("\nUploading!")
	build_name = 'firefly.uf2'
	copy_to = pico_dir + build_name
	
	shutil.copyfile(build_name, copy_to)
	print("Copied ", build_name, " to ", copy_to)
	print("Done!")


# Get the total number of args passed to the demo.py
args_total = len(sys.argv)
 
# Get the arguments list 
cmdargs = str(sys.argv)


if "nmake" not in cmdargs:
	cmake()
nmake()
if "-b" in cmdargs: #for ordinary build options
	exit()
upload()