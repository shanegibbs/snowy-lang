target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.10.0"

declare void @free(i8* nocapture)
declare noalias i8* @malloc(i64)

declare i32 @puts(i8*)
declare void @itoa(i8, i8**, i8)
declare i32 @sprintf(i8*, i8*, ...)

@itoa_fmt = constant [3 x i8] c"%i\00"
@hello = constant [24 x i8] c"my hello world function\00"

define void @print_hello_world() {
  %hello_ptr = getelementptr [24 x i8]* @hello, i64 0, i64 0
  call i32 @puts(i8* %hello_ptr)
  ret void
}

define void @print_int(i32 %a) #1 {
  %output = call i8* @malloc(i64 60)
  call i32 (i8*, i8*, ...)* @sprintf(i8* %output, i8* getelementptr inbounds ([3 x i8]* @itoa_fmt, i64 0, i64 0), i32 %a)
  call i32 @puts(i8* %output)
  call void @free(i8* %output)
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {

  call void @print_hello_world()

  %argv_1_ptr = getelementptr i8** %argv, i64 1
  %argv_1 = load i8** %argv_1_ptr
  call i32 @puts(i8* %argv_1)

  %a = add i32 2, 8
  call void @print_int(i32 %a)

  ret i32 %a
}
