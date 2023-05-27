# trollq

> Troll your friends!

That program will replace normal semicolons with semicolons for trolling (`；`, U+FF1B fullwidth semicolon)

## Usage

```bash
$ cat hello.cpp
#include <iostream>

int main()
{
  std::cout << "hello, world!\n";
  return 0;
}
$ ./trollq hello.cpp new_hello.cpp
$ cat new_hello.cpp
#include <iostream>

int main()
{
  std::cout << "hello, world!\n"；
  return 0；
}
```
