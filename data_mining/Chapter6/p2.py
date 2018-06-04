from re import search
#Class to construct FP-Growth tree.
class Tree(object):
    def __init__(self, name= 'root', count = 0):
        self.name  = name
        self.count = count
        self.data  = [(name, count)]

    def AddChild(self, child, child_count):
        self.data.append((child, child_count))

    def SortNodes(self):
        self.data.sort(key = lambda node: node[1], reverse=True)

    def Print(self):
        for node in self.data:
            print('%s : %d' %(node[0], node[1]))
#******************************************************************************

#Define minimum support.
MIN_SUP = 2

#0: Main.
#******************************************************************************
def main():
    s = {}
    with open('p2.csv') as f:
        for line in f:
            s[line.split(sep = ',')[0]] = line.split()[1:]

    print("Apriori Yields:\n")
    Apriori(s)
    print('#'*80 + '\nFrequent Pattern Growth Yields:\n')
    FP_Growth(s)

#1: This function is responsible for going through the Apriori process.
#******************************************************************************
def Apriori(s):
    for i in range(3):
        if i == 0:
            letters     = GenLetters(s)
            dictionary  = GenDict(s, letters)
            letters     = PrintTiers(dictionary, letters, 1)
            new_letters = MakeString(letters, 1)
        else:
            dictionary  = GenDict(s, new_letters)
            new_dict    = Refine(dictionary)
            letters     = PrintTiers(new_dict, letters)
            new_letters = MakeString(letters)

#2: This function is responsible for implementing an FP-Growth tree.
#******************************************************************************
def FP_Growth(s):
    letters       = GenLetters(s)
    dictionary    = GenDict(s, letters)
    maxKey, count = LocateMostFrequent(dictionary)
    fpTree        = Tree(maxKey, count)
    del dictionary[maxKey]
    for i in range(len(dictionary)):
        maxKey, count = LocateMostFrequent(dictionary)
        del dictionary[maxKey]
        fpTree.AddChild(maxKey, count)

    fpTree.Print()

#1.1: This function generates a set of frequently occuring letters.
#******************************************************************************
def GenLetters(s):
    letters = set()
    for key in s:
        for lst in s[key]:
            for letter in lst:
                letters.add(letter)
    letters.remove(',')

    return letters

#1.2: Generate a dictionary based on input string.
#******************************************************************************
def GenDict(s,letters):
    new_dict = {}
    for letter in letters:
        new_dict[letter] = 0

    for key in s:
        for letter in new_dict.keys():
            if search(ConvertString(letter), s[key][0]):
                new_dict[letter] += 1

    return new_dict

#1.3: This function prints each level of abstraction during the Apriori process.
#******************************************************************************
def PrintTiers(dictionary, letters, fresh_start = False):
    if fresh_start:
        PrintTiers.num = 1

    print("Tier %d \n" %(PrintTiers.num) +'-'*30)
    for (key, value) in sorted(dictionary.items()):
        print("%s : %d" %(key, value))
    print("Frequent items in Tier %d \n"%PrintTiers.num+'-'*30)
    for (key, value) in sorted(dictionary.items()):
        if value > MIN_SUP:
            letters.add(key)
            print("%s : %d" %(key, value))
    print('*'*30)

    PrintTiers.num += 1
    return letters

#1.4: This function is what strings together frequent letters to construct
#frequently occurring patterns during the Apriori process.
#******************************************************************************
def MakeString(letters, length_1 = False):
    new_letters = set()
    for letter_i in letters:
        for letter_j in letters:
            if length_1 or len(letter_i) > len(letter_j):
                new_letters.add(letter_i + letter_j)

    return new_letters

#1.5: This function filters out all letters in the input dictionary that have a
#count of 0.
#******************************************************************************
def Refine(dictionary):
    new_dict = {}
    for key in dictionary:
        if dictionary[key] != 0:
            new_dict[key] = dictionary[key]
    return new_dict

#2.1: This funciton finds the most frequently occuring entry in an input
#dictionary.
#******************************************************************************
def LocateMostFrequent(dictionary):
    maxKey = ''
    dictionary[maxKey] = -1
    for key in dictionary:
        if dictionary[key] > dictionary[maxKey]:
            maxKey = key
    del dictionary['']
    return maxKey, dictionary[maxKey]

#1.2.1: Recursively add '.*' after each letter in a string for ease of use with
#regular expressions.
#******************************************************************************
def ConvertString(string):
    if len(string) == 1:
        return string
    return string[0] + '.*' + ConvertString(string[1:])

#Call main.
main()
