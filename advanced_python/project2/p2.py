import sys, re

def Process(gene):
    genes      = []
    codon_t    = [pos.start() for pos in re.finditer("tag", gene)]
    codon_a    = [pos.start() for pos in re.finditer("atg", gene)]
    codon_g    = [pos.start() for pos in re.finditer("gtg", gene)]

    iter_a     = 0
    iter_g     = 0
    for t in codon_t:
       while iter_a < len(codon_a):
           testVal = codon_a[iter_a]
           val     = t+3-testVal
           if testVal < t and val in range(33,100) and val%3 == 0:
               genes.append((codon_a[iter_a], t+3-codon_a[iter_a], "atg"))
               iter_a += 1
           else:
               break
       while iter_g < len(codon_g):
           testVal = codon_g[iter_g]
           val     = t+3-testVal
           if testVal < t and val in range(33,100) and val%3 == 0:
               genes.append((codon_g[iter_g], t+3-codon_g[iter_g], "gtg"))
               iter_g += 1
           else:
               break

    genes.sort(key = lambda l: l[0])

    return genes

def main():
    seq    = {}

    for line in open(sys.argv[1]):
        seq[str.lower(line).split()[0]] = [str.lower(line).split()[1]]

    print("seqID  start_loc_relative_to_0  length_including_start_and_stop  \
start_codon  stop_codon")
    for key in sorted(seq):
        gene = (seq[key])[0]
        if "tag" in gene:
            seq[key] = Process(gene)
        for e in seq[key]:
            print(key, '%13d'%e[0],'%28d'%e[1],'%23s'%e[2],'%11s'%"tag")

main()
