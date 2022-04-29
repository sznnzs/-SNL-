#include <bits/stdc++.h>
using namespace std;


bool debug_1 = 0;


struct token
{
	string type; // RES, ID, SYM, NUM 
	string name;
};


vector<token> tokens;
vector<string> output_message;
vector<pair<int, string>> tree_output;
int idx = 0;
int layers = 0;


void logging(string s)
{
	output_message.push_back(s);
}


void log_tree(string s)
{
	layers ++ ;
	tree_output.push_back({layers, s});
	layers -- ;
}


void match_total_program();
void match_program_head();
void match_declare_part();
void match_program_body();
void match_program_name();
void match_type_decpart();
void match_var_decpart();
void match_proc_decpart();
void match_type_dec();
void match_type_dec_list();
void match_typeid();
void match_type_name();
void match_type_decmore();
void match_base_type();
void match_structure_type();
void match_array_type();
void match_rec_type();
void match_field_dec_list();
void match_id_list();
void match_field_dec_more();
void match_id_more();
void match_vardec();
void match_var_dec_list();
void match_var_id_list();
void match_var_dec_more();
void match_var_id_more();
void match_proc_dec();
void match_proc_name();
void match_param_list();
void match_proc_body();
void match_proc_dec_more();
void match_param_dec_list();
void match_param();
void match_param_more();
void match_form_list();
void match_fid_more();
void match_stm_list();
void match_stm();
void match_stm_more();
void match_conditional_stm();
void match_loop_stm();
void match_input_stm();
void match_output_stm();
void match_return_stm();
void match_ass_call();
void match_call_stm_rest();
void match_assignment_rest();
void match_vari_more();
void match_exp();
void match_act_param_list();
void match_rel_exp();
void match_term();
void match_other_term();
void match_factor();
void match_other_factor();
void match_variable();
void match_mulop();
void match_addop();
void match_act_param_more();
void match_other_rele();
void match_cmpop();
void match_field_var();
void match_field_var_more();


void match_total_program()
{
	layers ++ ;
	tree_output.push_back({layers, "TotalProgram"});
	
	match_program_head();
	match_declare_part();
	match_program_body();
	
	if (tokens[idx].name != ".")
	{
		printf("idx = %d\n", idx);
		puts("match_program error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_program right!"));
	
	layers -- ;
}


