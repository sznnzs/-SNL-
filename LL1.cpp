#include <bits/stdc++.h>
using namespace std;


int if_print_input_tokens = 0;
int if_print_predict = 0;
int if_print_LL1_table = 1;


struct token
{
	string type; // RES, ID, SYM, NUM 
	string name;
};

int tot;


vector<token> tokens;


string terminal[] = {".", "program", "ID", "null", "type", "=", ";", "integer", "char", 
					 "array", "[", "NUM", "..", "]", "of", "record", "end", ",", "var", 
					 "procedure", "(", ")", "begin", "end", ":=", "if", "then", "else",
					 "fi", "while", "do", "endwh", "read", "write", "return", "<", ">",
					 "+", "-", "*", "/"};
	

vector<string> log_output;


void logging(string s)
{
	log_output.push_back(s);
}


bool judge_terminal(string s)
{
	bool flag = false;
	for (int i = 0; i <= 40; i ++ ) if (terminal[i] == s) flag = true;
	return flag;
}


vector<vector<string>> grammer; 


void input_grammer_from_file()
{
	cin.clear();
	freopen("grammer.txt", "r", stdin);
	string grammer_line;
	while (getline(cin, grammer_line))
	{
		stringstream sstream(grammer_line);
		vector<string> temp_grammer;
		string str;
		while (sstream) sstream >> str, temp_grammer.push_back(str);
		temp_grammer.pop_back();
		grammer.push_back(temp_grammer);
	}
}


string get_grammer_str_by_id(int x)
{
	string res;
	res += grammer[x][0];
	for (int i = 1; i < grammer[x].size(); i ++ ) res += " ", res += grammer[x][i];
	return res;
}


vector<string> get_predict_by_string(string s)
{
	vector<string> res;
	
	for (int i = 0; i < grammer.size(); i ++ ) if (grammer[i][0] == s)
	{
		string right_first_string = grammer[i][2];
		
		if (judge_terminal(right_first_string)) res.push_back(right_first_string);
		else
		{
			auto predict_of_right_first_string = get_predict_by_string(right_first_string);
			for (auto t : predict_of_right_first_string) res.push_back(t);
		}
	}
	
	return res;
}


map<string, vector<string>> predict;


void print_predict()
{
	for (auto t : predict)
	{
		auto first = t.first;
		auto second = t.second;
		printf("%s   has %d predict:\n", first.c_str(), second.size());
		printf("---   ");
		for (int i = 0; i < second.size(); i ++ ) printf("%s   ", second[i].c_str());
		puts("");
		puts("");
	}
}


vector<vector<string>> LL1_table;


void print_LL1_table()
{
	for (int i = 0; i < grammer.size(); i ++ )
	{
		printf("grammer %d: ", i + 1);
		for (auto t : grammer[i]) printf("%s   ", t.c_str());
		puts("");
		printf("---   ");
		for (auto t : LL1_table[i]) printf("%s   ", t.c_str());
		puts("");
		puts("");
	}
}


void build_LL1_table()
{
	// every 'left' string has a predict of vector<string> 
	// here we consider 'null' as a terminal string 
	for (int i = 0; i < grammer.size(); i ++ ) if (predict.count(grammer[i][0]) == 0)
		predict[grammer[i][0]] = get_predict_by_string(grammer[i][0]);
	
	if (if_print_predict) print_predict();
	
	
	for (int i = 0; i < grammer.size(); i ++ )
	{
		vector<string> res;
		
		string right_first_string = grammer[i][2];
		if (judge_terminal(right_first_string)) res.push_back(right_first_string);
		else res = predict[right_first_string];
		
		LL1_table.push_back(res);
	}
	
	
	// assert LL1_table has no repeat 
	
	if (grammer.size() != LL1_table.size())
	{
		puts("LL1_table build error!");
		exit(0);
	}
	
	map<string, set<string>> assert_LL1_table_no_repeat;
	
	for (int i = 0; i < grammer.size(); i ++ )
	{
		auto s = grammer[i][0];
		for (auto t : LL1_table[i])
		{
			if (assert_LL1_table_no_repeat[s].count(t))
			{
				printf("%s %s\n", s.c_str(), t.c_str());
				puts("error, LL1_table has repeat!");
				exit(0);
			}
			assert_LL1_table_no_repeat[s].insert(t);
		}
	}
	
	if (if_print_LL1_table) print_LL1_table();
	if (if_print_LL1_table) puts("LL1_table has no repeat!");
}


stack<string> work_stk;
stack<token> token_stk;


