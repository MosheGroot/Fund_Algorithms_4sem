#include <fstream>
#include <cerrno>
#include <cstring>
#include <stack>
#include <vector>
#include "matrix_nn.hpp"

/* operands parser */

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

/* operators parser */

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
/* main parser */

void parse(const char *filename) {
	std::ifstream fin;
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

	std::string word;
	while (fin >> word) {
		try {
			if (word == "{")
				operands_m.push(parse_matrix(fin, operands_order));
			else if (word.size() == 1 && is_operation(word[0]))
				push_to_stack(word[0], operands_m, operands_n, operands_order, operators);
			else
				operands_n.push(parse_number(word, operands_order));
		}
		catch (const std::invalid_argument &e) {
			std::cerr << "[Wrong syntax!]: " << e.what() << std::endl;
			while ((fin >> word) && word != ";");
		}
		catch (const std::runtime_error &e) {
			std::cerr << "[Wrong operations!]: " << e.what() << std::endl;
			while ((fin >> word) && word != ";");
		}
	}

	while (!operators.empty())
	{
		//std::cout << operators.top() << std::endl;
		make_op(operands_m, operands_n, operands_order, operators);
	}

	if (operands_order.size() != 1)
		return;
	if (operands_order.back() == 1)
		std::cout << operands_n.top() << std::endl;
	else
		std::cout << operands_m.top() << std::endl;
}