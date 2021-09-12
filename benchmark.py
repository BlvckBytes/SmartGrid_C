import os
import time

start = time.time()
os.system("cat inp/level2/level2_5.in | ./a.out > level2_5.out");
end = time.time()

print(f'C code for level2_5.in took {end-start}s')
