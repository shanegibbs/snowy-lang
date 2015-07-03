#include <string.h>
#include <sstream>

#include "SnowyTestSuite.h"

#include <SnowyAssert.h>

#include <Type.h>
#include <Ident.h>
#include <IntLiteral.h>
#include <Operator.h>
#include <Tuple.h>
#include <DeclareVar.h>

using namespace Snowy;
using namespace std;

void node_basic_multi_test(void) {
  Tuple *one_plus_two =
      new Tuple(new IntLiteral(strptr("1")), new Operator(strptr("+")),
                new IntLiteral(strptr("2")));
  DeclareVar root(new Ident(strptr("a")), one_plus_two);

  Tuple *four_plus_five =
      new Tuple(new IntLiteral(strptr("4")), new Operator(strptr("+")),
                new IntLiteral(strptr("5")));
  DeclareVar *bDecl = new DeclareVar(new Ident(strptr("b")), four_plus_five);
  root.setNext(bDecl);

  Tuple *ten_plus_eleven =
      new Tuple(new IntLiteral(strptr("10")), new Operator(strptr("+")),
                new IntLiteral(strptr("11")));
  Ident *c = new Ident(strptr("c"));
  DeclareVar *cDecl = new DeclareVar(c, ten_plus_eleven);
  bDecl->setNext(cDecl);

  std::ostringstream ss;
  ss << "DeclareVar=[ident=[Ident[a type=int]] "
        "expr=[Tuple=[lhs=[IntLiteral=[1]] op=[+] rhs=[IntLiteral=[2]]]]]\n";
  ss << "DeclareVar=[ident=[Ident[b type=int]] "
        "expr=[Tuple=[lhs=[IntLiteral=[4]] op=[+] rhs=[IntLiteral=[5]]]]]\n";
  ss << "DeclareVar=[ident=[Ident[c type=int]] "
        "expr=[Tuple=[lhs=[IntLiteral=[10]] op=[+] rhs=[IntLiteral=[11]]]]]\n";
  const string expected = ss.str();

  const string &actual = root.to_program_string();
  s_assert_cmpint(actual.length(), >, 0);
  s_assert_cmpstr(actual, expected.c_str());
}
