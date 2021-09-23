#ind_task1
# -2 1 3 -1 -1 -1 100 10 -5 0
# max_value = 1000
cur_x = int(input())
prev_x = cur_x  
max_rising = 0
cur_rising = 0
count_numbers = 1
while cur_x:
    if cur_x - prev_x > 0:
        cur_rising += cur_x - prev_x
        if max_rising < cur_rising:
            max_rising = cur_rising
    else:
        cur_rising = 0
    prev_x = cur_x
    cur_x = int(input())
    count_numbers += 1
print("Получено ", count_numbers, " чисел")
print("Наибольшая высота подъема: ", max_rising)
#print(sequence)
