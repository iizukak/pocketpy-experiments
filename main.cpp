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
  PyObject *result = vm->exec("sum(a)", "main.py", EVAL_MODE);
  std::cout << CAST(int, result) << std::endl; // 6

  // Create a new Python module
  PyObject *mymodule = vm->new_module("mymodule");
  // Add a function to mymodule
  vm->bind_func<2>(mymodule, "add", [](VM *vm, ArgsView args) {
    i64 lhs = CAST(i64, args[0]);
    i64 rhs = CAST(i64, args[1]);
    return VAR(lhs + rhs);
  });
  vm->exec("import mymodule", "main.py", EXEC_MODE);
  PyObject *obj = vm->exec("mymodule.add(10, 20)", "main.py", EVAL_MODE);
  int i = CAST(int, obj);
  std::cout << i << std::endl;

  return 0;
}