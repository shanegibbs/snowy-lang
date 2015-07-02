#include <memory>
#include <sstream>
#include <string.h>

#include <SnowyAssert.h>
#include <Node.h>

#include "Driver.h"

using namespace std;

namespace Snowy {

  const Log Driver::log = Log("Driver");

  Driver::Driver() {
    program_parser = new ProgramParser(this);
    reached_eof = false;
    lexer = nullptr;
  }

  Driver::~Driver() {
    log.debug("Destroying Driver");
    delete program_parser;

    if (lexer != nullptr) {
      delete lexer;
    }
  }

// the return value is expecting to be manually deleted
// so we must make a copy of the shared_ptr to return
  const TypePtr *Driver::getType(const shared_ptr<const string> id) {
    const TypePtr *t;

    if (types.find(*id) == types.end()) {
      t = new const TypePtr(new Type(id));
      types.insert(pair<string, const TypePtr>(*id, *t));
    } else {
      t = new TypePtr(types[*id]);
    }

    s_assert_notnull(t);
    s_assert(t);
    return t;
  }

  const Callable *Driver::toFunc(const Ident *i) const {
    auto search = funcs.find(*i->getName());
    delete i;

    if (search != funcs.end()) {
      return search->second; // `first` == key, `second` == vale
    }

    log.fatal("Callable '%s' not found", i->getName()->c_str());
    return nullptr;
  }

  void Driver::registerFunc(const Callable *f) {
    funcs[f->getName()] = f;
  }

  static void copy_string(ProgramParser::semantic_type *val, FlexLexer *lexer) {
    val->str = new std::shared_ptr<const string>(new string(lexer->YYText()));
  }

  int Driver::mylex(ProgramParser::semantic_type *val) {
    // exec yylex
    int i = lexer->yylex();

    // tokens that do not need to be parsed
    if (i == ProgramParser::token::WHITE_SPACE) {
      /* log.debug("Skipping white space on line %d: %s",
              lexer->lineno(), lexer->YYText()); */
      return mylex(val);
    } else if (i == ProgramParser::token::COMMENT) {
      log.debug("Skipping comment on line %d: %s",
                lexer->lineno(), lexer->YYText());
      return mylex(val);
    }

    // make sure there is an ENDL before EOF
    if (i == 0) {
      if (!reached_eof) {
        reached_eof = true;
        i = ProgramParser::token::ENDL;
      }
    }

    log.debug("Called mylex - %s(%d), %s", getTokenString(i), i, lexer->YYText());

    // need to copy string as it will get nurfed when the
    // parser does a look ahead
    if (i == ProgramParser::token::ID) {
      copy_string(val, lexer);
    } else if (i == ProgramParser::token::INTEGER) {
      copy_string(val, lexer);
    } else if (i == ProgramParser::token::STRING_LIT) {
      copy_string(val, lexer);
    } else if (i == ProgramParser::token::OP) {
      copy_string(val, lexer);
    }

    return i;
  }

  Node *Driver::exec() {
    s_assert_notnull(lexer);
    program_parser->parse();
    return root;
  }

  void Driver::error(const char *err) {
    log.fatal("Snowy Parse Error: %s on line %d", err, lexer->lineno());
    root = NULL;
  }

  const char *Driver::getTokenString(int t) const {
    switch (t) {
    case ProgramParser::token::ID:
      return "ID";

    case ProgramParser::token::SEPERATOR:
      return "SEPERATOR";

    case ProgramParser::token::INTEGER:
      return "INTEGER";

    case ProgramParser::token::STRING_LIT:
      return "STRING_LIT";

    case ProgramParser::token::EQ_OP:
      return "EQ_OP";

    case ProgramParser::token::OP:
      return "OP";

    case ProgramParser::token::CLASS:
      return "CLASS";

    case ProgramParser::token::DEF:
      return "DEF";

    case ProgramParser::token::DECLARE:
      return "DECLARE";

    case ProgramParser::token::COMMA:
      return "COMMA";

    case ProgramParser::token::OPEN_BRACKET:
      return "OPEN_BRACKET";

    case ProgramParser::token::CLOSE_BRACKET:
      return "CLOSE_BRACKET";

    case ProgramParser::token::DO:
      return "DO";

    case ProgramParser::token::END:
      return "END";

    case ProgramParser::token::ENDL:
      return "ENDL";

    case 0:
      return "EOF";
    }

    return "UNKNOWN";
  }

}
