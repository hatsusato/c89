target triple = "x86_64-pc-linux-gnu"

define dso_local i32 @f5() {
  %1 = alloca i32, align 4
  store i32 1, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %4, label %7

4:
  %5 = load i32, i32* %1, align 4
  %6 = add nsw i32 %5, 2
  store i32 %6, i32* %1, align 4
  br label %7

7:
  %8 = load i32, i32* %1, align 4
  %9 = add nsw i32 %8, 3
  store i32 %9, i32* %1, align 4
  %10 = load i32, i32* %1, align 4
  ret i32 %10
}
