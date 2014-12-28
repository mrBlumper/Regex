"""from graphviz import Digraph

dot = Digraph(comment='The Round Table')
dot.format = "png"
dot.render('test.cv', view=True)"""


operations = {'(': 1, '|': 2, '.': 3, '?': 4, '*': 4, '+': 4}

def get_precedance(w):
    try:
        return operations[w]
    except:
        return 6

def to_postfix(reg):
    output = []
    stack = []
    for c in reg:
        if c == '(':
            stack.append(c)
        elif c == ")":
            while len(stack) and stack[-1] != '(':
                output.append(stack.pop())
            if len(stack):
                stack.pop()
        else:
            while len(stack):
                c_s = stack[-1]
                if get_precedance(c_s) >= get_precedance(c):
                    output.append(stack.pop())
                else:
                    break
            stack.append(c)
    while len(stack):
        output.append(stack.pop())
    return output

def format_regex(regex):
    output = ""
    for i, c in enumerate(regex):
        if i + 1 < len(regex):
            output += c
            n = regex[i + 1]
            if c != '(' and n != ')' and c != '|' and n != '|' and n != '.' and n != '?' and n != '*' and n != '+':
                output += '.'
    output += regex[-1]
    return output

def to_infix(postfix):
    stack = []
    for c in postfix:
        #print (c)
        if c in "*+?":
            stack.append(stack.pop() + c)
        elif c in "|.":
            temp = "(" + stack[-2] + c + stack[-1] + ")"
            stack.pop()
            stack.pop()
            stack.append(temp)
        else:
            stack.append(c)
    return stack[0]

def build_nfa(postfix):
    pass

reg_str = "(c|(ab)+|d)+"
import re
reg = re.compile(reg_str)

tests = ["abc", "ab|c", "ab+c", "a(bb)+c"]
for test in tests:
    print ("regex: ", "".join((format_regex(test))))
    print ("    postfix: ", "".join(to_postfix(format_regex(test))))
    print ("    infix: ", to_infix("".join(to_postfix(format_regex(test)))))
