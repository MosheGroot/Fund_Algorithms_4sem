#include <fstream>
#include <cerrno>
#include <cstring>
#include <stack>
#include <vector>
#include "matrix_nn.hpp"

/*******************/
/* operands parser */
/*******************/

static Matrix_NN parse_matrix(std::ifstream &fin, std::vector<int> &order)
{
	size_t n;
	std::string tmp;

	fin >> n >> tmp;
	if (tmp != ":")
		throw std::invalid_argument("No ':' after size");

	Matrix_NN m(n);
	fin >> m;

	fin >> tmp;
	if (tmp != "}")
		throw std::invalid_argument("Wrong end of matrix!");

	order.push_back(2);
	return m;
}

static double parse_number(std::string &word, std::vector<int> &order)
{
	size_t shift = 0;

	if (word[0] == '-')
		shift = 1;
	for (size_t i = 0 + shift; i < word.size(); i++)
		if (!isdigit(word[i]))
			throw std::invalid_argument("Can't recognize command. "
														"Operands, digits and )"
							   							"( must be separated!");
	double out = std::strtod(word.c_str(), nullptr);
	order.push_back(1);
	return out;
}

/********************/
/* operators parser */
/********************/

static int is_operation(std::string &c)
{
	if (c == "det" || c == "inv" || c == "transp" || c == "tr" || c == "exp")
		return 5;
	if (c == "*" || c == "/")
		return 4;
	if (c == "+" || c == "-")
		return 3;
	if (c == "==" || c == "!=")
		return 2;
	if (c == "(" || c == ")")
		return 1;
	return 0;
}

static void make_unary_matrix_op(std::stack<Matrix_NN> &op_m,
								std::stack<double> &op_n,
								std::vector<int> &op_order,
								std::stack<std::string> &operators)
{
	if (op_order.empty() || op_m.empty())
		throw std::runtime_error("No argument for matrix operator!");
	if (op_order[op_order.size() - 1] == 1)
		throw std::runtime_error("Matrix operator for scalar!");
	op_order.pop_back();

	Matrix_NN m = op_m.top(); op_m.pop();
	std::string op = operators.top(); operators.pop();

	if (op == "tr" || op == "det")
	{
		if (op == "tr")
			op_n.push(trace(m));
		else
			op_n.push(det(m));
		op_order.push_back(1);
		return;
	}
	
	else if (op == "inv")
		op_m.push(invert(m));
	else if (op == "transp")
		op_m.push(transp(m));
	else if (op == "exp")
		op_m.push(exp(m, 5));
	op_order.push_back(2);
}

static void make_op(std::stack<Matrix_NN> &op_m,
					std::stack<double> &op_n,
					std::vector<int> &op_order,
					std::stack<std::string> &operators)
{
	// det, inv, transp, tr, exp
	if (is_operation(operators.top()) == 5)
	{
		make_unary_matrix_op(op_m, op_n, op_order, operators);
		return;
	}

	// binary operations
	size_t ord_size = op_order.size();
	std::string op = operators.top(); operators.pop();
	Matrix_NN a, b;
	double f, g;
	if (ord_size < 2)
		throw std::runtime_error("Not enought operands!");

	if (op_order[ord_size - 1] == 1 && op_order[ord_size - 2] == 2
			&& (op == "*" || is_operation(op) == 2))
	{
		f = op_n.top(); op_n.pop();
		b = op_m.top(); op_m.pop();
		op_order.pop_back(); op_order.pop_back();

		// arifmetics
		if (op == "*")
		{
			op_m.push(f * b);
			op_order.push_back(2);
			return;
		}
	
		// equals or not
		if (op == "==")
			op_n.push(0);
		else
			op_n.push(1);
		op_order.push_back(1);
	}
	else if (op_order[ord_size - 1] == 2 && op_order[ord_size - 2] == 1
						&& (is_operation(op) == 4 || is_operation(op) == 2)) {
		a = op_m.top(); op_m.pop();
		g = op_n.top(); op_n.pop();
		op_order.pop_back(); op_order.pop_back();

		// arifmetics
		if (op == "*" || op == "/")
		{
			if (op == "*")
				op_m.push(a * g);
			else
				op_m.push(a / g);
			op_order.push_back(2);
			return;
		}

		// equals or not
		if (op == "==")
			op_n.push(0);
		else
			op_n.push(1);
		op_order.push_back(1);
	}
	else if (op_order[ord_size - 1] == 1 && op_order[ord_size - 2] == 1) {
		g = op_n.top(); op_n.pop();
		f = op_n.top(); op_n.pop();
		op_order.pop_back(); op_order.pop_back();

		if (op == "+") op_n.push(f + g);
		else if (op == "-") op_n.push(f - g);
		else if (op == "*") op_n.push(f * g);
		else if (op == "/") op_n.push(f / g);
		else if (op == "==") op_n.push(f == g);
		else if (op == "!=") op_n.push(f != g);
		op_order.push_back(1);
	}
	else if (op_order[ord_size - 1] == 2 && op_order[ord_size - 2] == 2)
	{
		b = op_m.top(); op_m.pop();
		a = op_m.top(); op_m.pop();
		op_order.pop_back(); op_order.pop_back();

		// equals or not
		if (is_operation(op) == 2)
		{
			if (op == "==")
				op_n.push(a == b);
			else
				op_n.push(a != b);
			op_order.push_back(1);
			return;
		}
		
		// arifmetics
		if (op == "*") op_m.push(a * b);
		else if (op == "+") op_m.push(a + b);
		else if (op == "-") op_m.push(a - b);
		else if (op == "/")
			throw std::runtime_error("Unable to divide matrix by matrix!");
		op_order.push_back(2);
	}
	else
		throw std::runtime_error("invalid operands for operation!");
}

