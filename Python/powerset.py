import pprint

# def powerset(s, result):
#    return ([powerset(s[1:], result + [s[0]]), powerset(s[1:], result)]
#            if s
#            else result)


def powerset(set_, path):
    return (
        powerset(set_[1:], path + [set_[0]]) + powerset(set_[1:], path)
        if set_
        else [path]
    )


# def traverse(s, path):
#    if s:
#        traverse(s[1:], path + [s[0]])
#        traverse(s[1:], path)
#    else:
#        print(path)

print(powerset([1, 2, 3, 4], []))
# pprint.pprint(powerset([1,2,3], []))
