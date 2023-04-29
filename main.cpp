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

  // Create a new Python module in C++
  PyObject *mymodule = vm->new_module("mymodule");
  // Add a function to mymodule
  vm->bind_func<2>(mymodule, "add", [](VM *vm, ArgsView args) {
    i64 lhs = CAST(i64, args[0]);
    i64 rhs = CAST(i64, args[1]);
    return VAR(lhs + rhs);
  });
  vm->exec("import mymodule", "main.py", EXEC_MODE);
  PyObject *result_add = vm->exec("mymodule.add(10, 20)", "main.py", EVAL_MODE);
  int add_result = CAST(int, result_add);
  std::cout << add_result << std::endl;

  // Create a new Python function in C++
  vm->bind_builtin_func<2>("sub", [](VM *vm, ArgsView args) {
    i64 lhs = CAST(i64, args[0]);
    i64 rhs = CAST(i64, args[1]);
    return VAR(lhs - rhs);
  });
  PyObject *result_sub = vm->exec("sub(10, 20)", "main.py", EVAL_MODE);
  int sub_result = CAST(int, result_sub);
  std::cout << sub_result << std::endl;

  // Call Python function from C++
  std::string hello_function_string = "def hello():"
                                      "    print('Hello, from Python')";
  vm->exec(hello_function_string, "main.py", EXEC_MODE);
  PyObject *hello_function_object = vm->getattr(vm->_main, "hello");
  vm->call(hello_function_object);

  return 0;
}