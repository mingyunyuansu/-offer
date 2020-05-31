s = 'We are happy.'

def with_lib():
    global s
    s = s.replace(' ', '%20')


with_lib()
print (s)