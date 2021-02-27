#include <fstream>
#include <cerrno>
#include <cstring>
#include <string>
#include <stack>
#include <vector>
#include "nomes.hpp"

/*******************/
/* operands parser */
/*******************/

static Polynome parse_polynome(std::ifstream &fin, std::vector<int> &order)
{
	std::string str;
	char c;

	while (fin >> c && c != ']' && c != ';')
		str.push_back(c);
	if (c != ']')
		throw std::invalid_argument("Wrong end of polynome!");

	order.push_back(1);
	return Polynome(str.c_str());
}

/********************/
/* operators parser */
/********************/

static int is_operation(std::string &c)
{
	if (c == "is_homogenous" || c == "is_harmonic")
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

static void make_unary_polynome_op(std::stack<Polynome> &op_p,
								std::vector<int> &op_order,
								std::stack<std::string> &operators)
{
	if (op_order.empty() || op_p.empty())
		throw std::runtime_error("No argument for matrix operator!");
	if (op_order[op_order.size() - 1] == 2)
		throw std::runtime_error("Matrix operator for charset!");
	op_order.pop_back();

	Polynome p = op_p.top(); op_p.pop();
	std::string op = operators.top(); operators.pop();

	bool result;
	if (op == "is_homogenous")
		result = is_homogenous_polynome(p);
	else
		result = is_harmonic_polynome(p);

	if (result)
		op_p.push(Polynome("1"));
	else
		op_p.push(Polynome("0"));

	op_order.push_back(1);
}

static void make_op(std::stack<Polynome> &op_p,
					std::stack<std::string> &op_chs,
					std::vector<int> &op_order,
					std::stack<std::string> &operators)
{
	// is_homogenpus, is_harmonic 
	if (is_operation(operators.top()) == 5)
	{
		make_unary_polynome_op(op_p, op_order, operators);
		return;
	}

	// binary operations
	std::string op = operators.top(); operators.pop();
	Polynome a, b;
	std::string charset, tmp;
	size_t ord_size = op_order.size();
	if (ord_size < 2)
		throw std::runtime_error("Not enought operands!");

	if (op_order[ord_size - 1] == 1 && op_order[ord_size - 2] == 2
			&& (op == "/" || is_operation(op) == 2))
	{
		a = op_p.top(); op_p.pop();
		charset = op_chs.top(); op_chs.pop();
		op_order.pop_back(); op_order.pop_back();

		// arifmetics
		if (op == "/")
			op_p.push(a / charset.c_str());
		else if (op == "==")	// equals or not
			op_p.push(Polynome("0"));
		else
			op_p.push(Polynome("1"));
		op_order.push_back(1);
	}
	else if (op_order[ord_size - 1] == 2 && op_order[ord_size - 2] == 1
						&& (is_operation(op) == 2)) {
		a = op_p.top(); op_p.pop();
		charset = op_chs.top(); op_chs.pop();
		op_order.pop_back(); op_order.pop_back();

		// equals or not
		if (op == "==")
			op_p.push(Polynome("0"));
		else
			op_p.push(Polynome("1"));
		op_order.push_back(1);
	}
	else if (op_order[ord_size - 1] == 1 && op_order[ord_size - 2] == 1) {
		b = op_p.top(); op_p.pop();
		a = op_p.top(); op_p.pop();
		op_order.pop_back(); op_order.pop_back();

		if (op == "+") op_p.push(a + b);
		else if (op == "-") op_p.push(a - b);
		else if (op == "*") op_p.push(a * b);
		else if (op == "==") op_p.push(Polynome((a == b) ? "1" : "0"));
		else if (op == "!=") op_p.push(Polynome((a != b) ? "1" : "0"));
		else
			throw std::runtime_error("Can't divide polynome by polynome :C");
		op_order.push_back(1);
	}
	else if (op_order[ord_size - 1] == 2 && op_order[ord_size - 2] == 2
			&& is_operation(op) == 2)
	{
		charset = op_chs.top(); op_chs.pop();
		tmp = op_chs.top(); op_chs.pop();
		op_order.pop_back(); op_order.pop_back();

		// equals or not
		if (op == "==")
			op_p.push(Polynome((tmp == charset) ? "1" : "0"));
		else
			op_p.push(Polynome((tmp != charset) ? "1" : "0"));
		op_order.push_back(1);
	}
	else
		throw std::runtime_error("invalid operands for operation!");
}

static void push_to_stack(std::string cur,
						  std::stack<Polynome> &op_p,
						  std::stack<std::string> &op_chs,
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
			make_op(op_p, op_chs, op_order, operators);
		operators.pop();
	}
	else
	{
		while (!operators.empty()
						&& is_operation(operators.top()) >= is_operation(cur))
			make_op(op_p, op_chs, op_order, operators);
		operators.push(cur);
	}
}

/***************/
/* main parser */
/***************/

static int parse_expretion(std::ifstream &fin, std::string &out, size_t expr_n)
{
	std::stack<Polynome> operands_p;
	std::stack<std::string> operands_chs;
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
			if (word == "[")
			{
				operands_p.push(parse_polynome(fin, operands_order));
				out += operands_p.top().convert() + " ";
			}
			else if (is_operation(word))
			{
				out += word + " ";
				push_to_stack(word, operands_p, operands_chs,
													operands_order, operators);
			}
			else if (word == ";")
			{
				if (operands_p.empty() && operands_chs.empty()
						&& operators.empty())
					return -2;
				status = 2;
				break;
			}
			else if (word == "#")
				getline(fin, tmp);
			else
			{
				operands_chs.push(word);
				operands_order.push_back(2);
				out += word + " ";
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
		make_op(operands_p, operands_chs, operands_order, operators);
	
	if (operands_order.size() != 1)
		throw std::runtime_error("Parser error!");
	else if (operands_order.back() == 2)
		throw std::runtime_error("Wrong expretion!..");

	out += "= " + operands_p.top().convert() + " $";

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
