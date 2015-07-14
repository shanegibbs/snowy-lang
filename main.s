#!/usr/bin/env snowy

declare int:puts(String:s)
declare int:atoi(String:s)
declare int:printf(String:s, ...)
declare String:getenv(String:s)

def hello(int:i)
  printf("hello world %d!%c", i + 2, 10) # TODO parse \n
end

hello(1)
hello(2)
hello(3)

home = getenv("HOME")
printf("Theres no place like %s%c", home, 10)

user = "someone"
printf("Good bye %s%c", user, 10)

# parse "0" to 0 and exit with result
atoi("0")
