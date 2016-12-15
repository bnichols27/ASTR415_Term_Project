import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

f=open('xy.dat','r')

x=[]
y=[]
z=[]
x2=[]
y2=[]
z2=[]
a=0

for line in f.readlines():
	line=line.split()
	x.append(float(line[0]))
        y.append(float(line[1]))
        z.append(float(line[2]))

"""
for line in f.readlines():
	a+=1;
	line=line.split()
	if a<=499:
		x.append(float(line[0]))
		y.append(float(line[1]))
		z.append(float(line[2]))
	else:
		x2.append(float(line[0]))
		y2.append(float(line[1]))
		z2.append(float(line[2]))
"""
f.close()

fig=plt.figure()
ax=Axes3D(fig)
ax.scatter(x[0:500],y[0:500],z[0:500],c='r')
ax.scatter(x[500:1000],y[500:1000],z[500:1000],c='b')
#ax.scatter(x2,y2,z2,c='b')
ax.set_xlabel('X position')
ax.set_ylabel('Y position')
ax.set_zlabel('Z position')
plt.show()	

