# Giới thiệu về CppCheck

CppCheck là một công cụ phân tích và tìm lỗi trong code C/C++. Nó cung cấp cho ta khả năng phát hiện các lỗi nguy hiểm mà trình biên dịch không phát hiện được. CppCheck đặc biệt tập trung vào phát hiện các lỗi "Undefined behaviour" và các cấu trúc code nguy hiểm. Mục tiêu của cppcheck là chỉ phát hiện các lỗi thực sự trong code của bạn.
- Cppcheck có thể kiểm tra trên ngay cả code C/C++ chứa các compiler extension, mã nhúng assembly không phải C/C++ tiêu chuẩn.
- Cppcheck tương thích và hỗ trợ mọi trình biên dịch C/C++, hỗ trợ tìm lỗi cho từng version C++ khác nhau. Trong đó có cả phiên bản C++ mới nhất (C++17)
- Cppcheck hỗ trợ đa nền tảng và có thể hoạt động trên các máy tính có cấu hình cơ bản sử dụng hàng ngày. Nó có phép bạn kiểm tra lỗi code theo từng hệ điều hành và phiên bản C++ cụ thể nếu cần.

## Các lỗi Undefined behaviour:

- Dead pointers
- Division by zero
- Integer overflows
- Invalid bit shift operands
- Invalid conversions
- Invalid usage of STL
- Memory management
- Null pointer dereferences
- Out of bounds checking
- Uninitialized variables
- Writing const data

Ngoài ra, Cppcheck còn check được rất nhiều lỗi khác: https://sourceforge.net/p/cppcheck/wiki/ListOfChecks/. Có rất nhiều lỗi mà chỉ Cppcheck check được, nhưng cũng có những lỗi mà nó không kiểm tra được, bạn vẫn cần test kỹ code trước khi đưa vào sử dụng.

Tài liệu Cppcheck: http://cppcheck.sourceforge.net/manual.pdf

# Kiểm tra kiểm thử

Kết quả kiểm tra của mỗi tập dữ liệu được ghi tại file `cpp_check.log` dưới đây:

- [Juliet Test Suite for CC++/cpp_check.log](Juliet Test Suite for CC++/cpp_check.log)
- [SARD-testsuite-57/cpp_check.log](SARD-testsuite-57/cpp_check.log)
- [SARD-testsuite-58/cpp_check.log](SARD-testsuite-58/cpp_check.log)
- [SARD-testsuite-59/cpp_check.log](SARD-testsuite-59/cpp_check.log)
- [SARD-testsuite-100/cpp_check.log](SARD-testsuite-100/cpp_check.log)
- [SARD-testsuite-101/cpp_check.log](SARD-testsuite-101/cpp_check.log)
- [SARD-testsuite-app-3/cpp_check.log](SARD-testsuite-app-3/cpp_check.log)

# Chi tiết kiểm thử tập `Juliet Test Suite for C C++`

Do nhóm em làm công cụ kiểm tra code C/C++, chúng em download dữ liệu "Juliet Test Suite for C/C++".

**Thống kê ban đầu**
- Thư mục testcase chứa 54484 file `*.c` và 46747 file `*.cpp`
- Tài liệu cho thấy bộ mã nguồn này có 64295 test.
- Một file code có thể có nhiều lỗi.
- Các file code này đã được chia theo thư mục của từng loại lỗi
```
CWE114_Process_Control
CWE121_Stack_Based_Buffer_Overflow
CWE122_Heap_Based_Buffer_Overflow
CWE124_Buffer_Underwrite
CWE90_LDAP_Injection
CWE832_Unlock_of_Resource_That_is_Not_Locked
...
```

**Thực hiện kiểm tra**

Theo tài liệu Cppcheck hướng dẫn, cppcheck hỗ trợ chúng ta kiểm tra toàn bộ các file code trong 1 thư mục. Do đó, chúng em thực hiện test như sau:

1. Giải nén file `Juliet_Test_Suite_v1.3_for_C_Cpp.zip`
2. Di chuyển tới thư mục đã giải nén
3. Thực hiện command sau để chạy cppcheck cho bộ code này:
```
# testcase/ là thư mục chưa các file `*.c` cần kiểm tra
# --output-file: Xuất báo cáo của cppcheck ra file
cppcheck testcases/ --output-file=cpp_check.log
```

Chúng ta cũng có thể xuất báo cáo ra file xml rồi sau đó convert sang html để xem:
```
$ cppcheck testcases --xml 2> err.xml
$ cppcheck-htmlreport --file=err.xml --report-dir=test1 --source-dir=.
# Khi đó, mỗi file code sẽ là 1 file html tương ứng, nhìn thấy rõ lỗi (xem ảnh dưới)
```
![](https://i.imgur.com/rGPtdGQ.png)
*Kết quả báo cáo lỗi Cppcheck trên 1 file code là các dòng bôi màu vàng*

## Kết quả kiểm tra

- Có tổng cộng 13259 thông báo lỗi + cảnh báo của 54484 file code:
	+ Có 10257 lỗi (error)
	+ Có 3002 cảnh báo (warning)
- Thống kê theo từng lỗi:
	+ Memory leak: 4088
	+ Null Pointer: 3002
	+ Uninitialized variable: 1902
	+ Out Of Bounds: 246 + 106
- Mỗi lỗi trong file report đều có đường dẫn file, loại lỗi, tên lỗi và vị trí lỗi:

```
[testcases/CWE680_Integer_Overflow_to_Buffer_Overflow/CWE680_Integer_Overflow_to_Buffer_Overflow__malloc_connect_socket_05.c:119]: (error) Invalid malloc() argument nr 1. The value is -4 but the valid values are '0:'.
```

# Đánh giá Cppcheck

- Kết quả sơ bộ cho thấy Cppcheck pass được 13259/64295. Cppcheck kiểm tra được rất ít so với số lỗi thực tế mà bộ test có. Mặc dù vậy, Cppcheck đã giúp chúng ta phát hiện được ít nhất 20% số lỗi và đó đều là các lỗi nguy hiểm.
- Công cụ phát hiện được cả lỗi và cảnh báo, chỉ đích danh vị trí lỗi/cảnh báo đó.
- Chưa có phân tích/ thống kê lỗi khi kiểm tra nhiều file