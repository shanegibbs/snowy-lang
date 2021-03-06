#include <stdio.h>

#include <Parser.h>
#include <Node.h>
#include <DeclareClass.h>
#include <DeclareVar.h>
#include <FuncDef.h>
#include <Type.h>
#include <Ident.h>

#include "SnowyTestSuite.h"

using namespace Snowy;

static const Node *build_graph(string code) {
  Log("Test").debug("Building:\n---\n%s---", code.c_str());
  std::stringstream ins;
  ins << code;

  Parser parser;
  const Node *root = parser.parse(ins);
  s_assert_notnull(root);
  return root;
}

static void assert_code_desc(const char *code, const string &expected) {
  std::stringstream ins;
  ins << code;

  Parser parser;
  const Node *root = build_graph(string(code));

  const string &actual = root->to_program_string();
  s_assert_cmpstr(actual, expected);

  delete root;
}

void string_literal_test(void) {
  assert_code_desc("\"abc\"\n", "StringLiteral=[\"abc\"]\n");
}

void int_literal_test(void) { assert_code_desc("1\n", "IntLiteral=[1]\n"); }

void multi_node_test(void) {
  assert_code_desc("1\n2\n3\n",
                   "IntLiteral=[1]\nIntLiteral=[2]\nIntLiteral=[3]\n");
}

void arithmetic_expr_test(void) {
  const char *code = "1 + 2\n";
  const char *desc =
      "Tuple=[lhs=[IntLiteral=[1]] op=[+] rhs=[IntLiteral=[2]]]\n";
  assert_code_desc(code, desc);
}

void assignment_test(void) {
  const char *code = "a = 1 + 2\n";
  const char *desc =
      "DeclareVar=[ident=[Ident[a type=int]] expr=[Tuple=[lhs=[IntLiteral=[1]] "
      "op=[+] rhs=[IntLiteral=[2]]]]]\n";
  assert_code_desc(code, desc);
}

void string_assignment_test(void) {
  const char *code = "a = \"this is a test\"\n";
  const char *desc =
      "DeclareVar=[ident=[Ident[a type=String]] expr=[StringLiteral=[\"this is "
      "a test\"]]]\n";
  assert_code_desc(code, desc);
}

void multi_assignment_test(void) {
  // TODO
}

void func_decl_no_args(void) {
  const char *code = "declare int:puts()\n";
  const char *desc =
      "FuncDecl=[ident=[Ident[puts type=int]] args=[ArgsDecl[size=0]]]\n";
  assert_code_desc(code, desc);
}

void func_decl_one_arg(void) {
  const char *code = "declare int:puts(String:s)\n";
  const char *desc =
      "FuncDecl=[ident=[Ident[puts type=int]] args=[ArgsDecl[size=1 "
      "arg0=[Ident[s type=String]]]]]\n";
  assert_code_desc(code, desc);
}

static void func_decl_var_arg() {
  const char *code = "declare int:printf(String:s, ...)\n";
  const char *desc =
      "FuncDecl=[ident=[Ident[printf type=int]] args=[ArgsDecl[size=1 "
      "arg0=[Ident[s type=String]]]] vararg=true]\n";
  assert_code_desc(code, desc);
}

void func_no_args(void) {
  const char *code = "def add()\nend\n";
  const char *desc =
      "FuncDef=[ident=[Ident[add]] args=[ArgsDecl[size=0]] block=[NULL]]\n";
  assert_code_desc(code, desc);
}

void func_one_arg(void) {
  const char *code = "def add(one)\nend\n";
  const char *desc =
      "FuncDef=[ident=[Ident[add]] args=[ArgsDecl[size=1 arg0=[Ident[one]]]] "
      "block=[NULL]]\n";
  assert_code_desc(code, desc);
}

void func_two_args(void) {
  const char *code = "def add(one, two)\nend\n";
  const char *desc =
      "FuncDef=[ident=[Ident[add]] args=[ArgsDecl[size=2 arg0=[Ident[one]] "
      "arg1=[Ident[two]]]] block=[NULL]]\n";
  assert_code_desc(code, desc);
}

void func_body_one_line(void) {
  const char *code = "def test()\n1\nend\n";
  const char *desc =
      "FuncDef=[ident=[Ident[test]] args=[ArgsDecl[size=0]] block=[\n "
      "IntLiteral=[1]\n]]\n";
  assert_code_desc(code, desc);
}

