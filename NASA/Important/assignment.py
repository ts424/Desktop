
from array import *
Array1 = array("f",[10, 22, 33, 78, 16, 90, 23, 66, 87, 90])

sum = 0
for num in Array1:
    sum = sum + num
    
mean = sum / len(Array1)

Array1.append(mean)

print("Mean", mean)
print("Updated Array1:", Array1)