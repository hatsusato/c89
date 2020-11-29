target triple = "x86_64-pc-linux-gnu"

define i32 @main() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 1, i32* %1, align 4
  %4 = load i32, i32* %1, align 4
  %5 = add i32 2, %4
  store i32 %5, i32* %2, align 4
  %6 = load i32, i32* %1, align 4
  %7 = load i32, i32* %2, align 4
  %8 = add i32 %6, %7
  store i32 %8, i32* %3, align 4
  %9 = load i32, i32* %1, align 4
  %10 = load i32, i32* %2, align 4
  %11 = add i32 %9, %10
  %12 = load i32, i32* %3, align 4
  %13 = add i32 %11, %12
  ret i32 %13
}
