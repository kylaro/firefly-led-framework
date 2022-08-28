import os
import os
import shutil
import time
import sys
 


# os.system('cmake -G \"NMake Makefiles\" ..')
# os.system('nmake')



is_windows = False
windows_string = 'not recognized'
stream = os.popen('ls')
output = stream.read()
if len(output) == 0:
	is_windows = True
	print("detected windows")
is_linux = not is_windows
if is_linux:
	print("detected linux")

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
	linux_command = 'make'
	command = windows_command if is_windows else linux_command
	stream = os.popen(command)
	output = stream.read()
	nmake_success_string = "[100%] Built target firefly"
	if nmake_success_string not in output:
		error("nmake FAILED")

def upload():
	print("Python waiting for Pico available")
	count = 0
	windows_dir = 'D:\\'
	linux_dir = '/mnt/d'
	linux_mount1 = 'sudo mkdir /mnt/d'
	linux_mount2 = 'sudo mount -t drvfs D: /mnt/d'
	pico_dir = windows_dir if is_windows else linux_dir
	while not os.path.isdir(pico_dir):
		time.sleep(0.1)
		print(".", end="", flush=True)
		if is_linux:
			os.popen(linux_mount1)
			os.popen(linux_mount2)


	print("Uploading!")
	build_name = 'firefly.uf2'
	windows_copy_dir = 'D:\\'
	linux_copy_dir = '/mnt/d/'
	copy_to = windows_copy_dir if is_windows else linux_copy_dir
	copy_to = copy_to + build_name
	
	shutil.copy(build_name, copy_to)

	print("Done!")


# Get the total number of args passed to the demo.py
args_total = len(sys.argv)
 
# Get the arguments list 
cmdargs = str(sys.argv)

if "nmake" not in cmdargs:
	cmake()
nmake()
upload()