/******************************************************************************/
void match_program_head()
{
	layers ++ ;
	tree_output.push_back({layers, "ProgramHead"});
	
	if (tokens[idx].name != "program")
	{
		printf("idx = %d\n", idx);
		puts("match_program_head error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_program_name();
	
	logging(string("match_program_head right!"));
	
	layers -- ;
}


void match_program_name()
{
	layers ++ ;
	tree_output.push_back({layers, "ProgramName"});
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_program_name error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_program_name right!"));
	
	layers -- ;
}


void match_declare_part()
{
	layers ++ ;
	tree_output.push_back({layers, "DeclarePart"});
	
	match_type_decpart();
	match_var_decpart();
	match_proc_decpart();
	
	logging(string("match_declare_part right!"));
	
	layers -- ;
}


/******************************************************************************/
void match_type_decpart()
{
	layers ++ ;
	tree_output.push_back({layers, "TypeDecpart"});
	
	if (tokens[idx].name == "type")
	{
		match_type_dec();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_type_decpart right!"));
	
	layers -- ;
}


void match_type_dec()
{
	layers ++ ;
	tree_output.push_back({layers, "TypeDec"});
	
	if (tokens[idx].name != "type")
	{
		printf("idx = %d\n", idx);
		puts("match_type_dec error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_type_dec_list();
	
	logging(string("match_type_dec right!"));
	
	layers -- ;
}


void match_type_dec_list()
{
	layers ++ ;
	tree_output.push_back({layers, "TypeDecList"});
	
	match_typeid();
	
	if (tokens[idx].name != "=")
	{
		printf("idx = %d\n", idx);
		puts("match_type_dec_list error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_type_name();
	
	if (tokens[idx].name != ";")
	{
		printf("idx = %d\n", idx);
		puts("match_type_dec_list error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_type_decmore();
	
	logging(string("match_type_dec_list right!"));
	
	layers -- ;
}


void match_typeid()
{
	layers ++ ;
	tree_output.push_back({layers, "TypeId"});
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_typeid error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_typeid right!"));
	
	layers -- ;
}


void match_type_decmore()
{
	layers ++ ;
	tree_output.push_back({layers, "TypeDecMore"});
	
	if (tokens[idx].type == "ID")
	{
		match_type_dec_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_type_decmore right!"));
	
	layers -- ;
}


void match_type_name()
{
	layers ++ ;
	tree_output.push_back({layers, "TypeName"});
	
	if (tokens[idx].name == "integer" || tokens[idx].name == "char")
	{
		match_base_type();
		logging(string("match_type_name right!"));
	}
	else if (tokens[idx].name == "array" || tokens[idx].name == "record")
	{
		match_structure_type();
		logging(string("match_type_name right!"));
	}
	else if (tokens[idx].type == "ID")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		logging(string("match_type_name right!"));
	}
	else
	{
		printf("idx = %d\n", idx);
		puts("match_type_name error!");
		exit(0);
	}
	
	layers -- ;
}


void match_base_type()
{
	layers ++ ;
	tree_output.push_back({layers, "BaseType"});
	
	if (tokens[idx].name != "integer" && tokens[idx].name != "char")
	{
		printf("idx = %d\n", idx);
		puts("match_base_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_base_type right!"));
	
	layers -- ;
}


void match_structure_type()
{
	layers ++ ;
	tree_output.push_back({layers, "StructureType"});
	
	if (tokens[idx].name == "array")
	{
		match_array_type();
		logging(string("match_structure_type right!"));
	}
	else if (tokens[idx].name == "record")
	{
		match_rec_type();
		logging(string("match_structure_type right!"));
	}
	else
	{
		printf("idx = %d\n", idx);
		puts("match_structure_type error!");
		exit(0);
	}
	
	layers -- ;
}


void match_array_type()
{
	layers ++ ;
	tree_output.push_back({layers, "ArrayType"});
	
	if (tokens[idx].name != "array")
	{
		printf("idx = %d\n", idx);
		puts("match_array_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != "[")
	{
		printf("idx = %d\n", idx);
		puts("match_array_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].type != "NUM")
	{
		printf("idx = %d\n", idx);
		puts("match_array_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != "..")
	{
		printf("idx = %d\n", idx);
		puts("match_array_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].type != "NUM")
	{
		printf("idx = %d\n", idx);
		puts("match_array_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != "]")
	{
		printf("idx = %d\n", idx);
		puts("match_array_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != "of")
	{
		printf("idx = %d\n", idx);
		puts("match_array_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_base_type();
	
	logging(string("match_array_type right!"));
	
	layers -- ;
}


void match_rec_type()
{
	layers ++ ;
	tree_output.push_back({layers, "RecType"});
	
	if (tokens[idx].name != "record")
	{
		printf("idx = %d\n", idx);
		puts("match_rec_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_field_dec_list();
	
	if (tokens[idx].name != "end")
	{
		printf("idx = %d\n", idx);
		puts("match_rec_type error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_rec_type right!"));
	
	layers -- ;
}


void match_field_dec_list()
{
	layers ++ ;
	tree_output.push_back({layers, "FieldDecList"});
	
	if (tokens[idx].name == "integer" || tokens[idx].name == "char")
	{
		match_base_type();
		match_id_list();
		
		if (tokens[idx].name != ";")
		{
			printf("idx = %d\n", idx);
			puts("match_field_dec_list error!");
			exit(0);
		}
		
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_field_dec_more();
		
		logging(string("match_field_dec_list right!"));
	}
	else if (tokens[idx].name == "array")
	{
		match_array_type();
		match_id_list();
		
		if (tokens[idx].name != ";")
		{
			printf("idx = %d\n", idx);
			puts("match_field_dec_list error!");
			exit(0);
		}
		
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_field_dec_more();
		
		logging(string("match_field_dec_list right!"));
	}
	else
	{
		printf("idx = %d\n", idx);
		puts("match_field_dec_list error!");
		exit(0);
	}
	
	layers -- ;
}


void match_id_list()
{
	layers ++ ;
	tree_output.push_back({layers, "IdList"});
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_id_list error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_id_more();
	
	logging(string("match_id_list right!"));
	
	layers -- ;
}


void match_id_more()
{
	layers ++ ;
	tree_output.push_back({layers, "IdMore"});
	
	if (tokens[idx].name == ",")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		match_id_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_id_more right!"));
	
	layers -- ;
}


void match_field_dec_more()
{
	layers ++ ;
	tree_output.push_back({layers, "FieldDecMore"});
	
	if (tokens[idx].name == "integer" || tokens[idx].name == "char" || tokens[idx].name == "array")
	{
		match_field_dec_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_field_dec_more right!"));
	
	layers -- ;
}


/******************************************************************************/
void match_var_decpart()
{
	layers ++ ;
	tree_output.push_back({layers, "VarDecpart"});
	
	if (tokens[idx].name == "var")
	{
		match_vardec();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_var_decpart right!"));
	
	layers -- ;
}


void match_vardec()
{
	layers ++ ;
	tree_output.push_back({layers, "VarDec"});
	
	if (tokens[idx].name != "var")
	{
		printf("idx = %d\n", idx);
		puts("match_vardec error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_var_dec_list();
	
	logging(string("match_vardec right!"));
	
	layers -- ;
}


void match_var_dec_list()
{
	layers ++ ;
	tree_output.push_back({layers, "VarDecList"});
	
	match_type_name();
	match_var_id_list();
	
	if (tokens[idx].name != ";")
	{
		printf("idx = %d\n", idx);
		puts("match_var_dec_list error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_var_dec_more();
	
	logging(string("match_var_dec_list right!"));
	
	layers -- ;
}


void match_var_id_list()
{
	layers ++ ;
	tree_output.push_back({layers, "VarIdList"});
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_var_id_list error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_var_id_more();
	
	logging(string("match_var_id_list right!"));
	
	layers -- ;
}


void match_var_dec_more()
{
	layers ++ ;
	tree_output.push_back({layers, "VarDecMore"});
	
	string name = tokens[idx].name;
	string type = tokens[idx].type;
	
	if (name == "integer" || name == "char" || name == "array" || name == "record" || type == "ID")
	{
		match_var_dec_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_var_dec_more right!"));
	
	layers -- ;
}


void match_var_id_more()
{
	layers ++ ;
	tree_output.push_back({layers, "VarIdMore"});
	
	if (tokens[idx].name == ",")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		match_var_id_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_var_id_more right!"));
	
	layers -- ;
}


/******************************************************************************/
void match_proc_decpart()
{
	layers ++ ;
	tree_output.push_back({layers, "ProDecpart"});
	
	if (tokens[idx].name == "procedure")
	{
		match_proc_dec();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_proc_decpart right!"));
	
	layers -- ;
}


void match_proc_dec()
{
	layers ++ ;
	tree_output.push_back({layers, "ProDec"});
	
	if (tokens[idx].name != "procedure")
	{
		printf("idx = %d\n", idx);
		puts("match_proc_dec error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_proc_name();
	
	if (tokens[idx].name != "(")
	{
		printf("idx = %d\n", idx);
		puts("match_proc_dec error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_param_list();
	
	if (tokens[idx].name != ")")
	{
		printf("idx = %d\n", idx);
		puts("match_proc_dec error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != ";")
	{
		printf("idx = %d\n", idx);
		puts("match_proc_dec error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_declare_part();
	match_proc_body();
	match_proc_dec_more();
	
	logging(string("match_proc_dec right!"));
	
	layers -- ;
}


void match_proc_name()
{
	layers ++ ;
	tree_output.push_back({layers, "ProName"});
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_proc_name error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_proc_name right!"));
	
	layers -- ;
}


void match_param_list()
{
	layers ++ ;
	tree_output.push_back({layers, "ParamList"});
	
	string name = tokens[idx].name;
	string type = tokens[idx].type;
	if (type == "ID" || name == "integer" || name == "char" || name == "array" || name == "record" || name == "var")
	{
		match_param_dec_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_param_list right!"));
	
	layers -- ;
}


void match_param_dec_list()
{
	layers ++ ;
	tree_output.push_back({layers, "ParamDecList"});
	
	match_param();
	match_param_more();
	
	logging(string("match_param_dec_list right!"));
	
	layers -- ;
}


void match_param()
{
	layers ++ ;
	tree_output.push_back({layers, "Param"});
	
	if (tokens[idx].name == "var")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_type_name();
		match_form_list();
	}
	else
	{
		match_type_name();
		match_form_list();
	}
	
	logging(string("match_param right!"));
	
	layers -- ;
}


void match_form_list()
{
	layers ++ ;
	tree_output.push_back({layers, "FormList"});
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_form_list error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_fid_more();
	
	logging(string("match_form_list right!"));
	
	layers -- ;
}


void match_fid_more()
{
	layers ++ ;
	tree_output.push_back({layers, "FidMore"});
	
	if (tokens[idx].name == ",")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		match_form_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_fid_more right!"));
	
	layers -- ;
}


void match_param_more()
{
	layers ++ ;
	tree_output.push_back({layers, "ParamMore"});
	
	if (tokens[idx].name == ";")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		match_param_dec_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_param_more right!"));
	
	layers -- ;
}


void match_proc_body()
{
	layers ++ ;
	tree_output.push_back({layers, "ProcBody"});
	
	match_program_body();
	
	logging(string("match_proc_body right!"));
	
	layers -- ;
}


void match_proc_dec_more()
{
	layers ++ ;
	tree_output.push_back({layers, "ProDecMore"});
	
	if (tokens[idx].name == "procedure")
	{
		match_proc_dec();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_proc_dec_more right!"));
	
	layers -- ;
}


/******************************************************************************/
void match_program_body()
{
	layers ++ ;
	tree_output.push_back({layers, "ProgramBody"});
	
	if (tokens[idx].name != "begin")
	{
		printf("idx = %d\n", idx);
		puts("match_program_body error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_stm_list();
	
	//printf("idx = %d\n", idx);
	if (tokens[idx].name != "end")
	{
		printf("idx = %d\n", idx);
		puts("match_program_body error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_program_body right!"));
	
	layers -- ;
}


void match_stm_list()
{
	layers ++ ;
	tree_output.push_back({layers, "StmList"});
	
	match_stm();
	match_stm_more();
	
	logging(string("match_stm_list right!"));
	
	layers -- ;
}


void match_stm()
{
	layers ++ ;
	tree_output.push_back({layers, "Stm"});
	
	string name = tokens[idx].name;
	string type = tokens[idx].type;
	
	if (name == "if")
	{
		match_conditional_stm();
	}
	else if (name == "while")
	{
		match_loop_stm();
	}
	else if (name == "read")
	{
		match_input_stm();
	}
	else if (name == "write")
	{
		match_output_stm();
	}
	else if (name == "return")
	{
		match_return_stm();
	}
	else
	{
		if (type != "ID")
		{
			printf("idx = %d\n", idx);
			puts("match_stm error!");
			exit(0);
		}
		
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_ass_call();
	}
	
	logging(string("match_stm right!"));
	
	layers -- ;
}


void match_ass_call()
{
	layers ++ ;
	tree_output.push_back({layers, "AssCall"});
	
	if (tokens[idx].name == "(")
	{
		match_call_stm_rest();
	}
	else
	{
		match_assignment_rest();
	}
	
	logging(string("match_ass_call right!"));
	
	layers -- ;
}


void match_assignment_rest()
{
	layers ++ ;
	tree_output.push_back({layers, "AssignmentRest"});
	
	match_vari_more();
	
	if (tokens[idx].name != ":=")
	{
		printf("idx = %d\n", idx);
		puts("match_assignment_rest error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_exp();
	
	logging(string("match_assignment_rest right!"));
	
	layers -- ;
}


void match_vari_more()
{
	layers ++ ;
	tree_output.push_back({layers, "VariMore"});
	
	if (tokens[idx].name == "[")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_exp();
		
		if (tokens[idx].name != "]")
		{
			printf("idx = %d\n", idx);
			puts("match_vari_more error!");
			exit(0);
		}
		
		log_tree(tokens[idx].name);
		idx ++ ;
	}
	else if (tokens[idx].name == ".")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_field_var();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_vari_more right!"));
	
	layers -- ;
}


void match_field_var()
{
	layers ++ ;
	tree_output.push_back({layers, "FieldVar"});
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_field_var error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_field_var_more();
	
	logging(string("match_field_var right!"));
	
	layers -- ;
}


void match_field_var_more()
{
	layers ++ ;
	tree_output.push_back({layers, "FieldVarMore"});
	
	if (tokens[idx].name == "[")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_exp();
		
		if (tokens[idx].name != "]")
		{
			printf("idx = %d\n", idx);
			puts("match_field_var_more error!");
			exit(0);
		}
		
		log_tree(tokens[idx].name);
		idx ++ ;
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_field_var_more right!"));
	
	layers -- ;
}


void match_exp()
{
	layers ++ ;
	tree_output.push_back({layers, "Exp"});
	
	match_term();
	match_other_term();
	
	logging(string("match_exp right!"));
	
	layers -- ;
}


void match_term()
{
	layers ++ ;
	tree_output.push_back({layers, "Term"});
	
	match_factor();
	match_other_factor();
	
	logging(string("match_term right!"));
	
	layers -- ;
}


void match_factor()
{
	layers ++ ;
	tree_output.push_back({layers, "Factor"});
	
	if (tokens[idx].name == "(")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		
		match_exp();
		
		if (tokens[idx].name != ")")
		{
			printf("idx = %d\n", idx);
			puts("match_factor error!");
			exit(0);
		}
		
		log_tree(tokens[idx].name);
		idx ++ ;
	}
	else if (tokens[idx].type == "NUM")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
	}
	else 
	{
		if (tokens[idx].type != "ID")
		{
			printf("idx = %d\n", idx);
			puts("match_factor error!");
			exit(0);	
		}
		
		match_variable();
	}
	
	logging(string("match_factor right!"));
	
	layers -- ;
}


void match_variable()
{
	layers ++ ;
	tree_output.push_back({layers, "Variable"});
	
	if (tokens[idx].type != "ID")
	{
		puts("match_variable");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_vari_more();
	
	logging(string("match_variable right!"));
	
	layers -- ;
}


void match_other_factor()
{
	layers ++ ;
	tree_output.push_back({layers, "OtherFactor"});
	
	if (tokens[idx].name == "*" || tokens[idx].name == "/")
	{
		match_mulop();
		match_term();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_other_factor right!"));
	
	layers -- ;
}


void match_mulop()
{
	layers ++ ;
	tree_output.push_back({layers, "MulOp"});
	
	if (tokens[idx].name != "*" && tokens[idx].name != "/")
	{
		printf("idx = %d\n", idx);
		puts("match_mulop error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_mulop right!"));
	
	layers -- ;
}


void match_other_term()
{
	layers ++ ;
	tree_output.push_back({layers, "OtherTerm"});
	
	if (tokens[idx].name == "+" || tokens[idx].name == "-")
	{
		match_addop();
		match_exp();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_other_term right!"));
	
	layers -- ;
}


void match_addop()
{
	layers ++ ;
	tree_output.push_back({layers, "AddOp"});
	
	if (tokens[idx].name != "+" && tokens[idx].name != "-")
	{
		printf("idx = %d\n", idx);
		puts("match_addop error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_addop right!"));
	
	layers -- ;
}


void match_call_stm_rest()
{
	layers ++ ;
	tree_output.push_back({layers, "CallStmRest"});
	
	//printf("idx = %d\n", idx);
	if (tokens[idx].name != "(")
	{
		printf("idx = %d\n", idx);
		puts("match_call_stm_rest error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_act_param_list();
	
	if (tokens[idx].name != ")")
	{
		printf("idx = %d\n", idx);
		puts("match_call_stm_rest error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_call_stm_rest right!"));
	
	layers -- ;
}


void match_act_param_list()
{
	layers ++ ;
	tree_output.push_back({layers, "ActParamList"});
	
	string name = tokens[idx].name;
	string type = tokens[idx].type;
	
	if (name == "(" || type == "NUM" || type == "ID")
	{
		match_exp();
		match_act_param_more();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_act_param_list right!"));
	
	layers -- ;
}


void match_act_param_more()
{
	layers ++ ;
	tree_output.push_back({layers, "ActParamMore"});
	
	// blog is ";", but true is "," 
	if (tokens[idx].name == ",")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		match_act_param_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_act_param_more right!"));
	
	layers -- ;
}


void match_conditional_stm()
{
	layers ++ ;
	tree_output.push_back({layers, "ConditionalStm"});
	
	if (tokens[idx].name != "if")
	{
		printf("idx = %d\n", idx);
		puts("match_conditional_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_rel_exp();
	
	if (tokens[idx].name != "then")
	{
		printf("idx = %d\n", idx);
		puts("match_conditional_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_stm_list();
	
	if (tokens[idx].name != "else")
	{
		printf("idx = %d\n", idx);
		puts("match_conditional_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_stm_list();
	
	if (tokens[idx].name != "fi")
	{
		printf("idx = %d\n", idx);
		puts("match_conditional_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_conditional_stm right!"));
	
	layers -- ;
}


void match_rel_exp()
{
	layers ++ ;
	tree_output.push_back({layers, "RelExp"});
	
	match_exp();
	match_other_rele();
	
	logging(string("match_rel_exp right!"));
	
	layers -- ;
}


void match_other_rele()
{
	layers ++ ;
	tree_output.push_back({layers, "OtherRele"});
	
	match_cmpop();
	match_exp();
	
	logging(string("match_other_rele right!"));
	
	layers -- ;
}


void match_cmpop()
{
	layers ++ ;
	tree_output.push_back({layers, "CmpOp"});
	
	if (tokens[idx].name != "<" && tokens[idx].name != "=" && tokens[idx].name != ">")
	{
		printf("idx = %d\n", idx);
		puts("match_cmpop error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_cmpop right!"));
	
	layers -- ;
}


void match_loop_stm()
{
	layers ++ ;
	tree_output.push_back({layers, "LoopStm"});
	
	if (tokens[idx].name != "while")
	{
		printf("idx = %d\n", idx);
		puts("match_loop_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_rel_exp();
	
	if (tokens[idx].name != "do")
	{
		printf("idx = %d\n", idx);
		puts("match_loop_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_stm_list();
	
	if (tokens[idx].name != "endwh")
	{
		printf("idx = %d\n", idx);
		puts("match_loop_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_loop_stm right!"));
	
	layers -- ;
}


void match_input_stm()
{
	layers ++ ;
	tree_output.push_back({layers, "InputStm"});
	
	if (tokens[idx].name != "read")
	{
		printf("idx = %d\n", idx);
		puts("match_input_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != "(")
	{
		printf("idx = %d\n", idx);
		puts("match_input_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].type != "ID")
	{
		printf("idx = %d\n", idx);
		puts("match_input_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != ")")
	{
		printf("idx = %d\n", idx);
		puts("match_input_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_input_stm right!"));
	
	layers -- ;
}


void match_output_stm()
{
	layers ++ ;
	tree_output.push_back({layers, "OutputStm"});
	
	if (tokens[idx].name != "write")
	{
		printf("idx = %d\n", idx);
		puts("match_output_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != "(")
	{
		printf("idx = %d\n", idx);
		puts("match_output_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_exp();
	
	if (tokens[idx].name != ")")
	{
		printf("idx = %d\n", idx);
		puts("match_output_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_output_stm right!"));
	
	layers -- ;
}


void match_return_stm()
{
	layers ++ ;
	tree_output.push_back({layers, "ReturnStm"});
	
	if (tokens[idx].name != "return")
	{
		printf("idx = %d\n", idx);
		puts("match_return_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	if (tokens[idx].name != "(")
	{
		printf("idx = %d\n", idx);
		puts("match_return_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	match_exp();
	
	if (tokens[idx].name != ")")
	{
		printf("idx = %d\n", idx);
		puts("match_return_stm error!");
		exit(0);
	}
	
	log_tree(tokens[idx].name);
	idx ++ ;
	
	logging(string("match_return_stm right!"));
	
	layers -- ;
}


void match_stm_more()
{
	layers ++ ;
	tree_output.push_back({layers, "StmMore"});
	
	if (tokens[idx].name == ";")
	{
		log_tree(tokens[idx].name);
		idx ++ ;
		match_stm_list();
	}
	else
	{
		// null 
		log_tree("NULL");
	}
	
	logging(string("match_stm_more right!"));
	
	layers -- ;
}


/******************************************************************************/
int main()
{
	freopen("token_list.txt", "r", stdin);
	//freopen("dfs_tree.txt", "w", stdout);
	string input_line;
	getline(cin, input_line);
	getline(cin, input_line);
	while (getline(cin, input_line))
	{
		if (debug_1) printf("%s\n", input_line.c_str());
		stringstream sstream(input_line);
		string x[4];
		int i = 0;
		while (sstream) sstream >> x[i], i ++ ;
		tokens.push_back({x[2], x[3]});
	}
	
	if (debug_1) printf("%d\n", tokens.size());
	if (debug_1) for (int i = 0; i < tokens.size(); i ++ ) 
		printf("%s %s\n", tokens[i].type.c_str(), tokens[i].name.c_str());
	
	match_total_program();
	
	//printf("tokens.size() = %d, final_idx = %d\n", (int)tokens.size(), idx);
	//for (int i = 0; i < (int)output_message.size(); i ++ ) printf("%s\n", output_message[i].c_str());
	
	vector<vector<char>> format;
	for (int i = 0; i < (int)tree_output.size(); i ++ )
	{
		vector<char> t;
		for (int j = 0; j < 100; j ++ ) t.push_back(' ');
		format.push_back(t);
	}
	
	
	for (int i = 0; i < (int)tree_output.size() - 1; i ++ )
	{
		int len_1 = tree_output[i].first, len_2 = tree_output[i + 1].first;
		format[i][2 * len_1 - 1] = '-';
		if (len_2 < len_1) continue;
		
		if (len_2 == len_1) format[i][len_1 * 2 - 2] = format[i + 1][len_2 * 2 - 2] = '|';
		//if (len_2 == len_1 + 1) format[i + 1][len_2 * 2 - 1] = '-';
		
		int p = -1;
		for (int j = i + 1; j < (int)tree_output.size(); j ++ )
		{
			int len_3 = tree_output[j].first;
			if (len_3 <= len_1) break;
			if (len_3 == len_1 + 1) p = j;
		}
		
		if (p != -1)
		{
			for (int j = i + 1; j <= p; j ++ ) format[j][len_1 * 2] = '|';
		}
	}
	
	format[(int)tree_output.size() - 1][2 * tree_output[(int)tree_output.size() - 1].first - 1] = '-';
	
	for (int i = 0; i < (int)tree_output.size(); i ++ )
	{
		for (int j = 0; j < tree_output[i].first * 2; j ++ )
		{
			if (format[i][j] == '|' && format[i][j + 1] == '-') cout << "©À";
			else if (format[i][j] == '-') cout << " ";
			else if (format[i][j] == '|') cout << "©¦";
			else cout << format[i][j];
		}
		printf("%s\n", tree_output[i].second.c_str());
	}
	
	//puts("©À©¤");
	//cout << "©¤" << endl;
	
	return 0;
}










