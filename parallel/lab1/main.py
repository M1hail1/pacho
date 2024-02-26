import os

import pandas as pd
import numpy as np
import matplotlib as mpl


N1 = 370
N2 = 9350
STEP = int((N2-N1) / 10)

iterations = [x for x in range(N1, N2 + 1, STEP)]
programms = ["lab1-seq", "lab1-par-1", "lab1-par-10", "lab1-par-20", "lab1-par-40"]

output = {}

for pr in programms:
    output[pr] = []
    for i in iterations:
        txt = os.popen(pr + " " + str(i) + " 5").read().replace("\n", "")
        output[pr].append(txt)

df = pd.DataFrame(output, index=iterations)

print(df)