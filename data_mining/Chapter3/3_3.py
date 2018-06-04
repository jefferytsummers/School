#0: Main.
def main():
    #The data file to use with this program is ages.dat
    inFile = open(input("Enter data file: "), 'r')
    data = [int(i) for i in inFile.readlines()]
    data.sort()

    #The bin depth for this problem is 3.
    depth = int(input("Enter desired bin depth: "))
    col = len(data)//depth

    '''
    Place data read in from ages.dat into bins of appropriate sizes and
    display results for the user.
    '''
    binned_data = bin(data, depth, col)
    print("Original data set (binned):")
    print('\n'.join([' '.join(['{:.4f}'.format(item) for item in row])
              for row in binned_data]))
    print('\n')

    #Call to various smoothing functions.
    smooth_by_mean(binned_data, depth, col)
    smooth_by_median(binned_data, depth, col)
    smooth_by_boundaries(binned_data, depth, col)

#******************************************************************************
#1: Place data in bins of specified depth.
def bin(vec, depth, col):
    bins = [[0 for x in range(depth)] for y in range(col)]
    for i in range(col):
        for j in range(depth):
            bins[i][j] = vec[depth*i + j]
    return bins

#******************************************************************************
#2: Smooth bin by mean.
def smooth_by_mean(vec, depth, col):
    #Temporary list for holding mean values.
    temp = [0 for x in range(depth)]
    #New smoothed list.
    smooth = [[0.0 for x in range(depth)] for y in range(col)]
    #Hold average value of each bin.
    avg = 0

    #Fill in the smooth list by calculating the average of each bin.
    for j in range(col):
        for i in range(depth):
            temp[i] = vec[j][i]
        avg = find_average(temp, depth)
        for i in range(depth):
            smooth[j][i] = avg

    #Display smoothed data for user.
    print("Smoothing bins by mean:")
    print('\n'.join([' '.join(['{:.4f}'.format(item) for item in row])
              for row in smooth]))
    print('\n')

#******************************************************************************
#3: Smooth bin by median.
def smooth_by_median(vec, depth, col):
    #Temporary list for holding median values.
    temp = [0 for x in range(depth)]
    #New smoothed list.
    smooth = [[0.0 for x in range(depth)] for y in range(col)]

    #Fill in the smooth list by finding the median of each bin.
    for j in range(col):
        for i in range(depth):
            smooth[j][i] = vec[j][1]

    #Display smoothed data for user.
    print("Smoothing bins by median:")
    print('\n'.join([' '.join(['{:.4f}'.format(item) for item in row])
              for row in smooth]))
    print('\n')

#******************************************************************************
#4: Smooth bin by boundaries.
def smooth_by_boundaries(vec, depth, col):
    #New smoothed list.
    smooth = [[0.0 for x in range(depth)] for y in range(col)]

    #Fill in the smooth list based on the boundaries of each bin.
    for j in range(col):
        #We know the boundaries will be the same, so we manually assign these.
        smooth[j][0] = vec[j][0]
        smooth[j][-1] = vec[j][-1]
        for i in range(1,depth-1):
            #Assign new values to other positions in the bins based on boundary
            if abs(vec[j][i] - vec[j][0]) < abs(vec[j][i] - vec[j][-1]):
                smooth[j][i] = vec[j][0]
            else:
                smooth[j][i] = vec[j][-1]

    #Display smoothed data for user.
    print("Smoothing bins by boundaries:")
    print('\n'.join([' '.join(['{:.4f}'.format(item) for item in row])
              for row in smooth]))
    print('\n')

#******************************************************************************
#2.1: Calculate average value of input list.
def find_average(vec, depth):
    avg = 0.0
    for i in range(len(vec)):
        avg += vec[i]
    avg /= float(depth)
    return avg

#******************************************************************************
#Call main.
main()
