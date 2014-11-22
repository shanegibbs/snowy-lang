#ifndef SNOWY_SCANNER_H
#define SNOWY_SCANNER_H

#include <FlexLexer.h>

#include "Parser/Driver.hpp"
#include "Parser.h"

namespace Snowy {

  class Scanner : public FlexLexer {

    public:
      int yylex();

  };

}

#endif
