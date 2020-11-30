target triple = "x86_64-pc-linux-gnu"

define dso_local i32 @f1() {
  %1 = add nsw i32 1, 2
  %2 = add nsw i32 %1, 3
  %3 = add nsw i32 %2, 4
  ret i32 %3
}
