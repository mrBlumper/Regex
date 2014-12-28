from graphviz import Digraph
"""
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


class Link:
    def __init__(self, what, to):
        self.what = what
        self.to = to


NB_NODES = 0
class Node:
    def __init__(self, id = -1):
        global NB_NODES
        self.start = None
        self.out = []
        if id < 0:
            self.id = NB_NODES
            NB_NODES += 1
        else:
            self.id = id
    def addLink(self, link, to):
        if isinstance(link, Link):
            self.out.append(link)
        else:
            self.out.append(Link(link, to))

def show_nfa(node):
    dot = Digraph(comment='NFA')
    cache = {i: False for i in range(NB_NODES)}
    cache_links = {}
    stack = [node]
    while len(stack):
        current = stack.pop()
        dot.node(str(current.id), str(current.id))
        cache[current.id] = True
        for n in current.out:
            key = str(str(current.id)+str(n.to.id)+n.what)
            if not key in cache_links:
                dot.edge(str(current.id), str(n.to.id), label = (n.what, "&#949;")[n.what == "¤"])

                cache_links[key] = True
            if cache[n.to.id]:
                continue
            stack.append(n.to)
    dot.format = "png"
    dot.render("test.gv", view = True)

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
    stack = []
    start = Node()
    current = start
    for c in postfix:
        if c == "?":
            s, e = stack.pop()
            s.addLink("¤", e)
            stack.append((s, e))
        elif c == "+":
            s, e = Node(), Node()
            t_s, t_e = stack.pop()
            t_s.addLink("¤", t_e)
            s.addLink("¤", t_s)
            t_e.addLink("¤", e)
            stack.append((s, e))
        elif c == "*":
            s, e = Node(), Node()
            t_s, t_e = stack.pop()
            t_s.addLink("¤", t_e)
            s.addLink("¤", t_s)
            t_e.addLink("¤", e)
            s.addLink("¤", e)
            stack.append((s, e))
        elif c == ".":
            n1_s, n1_e = stack.pop()
            n2_s, n2_e = stack.pop()
            for o in n1_s.out:
                n2_e.out.append(o)

            stack.append((n2_s, n1_e))
        elif c == "|":
            n1_s, n1_e = stack.pop()
            n2_s, n2_e = stack.pop()
            s = Node()
            e = Node()
            s.addLink("¤", n1_s)
            s.addLink("¤", n2_s)
            n1_e.addLink("¤", e)
            n2_e.addLink("¤", e)
            stack.append((s, e))
        else:
            temp_s = Node()
            temp_e = Node()
            temp_s.addLink(c, temp_e)
            stack.append((temp_s, temp_e))

    return stack[0][0]


reg_str = "(c|(ab)+|d)+"
import re
reg = re.compile(reg_str)
"""
tests = ["abc", "ab|c", "ab+c", "a(bb)+c"]
for test in tests:
    print ("regex: ", "".join((format_regex(test))))
    print ("    postfix: ", "".join(to_postfix(format_regex(test))))
    print ("    infix: ", to_infix("".join(to_postfix(format_regex(test)))))
"""
"""
n1 = Node()
n2 = Node()
n3 = Node()
n1.addLink('a', n2)
n1.addLink('b', n2)
n2.addLink('o', n3)


show_nfa(n1)

"""
test = "a*(b|cd?)+"
print (format_regex(test))
show_nfa(build_nfa("".join(to_postfix(format_regex(test)))))