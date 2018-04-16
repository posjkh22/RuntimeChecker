; ModuleID = 'SignalCodeImplanted.bc'
source_filename = "testcase1.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define void @task() #0 {
  call void @sig_checker()
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 2, i32* %1, align 4
  store i32 3, i32* %2, align 4
  store i32 0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %6, label %10

; <label>:6:                                      ; preds = %0
  call void @sig_checker()
  %7 = load i32, i32* %1, align 4
  %8 = load i32, i32* %2, align 4
  %9 = sub nsw i32 %7, %8
  store i32 %9, i32* %1, align 4
  br label %14

; <label>:10:                                     ; preds = %0
  call void @sig_checker()
  %11 = load i32, i32* %1, align 4
  %12 = load i32, i32* %2, align 4
  %13 = sub nsw i32 %11, %12
  store i32 %13, i32* %2, align 4
  br label %14

; <label>:14:                                     ; preds = %10, %6
  call void @sig_checker()
  %15 = load i32, i32* %1, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, i32* %1, align 4
  store i32 %15, i32* %1, align 4
  %17 = load i32, i32* %2, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, i32* %2, align 4
  store i32 %17, i32* %2, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 {
  call void @sig_checker()
  call void @sig_initializer()
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %2, align 4
  store i32 0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %6, label %9

; <label>:6:                                      ; preds = %0
  call void @sig_checker()
  %7 = load i32, i32* %2, align 4
  %8 = add nsw i32 %7, 1
  store i32 %8, i32* %2, align 4
  call void @task()
  br label %9

; <label>:9:                                      ; preds = %6, %0
  call void @sig_checker()
  store i32 2, i32* %3, align 4
  %10 = load i32, i32* %2, align 4
  %11 = load i32, i32* %3, align 4
  %12 = add nsw i32 %10, %11
  store i32 %12, i32* %2, align 4
  ret i32 0
}

declare void @sig_initializer()

declare void @sig_checker()

define void @CallcheckerSet() {
entry:
  call void @sig_initializer()
  call void @sig_checker()
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 5.0.0 (tags/RELEASE_500/final)"}
