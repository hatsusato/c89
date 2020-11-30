target triple = "x86_64-pc-linux-gnu"

define dso_local i32 @f3() {
  %1 = alloca i32, align 4
  store i32 2, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = add nsw i32 1, %2
  %4 = add nsw i32 %3, 3
  store i32 %4, i32* %1, align 4
  %5 = load i32, i32* %1, align 4
  %6 = add nsw i32 %5, 4
  ret i32 %6
}
