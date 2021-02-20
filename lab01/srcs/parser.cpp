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
			throw std::invalid_argument("Operands, digits and )"
							   							"( must be separated!");
	double out = std::strtod(word.c_str(), nullptr);
	order.push_back(1);
	return out;
}

/********************/
/* operators parser */
/********************/

static int is_operation(char c)
{
	if (c == '*' || c == '/')
		return 3;
	if (c == '+' || c == '-')
		return 2;
	if (c == '(' || c == ')')
		return 1;
	return 0;
}

static void make_op(std::stack<Matrix_NN> &op_m, std::stack<double> &op_n,
						std::vector<int> &op_order, std::stack<char> &operators)
{
	size_t ord_size = op_order.size();
	char op = operators.top(); operators.pop();
	Matrix_NN a, b;
	double f, g;

	if (op_order[ord_size - 1] == 1 && op_order[ord_size - 2] == 2 && op == '*')
	{
		f = op_n.top(); op_n.pop();
		b = op_m.top(); op_m.pop();
		op_order.pop_back(); op_order.pop_back();

		op_m.push(f * b);
		op_order.push_back(2);
	}
	else if (op_order[ord_size - 1] == 2 && op_order[ord_size - 2] == 1
													&& is_operation(op) == 3) {
		a = op_m.top(); op_m.pop();
		g = op_n.top(); op_n.pop();
		op_order.pop_back(); op_order.pop_back();

		if (op == '*') op_m.push(a * g);
		else op_m.push(a / g);
		op_order.push_back(2);
	}
	else if (op_order[ord_size - 1] == 1 && op_order[ord_size - 2] == 1) {
		g = op_n.top(); op_n.pop();
		f = op_n.top(); op_n.pop();
		op_order.pop_back(); op_order.pop_back();

		if (op == '+') op_n.push(f + g);
		else if (op == '-') op_n.push(f - g);
		else if (op == '*') op_n.push(f * g);
		else if (op == '/') op_n.push(f / g);
		op_order.push_back(1);
	}
	else if (op_order[ord_size - 1] == 2 && op_order[ord_size - 2] == 2)
	{
		b = op_m.top(); op_m.pop();
		a = op_m.top(); op_m.pop();
		op_order.pop_back(); op_order.pop_back();

		if (op == '*') op_m.push(a * b);
		else if (op == '+') op_m.push(a + b);
		else if (op == '-') op_m.push(a - b);
		else
			throw std::runtime_error("Unable to divide matrix by matrix!");
		op_order.push_back(2);
	}
	else
		throw std::runtime_error("invalid operands for operation!");
}

static void push_to_stack(char cur,
						  std::stack<Matrix_NN> &op_m,
						  std::stack<double> &op_n,
						  std::vector<int> &op_order,
						  std::stack<char> &operators)
{
	if (operators.empty() || cur == '('
						|| is_operation(cur) > is_operation(operators.top())) {
		operators.push(cur);
		return;
	}

	if (cur == ')') {
		while (operators.top() != '(')
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

static int parse_expretion(std::ifstream &fin, std::ostream &fout,
							  std::stack<Matrix_NN> &operands_m,
							  std::stack<double> &operands_n,
							  std::vector<int> &operands_order,
							  std::stack<char> &operators)
{
	int status = 0;
	std::string word;

	fout << "\n$";
	while (fin >> word)
	{
		status = 1;
		try
		{
			if (word == "{")
			{
				operands_m.push(parse_matrix(fin, operands_order));
				fout << operands_m.top().convert() << ' ';
			}
			else if (word.size() == 1 && is_operation(word[0]))
			{
				push_to_stack(word[0], operands_m, operands_n,
													operands_order, operators);
				fout << operators.top() << ' ';
			}
			else if (word == ";")
			{
				status = 2;
				break;
			}
			else
			{
				operands_n.push(parse_number(word, operands_order));
				fout << operands_n.top() << ' ';
			}
		}
		catch (const std::invalid_argument &e) {
			std::cerr << "[Wrong syntax!]: " << e.what() << std::endl;
			while ((fin >> word) && word != ";");
			if (word == ";")
				status = 2;
			return status;
		}
		catch (const std::runtime_error &e) {
			std::cerr << "[Wrong operations!]: " << e.what() << std::endl;
			while ((fin >> word) && word != ";");
			if (word == ";")
				status = 2;
			return status;
		}
	}
	
	if (status == 0)
		return 0;

	while (!operators.empty())
		make_op(operands_m, operands_n, operands_order, operators);

	if (operands_order.size() != 1)
		throw std::runtime_error("Parser error!");

	fout << "= ";
	if (operands_order.back() == 1)
		fout << operands_n.top() << std::endl;
	else
		fout << operands_m.top().convert() << std::endl;

	fout << "$\n";
	return status;
}

void parse(const char *filename) {
	std::ifstream fin;
	std::ofstream fout;
	std::stack<Matrix_NN> operands_m;
	std::stack<double> operands_n;
	std::vector<int> operands_order;
	std::stack<char> operators;

	fin.open(filename);
	if (!fin.is_open()) {
		std::cerr << "[ERROR] Can't open file!\n"
				  << strerror(errno) << std::endl;
		return;
	}

	std::string outpath = std::string(filename) + ".tex";
	fout.open(outpath);
	if(!fout.is_open())
	{
		std::cerr << "[ERROR]: Can't create output file!\n"
					<< strerror(errno) << std::endl;
		return;
	}
	fout << "\documentclass[12pt]{article}\n"
			"\\usepackage[cp1251]{inputenc}\n"
			"\\usepackage[english,russian]{babel}\n\n"
			"\\begin\{document}" << std::endl;

	int status = -1;
	while (status)
	{
		try
		{
			status = parse_expretion(fin, fout, operands_m, operands_n,
												operands_order, operators);
		}
		catch (const std::runtime_error &e) {
			std::cerr << "[Parser error!]: " << e.what() << std::endl;
		}
	}

	fout << "\n\\end{document}" << std::endl;
}
