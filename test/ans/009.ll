target triple = "x86_64-pc-linux-gnu"

define dso_local i32 @f9() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 1, i32* %2, align 4
  %5 = load i32, i32* %2, align 4
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %7, label %18

7:
  %8 = load i32, i32* %2, align 4
  %9 = add nsw i32 %8, 2
  store i32 %9, i32* %3, align 4
  %10 = load i32, i32* %3, align 4
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %12, label %16

12:
  %13 = load i32, i32* %3, align 4
  %14 = add nsw i32 %13, 3
  store i32 %14, i32* %4, align 4
  %15 = load i32, i32* %4, align 4
  store i32 %15, i32* %1, align 4
  br label %20

16:
  %17 = load i32, i32* %3, align 4
  store i32 %17, i32* %1, align 4
  br label %20

18:
  %19 = load i32, i32* %2, align 4
  store i32 %19, i32* %1, align 4
  br label %20

20:
  %21 = load i32, i32* %1, align 4
  ret i32 %21
}
