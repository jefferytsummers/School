import math
#0: Main.
def main():
    iFile = input("Enter data file: ")
    infile = open(iFile, 'r')
    inList = infile.readlines()
    data = [int(i) for i in inList]
    Sort(data)
    item = int(input("Enter value in question: "))
    index = -1
    for i in range(len(data)):
        if data[i] == item:
            index = i
    if index == -1:
        print("Value not in list.")
        exit()
    Min_Max(data, index)
    Z_Score(data, index)
    Z_Score_Absolute(data, index)
    Decimal_Scaling(data, index)

#******************************************************************************
#1: Sort vector based on absolute values.
def Sort(vec):
    for i in range(len(vec)):
        for j in range(len(vec)):
            if abs(vec[j]) > abs(vec[i]):
                vec[i], vec[j] = vec[j], vec[i]

#******************************************************************************
#2: Normalize data using min-max technique.
def Min_Max(x, pos):
    #Values specified by problem.
    min = 0
    max = 1
    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(x)):
        newdata.append((x[i]-x[0])/(x[-1]-x[0])*(max - min))

    #Display results of normalization.
    print("Min-max normalization yields:")
    print('{:.2f}'.format(newdata[pos]))
    print('\n')

#******************************************************************************
#3: Z-score normalization using standard deviation.
def Z_Score(x, pos):
    #Find average value and standard deviation.
    avg = Average(x)
    std = 12.94
    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(x)):
        newdata.append((x[i]-avg)/std)

    #Display results of normalization.
    print("Z-score normalization yields:")
    print('{:.2f}'.format(newdata[pos]))
    print('\n')

#******************************************************************************
#4: Z-score normalization using mean absolute deviation.
def Z_Score_Absolute(x, pos):
    #Find average and mean absolute deviation.
    avg = Average(x)
    std_abs = Absolute_Dev(avg, x)
    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(x)):
        newdata.append((x[i]-avg)/std_abs)

    #Display results of normalization.
    print("Z-score normalization using mean absolute deviation yields:")
    print('{:.2f}'.format(newdata[pos]))
    print('\n')

#******************************************************************************
#5: Normalize using decimal scaling.
def Decimal_Scaling(x, pos):
    #Stores value of appropriate exponent.
    exponent = 1
    '''
    We know the last value of the list will be the maximum values, so this
    will be our check value.
    '''
    check = x[-1]

    #Calculate exponenet value.
    while check//10 != 0:
        check /= 10
        exponent += 1

    #Normalization factor.
    scale = 10**exponent

    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(x)):
        newdata.append(x[i]/scale)

    #Display results of normalization.
    print("Normalization by decimal scaling yields:")
    print('{:.2f}'.format(newdata[pos]))
    print('\n')


#******************************************************************************
#3.1: Calculate average of input vector.
def Average(y):
    a = 0.0
    for i in range(len(y)):
        a += y[i]
    a = a/float(len(y))
    return a

#******************************************************************************
#4.1: Calculate mean absolute deviation of input vector.
def Absolute_Dev(average, y):
    sum = 0.0
    for i in range(len(y)):
        sum += abs(y[i]-average)

    sum /= len(y)
    return sum

#******************************************************************************
#Call main.
main()
