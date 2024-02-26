import os

import pandas as pd
import numpy as np
import matplotlib as mpl

def get_shedule_from_int(shed) -> str:
    if shed == 1:
        return "static"
    elif shed == 2:
        return "dynamic"
    elif shed == 3:
        return "guided"
    
    return "zalupa"
    

N1 = 370
N2 = 9350
STEP = int((N2-N1) / 10)

iterations = [x for x in range(N1, N2 + 1, STEP)]
#programms = ["./lab1-seq", "./lab1-par-1", "./lab1-par-10", "./lab1-par-20", "./lab1-par-40"]

shedules = [1, 2, 3]
chunks = [1, 10, 20, 40]


output = {}

for shed in shedules:
    print("shedule: ", get_shedule_from_int(shed), sep="")
    for chunk in chunks:
        output[chunk] = []
        for i in iterations:
            program_to_execute = "./lab1-seq " + str(i) + " 5 " + str(shed) + " " + str(chunk)
            #print(program_to_execute)
            txt = os.popen(program_to_execute).read().replace("\n", "")
            output[chunk].append(txt)

    df = pd.DataFrame(output, index=iterations)
    print(df)