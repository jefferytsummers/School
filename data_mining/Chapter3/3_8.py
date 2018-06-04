#0: Main.
def main():
    #Open input file (sales.dat) and store information in data list.
    inFile = open(input("Enter data file: "), 'r')
    data = [int(i) for i in inFile.readlines()]
    data.sort()

    #Get desired depth from user, 3 in this case.
    depth = int(input("Enter desired bin depth: "))
    col = len(data)//depth

    #Call binning functions.
    Bin_Equal_Freq(data, depth, col)
    Bin_Equal_Width(data, depth, col)

#******************************************************************************
#1: Place data in bins of equal depth.
def Bin_Equal_Freq(vec, depth, col):
    bins = [[0 for x in range(depth)] for y in range(col)]

    #Bin data based on depth.
    for i in range(col):
        for j in range(depth):
            bins[i][j] = vec[depth*i + j]

    #Display binned data.
    print("Sales data binned by frequency:")
    print('\n'.join([' '.join(['{:.3f}'.format(item) for item in row])
              for row in bins]))
    print('\n')

#******************************************************************************
#2: Place data in bins of equal width.
def Bin_Equal_Width(vec, depth, col):
    #Holds value of proper bin width.
    width = (vec[-1]-vec[0])//depth
    #Three bins of equal width.
    dim0 = []
    dim1 = []
    dim2 = []

    #Fill respective lists with appropriate values.
    for x in vec:
        if x < vec[0] + width:
            dim0.append(x)
    for x in vec:
        if (x == vec[0] + width or x > vec[0] + width) and x < vec[0] + 2*width:
            dim1.append(x)
    for x in vec:
        if x == vec[0] + 2*width or x > vec[0] + 2*width:
            dim2.append(x)

    #Store bins in a new list.
    bins = [[] for x in range(depth)]
    for i in range(len(dim0)):
        bins[0].append(dim0[i])
    for i in range(len(dim1)):
        bins[1].append(dim1[i])
    for i in range(len(dim2)):
        bins[2].append(dim2[i])

    #Display binned data.
    print("Sales data binned by width:")
    print('\n'.join([' '.join(['{:.3f}'.format(item) for item in row])
              for row in equal_w]))
    print('\n')

#******************************************************************************
#Call main.
main()