static void push_to_stack(std::string cur,
						  std::stack<Matrix_NN> &op_m,
						  std::stack<double> &op_n,
						  std::vector<int> &op_order,
						  std::stack<std::string> &operators)
{
	if (operators.empty() || cur == "("
						|| is_operation(cur) > is_operation(operators.top())) {
		operators.push(cur);
		return;
	}

	if (cur == ")") {
		while (operators.top() != "(")
			make_op(op_m, op_n, op_order, operators);
		operators.pop();
	}
	else
	{
		while (!operators.empty()
						&& is_operation(operators.top()) >= is_operation(cur))
			make_op(op_m, op_n, op_order, operators);
		operators.push(cur);
	}
}

/***************/
/* main parser */
/***************/

static int parse_expretion(std::ifstream &fin, std::string &out, size_t expr_n)
{
	std::stack<Matrix_NN> operands_m;
	std::stack<double> operands_n;
	std::vector<int> operands_order;
	std::stack<std::string> operators;
	std::string word;
	std::string tmp;
	int status = 0;

	out = "\n$ ";
	while (fin >> word)
	{
		status = 1;
		try
		{
			if (word == "{")
			{
				operands_m.push(parse_matrix(fin, operands_order));
				out += operands_m.top().convert() + " ";
			}
			else if (is_operation(word))
			{
				out += word;
				push_to_stack(word, operands_m, operands_n,
													operands_order, operators);
			}
			else if (word == ";")
			{
				if (operands_n.empty() && operands_m.empty()
						&& operators.empty())
					return -2;
				status = 2;
				break;
			}
			else if (word == "#")
				getline(fin, tmp);
			else
			{
				operands_n.push(parse_number(word, operands_order));
				out += std::to_string(operands_n.top()) + " ";
			}
		}
		catch (const std::invalid_argument &e) {
			std::cerr << "[Wrong syntax at " << expr_n << " expretion!]: "
													<< e.what() << std::endl;
			while ((fin >> word) && word != ";");
			status = -1;
			if (word == ";")
				status = -2;
			return status;
		}
		catch (const std::runtime_error &e) {
			std::cerr << "[Wrong operations at " << expr_n << " expretion!]: "
													<< e.what() << std::endl;
			while ((fin >> word) && word != ";");
			status = -1;
			if (word == ";")
				status = -2;
			return status;
		}
	}
	
	if (status == 0)
		return 0;

	while (!operators.empty())
		make_op(operands_m, operands_n, operands_order, operators);

	if (operands_order.size() != 1)
		throw std::runtime_error("Parser error!");

	out += "= ";
	if (operands_order.back() == 1)
		out += std::to_string(operands_n.top());
	else
		out += operands_m.top().convert();

	out += " $";
	return status;
}

static int create_outfile(const char *filename,
							std::string &outfile, std::ofstream &fout)
{
	std::string outpath = std::string(filename) + ".tex";
	
	fout.open(outpath);
	if(!fout.is_open())
	{
		std::cerr << "[ERROR]: Can't create output file!\n"
					<< strerror(errno) << std::endl;
		return -1;
	}
	
	fout << "\\documentclass[12pt]{article}\n"
			"\\usepackage{amsmath}\n\n"
			"\\begin\{document}" << std::endl;
	outfile = outpath;
	return 0;
}

std::string parse(const char *filename) {
	std::ifstream fin;
	std::ofstream fout;

	fin.open(filename);
	if (!fin.is_open()) {
		std::cerr << "[ERROR] Can't open file!\n"
				  << strerror(errno) << std::endl;
		return "";
	}
	
	std::string outfile_name;
	if (create_outfile(filename, outfile_name, fout) == -1)
		return "";

	int status = -2;
	size_t expr_count = 1;
	std::string out_str;
	while (status != 0 && status != -1)
	{
		try
		{
			status = parse_expretion(fin, out_str, expr_count);
			if (status > 0)
				fout << out_str << "\n\\\\\\\\" << std::endl;
		}
		catch (const std::runtime_error &e) {
			std::cerr << "[Parser error at " << expr_count<< " expretion!] "
													<< e.what() << std::endl;
		}
		expr_count++;
	}

	fout << "\n\\end{document}" << std::endl;

	fout.close();
	return outfile_name;
}
