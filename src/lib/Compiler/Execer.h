namespace llvm {
class Module;
}

namespace Snowy {

class Log;

class Execer {
 public:
  Execer();
  int exec(llvm::Module *);
  void setStdoutBuffer(char *buffer, int size);
  static void shutdown();

 private:
  static const Log log;
  char *buffer;
  unsigned int buffer_size;
};
}
