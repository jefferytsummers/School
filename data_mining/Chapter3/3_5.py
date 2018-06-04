import math
#0: Main.
def main():
    #Initialize and display original data vector.
    data = [200, 300, 400, 600, 1000]
    print("Original data vector:")
    print(data)
    print('\n')

    #Call to normalization functions.
    Min_Max(data)
    Z_Score(data)
    Z_Score_Absolute(data)
    Decimal_Scaling(data)

#******************************************************************************
#1: Normalize data using min-max technique.
def Min_Max(vec):
    #Values specified by problem.
    min = 0
    max = 1
    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(vec)):
        newdata.append((vec[i]-vec[0])/(vec[-1]-vec[0])*(max - min))

    #Display results of normalization.
    print("Min-max normalization yields:")
    print(newdata)
    print('\n')

#******************************************************************************
#2: Z-score normalization using standard deviation.
def Z_Score(vec):
    #Find average value and standard deviation.
    avg = Average(vec)
    std = Std_Dev(avg, vec)
    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(vec)):
        newdata.append((vec[i]-avg)/std)

    #Display results of normalization.
    print("Z-score normalization yields:")
    print('[' + ', '.join('%.4f' % val for val in newdata) + ']')
    print('\n')

#******************************************************************************
#3: Z-score normalization using mean absolute deviation.
def Z_Score_Absolute(vec):
    #Find average and mean absolute deviation.
    avg = Average(vec)
    abs_dev = Absolute_Dev(avg, vec)
    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(vec)):
        newdata.append((vec[i]-avg)/abs_dev)

    #Display results of normalization.
    print("Z-score normalization using mean absolute deviation yields:")
    print('[' + ', '.join('%.4f' % val for val in newdata) + ']')
    print('\n')

#******************************************************************************
#4: Normalize using decimal scaling.
def Decimal_Scaling(vec):
    #Stores value of appropriate exponent.
    exponent = 1
    '''
    We know the last value of the list will be the maximum values, so this
    will be our check value.
    '''
    check = vec[-1]

    #Calculate exponenet value.
    while check//10 != 0:
        check //= 10
        exponent += 1

    #Normalization factor.
    scale = 10**exponent

    #Stores normalized data.
    newdata = []

    #Perform normalization.
    for i in range(len(vec)):
        newdata.append(vec[i]/scale)

    #Display results of normalization.
    print("Normalization by decimal scaling yields:")
    print(newdata)
    print('\n')

#******************************************************************************
#2.1: Calculate average of input vector.
def Average(vec):
    avg = 0.0
    for i in range(len(vec)):
        avg += vec[i]
    avg = avg/float(len(vec))
    return avg

#******************************************************************************
#2.2: Calculate standard deviation of input vector.
def Std_Dev(avg, vec):
    #Variance
    var = 0.0

    #Calculate variance.
    sum = 0.0
    for i in range(len(vec)):
        sum += (vec[i]**2)
    sum /= len(vec)
    var = sum - (avg**2)

    #Return standard deviation.
    return math.sqrt(var)

#******************************************************************************
#3.1: Calculate mean absolute deviation of input vector.
def Absolute_Dev(avg, vec):
    sum = 0.0
    for i in range(len(vec)):
        sum += abs(vec[i]-avg)

    sum /= len(vec)
    return sum

#******************************************************************************
#Call main.
main()