void func_body_multi_line(void) {
  const char *code = "def test()\n1\n2\n3\nend\n";
  const char *desc =
      "FuncDef=[ident=[Ident[test]] args=[ArgsDecl[size=0]] block=[\n "
      "IntLiteral=[1]\n IntLiteral=[2]\n IntLiteral=[3]\n]]\n";
  assert_code_desc(code, desc);
}

static void empty_line_test(void) {
  assert_code_desc(R"snow(

        1
    )snow",
                   "IntLiteral=[1]\n");
}

static void comment_full_line_test(void) {
  assert_code_desc(R"snow(
        # 1
        1
    )snow",
                   "IntLiteral=[1]\n");
}

static void comment_part_line_test(void) {
  assert_code_desc(R"snow(
        1 # 2
    )snow",
                   "IntLiteral=[1]\n");
}

static void class_declare_empty(void) {
  assert_code_desc(R"snow(
        class MyClass do
        end
    )snow",
                   "DeclareClass=[type=[Type[MyClass]]]\n");
}

static void class_declare_with_var(void) {
  const Node *n = build_graph(R"snow(
        class MyClass do
          i = 0
        end
    )snow");

  s_assert(n->isNodeType(DECLARE_CLASS));
  DeclareClass *c = (DeclareClass *)n;

  s_assert_cmpstr(c->getClassType().getId(), "MyClass");
  s_assert(c->getVars().size() == 1);

  DeclareVar *var = c->getVars()[0];
  s_assert_cmpstr(
      var->to_program_string(),
      "DeclareVar=[ident=[Ident[i type=int]] expr=[IntLiteral=[0]]]\n");

  delete n;
}

static void class_declare_with_var_no_spaces(void) {
  const Node *n = build_graph("class MyClass do\ni = 0\nend\n");

  s_assert(n->isNodeType(DECLARE_CLASS));
  DeclareClass *c = (DeclareClass *)n;

  s_assert_cmpstr(c->getClassType().getId(), "MyClass");
  s_assert(c->getVars().size() == 1);

  DeclareVar *var = c->getVars()[0];
  s_assert_cmpstr(
      var->to_program_string(),
      "DeclareVar=[ident=[Ident[i type=int]] expr=[IntLiteral=[0]]]\n");

  delete n;
}

static void class_declare_with_two_vars(void) {
  const Node *n = build_graph(R"snow(
        class MyClass do
          a = 0
          b = 0
        end
    )snow");

  s_assert(n->isNodeType(DECLARE_CLASS));
  DeclareClass *c = (DeclareClass *)n;

  cout << c->getClassType().getNodeId() << "\n";
  s_assert_cmpstr(c->getClassType().getId(), "MyClass");
  s_assert(c->getVars().size() == 2);

  DeclareVar &a = *c->getVars()[0];
  s_assert_cmpstr(
      a.to_program_string(),
      "DeclareVar=[ident=[Ident[a type=int]] expr=[IntLiteral=[0]]]\n");

  DeclareVar &b = *c->getVars()[1];
  s_assert_cmpstr(
      b.to_program_string(),
      "DeclareVar=[ident=[Ident[b type=int]] expr=[IntLiteral=[0]]]\n");

  delete n;
}

static void class_declare_with_func(void) {
  const Node *n = build_graph(R"snow(
        class MyClass do
          def myfunc()
          end
        end
    )snow");

  s_assert(n->isNodeType(DECLARE_CLASS));
  DeclareClass *c = (DeclareClass *)n;

  s_assert_cmpstr(c->getClassType().getId(), "MyClass");
  s_assert(c->getFuncs().size() == 1);

  FuncDef &func = *c->getFuncs()[0];
  s_assert_cmpstr(func.getName(), "myfunc");

  delete n;
}

static void class_declare_with_two_funcs(void) {
  const Node *n = build_graph(R"snow(
        class MyClass do
          def firstFunc()
            a = 0
          end
          def secondFunc()
            b = 0
          end
        end
    )snow");

  s_assert(n->isNodeType(DECLARE_CLASS));
  DeclareClass *c = (DeclareClass *)n;

  s_assert_cmpstr(c->getClassType().getId(), "MyClass");
  s_assert(c->getFuncs().size() == 2);

  FuncDef &first_func = *c->getFuncs()[0];
  s_assert_cmpstr(first_func.getName(), "firstFunc");

  FuncDef &second_func = *c->getFuncs()[1];
  s_assert_cmpstr(second_func.getName(), "secondFunc");

  delete n;
}

