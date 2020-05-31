arr = [[1, 2, 8, 9], 
       [2, 4, 9, 12], 
       [4, 7, 10, 13], 
       [6, 8, 11, 15]]

len_arr = 4
num = 7
result = ''

def brute_force():
    global result, num
    for each_line in arr:
        for x in each_line:
            if x == num:
                result = 'Found!'
                break

def from_right_up():
    global result, num, len_arr
    j = len_arr - 1
    i = 0
    while (i < len_arr and j >= 0):
        if arr[i][j] == num:
            result = 'Found!'
            break
        elif (arr[i][j] < num):
            i += 1
        elif (arr[i][j] > num):
            j -= 1

def from_down_left():
    global len_arr, num, result
    i = len_arr - 1
    j = 0
    while (i >= 0 and j < len_arr):
        if (arr[i][j] == num):
            result = 'Found!'
            break
        elif (arr[i][j] < num):
            j += 1
        elif (arr[i][j] > num):
            i -= 1



#brute_force()
#from_right_up()
#from_down_left ()




if result:
    print(result)
else:
    print('Not found.')


