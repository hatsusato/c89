target triple = "x86_64-pc-linux-gnu"

define dso_local i32 @f6() {
  %1 = alloca i32, align 4
  store i32 1, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %4, label %13

4:
  %5 = load i32, i32* %1, align 4
  %6 = add nsw i32 %5, 2
  store i32 %6, i32* %1, align 4
  %7 = load i32, i32* %1, align 4
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %9, label %12

9:
  %10 = load i32, i32* %1, align 4
  %11 = add nsw i32 %10, 3
  store i32 %11, i32* %1, align 4
  br label %12

12:
  br label %13

13:
  %14 = load i32, i32* %1, align 4
  %15 = add nsw i32 %14, 4
  store i32 %15, i32* %1, align 4
  %16 = load i32, i32* %1, align 4
  ret i32 %16
}