void LL1_process()
{
	for (int i = tokens.size() - 1; i >= 0; i -- ) token_stk.push(tokens[i]);
	work_stk.push("total_program");
	
	while (work_stk.size())
	{
		string top_work_string = work_stk.top();
		auto top_token_string = token_stk.top();
		
		if (judge_terminal(top_work_string))
		{
			if (top_work_string == "ID" || top_work_string == "NUM")
			{
				if (top_work_string == top_token_string.type)
				{
					string _log = top_work_string + "   " + top_token_string.name + "   match!";
					logging(_log);
					printf("%-20s%-15s匹配！\n", top_work_string.c_str(), top_token_string.name.c_str());
					work_stk.pop();
					token_stk.pop();
				}
				else
				{
					printf("idx = %d\n", tot - token_stk.size());
					printf("%s   %s   not match!\n", top_work_string.c_str(), top_token_string.name.c_str());
					exit(0);
				}
			}
			else
			{
				if (top_work_string == top_token_string.name)
				{
					string _log = top_work_string + "   " + top_token_string.name + "   match!";
					logging(_log);
					printf("%-20s%-15s匹配！\n", top_work_string.c_str(), top_token_string.name.c_str());
					work_stk.pop();
					token_stk.pop();
				}
				else
				{
					printf("idx = %d\n", tot - token_stk.size());
					printf("%s   %s   not match!\n", top_work_string.c_str(), top_token_string.name.c_str());
					exit(0);
				}
			}
		}
		else // not terminal 
		{
			string token_name = top_token_string.name;
			string token_type = top_token_string.type;
			bool has_null = false;
			int match_grammer = -1;
			int null_grammer = -1;
			
			for (int i = 0; i < grammer.size(); i ++ ) if (grammer[i][0] == top_work_string)
			{
				for (auto t : LL1_table[i])
				{
					if (t == "null") has_null = true, null_grammer = i;
					else if (t == token_name || 
							 token_type == "ID" && t == token_type || 
							 token_type == "NUM" && t == token_type) 
						match_grammer = i;
				}
			}
			
			if (match_grammer != -1)
			{
				string _log = top_work_string + "   " + top_token_string.name + "   ";
				_log += "grammer = " + to_string(match_grammer);
				logging(_log);
				printf("%-20s%-15s%-15s%s\n", top_work_string.c_str(), top_token_string.name.c_str(), 
											  "移入！", get_grammer_str_by_id(match_grammer).c_str());
				work_stk.pop();
				for (int i = grammer[match_grammer].size() - 1; i >= 2; i -- )
					work_stk.push(grammer[match_grammer][i]);
			}
			else
			{
				if (has_null)
				{
					string _log = top_work_string + "   " + top_token_string.name + "   ";
					_log += "grammer = " + to_string(null_grammer);
					logging(_log);
					printf("%-20s%-15s%-15s%s\n", top_work_string.c_str(), top_token_string.name.c_str(), 
											  	  "移入！", get_grammer_str_by_id(null_grammer).c_str());
					work_stk.pop();
					for (int i = grammer[null_grammer].size() - 1; i >= 2; i -- )
					work_stk.push(grammer[null_grammer][i]);
					if (work_stk.top() == "null") work_stk.pop();
				}
				else
				{
					//for (int i = 0; i < log_output.size(); i ++ ) printf("%s\n", log_output[i].c_str());
					printf("idx = %d\n", tot - token_stk.size());
					printf("%s   %s   cannot match!\n", top_work_string.c_str(), top_token_string.name.c_str());
					exit(0);
				}
			}
		}
	}
}


int main()
{
	freopen("token_list.txt", "r", stdin);
	//freopen("LL1_output.txt", "w", stdout);
	string input_line;
	getline(cin, input_line);
	getline(cin, input_line);
	while (getline(cin, input_line))
	{
		stringstream sstream(input_line);
		string x[4];
		int i = 0;
		while (sstream) sstream >> x[i], i ++ ;
		tokens.push_back({x[2], x[3]});
	}
	
	if (if_print_input_tokens) printf("tokens.size() = %d\n", tokens.size());
	if (if_print_input_tokens) for (int i = 0; i < tokens.size(); i ++ ) 
		printf("%s %s\n", tokens[i].type.c_str(), tokens[i].name.c_str());
	
	tot = tokens.size();
	
	input_grammer_from_file();
	
	build_LL1_table();
	
	printf("%-20s%-15s%-15s%-15s\n", "分析栈栈顶", "输入栈栈顶", "语法动作", "依据的文法"); 
	LL1_process();
	
	//for (int i = 0; i < log_output.size(); i ++ ) printf("%s\n", log_output[i].c_str());
	puts("语法分析成功！"); 
	
	return 0;
}










