import re

def rem_special(s):
    return re.sub("[^\w\s]","",s)

def rem_singleC(s):
    return re.sub('\s+\S\s+|^\S\s+','',s)

def rem_mulSpace(s):
    return re.sub(' {2,}',' ',s)

def lower_all(s):
    return s.lower()

def to_literal(s):
    s = re.sub("won't","will not",s)
    return re.sub("([a-zA-Z]+)n't",'\\1 not',s)

try:
    f = open("1.txt","r+")
except Exception as e:
    print(e)

s = f.read()
funcs = {'a':rem_special,'b':rem_singleC,'c':rem_mulSpace,'d':lower_all,'e':to_literal}

while(True):
    uin = input('a: remove special characters,\nb: remove single character words,\nc: remove reduntant spaces,\nd: make lowercase,\ne: abbreviation to literal,\nAny other key to exit\nYour choice: ').strip()[0].lower()
    func = funcs.setdefault(uin,"No such option, exiting")

    if(isinstance(func,str)):
        print(func)
        del funcs[uin]
        break
    else:
        print('\nBefore:',s,end='')
        x = func(s)
        print('After:',x,end='')
        f.seek(0)
        f.truncate()
        f.write(x)
        
        f.seek(0)
        print('File:',f.read())

f.close()
