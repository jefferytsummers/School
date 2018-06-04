import re
#******************************************************************************
#1: Process a given potential gene sequence.
def find_start_positions():
    g = yield
    while True:
        g = yield tuple(sorted([loc.start() for loc in re.finditer("atg", g)]+\
                [loc.start() for loc in re.finditer("gtg", g)]))
