#!/usr/bin/python

# Copyright 2017, Gurobi Optimization, Inc.

# Want to cover three different sets but subject to a common budget of
# elements allowed to be used. However, the sets have different priorities to
# be covered; and we tackle this by using multi-objective optimization.

from __future__ import print_function
from gurobipy import *


mT = 6
mN = 9
mC = 4
n = 6
N = list(range(n))
MT = list(range(mT))
MN = list(range(mN))
MC = list(range(mC))

TLB = 70
CUB = 45
NUB = 50

At = [[0.3, 0.3, 0.3, 0.3, 0.3, 0.3], [0.28, 0.28, 0.28, 0.28, 0.28, 0.28], [0.25, 0.25, 0.25, 0.25, 0.25, 0.25], [0.33, 0.33, 0.33, 0.33, 0.33, 0.33], [0.24, 0.24, 0.24, 0.24, 0.24, 0.28], [0.3, 0.3, 0.3, 0.3, 0.3, 0.3]]
An = [[0.3, 0.3, 0.3, 0.3, 0.3, 0.3], [0.28, 0.28, 0.28, 0.28, 0.28, 0.28], [0.25, 0.25, 0.25, 0.25, 0.25, 0.25], [0.33, 0.33, 0.33, 0.33, 0.33, 0.33], [0.24, 0.24, 0.24, 0.24, 0.24, 0.28], [0.3, 0.3, 0.3, 0.3, 0.3, 0.3], [0.12, 0.12, 0.12, 0.12, 0.12, 0.12], [0.16, 0.16, 0.16, 0.16, 0.16, 0.16], [0.18, 0.18, 0.18, 0.18, 0.18, 0.18]]
Ac = [[0.12, 0.12, 0.12, 0.12, 0.12, 0.12], [0.28, 0.28, 0.28, 0.28, 0.28, 0.28], [0.16, 0.16, 0.16, 0.16, 0.16, 0.16], [0.25, 0.25, 0.25, 0.25, 0.25, 0.25]]

m = Model()

x = [m.addVar(lb = 0, ub = GRB.INFINITY, obj = 0, vtype = GRB.CONTINUOUS, name = "x_"+str(i)) for i in N]
z1 = m.addVar(lb = 0, ub = GRB.INFINITY, obj = 0, vtype = GRB.CONTINUOUS, name = "z_T")
z2 = m.addVar(lb = 0, ub = GRB.INFINITY, obj = 0, vtype = GRB.CONTINUOUS, name = "z_N")
z3 = m.addVar(lb = 0, ub = GRB.INFINITY, obj = 0, vtype = GRB.CONTINUOUS, name = "z_C")
fT = m.addVar(lb = 0, ub = GRB.INFINITY, obj = 0, vtype = GRB.CONTINUOUS, name = "f_T")
fN = m.addVar(lb = 0, ub = GRB.INFINITY, obj = 0, vtype = GRB.CONTINUOUS, name = "f_N")
fC = m.addVar(lb = 0, ub = GRB.INFINITY, obj = 0, vtype = GRB.CONTINUOUS, name = "f_C")

m.addConstr(z1 == (1.0/mT)*(quicksum(quicksum(At[i][j]*x[j] for j in N) for i in MT)))

m.addConstr(z2 == (1.0/mN)*(quicksum(quicksum(An[i][j]*x[j] for j in N) for i in MN)))

m.addConstr(z3 == (1.0/mC)*(quicksum(quicksum(Ac[i][j]*x[j] for j in N) for i in MC)))

m.addConstr(z1 >= TLB*(1-fT))

m.addConstr(z2 <= NUB*(1+fN))

m.addConstr(z3 <= CUB*(1+fC))

m.setObjective(0.1*fT + 0.2*fN + 0.7*fC)

m.optimize()

#print(fT)
#print(fN)
#print(fC)
#print(z1)
#print(z2)
#print(z3)
#print(x)
