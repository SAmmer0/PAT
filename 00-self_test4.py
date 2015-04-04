#-*-encoding=utf-8 -*-

def num_dict(num_str):
    digits = [str(i) for i in xrange(10)]
    res = dict()
    for item in digits:
        res[item] = 0
    for s in num_str:
        res[s]+=1
    return res

def compare(a_dict, b_dict):
    digits = [str(i) for i in xrange(10)]
    for item in digits:
        if a_dict[item] != b_dict[item]:
            return False
    return True

if __name__== "__main__":
    input = raw_input()
    input_dict = num_dict(input)
    output_dict = num_dict(str(2*int(input)))
    if compare(input_dict, output_dict):
        print "Yes"
    else:
        print "No"
    print 2*int(input)