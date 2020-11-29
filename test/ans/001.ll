target triple = "x86_64-pc-linux-gnu"

define i32 @main() {
  %1 = add i32 1, 2
  %2 = add i32 %1, 3
  %3 = add i32 %2, 4
  ret i32 %3
}
