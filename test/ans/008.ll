target triple = "x86_64-pc-linux-gnu"

define dso_local i32 @f8() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 1, i32* %1, align 4
  %4 = load i32, i32* %1, align 4
  %5 = add nsw i32 %4, 2
  store i32 %5, i32* %2, align 4
  %6 = load i32, i32* %2, align 4
  %7 = add nsw i32 %6, 3
  store i32 %7, i32* %3, align 4
  %8 = load i32, i32* %3, align 4
  ret i32 %8
}
