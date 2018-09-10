#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "BoolGenerator.h"
#include "OpNot.h"
#include "OpAnd.h"
#include "OpOr.h"
#include "OpXor.h"

static void PrintEval(BoolGenerator &gen, PropVar &var);

int main(int argc, char *argv[])
{
	try
	{	
		BoolGenerator gen;
		gen
			.AddVarProp("P")
			.AddVarProp("Q")
			.AddVarProp("R")
			.Build();

		PropVar p = gen["P"];
		PropVar q = gen["Q"];
		PropVar r = gen["R"];


		/*
		///////////////////////////////////////////////////////////////////////
		//                           Prove "Not P"
		///////////////////////////////////////////////////////////////////////

		PropVar rNot("  Not P", p.rows);
		std::transform(
			rNot.rows.begin(), rNot.rows.end(),
			rNot.rows.begin(), OpNot());
		PrintEval(gen, rNot);
		std::cout << std::endl;

		///////////////////////////////////////////////////////////////////////
		//                           Prove "P and Q
		///////////////////////////////////////////////////////////////////////
		PropVar rAnd("P and Q", q.rows);
		std::transform(
			p.rows.begin(), p.rows.end(), 
			rAnd.rows.begin(),
			rAnd.rows.begin(), OpAnd());

		PrintEval(gen, rAnd);
		std::cout << std::endl;

		///////////////////////////////////////////////////////////////////////
		//                           Prove "P or Q
		///////////////////////////////////////////////////////////////////////
		PropVar rOr("P or Q", q.rows);
		std::transform(
			p.rows.begin(), p.rows.end(),
			rOr.rows.begin(),
			rOr.rows.begin(), OpOr());

		PrintEval(gen, rOr);
		std::cout << std::endl;

		///////////////////////////////////////////////////////////////////////
		//                           Prove "P xor Q
		///////////////////////////////////////////////////////////////////////
		PropVar rXor("P xor Q", q.rows);
		std::transform(
			p.rows.begin(), p.rows.end(),
			rXor.rows.begin(),
			rXor.rows.begin(), OpXor());

		PrintEval(gen, rXor);
		std::cout << std::endl;

		///////////////////////////////////////////////////////////////////////
		//                      Prove "((P or Q) and R)"
		///////////////////////////////////////////////////////////////////////
		PropVar rEval("(P or Q) and R", r.rows);
		std::transform(
			rOr.rows.begin(), rOr.rows.end(),
			rEval.rows.begin(),
			rEval.rows.begin(), OpAnd());

		PrintEval(gen, rEval);
		std::cout << std::endl;
		*/

		///////////////////////////////////////////////////////////////////////
		//                      Commutative "P and Q <=> Q and P"
		///////////////////////////////////////////////////////////////////////

		PropVar pandq("P and Q", q.rows);
		std::transform(
			p.rows.begin(), p.rows.end(),
			pandq.rows.begin(),
			pandq.rows.begin(), OpAnd());
		PrintEval(gen, pandq);
		std::cout << std::endl;

		PropVar qandp("Q and P", p.rows);
		std::transform(
			q.rows.begin(), q.rows.end(),
			qandp.rows.begin(),
			qandp.rows.begin(), OpAnd());
		PrintEval(gen, qandp);
		std::cout << std::endl;

		///////////////////////////////////////////////////////////////////////
		//                      Commutative "P or Q <=> Q or P"
		///////////////////////////////////////////////////////////////////////
		PropVar porq("P or Q", q.rows);
		std::transform(
			p.rows.begin(), p.rows.end(),
			porq.rows.begin(),
			porq.rows.begin(), OpOr());
		PrintEval(gen, porq);
		std::cout << std::endl;

		PropVar qorp("Q or P", p.rows);
		std::transform(
			q.rows.begin(), q.rows.end(),
			qorp.rows.begin(),
			qorp.rows.begin(), OpOr());
		PrintEval(gen, qorp);
		std::cout << std::endl;


		///////////////////////////////////////////////////////////////////////
		//             Associative "(P and Q) and R   P and (Q and R)"
		///////////////////////////////////////////////////////////////////////
		PropVar rEval1("(P and Q) and R", r.rows);
		std::transform(
			pandq.rows.begin(), pandq.rows.end(),
			rEval1.rows.begin(),
			rEval1.rows.begin(), OpAnd());
		PrintEval(gen, rEval1);
		std::cout << std::endl;


		// Q and R
		PropVar qandr("Q and R", r.rows);
		std::transform(
			q.rows.begin(), q.rows.end(),
			qandr.rows.begin(),
			qandr.rows.begin(), OpAnd());
		

		PropVar rEval2("P and (Q and R)", qandr.rows);
		std::transform(
			p.rows.begin(), p.rows.end(),
			rEval2.rows.begin(),
			rEval2.rows.begin(), OpAnd());
		PrintEval(gen, rEval2);
		std::cout << std::endl;

	}
	catch (const std::runtime_error &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}

static void PrintEval(BoolGenerator &gen, PropVar &var)
{
	std::vector<PropVar> pvars = gen.GetPropVars();
	for (auto prop : pvars)
		std::cout << std::setw(6) << prop.name << " ";

	std::cout << "\t" << var.name << std::endl;

	const int rows = int(pvars[0].rows.size());
	const int cols = int(pvars.size());

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
			std::cout << std::setw(7) << std::boolalpha << gen[col].rows[row];

		std::cout << "\t" << std::setw(var.name.size()) << var[row];
		std::cout << std::endl;
	}
}
