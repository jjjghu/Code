import numpy as np
import matplotlib.pyplot as plt

t= np.arange(-6, 6, 0.1)
s=1/(1+(np.e**(-t)))

plt.plot(t,s)
plt.title("sigmoid function")
plt.show()