static void type_static() {
  const Node *n = build_graph("int:i = 0");
  s_assert(n->isNodeType(DECLARE_VAR));

  const DeclareVar &decl = *(DeclareVar *)n;
  const Ident &i = decl.getIdent();
  s_assert_cmpstr(i.getName()->c_str(), "i");

  s_assert(i.getType());
  s_assert(i.getType()->getId() == "int");

  delete n;
}

static void type_inference_assignment_test() {
  const Node *n = build_graph("i = 0");
  s_assert(n->isNodeType(DECLARE_VAR));

  const DeclareVar &decl = *(DeclareVar *)n;
  const Ident &i = decl.getIdent();

  s_assert(i.getType());
  s_assert(i.getType()->getId() == "int");

  delete n;
}

static void type_inference_assignment_from_call_test() {
  const Node *n = build_graph(R"snow(
        def int:one()
            0
        end
        x = one()
    )snow");

  s_assert(n->getNext()->isNodeType(DECLARE_VAR));

  const DeclareVar &decl = *(DeclareVar *)n->getNext();
  const Ident &i = decl.getIdent();

  s_assert(i.getType()->getId() == "int");

  delete n;
}

static void parse_if_then_block_oneline() {
  const Node *n = build_graph(R"snow(
    declare int:puts(String:s)
    if (true)
      1
    end
  )snow");

  const char *expected = 1 + R"prog(
FuncDecl=[ident=[Ident[puts type=int]] args=[ArgsDecl[size=1 arg0=[Ident[s type=String]]]]]
IfCond=[cond=[BoolLiteral=[true]] then=[
IntLiteral=[1]
]]
)prog";

  s_assert_cmpstr(n->to_program_string(), expected);
  delete n;
}

static void parse_if_then_block_twoline() {
  const Node *n = build_graph(R"snow(
    declare int:puts(String:s)
    if (true)
      1
      2
    end
  )snow");

  const char *expected = 1 + R"prog(
FuncDecl=[ident=[Ident[puts type=int]] args=[ArgsDecl[size=1 arg0=[Ident[s type=String]]]]]
IfCond=[cond=[BoolLiteral=[true]] then=[
IntLiteral=[1]
IntLiteral=[2]
]]
)prog";

  s_assert_cmpstr(n->to_program_string(), expected);
  delete n;
}

void parser_tests(TestSuite &tests) {
  tests.add("/Parser/int_literal", int_literal_test);
  tests.add("/Parser/string_literal", string_literal_test);
  tests.add("/Parser/multi_node", multi_node_test);
  tests.add("/Parser/arithmetic_expr_test", arithmetic_expr_test);
  tests.add("/Parser/assignment_test", assignment_test);
  tests.add("/Parser/string_assignment_test", string_assignment_test);
  tests.add("/Parser/multi_assignment_test", multi_assignment_test);
  tests.add("/Parser/func_decl/no_args", func_decl_no_args);
  tests.add("/Parser/func_decl/one_arg", func_decl_one_arg);
  tests.add("/Parser/func_decl/var_arg", func_decl_var_arg);
  tests.add("/Parser/func/no_args", func_no_args);
  tests.add("/Parser/func/one_arg", func_one_arg);
  tests.add("/Parser/func/two_args", func_two_args);
  tests.add("/Parser/func/body_one_line", func_body_one_line);
  tests.add("/Parser/func/body_multi_line", func_body_multi_line);
  tests.add("/Parser/empty_line", empty_line_test);
  tests.add("/Parser/comment/full_line", comment_full_line_test);
  tests.add("/Parser/comment/part_line", comment_part_line_test);
  tests.add("/Parser/class/empty", class_declare_empty);
  tests.add("/Parser/class/with_var", class_declare_with_var);
  tests.add("/Parser/class/with_var_no_spaces",
            class_declare_with_var_no_spaces);
  tests.add("/Parser/class/with_two_vars", class_declare_with_two_vars);
  tests.add("/Parser/class/with_func", class_declare_with_func);
  tests.add("/Parser/class/with_two_funcs", class_declare_with_two_funcs);
  tests.add("/Parser/type/static", type_static);
  tests.add("/Parser/type/assignment_inference",
            type_inference_assignment_test);
  tests.add("/Parser/type/assignment_from_call",
            type_inference_assignment_from_call_test);
  tests.add("/Parser/if/then/oneline", parse_if_then_block_oneline);
  tests.add("/Parser/if/then/twoline", parse_if_then_block_twoline);
}
