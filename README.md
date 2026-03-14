# SFIio - Specfic file index io library
## Features
is a fast C lightweight C libaray made for applications such as 'Self Modifing code', updating config files 
It's memory safe and uses Arena allocator's for fast allocation and avoiding memory fragmentation (you can view valgrind report's and the screenshots
provided in the (`repo`) folder)
## Use cases:
1.'Self Modifing code'
i.e program's that rewrite their own code
```c
    #include "SFI.h"
    int main() {
        const char *code = "int i = 0, j = 0, k  = 0; //... some code";
        SFIwrite("myprog.c", 120, code);
    }
```
2. Code Generation Tool's it can be used to insert code at a given index significantly reducing the boilerplate
```c 
      void add_function(const char *file, const char *func_name) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), 
             "int %s() {\n    return 0;\n}\n", func_name);
    
    // Append to end of file (using line count)
    long int last_line = FileLines(file) + 1;
    SFIwrite(file, last_line, buffer);
   }
```
3. PrePrecisely update config files:
```c
// Update max_connections in postgresql.conf
SFIwrite("postgresql.conf", 42, "max_connections = 200");
```


## Quick Start
```c
#include "SFIio.c"

int main() {
    SFIwrite("main.c", 3, "//hello, world");   
    return 0;
}
```
-After compilation and execution (`main.c`) becomes 

```c
#include "SFIio.c" 

int main() { 
    //hello, world
    SFIwrite("main.c", 3, "//hello, world");
}
```

## Installation
-To install SFIio
```bash
git clone https://github.com/aguyname/SFIio.git
cd SFI
chmod +x scripts/install.sh
./scripts/install.sh
```
