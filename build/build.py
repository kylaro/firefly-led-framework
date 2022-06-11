import os
import shutil
import time
# os.system('cmake -G \"NMake Makefiles\" ..')
# os.system('nmake')

def error(message):
	print(message)
	exit()

print("Python style CMake Build...")

stream = os.popen('cmake -G \"NMake Makefiles\" ..')
output = stream.read()
cmake_success_string = "-- Build files have been written to:"
if cmake_success_string not in output:
	error("CMAKE FAILED")

print("Python style NMake Build...")

stream = os.popen('nmake')
output = stream.read()
nmake_success_string = "[100%] Built target firefly"
if nmake_success_string not in output:
	error("nmake FAILED")

print("Python waiting for Pico available")
count = 0
while not os.path.isdir('D:\\'):
	time.sleep(0.01)
	count += 1
	if count > 10:
		print(".", end="", flush=True)
		count = 0

print("Uploading!")
shutil.copy('firefly.uf2', 'D:\\firefly.uf2')

print("Done!")