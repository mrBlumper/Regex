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
NODES_pointers = []
class Node:
    def __init__(self, id = -1):
        global NB_NODES
        self.start = None
        self.out = []
        if id < 0:
            self.id = NB_NODES
            NB_NODES += 1
            NODES_pointers.append(self)
        else:
            self.id = id
            NODES_pointers[id] = self
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
            t_e.addLink("¤", t_s)
            s.addLink("¤", t_s)
            t_e.addLink("¤", e)
            stack.append((s, e))
        elif c == "*":
            s, e = Node(), Node()
            t_s, t_e = stack.pop()
            t_e.addLink("¤", t_s)
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

    return stack[0]

def closures(input):
    output = []

def find_epsilons(nodes):
    if not isinstance(nodes, list):
        nodes = [nodes]
    results = [n for n in nodes]
    stack = [n for n in nodes]
    cache = {n.id: True for n in nodes}
    while len (stack):
        current = stack.pop()
        cache[current.id] = True
        for n in current.out:
            if n.what == "¤" and not n.to.id in cache:
                stack.append(n.to)
                results.append(n.to)
    return results

def move_NFA(nodes, symbol):
    result = []
    for node in nodes:
        for edge in node.out:
            if edge.what == symbol:
                result.append(edge.to)
    return result

def move_DFA(nodes, symbol):
    return find_epsilons(move_NFA(nodes, symbol))

def show_dfa(dfa):
    dot = Digraph(comment='DFA')
    for i, node in enumerate(dfa):
        dot.node(str(i), str(i), shape = ("circle", "doublecircle")[node.is_end])
        for c in node.out:
            dot.edge(str(i), str(node.out[c]), label = c)
    dot.format = "png"
    dot.render("test.gv", view = True)



def exist(dfa, current):
    for i, n in enumerate(dfa):
        if n == current:
            return i
    return -1

class DFA_branch:
    def __init__(self, nodes, id_end):
        self.nodes = nodes
        self.is_end = False
        if id_end in self.nodes:
            self.is_end = True
        self.out = {}
        self.sum = sum(self.nodes)
    def add_link(self, symbol, target):
        self.out[symbol] = target
    def __eq__(self, other):
        if not (len(self.nodes) == len(other.nodes)  and self.sum == other.sum) :
            return False
        self.nodes.sort()
        other.nodes.sort()
        for a, b in zip(self.nodes, other.nodes):
            if not a == b:
                return False
        return True

def convert_to_dfa(nfa, end = None, alphabet = None):
    if alphabet is None:
        alphabet = [chr(i) for i in range(33, 126)]
    dfa = []
    dfa.append(DFA_branch([n.id for n in find_epsilons(nfa)], end.id))
    stack = [dfa[0]]
    while len(stack):
        current = stack.pop()
        for c in alphabet:
            temp = DFA_branch([n.id for n in move_DFA([NODES_pointers[i] for i in current.nodes], c)], end.id)
            if not len(temp.nodes):
                continue
            #print ("-",[n.id for n in current.nodes], [n.id for n in temp.nodes])
            pos = exist(dfa, temp)
            if pos < 0:
                dfa.append(temp)
                stack.append(temp)
                pos = len(dfa) - 1
            current.add_link(c, pos)

    return dfa




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

def match(dfa, string):
    state = 0
    last_end = 0
    for i, c in enumerate(string):
        #print (c, state)
        if not c in dfa[state].out:
            break

        if dfa[dfa[state].out[c]].is_end:
            last_end = i+1
        state = dfa[state].out[c]

    #print (last_end)
    return string[:last_end]

test = "bon(jour|soir)"
print (format_regex(test))
nfa, end_nfa = build_nfa("".join(to_postfix(format_regex(test))))
#show_nfa(build_nfa("".join(to_postfix(format_regex(test)))))
"""
print (NODES_pointers[7].id)
print ([n.id for n in find_epsilons(NODES_pointers[7])])
A = move_NFA(find_epsilons(NODES_pointers[7]), 'b')
print ([n.id for n in find_epsilons(A)])
"""
dfa_ = convert_to_dfa(nfa, end_nfa)
show_dfa(dfa_)

print (match(dfa_, "bonjour"))
print (match(dfa_, "bonsoir"))
print (match(dfa_, "bonp"))
