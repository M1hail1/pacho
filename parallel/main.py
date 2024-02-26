import os


N = 9750

program_1 = "./lab1/lab1-seq "
program_2 = "./lab2/lab1-seq "

while True:
    program_1_result = os.popen(program_1 + str(N) + " 5").read().replace("\n", "")[0:-3]   # НЕ параллельно
    program_2_result = os.popen(program_2 + str(N) + " 5").read().replace("\n", "")[0:-3]   # Параллельно
    print("N = ", N, ":")
    print('1) ', program_1_result)
    print('2) ', program_2_result)
    if float(program_1_result) <= float(program_2_result):
        print("N found!")
    else:
        print()
    N -= 150

