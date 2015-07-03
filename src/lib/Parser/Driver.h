#ifndef SNOWY_DRIVER_HPP
#define SNOWY_DRIVER_HPP

#include <string>
#include <map>
#include <FlexLexer.h>

#include <Log.h>
#include <ProgramParser.h>

class FlexLexer;

namespace Snowy {

class Type;
class Log;

class Driver {
 public:
  Driver();
  ~Driver();

  int mylex(ProgramParser::semantic_type *);

  void error(const char *);

  Node *exec();

  void setLexer(FlexLexer *l) { lexer = l; }

  void setRoot(Node *r) { root = r; }

  const TypePtr *getType(const shared_ptr<const string>);

  const Callable *toFunc(const Ident *i) const;

  void registerFunc(const Callable *);

  const char *getTokenString(int) const;

 private:
  static const Log log;
  Node *root;
  FlexLexer *lexer;
  ProgramParser *program_parser;
  bool reached_eof;

  map<string, const TypePtr> types;
  map<const string, const Callable *> funcs;
};
}
#endif
