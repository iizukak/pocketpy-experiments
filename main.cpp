#include "pocketpy.h"

using namespace pkpy;

int main() {
  // Create a virtual machine
  VM *vm = new VM();

  // Hello world!
  vm->exec("print('Hello world!')", "main.py", EXEC_MODE);

  // Create a list
  vm->exec("a = [1, 2, 3]", "main.py", EXEC_MODE);

  // Eval the sum of the list
  PyObject *result = vm->exec("sum(a)", "<eval>", EVAL_MODE);
  std::cout << CAST(int, result); // 6
  return 0;
}
