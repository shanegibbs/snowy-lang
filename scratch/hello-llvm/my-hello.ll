target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.10.0"

declare i32 @puts(i8*)

@hello = constant [15 x i8] c"my hello world\00"

define i32 @main(i32 %argc, i8** %argv) {

  %hello_ptr = getelementptr [15 x i8]* @hello, i64 0, i64 0
  call i32 @puts(i8* %hello_ptr)

  %argv_1_ptr = getelementptr inbounds i8** %argv, i64 1
  %argv_1 = load i8** %argv_1_ptr
  call i32 @puts(i8* %argv_1)

  ret i32 0
}
