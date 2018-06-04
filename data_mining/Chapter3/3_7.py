import math

#0: Main.
def main():
    inFile = open(input("Enter data file: "), 'r')
    inList = inFile.readlines()
    age = []
    bf = []
    for i in range(len(inList)):
        age.append(int(inList[i].split(',')[0]))
        bf.append(float(inList[i].split(',')[1]))
    print("Original data vectors: \nAge:")
    print(age)
    print('\nBody fat:')
    print(bf)
    print('\n')

    Z_Score(age, bf)

#******************************************************************************
#1: Z-score normalization using standard deviation.
def Z_Score(aVec, bVec):
    a_avg = Average(aVec)
    b_avg = Average(bVec)
    a_std = Std_Dev(a_avg, aVec)
    b_std = Std_Dev(b_avg, bVec)
    new_age_data = []
    new_bf_data = []
    for i in range(len(aVec)):
        new_age_data.append((aVec[i]-a_avg)/a_std)
        new_bf_data.append((bVec[i]-b_avg)/b_std)

    print("Z-score normalization for age data:")
    print('[' + ', '.join('%.3f' % val for val in new_age_data) + ']')
    print('\n')
    print("Z-score normalization for body fat data:")
    print('[' + ', '.join('%.3f' % val for val in new_bf_data) + ']')
    print('\n')

    r_AB = Pearson_Coeff(aVec, bVec, a_avg, b_avg, a_std, b_std)
    print("The Pearson product moment coefficient is: ",'{:.3f}'.format(r_AB),'\n')

    cov = Covariance(aVec, bVec, a_avg, b_avg)
    print("The covariance is: ",'{:.3f}'.format(cov),'\n')

#******************************************************************************
#1.1: Calculate average value of input vector.
def Average(y):
    a = 0.0
    for i in range(len(y)):
        a += y[i]
    a = a/float(len(y))
    return a

#******************************************************************************
#1.2: Calculate standard deviation of input vector.
def Std_Dev(average, y):
    var = 0.0
    sum = 0.0
    for i in range(len(y)):
        sum += (y[i]**2)
    sum /= len(y)
    var = sum - (average**2)
    return math.sqrt(var)

#******************************************************************************
#1.3: Calculate Pearson product moment coefficient.
def Pearson_Coeff(aVec, bVec, a_avg, b_avg, a_std, b_std):
    product = 0.0
    for i in range(len(aVec)):
        product += aVec[i]*bVec[i]
    return (product - len(aVec)*a_avg*b_avg)/(len(aVec)*a_std*b_std)

#******************************************************************************
#1.4: Calculate covariance.
def Covariance(aVec, bVec, a_avg, b_avg):
    sum = 0
    for i in range(len(aVec)):
        sum += (aVec[i] - a_avg)*(bVec[i] - b_avg)/len(aVec)

    return sum

#******************************************************************************
#Call main.
main()
