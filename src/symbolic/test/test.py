import time, os

total_run = 100

time_start = time.time()
for i in range(total_run):
  #os.system("chicken-csc test/note-structure-test.scm")
  #os.system("test/note-structure-test")
  os.system("guile note-structure-test.scm")
time_end = time.time()

print("\n")
print("Average time: {}".format((time_end - time_start)/total_run))

#print("Total time: {}".format(time_end - time_start))