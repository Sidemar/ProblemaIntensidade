#include <iostream>
#include "gurobi_c++.h"

using namespace std;

GRBEnv env = GRBEnv();
GRBModel model = GRBModel(env);

void terminate(int) { 
	model.terminate();
}

int main() {
	int N = 6;

	int MT = 6;
	int MN = 9;
	int MC = 4;

	int TLB = 70;
	int NUB = 50;
	int CUB = 45;

	double At[6][6] = {{0.3, 0.3, 0.3, 0.3, 0.3, 0.3}, {0.28, 0.28, 0.28, 0.28, 0.28, 0.28}, {0.25, 0.25, 0.25, 0.25, 0.25, 0.25}, {0.33, 0.33, 0.33, 0.33, 0.33, 0.33}, {0.24, 0.24, 0.24, 0.24, 0.24, 0.28}, {0.3, 0.3, 0.3, 0.3, 0.3, 0.3}};
	double An[9][6] = {{0.3, 0.3, 0.3, 0.3, 0.3, 0.3}, {0.28, 0.28, 0.28, 0.28, 0.28, 0.28}, {0.25, 0.25, 0.25, 0.25, 0.25, 0.25}, {0.33, 0.33, 0.33, 0.33, 0.33, 0.33}, {0.24, 0.24, 0.24, 0.24, 0.24, 0.28}, {0.3, 0.3, 0.3, 0.3, 0.3, 0.3}, {0.12, 0.12, 0.12, 0.12, 0.12, 0.12}, {0.16, 0.16, 0.16, 0.16, 0.16, 0.16}, {0.18, 0.18, 0.18, 0.18, 0.18, 0.18}};
	double Ac[4][6] = {{0.12, 0.12, 0.12, 0.12, 0.12, 0.12}, {0.28, 0.28, 0.28, 0.28, 0.28, 0.28}, {0.16, 0.16, 0.16, 0.16, 0.16, 0.16}, {0.25, 0.25, 0.25, 0.25, 0.25, 0.25}};

	try {

		GRBVar x[N]; //x_{i}
		GRBVar fT; //fT
		GRBVar fN; //fN
		GRBVar fC; //fC

		for (int i = 0; i < N; ++i)
		{
			x[i] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x_" + to_string(i));
		}

		fT = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "f_T");
		fN = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "f_N");
		fC = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "f_C");

		GRBLinExpr exp1 = 0;

		for (int i = 0; i < MT; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				exp1 += At[i][j]*x[j];
			}
		}

		exp1 /= MT;
		model.addConstr(exp1 >= TLB*(1-fT), "c1");

		GRBLinExpr exp2 = 0;

		for (int i = 0; i < MN; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				exp2 += An[i][j]*x[j];
			}
		}

		exp2 /= MN;
		model.addConstr(exp2 <= NUB*(1+fN), "c2");

		GRBLinExpr exp3 = 0;

		for (int i = 0; i < MC; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				exp3 += Ac[i][j]*x[j];
			}
		}

		exp3 /= MC;
		model.addConstr(exp3 <= CUB*(1+fC), "c3");

		model.setObjective(0.1*fT + 0.2*fN + 0.7*fC, GRB_MINIMIZE);

	 	model.optimize();

	 	cout << "\nCUSTO: " << model.get(GRB_DoubleAttr_ObjVal) << endl;


	} catch (GRBException e) {
	    	cout << "Error code = " << e.getErrorCode() << endl;
	    	cout << e.getMessage() << endl;
	} catch(...) {
	    	cout << "Exception during optimization" << endl;
	}	

	return 0;
}


