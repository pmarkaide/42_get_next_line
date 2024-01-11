

# Custom get_next_line Implementation

<p align="center">
  <img src="https://github.com/pmarkaide/meta/raw/master/get_next_line.png" alt="get_next_line Logo" width="600"/>
</p>

The `get_next_line` function reads a line from a file descriptor, handling dynamic memory allocation and providing a convenient way to process input line by line. The implementation focuses on low-level C programming concepts, ensuring readability and maintainability while avoiding the use of most built-in functions.

In developing this project, I learned about how to use **static variables** and improved memory handling using `malloc`. Defining the string as `static` at runtime ensures that we can make multiple calls to the `get_next_line` function, and we don't lose the information about where on the file we are positioned. Additionally, we have to dynamically update the memory as we append new characters to the previously existing string.

## Functions
* `get_next_line`: Main entry point orchestrating line reading, dynamic memory management, and processing.
* `load_buffer`: Reads and accumulates data from a file descriptor, dynamically allocating memory.
* `parse_line`: Extracts a line from the remainder, dynamically allocating memory for the line.
* `update_remainder`: Updates the remainder after parsing a line, excluding processed data.

Helper Functions:
* `ft_free`: Properly deallocates memory.
* `ft_strlenc`: Finds the length of a string until a specified character.
* `ft_strchr`: Finds the first occurrence of a character in a string.
* `ft_memmove`: Moves memory from one location to another.

## Implementation
When `get_next_line` is called, it initiates the line-reading process by calling the `load_buffer` function. This function reads data from the specified file descriptor (`fd`) into a buffer, dynamically allocating memory as needed. The reading process continues until a newline character is encountered or the end of the file is reached. Subsequently, the `parse_line` function is invoked to extract a line from the accumulated data in the buffer. This involves determining the length of the line and dynamically allocating memory for the line itself. After processing the line, the `update_remainder` function is called to update the remainder of the data in the buffer, excluding the already processed line. This process ensures that subsequent calls to `get_next_line` resume reading from the point after the last newline character. The extracted line is returned to the caller, providing a convenient mechanism for reading lines from a file descriptor in a memory-efficient manner while managing dynamic memory allocation and updates to the data buffer.

## How to Use
Include the `get_next_line.h` header file in your project. Call the get_next_line function with the desired file descriptor to read lines.

```c
#include "get_next_line.h"

int main() {
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        // Process the line as needed
		// For example, printing it
        printf("Line: %s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

## Contributing
Feel free to open an issue if you see any error. Your feedback and improvements are highly appreciated.

## License
This project is licensed under the [MIT License](https://raw.githubusercontent.com/pmarkaide/42_get_next_line/master/LICENSE)..