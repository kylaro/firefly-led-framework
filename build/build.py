import os
import shutil
import time
import sys
 


# os.system('cmake -G \"NMake Makefiles\" ..')
# os.system('nmake')

def error(message):
	print(message)
	exit()

def cmake():
	print("Python style CMake Build...")

	stream = os.popen('cmake ..')
	output = stream.read()
	cmake_success_string = "-- Build files have been written to:"
	if cmake_success_string not in output:
		error("CMAKE FAILED")

def nmake():
	print("Python style NMake Build...")

	stream = os.popen('make')
	output = stream.read()
	nmake_success_string = "[100%] Built target firefly"
	if nmake_success_string not in output:
		error("nmake FAILED")

def upload():
	print("Python waiting for Pico available")
	count = 0
	while not os.path.isdir('/mnt/d'):
		
		time.sleep(0.1)
		count += 1
		if count > 10:
			os.popen('sudo mkdir /mnt/d', stdout=None)
			os.popen('sudo mount -t drvfs D: /mnt/d', stdout=None)
			print(".", end="", flush=True)
			count = 0

	print("Uploading!")
	shutil.copy('firefly.uf2', '/mnt/d/firefly.uf2')

	print("Done!")


# Get the total number of args passed to the demo.py
args_total = len(sys.argv)
 
# Get the arguments list 
cmdargs = str(sys.argv)

if "nmake" not in cmdargs:
	cmake()
nmake()
upload()
