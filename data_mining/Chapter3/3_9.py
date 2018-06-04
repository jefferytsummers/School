import numpy as np
import matplotlib.pyplot as plt

def main():
    #Vector to hold the data.
    data = [13,15,16,16,19,20,20,21,22,22,25,25,25,25,30,33,33,35,35,35,35,36,40,45,46,52,70]

    #Plot the histogram using matplotlib's histogram tool.
    plt.hist(data, bins=[13,23,33,43,53,63,73], color = 'purple')
    plt.xlabel('Age')
    plt.ylabel('Frequency')
    plt.title(r'$\mathrm{Histogram\ of\ Age:}$')
    plt.show()

#Call main.
main()
