# 42 Lisboa's libft project.

  <img src="https://raw.githubusercontent.com/mbraga-s/42-project-badges/main/covers/cover-libft-bonus.png" alt="Libft 125 pts">

Passed 3 peer evaluations and Moulinette's evaluation - scored 125 points.

Makefile includes rules to add bonus and a .Phony to prevent issues in case there are files with the same name as makefile rules.


## Mandatory Part

### Included in `<ctype.h>`

`ft_isalnum` - checks for an alphanumeric character.

`ft_isalpha` - checks for an alphabetic character.

`ft_isascii` - checks for a 7-bit unsigned char value that fits into the ASCII character set.

`ft_isdigit` - checks for a digit (0 through 9).

`ft_isprint` - checks for any printable character including space.

`ft_tolower` - convert uppercase letters to lowercase.

`ft_toupper` - convert lowercase letters to uppercase.

### Included in `<string.h>`

`ft_bzero` - zero a byte string.

`ft_memchr` - zero a byte string.

`ft_memcmp` - compare memory areas
 
`ft_memcpy` - copy memory area. The memory areas must not overlap.

`ft_memmove` - copy memory area.

`ft_memset` - fill memory with a constant byte.

`ft_strchr` - locate character in string.

`ft_strdup` - duplicate a string.

`ft_strlcat` - appends the NUL-terminated string src to the end of dst.

`ft_strlcpy` - copies given amount of a string.

`ft_strlen` - calculate the length of a string.

`ft_strncmp` - compare two strings.

`ft_strnstr` - locate a substring in a string.

`ft_strrchr` - locate character in string.

### Included in `<stdlib.h>`

`ft_atoi` - convert a string to an integer.

`ft_calloc `- allocates memory for an array. The memory is set to zero.

### Extra functions

`ft_itoa` - converts an integer to a string.

`ft_putchar_fd` - writes a char to the given file descriptor.

`ft_putendl_fd` - writes a string followed by a newline to the given file descriptor.

`ft_putnbr_fd` - writes a integer to the given file descriptor.

`ft_putstr_fd` - writes a string to the given file descriptor.

`ft_split` - splits a string using a given char as breaking point.

`ft_striteri` - applies a function to each character of a string.

`ft_strjoin` - concatenates two strings.

`ft_strmapi` -  applies a function to each character of a string.

`ft_strtrim` - trims the beginning and end of string with specific set of chars.

`ft_substr` - returns a substring from a string.

## Bonus Part

`ft_lstadd_back` - Adds the node ’new’ at the end of the list.

`ft_lstadd_front` - Adds the node ’new’ at the beginning of the list.


`ft_lstclear` - Deletes and frees the given node and every successor of that node, using the function ’del’. The pointer to the list is set to NULL.

`ft_lstdelone` - Takes as a parameter a node and frees the memory of the node’s content using the function ’del’ given as a parameter and free the node. The memory of ’next’ is not be freed.

`ft_lstiter` - Iterates the list ’lst’ and applies the function ’f’ on the content of each node.

`ft_lstlast` - Returns the last node of the list.

`ft_lstmap` - Iterates the list ’lst’ and applies the function ’f’ on the content of each node, creating a new list. The ’del’ function is used to delete the content of a node if needed.

`ft_lstnew` - Allocates and returns a new node. The member variable ’content’ is initialized with the value of the parameter ’content’. The variable ’next’ is initialized to NULL.

`ft_lstsize` - Counts the number of nodes in a list.
