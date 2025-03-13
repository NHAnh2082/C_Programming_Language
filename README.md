<details><summary><b>1. Compiler</b></summary>
<p>

<details><summary><b>1.1. Giới thiệu về compiler</b></summary>
<p>

- Các ngôn ngữ lập trình thường dùng như C/C++, Java, Python, C#... được gọi là ngôn ngữ bậc cao. Khi code xong nhấn run thì chương trình chạy trên monitor, tưởng chừng như rất đơn giản nhưng thực chất phải trải qua rất nhiều bước xử lý phức tạp.
- Ngoài ra, để viết code thì thường sử dụng các IDE (Arduino IDE, VSCode, PyCharm, Android Studio,...). Các IDE thường sẽ tích hợp 2 thứ:

	+ **Editor**: trình soạn thảo văn bản, cung cấp giao diện để viết và chỉnh sửa mã nguồn.
 	+ **Compiler**: thực hiện chuyển đổi các ngôn ngữ bậc cao sang ngôn ngữ máy (0 và 1) để máy tính có thể hiểu được. Mỗi ngôn ngữ lập trình đều sẽ có một bộ biên dịch khác nhau, ví dụ: trong Arduino IDE thì sử dụng AVR-gcc, C/C++ sử dụng gcc/g++,...

- Quá trình biên dịch của gcc sẽ trải qua 4 bước chính:

	+ Preprocessor
 	+ Compiler
	+ Assembler
	+ Linker

![Image](https://github.com/user-attachments/assets/1792a1dc-221d-4039-9657-d6e4644484da)

</p>
</details>

<details><summary><b>1.2. Compiler process</b></summary>
<p>

Quá trình biên dịch một chương trình C sẽ trải qua 4 bước theo thứ tự như sau:

<details><summary><b>📚 Quá trình tiền xử lý (Preprocessor)</b></summary>
<p>

- Nhận mã nguồn.
- Xóa bỏ tất cả chú thích (comment) trong chương trình.
- Các đoạn mã khi được thêm vào (#include) sẽ được copy vào file .i
- Các định nghĩa (#define) cũng sẽ được thay thế trong file .i
- Câu lệnh: ``` gcc -E file.c -o file.i ```

💻
File **test.c**
```cpp
#include <stdio.h>

void display()
{
    printf("This is file test.c\n");
}
```

File **main.c**
```cpp
#include <stdio.h>
#include "test.c"

// create size array through macro
#define SIZE 20
int array[SIZE];

// create the function
void test()
{
    printf("Hello world\n");
}

// create a variable
int SIZE2 = 30;

int main(int argc, char const *argv[])
{
    int array2[SIZE2];
    display();
    test();
    return 0;
}
```

📝 Thực hiện câu lệnh để tạo file main.i: ``` gcc -E main.c -o main.i ```

File **main.i**
```cpp
# 1650 "D:/C++/msys64/ucrt64/include/stdio.h" 2 3
# 2 "main.c" 2
# 1 "test.c" 1


# 3 "test.c"
void display(){
    printf("This is file test.c\n");
}
# 3 "main.c" 2

int array[20];

void test(){
    printf("Hello world\n");
}

int SIZE2 = 30;

int main(int argc, char const *argv[])
{
    int array2[SIZE2];
    display();
    test();
    return 0;
}
```
📝 Toàn bộ mã nguồn của thư viện chuẩn ``` stdio ``` và file ``` test.c ``` đều được copy vào file ``` main.i ```

📝 2 chú thích (comment) đều đã bị xóa.

📝 Định nghĩa ``` SIZE ``` cũng được thay thế bằng giá trị 20 -> ``` int array[20] ```

📝 Các hàm, biến khai báo thông thường đều giữ nguyên.

<br>

</p>
</details>

<details><summary><b>📚 Quá trình dịch ngôn ngữ bậc cao sang Assembly (Compiler)</b></summary>
<p>

- Đây là quá trình chuyển từ file ``` .i ``` sang file ``` .s ``` (hợp ngữ) thông qua việc phân tích cú pháp (syntax) sau đó chuyển sang các câu lệnh hợp ngữ.
- Hợp ngữ (Assembly) là ngôn ngữ bậc thấp gần với tập lệnh của bộ vi xử lý.

	+ Thao tác trực tiếp với CPU và phần cứng:

		++ Truy cập và điều khiển các thanh ghi (registers) của CPU.

		++ Gán giá trị, thực hiện phép toán trực tiếp trên thanh ghi.

		++ Làm việc với địa chỉ vùng nhớ cụ thể (như đọc/ghi dữ liệu vào địa chỉ chính xác trong RAM).

		++ Tối ưu hóa chi tiết về hiệu suất và tài nguyên phần cứng.

	+ Kiểm soát thủ công:

		++ Lập trình viên có toàn quyền kiểm soát mọi thao tác ở mức phần cứng.
   
- Câu lệnh: ``` gcc -S main.i -o main.s ```

File **main.s**
```cpp
	.file	"main.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "This is file test.c\0"
	.text
	.globl	display
	.def	display;	.scl	2;	.type	32;	.endef
	.seh_proc	display
display:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	array
	.bss
	.align 32
...
```

<br>

</p>
</details>

<details><summary><b>📚 Quá trình dịch Assembly sang ngôn ngữ máy (Assembler)</b></summary>
<p>

- Dịch chương trình sang mã máy 0 và 1.
- Một tệp mã máy (.obj) được sinh ra trong hệ thống sau đó.
- Câu lệnh: ``` gcc -c main.s -o main.o ```

File **main.o**
![Image](https://github.com/user-attachments/assets/ba57e8bf-b5a6-44d3-874d-2d3fb1468ba1)

📝 Khi code trên VĐK thì đây chính là chương trình sẽ ghi vào bộ nhớ Flash của VĐK. Khi cấp nguồn cho VĐK thì nó sẽ tiến hành khởi tạo các PC, Stack Pointer và copy chương trình này vào bộ nhớ Flash và RAM rồi sau đó mới bắt đầu đi đến từng địa chỉ để thực thi.

<br>

</p>
</details>

<details><summary><b>📚 Quá trình liên kết (Linker)</b></summary>
<p>

- Trong giai đoạn này mã máy của một chương trình dịch từ nhiều nguồn (file .c hoặc file thư viện .lib) được liên kết lại với nhau để tạo thành chương trình đích duy nhất.
- Mã máy của các hàm thư viện gọi trong chương trình cũng được đưa vào chương trình cuối trong giai đoạn này.
- Các lỗi liên quan đến việc gọi hàm hay sử dụng biến tổng thể mà không tồn tại sẽ bị phát hiện. Kể cả lỗi viết chương trình chính không có hàm main() cũng được phát hiện trong liên kết.
- Câu lệnh: ``` gcc main.o -o main ```

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b> 2. Macro</b></summary>
<p>

<details><summary><b>2.1. Giới thiệu về Macro</b></summary>
<p>

- Macro là từ dùng để chỉ những thông tin được xử lý ở quá trình tiền xử lý (Preprocessor), được sử dụng để thay thế một đoạn mã trước khi chương trình được biên dịch.
- Macro giúp tạo ra các định nghĩa chung, thường để tránh việc viết lại mã nhiều lần hoặc để làm cho mã dễ bảo trì hơn. 

</p>
</details>

<details><summary><b>2.2. Các nhóm chỉ thị Macro</b></summary>
<p>

<details><summary><b>📚 Chi thị bao hàm tệp (#include)</b></summary>
<p>

- Chỉ thị #include dùng để chèn nội dung của một file khác vào mã nguồn chương trình.
- Tái sử dụng mã nguồn.
- Phân chia chương trình thành các phần nhỏ, giúp quản lý mã nguồn hiệu quả.
- Khi sử dụng ``` <> ``` thì preprocessor sẽ thêm nội dung những thư viện chuẩn trong thư mục cài đặt. 

```cpp
#include <stdio.h>
#include <stdlib.h>
```
- Khi sử dụng dấu ``` "" ```, bộ tiền xử lý sẽ tìm file thư mục do lập trình viên tự thiết kế trong thư mục chứa project. Nếu tìm không thấy thì nó sẽ tiếp tục tìm trong các file có sẵn trong thư mục cài đặt.

```cpp
#include "uart.h"
#include "spi.h"
```

<br>

</p>
</details>

<details><summary><b>📚 Chi thị định nghĩa Macro (#define)</b></summary>
<p>

Chỉ thị #define dùng để thay thế một chuỗi mã nguồn bằng một chuỗi khác trước khi chương trình biên dịch. Nó giúp giảm lặp lại mã, dễ bảo trì chương trình.

💻
File **main.c**
```cpp
#include <stdio.h>

#define CREATE_FUNC(name,cmd)   \
void name()			\
{                    		\
    printf(cmd);                \
}

CREATE_FUNC(test1, "this is function test1()\n");
CREATE_FUNC(test2, "this is function test2()\n");
CREATE_FUNC(test3, "this is function test3()\n");

int main(int argc, char const *argv[])
{
    test1();
    test2();
    test3();
    return 0;
}
```
File **main.i**
```cpp
# 8 "main.c"
void test1(){ printf("this is function test1()\n"); };
void test2(){ printf("this is function test2()\n"); };
void test3(){ printf("this is function test3()\n"); };

int main(int argc, char const *argv[])
{
    test1();
    test2();
    test3();
    return 0;
}
```

<br>

💻
```cpp
// Macro
#define sum(a,b) a+b
```
```cpp
// Function
int sum(int a, int b){ return a+b; }
```
📝 Cả 2 đều cho ra kết quả giống nhau. Vậy câu hỏi đặt ra là:

🤔 Sự khác nhau giữa Macro và Function là gì❓ 

🤔 Khi nào sử dụng Macro? Khi nào sử dụng Function❓ 

<br>

**Sử dụng Function**
```cpp
#include <stdio.h>

int sum(int a, int b)	// 0xc1 - 0xc9
{   
    return a+b;
}

int main(int argc, char const *argv[]){
    int a;         // 0x01              
    int b;         // 0x05
    int c = a+b;   // 0x09
    sum(5,7);       
    return 0;
}
```
📝 Khi sử dụng hàm thì compiler sẽ cấp 1 vùng nhớ cho hàm (giả sử ``` 0xc1 – 0xc9 ```).

📝 Khi bắt đầu thực thi chương trình, ``` Program Counter (PC) ``` sẽ đi đến từng địa chỉ: ``` 0x01 -> 0x02 -> 0x03 -> 0x04 ->... -> 0x09 ```. Khi đến hàm ``` sum() ```, địa chỉ 0x0A sẽ được lưu vào ``` Main Stack Pointer (MSP) ```, sau đó PC nhảy đến 0xc1 để thực hiện hàm.

📝 Khi thực hiện xong hàm thì sẽ vào ``` MSP ``` và lấy lại địa chỉ 0x0A để PC tiếp tục thực thi từ đó.

<br>

**Sử dụng Macro**
```cpp
#include <stdio.h>

#define sum(a,b) a+b        

int main(int argc, char const *argv[])
{
    int a;         // 0x01              
    int b;         // 0x05
    int c = a+b;   // 0x09
    5+7;           // 0x0A
    5+4;           // 0x0B
    return 0;
}
```
📝 Khi sử dụng Macro thì PC sẽ trỏ đến những địa chỉ liền kề nhau do đó sẽ tốn bộ nhớ để lưu giá trị sau mỗi lần gọi macro nhưng tốc độ xử lý sẽ nhanh hơn khi sử dụng hàm do không cần phải lưu vào ``` MSP ```.

<br>

<table>
  <tr>
    <th style="text-align: center;">Macro</th>
    <th style="text-align: center;">Function</th>
  </tr>
  <tr>
    <td style="text-align: center;">Tốn nhiều bộ nhớ để lưu chương trình</td>
    <td style="text-align: center;">Không tốn nhiều bộ nhớ trên RAM</td>
  </tr>
  <tr>
    <td style="text-align: center;">Tốc độ xử lý nhanh</td>
    <td style="text-align: center;">Tốc độ xử lý chậm</td>
  </tr>
</table>

<br>

</p>
</details>

<details><summary><b>📚 Chi thị hủy định nghĩa Macro (#undef)</b></summary>
<p>

Chỉ thị #undef dùng để hủy định nghĩa của một macro đã được định nghĩa trước đó bằng #define.

💻
```cpp
#include <stdio.h>

#define data 30

int main(int argc, char const *argv[])
{
    printf("Data = %d\n", data);

    #undef data

    #define data 50

    printf("Data = %d\n", data);

    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>📚 Chỉ thị biên dịch có điều kiện (#if, #elif, #else, #ifdef, #ifndef)</b></summary>
<p>

- Chỉ thị ``` #ifdef ``` dùng để kiểm tra một ``` macro ``` đã được **định nghĩa hay chưa**, nếu macro **đã được định nghĩa** thì **mã nguồn sau** ``` #ifdef ``` **sẽ được biên dịch**.
- Chỉ thị ``` #ifndef ``` dùng để kiểm tra một macro đã được định nghĩa hay chưa, nếu macro **chưa được định nghĩa** thì **mã nguồn sau** ``` #ifndef ``` **sẽ được biên dịch**.

💻 **Ví dụ 1**:
```cpp
#include <stdio.h>

//#define SIZE 30

#ifndef SIZE
#define SIZE 5

int arr[SIZE] = {1,2,3,4,5};

#endif

int main(int argc, char const *argv[])
{
    for (int i=0; i<SIZE; i++) printf("arr[%d] = %d\n", i, arr[i]);
    return 0;
}
```

<br>

💻 **Ví dụ 2**:

- File ``` test.h ```:

```cpp
#ifndef TEST_H
#define TEST_H

void display();

#endif
```

- File ``` test.c ```:

```cpp
#include <stdio.h>
#include "test.h"

void display()
{
    printf("This is file test.c\n");
}
```

- File ``` main.c ```:

```cpp
#include <stdio.h>
#include "test.h"

// create size array
#define SIZE 20
int array[SIZE];

// create the function
void test()
{
    printf("Hello world\n");
}

int SIZE2 = 30;

int main()
{
    int array2[SIZE2];
    display();
    test();
    return 0;
}
```

📝 Quá trình build file ``` main.c ```

gcc -E main.c -o main.i

gcc -S main.i -o main.s

gcc -c main.s -o main.o

📝 Quá trình build file ``` test.c ```

gcc -E test.c -o test.i

gcc -S test.i -o test.s

gcc -c test.s -o test.o

📝 Liên kết các file ``` .o ``` để tạo file thực thi ``` .exe ```

gcc main.o test.o -o main

📝 Chạy file thực thi ``` .exe ```

./main (./main.exe)

<br>

- Chỉ thị ``` #if ``` sử dụng để **bắt đầu một điều kiện tiền xử lý**. Nếu điều kiện trong là đúng, các dòng mã nguồn sau ``` #if ``` sẽ được biên dịch. Nếu sai, các dòng mã nguồn sẽ bị bỏ qua đến khi gặp ``` #endif ```.
- Chỉ thị ``` #elif ``` dùng để thêm một điều kiện mới khi điều kiện trước đó trong ``` #if ``` hoặc ``` #elif ``` là sai.
- Chỉ thị ``` #else ``` dùng khi không có điều kiện nào ở trên đúng.

🤔 Sự khác nhau giữa ``` #if, #elif, #else ``` và ``` if, else if, else ```?

``` #if, #elif, #else ```

- Hoạt động ở giai đoạn tiền xử lý (preprocessing): Các chỉ thị này được xử lý trước khi trình biên dịch bắt đầu biên dịch mã.
- Một phần mã sẽ được biên dịch nếu điều kiện thỏa mãn.

``` if, else if, else ```

- Hoạt động ở giai đoạn runtime: Các câu lệnh này được kiểm tra và thực thi khi chương trình đang chạy. Điều kiện có thể phụ thuộc vào giá trị biến hoặc kết quả của các phép tính.

🤔 Muốn build một source để có thể nạp cho nhiều chip, thay vì mỗi con chip viết một source thì mình có thể sử dụng ``` #if, #elif, #else ```

💻 **Ví dụ**:
```cpp
#include <stdio.h>

typedef enum
{
    LOW,    // LOW = 0
    HIGH    // HIGH = 1
} Status;

typedef enum
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
} Pin;

#define ESP32      1
#define STM32      2
#define ATmega324  3

#define MCU ATmega324

#if MCU == STM32
    void digitalWrite(Pin pin, Status state)
    {
        if (state == HIGH)
        {
            GPIOA->BSRR = (1 << pin);  		// Đặt bit tương ứng để thiết lập chân
        } 
        else
        {
            GPIOA->BSRR = (1 << (pin + 16));  	// Đặt bit tương ứng để reset chân
        }
    }

#elif MCU == ESP32
    void digitalWrite(Pin pin, Status state)
    {
        if (state == HIGH)
        {
            GPIO.out_w1ts = (1 << pin);  // Đặt bit tương ứng để thiết lập chân HIGH
        } 
        else
        {
            GPIO.out_w1tc = (1 << pin);  // Đặt bit tương ứng để reset chân LOW
        }
    }

#else
    void digitalWrite(Pin pin, Status state)
    {
        if (state == HIGH)
        {
            PORTA |= (1 << pin);  // Đặt bit tương ứng để thiết lập chân HIGH
        } 
        else
        {
            PORTA &= ~(1 << pin);  // Xóa bit tương ứng để reset chân LOW
        }
    }
#endif

int main(int argc, char const *argv[])
{
    while(1){}
    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>📚 Một số toán tử Macro</b></summary>
<p>

- Sử dụng **##** để nối chuỗi.
- Sử dụng **#** để chuẩn hóa đoạn văn bản lên chuỗi.

💻
File **main.c**
```cpp
#include <stdio.h>

// ## dùng để nối chuỗi
#define CREATE_VAR(name)    \
int    int_##name;          \
char   char_##name;         \
double double_##name     

// # chuẩn hóa đoạn văn bản lên chuỗi
#define CREATE_STRING(cmd) printf(#cmd)

int main(int argc, char const *argv[])
{
    CREATE_VAR(test);  
    CREATE_STRING(abc);
    return 0;
}
```
File **main.i**
```cpp
# 20 "main.c"
int main(int argc, char const *argv[])
{
    int int_test; char char_test; double double_test;
    printf("abc");
    return 0;
}
```

<br>

- Variadic macro: là một dạng macro cho phép nhận một số lượng biến tham số có thể thay đổi.

💻 **Ví dụ 1**:
```cpp
#define print(...)  __VA_ARGS__
```

<br>

💻 **Ví dụ 2**:
```cpp
#include <stdio.h>

#define print(...)          \
int arr[] = {__VA_ARGS__}   

int main()
{
    print(1,2,3);

    for (size_t i=0; i<(sizeof(arr)/sizeof(arr[0])); i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}
```

<br>

💻 **Tính tổng nhiều số (Cách 1)**:
```cpp
#define sum(a,b) a+b

#define sum(a,b,c) a+b+c
```
📝 Khi tính tổng 2 số thì dùng ``` sum(a,b) ```

📝 Khi tính tổng 3 số thì dùng ``` sum(a,b,c) ```

🤔 Vậy muốn tính tổng nhiều số thì hàm sum thay đổi thế nào❓ 

➡️Sử dụng variadic macro để giải quyết vấn đề trên.

```cpp
#include <stdio.h>

#define sum(...)                        \
do					\
{	                                \
    int arr[] = {__VA_ARGS__, 0};       \
    int tong = 0;                       \
    int i = 0;                          \
    while (arr[i] != 0)			\
    {               			\
        tong += arr[i];                 \
        i++;                            \
    }                                   \
    printf("Tong = %d\n", tong);        \
} while (0)

int main(int argc, char const *argv[])
{
    sum(1, 2);                          
    sum(1, 2, 3);                       
    sum(1, 3, 5, 7, 9, 10, 15);        
    return 0;
}
```

📝 Cách trên có thể tính tổng nhiều số nhưng với điều kiện các số đưa vào không được có số 0 chen ở giữa vì khi có số 0 thì việc thực hiện tính toán sẽ dừng lại ngay lập tức.

📝 Có thể khắc phục bằng cách kết hợp cả macro variadic và thư viện STDARG (sẽ nói đến ở bài sau).

<br>

💻 **Tính tổng nhiều số (Cách 2)**:
```cpp
#include <iostream>
using namespace std;

#define sum(...)                        \
do					\
{	                                \
    int arr[] = {__VA_ARGS__};          \
    int tong = 0;                       \
    int i = 0;                          \
    for (size_t i=0; i<(sizeof(arr)/sizeof(arr[0])); i++)	\
    {               			\
        tong += arr[i];                 \
    }                                   \
    cout << "Tong = " << tong;          \
} while (0)

int main(int argc, char const *argv[])
{
    sum(1, 2);                          
    sum(1, 2, 3);                       
    sum(1, 3, 5, 7, 9, 10, 15);        
    return 0;
}
```

<br>

💻 **Tạo menu**:
```cpp
/********************************************************************
* @file Menu.cpp
* @brief Chương trình hiển thị menu và xử lý lựa chọn của người dùng.
* @version 1.0
* @date 2025-01-12
* @author Anh Nguyen
********************************************************************/
#include <stdio.h>

/**
 * @brief Macro để in ra một mục trong menu.
 * @param[in] number Số thứ tự của mục menu.
 * @param[in] item Nội dung của mục menu.
 */
#define PRINT_MENU_ITEM(number, item) printf("%d. %s\n", number, item)


/**
 * @brief Macro để in toàn bộ menu.
 * @param[in] ... Danh sách các mục menu.
 */
#define PRINT_MENU(...)                             \
        const char* items[] = {__VA_ARGS__};        \
        int n = sizeof(items) / sizeof(items[0]);   \
        for (int i = 0; i < n; i++)		    \
	{              				    \
            PRINT_MENU_ITEM(i + 1, items[i]);       \
        }


/**
 * @brief Macro xử lý từng lựa chọn của người dùng.
 * @param[in] number Số thứ tự của tùy chọn.
 * @param[in] function Hàm xử lý tùy chọn tương ứng.
 */
#define CASE_OPTION(number, function) case number: function(); break;


/**
 * @brief Macro để xử lý lựa chọn của người dùng thông qua switch-case.
 * @param[in] option Biến lựa chọn của người dùng.
 * @param[in] ... Danh sách các CASE_OPTION tương ứng.
 */
#define HANDLE_OPTION(option, ...)              \
    switch (option)				\
    {                           	        \
        __VA_ARGS__                             \
        default: printf("Invalid option!\n");   \
    }

/**
 * @brief Hàm xử lý khi người dùng chọn tính năng 1.
 */
void feature1() { printf("Feature 1 selected\n"); }

/**
 * @brief Hàm xử lý khi người dùng chọn tính năng 2.
 */
void feature2() { printf("Feature 2 selected\n"); }

/**
 * @brief Hàm xử lý khi người dùng chọn tính năng 3.
 */
void feature3() { printf("Feature 3 selected\n"); }

/**
 * @brief Hàm xử lý khi người dùng chọn tính năng 4.
 */
void feature4() { printf("Feature 4 selected\n"); }

int main(int argc, char const *argv[])
{
    // Hiển thị menu cho người dùng
    PRINT_MENU("Option 1", "Option 2", "Option 3", "Option 4", "Exit");

    int option;
    scanf("%d", &option);

    // Xử lý lựa chọn của người dùng
    HANDLE_OPTION(option, 
        CASE_OPTION(1,feature1)
        CASE_OPTION(2,feature2)
        CASE_OPTION(3,feature3)
        CASE_OPTION(4,feature4)
        )
    return 0;
}
```

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>3. Thư viện STDARG</b></summary>
<p>

<details><summary><b>3.1. Giới thiệu thư viện stdarg</b></summary>
<p>

- Tương tự với macro variadic.
- Cung cấp các hàm, macros để làm việc với các hàm có số lượng tham số đầu vào không xác định.
- Các hàm như printf, scanf là ví dụ điển hình.

</p>
</details>

<details><summary><b>3.2. Các Macro trong thư viện stdarg</b></summary>
<p>

<details><summary><b>📚 va_list</b></summary>
<p>

Là một kiểu dữ liệu để đại diện cho danh sách các đối số biến đổi.

``` va_list args ```

📝 Bản chất va_list là một kiểu dữ liệu đã được sử dụng ``` typedef ``` để định nghĩa lại: ``` typedef char* va_list = "int label, ..." ```

📝 Khi thay thế các số trực tiếp vào ``` ... ```, ví dụ ``` 1,5,7 ``` thì trở thành ``` typedef char* va_list = "int count,1,5,7" ```

📝 Địa chỉ:

```cpp
0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
'i'  'n'  't'  ' '  'c'  'o'  'u'  'n'  't'  ','  '1'  ','  '5'  ','  '7'
```

📝 args: có thể hiểu là một con trỏ được cấp phát động bộ nhớ để truy cập vào từng ký tự trên.

</p>
</details>

<details><summary><b>📚 va_start</b></summary>
<p>

Bắt đầu một danh sách đối số biến đổi. Nó cần được gọi trước khi truy cập các đối số biến đổi đầu tiên.

``` va_start(args, label) ```

📝 label: chính là tên biến mà ta truyền vào, ví dụ ``` int count ``` thì label là ``` count ```, ``` int a ``` thì label là ``` a ```

📝 ``` va_start ``` thực hiện so sánh chuỗi phía trên với label (so sánh từng ký tự) để tìm kiếm đâu là nơi bắt đầu của những số cần thao tác chính. 

📝 Khi con trỏ ``` args ``` trỏ đến địa chỉ 0x0A (,) thì những số phía sau (1,5,7) sẽ là danh sách đối số cần thao tác chính, khi đó ``` args ``` sẽ chỉ còn quản lý danh sách này: ``` args = {'\1', '\5', '\7'} ``` hoặc có thể là ``` args = {"\001", "\005", "\007"} ```

</p>
</details>

<details><summary><b>📚 va_arg</b></summary>
<p>

Truy cập một đối số trong danh sách. Hàm này nhận một đối số của kiểu được xác định bởi tham số thứ hai.

``` va_arg(args, <data_type>) ```

- ``` args ```: con trỏ kiểu ``` va_list ```, trỏ đến danh sách tham số hiện tại.''
- ``` data_type ```: Kiểu dữ liệu của giá trị tiếp theo cần đọc từ danh sách.

	+ Xác định kích thước dữ liệu cần đọc từ vùng nhớ.
	+ Nếu kiểu dữ liệu không đúng, kết quả trả về sẽ không chính xác, dẫn đến hành vi không xác định (undefined behavior).

- Mỗi lần gọi ``` va_arg(args, <data_type>) ``` thì sẽ thực hiện truy cập và lấy ra 1 phần tử trong mảng.

</p>
</details>

<details><summary><b>📚 va_copy</b></summary>
<p>

Sao chép một đối tượng va_list.  Điều này rất hữu ích khi bạn muốn lưu trữ trạng thái hiện tại của va_list để sử dụng sau này hoặc khi cần đọc lại các đối số biến đổi mà không làm thay đổi va_list gốc.

```cpp
va_list args;
va_list check;
va_copy(check,args);
```

📝 ``` va_copy ``` giúp con trỏ ``` check ``` copy địa chỉ mà con trỏ ``` args ``` đang trỏ đến 

</p>
</details>

<details><summary><b>📚 va_end</b></summary>
<p>

Kết thúc việc sử dụng danh sách đối số biến đổi. Nó cần được gọi trước khi kết thúc hàm.

``` va_end(args) ```

📝 Thu hồi địa chỉ con trỏ ``` args ```

</p>
</details>

<details><summary><b>📚 Ví dụ</b></summary>
<p>

💻 **Ví dụ 1:**
```cpp
#include <stdio.h>
#include <stdarg.h>

void test(int count, ...)
{
    va_list args;

    va_start(args, count);

    printf("value 1: %d\n", va_arg(args, int));
    printf("value 2: %d\n", va_arg(args, int));
    printf("value 3: %f\n", va_arg(args, double));
    printf("value 4: %c\n", va_arg(args, char*));
    printf("value 5: %s\n", va_arg(args, char*));

    va_end(args);
}

int main(int argc, char const *argv[])
{
    test(4, 1, 2, 3.14, 'a', "hello world");

    return 0;
}
```

📝 tham số ``` count ``` được sử dụng để xác định **số lượng tham số biến đổi (...)** mà hàm sẽ nhận. Vì ``` stdarg.h ``` không có cách nào để tự động biết có bao nhiêu đối số nên cần một tham số đầu tiên để biểu thị số lượng tham số còn lại.

📝 Có thể đặt nhiều tham số cố định trước ``` ... ``` nhưng tham số cuối cùng trước ``` ... ``` sẽ được dùng trong ``` va_start() ```.

<br>

💻 **Tổng ``` n ``` số (Cách 1: chỉ sử dụng thư viện STDARG)**
```cpp
/***************************************************************************
 * @file    sum.c
 * @brief   Chương trình tính tổng các số nguyên sử dụng danh sách đối số biến đổi
 * @details Sử dụng thư viện stdarg.h để xử lý danh sách đối số có độ dài tùy ý.
 * @version 1.0
 * @date    2024-08-12
 * @author  Anh Nguyen
 ***************************************************************************/
#include <stdio.h>
#include <stdarg.h>


/**
 * @brief   Hàm tính tổng các số nguyên.
 * @details Nhận một số lượng tham số tùy ý và tính tổng các giá trị đó.
 * @param   count   Số lượng tham số truyền vào.
 * @return  Giá trị tổng của các số nguyên truyền vào.
 */
int sum(int count, ...)
{                                
    va_list args; 		/**< Danh sách các đối số biến đổi */
    
    va_start(args, count);	/**< Khởi tạo danh sách đối số */

    int result = 0;		 /**< Biến lưu trữ kết quả tổng */

    for (int i=0; i<count; i++)
    {
        result += va_arg(args, int); /**< Lấy từng tham số và cộng vào tổng */
    }

    va_end(args);   		/**< Kết thúc danh sách đối số */

    return result;		
}

int main(int argc, char const *argv[])
{
    printf("Tong = %d\n",sum(7, 1, 2, 3, 4, 5, 10, 15));
    return 0;
}
```

<br>

💻 **Tổng ``` n ``` số (Cách 2: thư viện STDARG kết hợp variadic với ``` số 0 ``` ở cuối để nhận biết kết thúc việc tính tổng)**
```cpp
/***************************************************************************
 * @file    sum_variadic.c
 * @brief   Chương trình tính tổng các số nguyên sử dụng macro và danh sách đối số biến đổi.
 * @details Sử dụng thư viện stdarg.h kết hợp variadic để xử lý danh sách đối số có độ dài tùy ý.
 * @version 1.0
 * @date    2024-08-12
 * @author  Anh Nguyen
 ***************************************************************************/
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief   Macro hỗ trợ gọi hàm sum với tham số cuối là 0.
 */
#define tong(...)   sum(__VA_ARGS__, 0)


/**
 * @brief   Hàm tính tổng các số nguyên.
 * @details Nhận một số lượng tham số tùy ý và tính tổng các giá trị đó.
 *          Sử dụng số 0 như giá trị kết thúc danh sách tham số.
 * @param   count   Số lượng tham số truyền vào.
 * @return  int     Giá trị tổng của các số nguyên truyền vào.
 */
int sum(int count,...)
{
    va_list args;
    va_start(args, count);

    int result = count;
    int value;

    while ((value = va_arg(args, int)) != 0) result += value;

    va_end(args);
    return result;
}

int main()
{
    printf("Tong: %d\n", tong(3, 0, -1, 2, 33, 4, 5));
    return 0;
}
```

<br>

💻 **Tổng ``` n ``` số (Cách 3: thư viện STDARG kết hợp variadic với ``` ký tự bất kỳ ``` ở cuối để nhận biết kết thúc việc tính tổng)**
```cpp
/***************************************************************************
 * @file    sum_variadic.c
 * @brief   Chương trình tính tổng các số nguyên sử dụng macro và danh sách đối số biến đổi.
 * @details Sử dụng thư viện stdarg.h kết hợp variadic để xử lý danh sách đối số có độ dài tùy ý.
 * @version 1.0
 * @date    2024-08-12
 * @author  Anh Nguyen
 ***************************************************************************/
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief   Macro gọi hàm sum với tham số cuối là ký tự xuống dòng '\n'.
 */
#define tong(...)   sum(__VA_ARGS__, '\n')

/**
 * @brief   Hàm tính tổng các số nguyên.
 * @details Kiểm tra danh sách đối số và cộng dồn đến khi gặp ký tự xuống dòng `\n`.
 * @param   count   Số lượng tham số truyền vào.
 * @return  int     Giá trị tổng của các số nguyên truyền vào.
 */
int sum(int count,...)
{
    va_list args;
    va_list check;
    
    va_start(args, count);
    va_copy(check, args);

    int result = count;
    while (va_arg(check, char*) != (char*)'\n') result += va_arg(args,int);

    va_end(args);
    return result;
}

int main(int argc, char const *argv[])
{
    printf("Tong: %d\n", tong(3, 0, -1, 2, 0, 4, 5));
    return 0;
}
```

<br>

💻 **Ví dụ 5:**
```cpp
/***************************************************************************
 * @file    display_struct.c
 * @brief   Hiển thị dữ liệu kiểu struct bằng danh sách đối số biến đổi.
 * @details Sử dụng va_list để truyền nhiều struct vào một hàm.
 * @version 1.0
 * @date    2024-09-12
 * @author  Anh Nguyen
 ***************************************************************************/
#include <stdio.h>
#include <stdarg.h>


/**
 * @brief   Định nghĩa cấu trúc dữ liệu chứa số nguyên và số thực.
 */
typedef struct Data
{
    int x;
    double y;
} Data;

/**
 * @brief   Hàm hiển thị thông tin struct `Data`.
 * @details Duyệt danh sách đối số biến đổi để in ra dữ liệu của từng struct.
 * @param   count   Số lượng struct được truyền vào.
 */
void display(int count, ...)
{
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        Data tmp = va_arg(args,Data);
        printf("Data.x at %d is: %d\n", i,tmp.x);
        printf("Data.y at %d is: %f\n", i,tmp.y);
    }
   
    va_end(args);
}

int main(int argc, char const *argv[])
{
    display(3, (Data){2,5.0} , (Data){10,57.0}, (Data){29,36.0});
    return 0;
}
```

<br>

💻 **Ví dụ 6:**
```cpp
/***************************************************************************
 * @file    sensor_data.c
 * @brief   Xử lý dữ liệu cảm biến sử dụng danh sách đối số biến đổi.
 * @details Hỗ trợ hai loại cảm biến: nhiệt độ và áp suất.
 * @version 1.0
 * @date    2024-09-12
 * @author  Anh Nguyen
 ***************************************************************************/
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief   Kiểu enum cho các loại cảm biến được hỗ trợ.
 */
typedef enum
{
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR
} SensorType;


/**
 * @brief   Hàm xử lý dữ liệu cảm biến.
 * @details Sử dụng danh sách đối số biến đổi để nhận các loại cảm biến khác nhau.
 * @param   type    Loại cảm biến (nhiệt độ hoặc áp suất).
 */
void processSensorData(SensorType type, ...)
{
    va_list args;
    va_start(args, type);

    switch (type)
    {
        case TEMPERATURE_SENSOR:
        {
            int numArgs  = va_arg(args, int);
            int sensorId = va_arg(args, int);
            double temperature = va_arg(args, double); 

            printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature);
            if (numArgs > 2)
	    {
                // Xử lý thêm tham số nếu có
                char *additionalInfo = va_arg(args, char*);
                printf("Additional Info: %s\n", additionalInfo);
            }
            break;
        }

        case PRESSURE_SENSOR:
        {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            int pressure = va_arg(args, int);

            printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
            if (numArgs > 2)
	    {
                // Xử lý thêm tham số nếu có
                char *unit = va_arg(args, char*);
                printf("Unit: %s\n", unit);
            }
            break;
        }
    }

    va_end(args);
}

int main(int argc, char const *argv[])
{
    processSensorData(TEMPERATURE_SENSOR, 3, 1, 36.5, "Room Temperature");
    processSensorData(PRESSURE_SENSOR, 4, 2, 101325, 123, "aads");
    return 0;
}
```

<br>

💻 **Ví dụ 7:**
```cpp
/***************************************************************************
 * @file    command_handler.c
 * @brief   Xử lý các lệnh điều khiển thiết bị sử dụng danh sách đối số biến đổi.
 * @details Hỗ trợ các lệnh: bật, tắt thiết bị, đặt mức độ, và gửi tin nhắn.
 * @version 1.0
 * @date    2024-09-12
 * @author  Anh Nguyen
 ***************************************************************************/
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief   Kiểu enum đại diện cho các loại lệnh điều khiển thiết bị.
 */
typedef enum
{
    TURN_ON,
    TURN_OFF,
    SET_LEVEL,
    SEND_MESSAGE
} CommandType;


/**
 * @brief   Xử lý và thực hiện lệnh điều khiển thiết bị.
 * @details Hàm này nhận một loại lệnh và các tham số tương ứng để thực hiện.
 * @param   command     Loại lệnh cần thực hiện (TURN_ON, TURN_OFF, SET_LEVEL, SEND_MESSAGE).
 * @return  void
 */
void sendCommand(CommandType command, ...)
{
    va_list args;
    va_start(args, command);

    switch (command)
    {
        case TURN_ON:
        case TURN_OFF:
	{
            int deviceID = va_arg(args, int);
            printf("Command: %s Device ID: %d\n", command == TURN_ON ? "Turn On" : "Turn Off", deviceID);
            break;
        }

        case SET_LEVEL:
	{
            int deviceID = va_arg(args, int);
            int level = va_arg(args, int);
            printf("Set Level of Device ID %d to %d\n", deviceID, level);
            break;
        }

        case SEND_MESSAGE:
	{
            char* message = va_arg(args, char*);
            printf("Send Message: %s\n", message);
            break;
        }
    }

    va_end(args);
}

int main()
{
    sendCommand(TURN_ON, 1);
    sendCommand(TURN_OFF, 5);
    sendCommand(SET_LEVEL, 3, 75);
    sendCommand(SEND_MESSAGE, "Hello World");
    return 0;
}
```

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>4. Thư viện assert</b></summary>
<p>

- Cung cấp macro assert dùng để kiểm tra một điều kiện.
- Nếu điều kiện đúng thì chương trình tiếp tục thực thi.
- Nếu điều kiện sai thì chương trình dừng lại ngay lập tức và thông báo một thông điệp lỗi.
- Dùng trong debug, dùng ``` #define NDEBUG ``` để tắt debug

💻
```cpp
#include <stdio.h>
#include <assert.h>

#define LOG(condition, cmd) assert(condition && #cmd)

double divide(int a, int b)

{
    LOG(b != 0, Mau bang 0);
    return (double)a/b;
}

int main(int argc, char const *argv[])
{
    int x = 6;    
    LOG(x==5, X phai bang 5);
    printf("x = %d\n", x);    
    
    printf("kq: %f\n", divide(6,0));
    return 0;
}
```

📝 Có thể thấy rằng khi sử dụng assert để kiểm tra lỗi, nếu có lỗi thì chương trình dừng ngay lập tức và không thực thi tiếp bất kỳ tác vụ nào.

📝 Để hạn chế vấn đề trên thì nên sử dụng TRY, CATCH, THROW (sẽ nói ở bài **Thư viện setjmp**).

<br>

💻
```cpp
#include <stdio.h>
#include <assert.h>

#define ASSERT_IN_RANGE(val, min, max) assert((val) >= (min) && (val) <= (max))

void setLevel(int level)
{
    ASSERT_IN_RANGE(level, 1, 10);
    // Thiết lập cấp độ
}
```

<br>

💻
```cpp
#include <assert.h>
#include <stdint.h>

#define ASSERT_SIZE(type, size) assert(sizeof(type) == (size))

void checkTypeSizes()
{
    ASSERT_SIZE(int, 4);
    // Kiểm tra các kích thước kiểu dữ liệu khác
}
```

<br>

</p>
</details>

<br>

<details><summary><b>5. Pointer</b></summary>
<p>

<details><summary><b>5.1. Khái niệm về con trỏ</b></summary>
<p>

- Con trỏ (pointer) là một biến chứa địa chỉ của một đối tượng (biến, mảng hoặc hàm) khác.
- Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.

</p>
</details>

<details><summary><b>5.2. Kích thước con trỏ</b></summary>
<p>

- Kích thước của con trỏ phụ thuộc vào **kiến trúc vi xử lý** hoặc **kiến trúc máy tính và trình biên dịch**.
- Hệ thống 32-bit, kích thước của con trỏ là 4 byte.
- Hệ thống 64-bit, kích thước của con trỏ là 8 byte.
- SMT32: kiến trúc 32-bit (ARM Cortex-M) nên kích thước con trỏ là 4 byte.
- STM8: kiến trúc 8-bit nên kích thước con trỏ là 1 byte.

🖥️
```cpp
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    printf("%d bytes\n", sizeof(int *));
    printf("%d bytes\n", sizeof(uint8_t *));
    printf("%d bytes\n", sizeof(int16_t *));
    printf("%d bytes\n", sizeof(char *));
    printf("%d bytes\n", sizeof(float *));
    printf("%d bytes\n", sizeof(double *));
    printf("%d bytes\n", sizeof(long *));
    printf("%d bytes\n", sizeof(short *));
    printf("%d bytes\n", sizeof(long long *));
    printf("%d bytes\n", sizeof(bool *));
    return 0;
}
```
<br>

🤔 Nếu kích thước con trỏ không thay đổi thì kiểu dữ liệu của nó sẽ ảnh hưởng như thế nào đến việc sử dụng nó❓ 

➡️ **Kích thước bước nhảy khi tăng/giảm giá trị của con trỏ**: giá trị con trỏ sẽ thay đổi theo kích thước của kiểu dữ liệu mà nó trỏ tới.

Ví dụ: 
```cpp
char:   0x00 -> 0x01 -> 0x02 -> ...
int:    0x00 -> 0x04 -> 0x08 -> ...
double: 0x00 -> 0x08 -> 0x10 -> ...
```

➡️ **Truy cập giá trị**: Khi truy cập giá trị thông qua con trỏ (bằng toán tử dereference ``` * ```), kiểu dữ liệu của con trỏ quyết định kích thước và cách thức dữ liệu được đọc hoặc ghi tại địa chỉ mà con trỏ trỏ đến.

Ví dụ: 
```cpp
char:   truy cập 1 byte tại địa chỉ pointer trỏ đến.
short:  truy cập 2 byte tại địa chỉ pointer trỏ đến.
int:    truy cập 4 byte tại địa chỉ pointer trỏ đến.
double: truy cập 8 byte tại địa chỉ pointer trỏ đến.
```

<br>

**Ứng dụng con trỏ**:

🖥️ **Ví dụ: Nhập số từ bàn phím**
```cpp
#include <stdio.h>

void input(int *a, int *b)
{
    printf("Nhap so 1: "); scanf("%d", a);
    printf("Nhap so 2: "); scanf("%d", b);
}

int main(int argc, char const *argv[])
{
    int a,b;
    input(&a,&b);
    return 0;
}
```

<br>

🖥️ **Ví dụ: Hoán đổi 2 số**
```cpp
#include <stdio.h>

void swap1(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
// Khi gọi hàm sẽ khởi tạo 2 địa chỉ, gs là 0xc1 và 0xf2 để lưu giá trị a,b
// Thực hiện copy giá trị của biến a,b trong hàm main và đưa vào 2 địa chỉ trên
// a,b ở đây là 2 tham số truyền vào của hàm nên sẽ lưu ở Stack và bị thu hồi vùng nhớ khi kết thúc việc gọi hàm
// Vì vậy, gọi hàm này sẽ không hoán đổi 2 số

void swap2(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Khi gọi hàm sẽ truy cập đến 2 địa chỉ 0x01 và 0xb4 để lấy giá trị và thực hiện hoán đổi

int main(int argc, char const *argv[])
{
    int a = 10;	// địa chỉ 0x01
    int b = 20; // địa chỉ 0xb4

    // swap1(a,b);
    swap2(&a,&b);
    printf("value a is: %d\n", a);
    printf("value b is: %d\n", b);
    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>5.3. Các kiểu con trỏ</b></summary>
<p>

<details><summary><b>📚 Con trỏ Void (Void Pointer)</b></summary>
<p>
	
- Thường dùng để **trỏ tới bất kỳ địa chỉ** với bất kỳ kiểu dữ liệu của giá trị tại địa chỉ đó.
- Muốn in ra giá trị thì phải sử dụng ép kiểu để đưa con trỏ void về đến kiểu dữ liệu của giá trị đó.
- Cú pháp: ``` void *ptr_void ```

🖥️
```cpp 
#include <stdio.h>

void sum(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a+b);
}

int main(int argc, char const *argv[])
{
    void *ptr_void;
    ptr_void = (void*)sum;
    ((void (*)(int,int))ptr_void)(9,3);

    int var_int = 10;
    ptr_void = &var_int;
    printf("Dia chi: %p, int: %d\n", ptr_void, *(int*)ptr_void);

    double var_double = 3.14;
    ptr_void = &var_double;
    printf("Dia chi: %p, double: %.3f\n", ptr_void, *(double*)ptr_void);

    char var_char = 'A';
    ptr_void = &var_char;
    printf("Dia chi: %p, char: %c\n", ptr_void, *(char*)ptr_void);

    char arr[] = "hello";
    ptr_void = arr;

    // printf("chuoi: %c\n", *(char*)(ptr_void+1));
    
    printf("Chuoi: ");
    for (int i=0; i<(sizeof(arr)/sizeof(arr[0])); i++){
        printf("%c\n", *(char*)(ptr_void+i));
    }
    printf("\n");

    void *ptr[] = {&var_int, &var_double, &var_char, sum, arr};
    printf("ptr[0] = %d\n", *(int*)ptr[0]);
    printf("ptr[1] = %f\n", *(double*)ptr[1]);
    printf("ptr[2] = %c\n", *(char*)ptr[2]);

    ((void (*)(int,int))ptr[3])(9,3);

    for (int i=0; i<(sizeof(arr)/sizeof(arr[0])); i++)
    {
        printf("%c", *(char*)(ptr[4]+i));
    }
    return 0;
}

```

<br>

</p>
</details>

<details><summary><b>📚 Con trỏ hàm (Function Pointer)</b></summary>
<p>
	
- Con trỏ hàm là một biến mà **giữ địa chỉ của hàm**.
- Cần chỉ định kiểu dữ liệu của hàm mà con trỏ đó sẽ tham chiếu đến khi khai báo, bao gồm kiểu trả về và các tham số của hàm. Sau đó, ta có thể gán con trỏ hàm này cho một hàm cụ thể.
- Khi gọi con trỏ hàm, chương trình sẽ thực thi hàm mà con trỏ đang tham chiếu đến.
- Cú pháp:

``` <return_type> (* func_pointer)(input_1_data type, input_2_data type,....) ```

🖥️ **Ví dụ 1:**
```cpp
#include <stdio.h>
// Hàm mẫu 1
void greetEnglish(){ printf("Hello!\n"); }

// Hàm mẫu 2
void greetFrench(){ printf("Bonjour!\n"); }

int main()
{
    // Khai báo con trỏ hàm
    void (*ptrToGreet)();
    
    // Gán địa chỉ của hàm greetEnglish cho con trỏ hàm
    ptrToGreet = greetEnglish;
    
    // Gọi hàm thông qua con trỏ hàm
    ptrToGreet();  // In ra: Hello!

    // Gán địa chỉ của hàm greetFrench cho con trỏ hàm
    ptrToGreet = greetFrench;
    
    // Gọi hàm thông qua con trỏ hàm
    (*ptrToGreet)();  // In ra: Bonjour!    
    
    return 0;
}
```

<br>

🖥️ **Ví dụ 2:**
```cpp
#include <stdio.h>

void tong(int a, int b){ printf("%d + %d = %d\n", a, b, a+b); }

void hieu(int a, int b){ printf("%d - %d = %d\n", a, b, a-b); }

void tich(int a, int b){ printf("%d x %d = %d\n", a, b, a*b); }

void thuong(int a, int b){ printf("%d / %d = %0.3f\n", a, b, a/(double)b); }

void tinhtoan(void (*pheptoan)(int,int), int a, int b)
{
    pheptoan(a,b);
}

int main(int argc, char const *argv[])
{
    int a = 10, b = 20;

    // cách 1
    void (*ptr)(int,int);
    ptr = tong;
    ptr(a,b);

    ptr = hieu;
    ptr(a,b);

    ptr = tich;
    ptr(a,b);

    ptr = thuong;
    ptr(a,b);
    printf("\n");


    // cách 2
    tinhtoan(tong,a,b);
    tinhtoan(hieu,a,b);
    tinhtoan(tich,a,b);
    tinhtoan(thuong,a,b);
    printf("\n");


    // cách 3
    void (*calculate[])(int,int) = {tong, hieu, tich, thuong};
    calculate[0](a,b);
    calculate[1](a,b);
    calculate[2](a,b);
    calculate[3](a,b);
    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>📚 Con trỏ hằng (Pointer to constant)</b></summary>
<p

- Con trỏ hằng là một cách định nghĩa một con trỏ **chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến (Read Only)** nhưng không thể thay đổi được giá trị đó.
- Đối với biến là hằng số thì phải luôn dùng con trỏ hằng khi trỏ đến.
- Cú pháp: 
```cpp
<data_type> const *ptr_const;
const <data_type> *ptr_const;
```

🖥️ **Ví dụ 1:**
```cpp
#include <stdio.h>

int value1 = 10;
int value2 = 3;
const int *ptr_const = &value1;

int main(int argc, char const *argv[])
{
    printf("%p\n", ptr_const);
    printf("%d\n", *ptr_const);

    value1 = 5;
    printf("%p\n", ptr_const);
    printf("%d\n", *ptr_const);

    //*ptr_const = 5;    // wrong
    ptr_const = &value2; // right
    printf("%p\n", ptr_const);
    printf("%d\n", *ptr_const);
    return 0;
}
```
📝 Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only location '*ptr_const'```

<br>

🖥️ **Ví dụ 2:**
```cpp
#include <stdio.h>

void test(const char *str)
{
	str[0] = 'A';
}

int main(int argc, char const *argv[])
{
    char arr[] = "Hello World";
    test(arr);
    printf("%s\n", arr);
    return 0;
}
```

📝 Trong hàm test, nếu khai báo ``` char* ``` thì chuỗi truyền vào hoàn toàn có thể bị thay đổi. Để ngăn việc thay đổi xảy ra, nghĩa là nhu cầu chỉ đọc chuỗi truyền vào thì phải khai báo ``` const char* ```.

<br>

</p>
</details>

<details><summary><b>📚 Hằng con trỏ (Constant to Pointer)</b></summary>
<p
    
- Hằng con trỏ là một con trỏ mà **trỏ đến 1 địa chỉ cố định**, nghĩa là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.
- Cú pháp: ``` int *const const_ptr = &value; ```

💻 **Ví dụ 1:**
```cpp
#include <stdio.h>

int value1 = 10;
int value2 = 20;
int *const const_ptr = &value1;

int main(int argc, char const *argv[])
{
    printf("%p\n", const_ptr);
    printf("%d\n", *const_ptr);

    *const_ptr = 5;
    printf("%p\n", const_ptr);
    printf("%d\n", *const_ptr);
    
    // const_ptr = &value2; // wrong
    // printf("%p\n", const_ptr);
    return 0;
}

```
📝 Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only variable 'const_ptr'```

<br>

**Ứng dụng**: thiết kế thư viện, ví dụ một GPIO sẽ có nhiều thanh ghi bên trong như GPIO_CRL, GPIO_CRH, GPIO_ODR, v.v. Mỗi thanh ghi sẽ được cấp cho một địa chỉ cố định.

</p>
</details>

<details><summary><b>📚 Con trỏ NULL (Null Pointer)</b></summary>
<p
    
- Con trỏ NULL là một con trỏ không trỏ đến bất kỳ địa chỉ hợp lệ nào trong bộ nhớ.

💻
```cpp
int *ptr_null = NULL;
//  ptr_null = 0x00: địa chỉ khởi tạo
// *ptr_null = 0   : giá trị tại địa chỉ khởi tạo
```

<br>

**Ý nghĩa của con trỏ NULL:**

- **Kiểm tra địa chỉ hợp lệ**: Trước khi sử dụng con trỏ, bạn có thể kiểm tra xem con trỏ có phải là NULL không, giúp tránh các lỗi truy cập vào bộ nhớ không hợp lệ.
- **Biểu thị giá trị không hợp lệ**: Trước khi sử dụng con trỏ, bạn có thể kiểm tra xem con trỏ có phải là NULL không, giúp tránh các lỗi truy cập vào bộ nhớ không hợp lệ.
- **Kết thúc cấu trúc dữ liệu**: NULL được sử dụng để đánh dấu kết thúc trong các cấu trúc dữ liệu như danh sách liên kết.

<br>

💻
```cpp
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr = NULL;  /**< Khởi tạo con trỏ NULL */

    // Cấp phát bộ nhớ cho con trỏ
    ptr = (int*)malloc(sizeof(int));

    // Kiểm tra xem cấp phát có thành công không
    if (ptr == NULL)
    {
        printf("Không đủ bộ nhớ để cấp phát.\n");
        return 1;  // Kết thúc chương trình với mã lỗi
    }

    // Nếu thành công, sử dụng con trỏ
    *ptr = 10;
    printf("Giá trị được lưu trong bộ nhớ: %d\n", *ptr);

    // Giải phóng bộ nhớ và đặt con trỏ về NULL
    free(ptr);
    ptr = NULL;  /**< Đặt lại con trỏ về NULL sau khi giải phóng bộ nhớ */

    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>📚 Pointer to pointer</b></summary>
<p
    
- Là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ.
- Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép bạn thay đổi giá trị của con trỏ gốc.
- Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi bạn làm việc với các hàm cần thay đổi giá trị của con trỏ.

💻
```cpp
int a = 10;		// a là 1 biến, giả sử có địa chỉ 0x01
int *ptr1  = &a;	// ptr1 là con trỏ cấp 1, trỏ đến địa chỉ biến a (0x01), dịa chỉ ptr1 là 0xf4
int **ptr2 = &ptr1;	// ptr2 là con trỏ cấp 2, trỏ đến địa chỉ ptr1 (0xf4)
```

```cpp
ptr1 = &a = 0x01;
*ptr1 = a = 10;

ptr2 = &ptr1 = 0xf4;
*ptr2 = *(&ptr1) = *(0xf4) = 0x01;
**ptr2 = *(0x01) = 10;
```

<br>

</p>
</details>

<details><summary><b>📚 Dangling pointer</b></summary>
<p>

**Dangling Pointer** là con trỏ trỏ đến một vùng nhớ không hợp lệ hoặc không còn tồn tại. Khi truy cập vào vùng nhớ này, chương trình có thể gặp lỗi nghiêm trọng như Undefined Behavior (UB), lỗi truy cập bộ nhớ (segmentation fault) hoặc rò rỉ bộ nhớ (memory leak).

<br>

💻 **Ví dụ 1: Giải phóng bộ nhớ nhưng vẫn giữ con trỏ**
```cpp
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    // Cấp phát động 5 byte
    int* ptr = (int*)malloc(5);

    // Giải phóng bộ nhớ
    free(ptr); 

    // Truy cập vào con trỏ đã bị giải phóng -> Undefined Behavior
    printf("%d\n", *ptr);

    return 0;
}
```

👉 **Cách khắc phục**: Đặt con trỏ về nullptr sau khi giải phóng.

```cp
free(ptr);
ptr = NULL;
```

<br>

💻 **Ví dụ 2: Con trỏ trỏ đến biến cục bộ của một hàm**
```cpp
#include <stdio.h>

int* func() 
{
    int x = 10;
    return &x; // Trả về địa chỉ biến cục bộ -> Dangling pointer
}

int main() 
{
    int* p = func();
    printf("%d\n", *p) ; // Lỗi! Biến x không còn tồn tại
    return 0;
}
```

👉 **Cách khắc phục**: Sử dụng biến **static**

```cpp
int* func()
{
    static int x = 10; // Giữ giá trị sau khi hàm kết thúc
    return &x;
}
```

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>6. Các biến đặc biệt</b></summary>
<p>

<details><summary><b>📚 Extern</b></summary>
<p>

- **extern** có thể sử dụng cho một đối tượng (biến hoặc hàm), nếu là **biến** thì phải được **khai báo toàn cục** với mục đích là thông báo rằng biến hoặc hàm này đã được định nghĩa ở một nơi khác trong chương trình hoặc trong 1 file nguồn khác.
- **extern** cho phép các file nguồn khác nhau trong cùng một chương trình chia sẽ và sử dụng các biến và hàm mà không cần định nghĩa lại.
- **extern** chỉ cho phép khai báo chứ không định nghĩa.
- Cú pháp: ``` extern <data_type> <name_variable>; ```

💻 

File **test1.c**
```cpp
#include <stdio.h>

int a = 10;

void display1(){ printf("This is test1.c\n"); }
```

File **test2.c**
```cpp
#include <stdio.h>

int b = 10;

void display2(){ printf("This is test2.c\n"); }
```

File **main.c**
```cpp
#include <stdio.h>
#include "test1.c"
#include "test2.c"

int main(int argc, char const *argv[])
{
    a = 20;
    printf("a = %d\n",a);

    b = 50;
    printf("b = %d\n",b);

    display1();
    display2();
    return 0;
}
```

📝 Muốn gọi đối tượng khác (biến hoặc hàm) đã được khai báo trong file khác thì sử dụng #include.

🤔 Vậy nếu có nhiều file hơn trong project thì làm sao❓

➡️ Có thể #include tất cả file vào.

➡️ Tuy nhiên, nếu không nhớ biến hoặc hàm nằm ở file nào thì việc làm trên thì vừa mất thời gian vừa tốn bộ nhớ để khởi tạo một số hàm hoặc biến không cần thiết.

➡️ Sử dụng extern và thực hiện liên kết các file.

File **main.c**
```cpp
#include <stdio.h>

extern int a;
extern int b;

extern void display1();
extern void display2();

int main(int argc, char const *argv[])
{
    a = 20;
    printf("a = %d\n",a);

    b = 50;
    printf("b = %d\n",b);

    display1();
    display2();
    return 0;
}
```

📝 Thực hiện liên kết file: gcc main.c File1.c File2.c -o main

📝 Lệnh trên sẽ tự động:

Thực hiện tiền xử lý (-E).
Tạo mã assembly (-S).
Tạo object file (-o).
Liên kết tất cả các file main.o, File1.o, File2.o để tạo ra file thực thi main.

<br>

**Ứng dụng**:

- Thiết kế thư viện.

💻 **Ví dụ**
File **test1.h**
```cpp
#ifndef TEST1_H
#define TEST1_H

extern int a;

void display1();

#endif
```

File **test1.c**
```cpp
#include <stdio.h>
#include "test1.h"

int a = 10;

void display1()
{
    printf("This is test1.c\n");
}
```

File **test2.h**
```cpp
#ifndef TEST2_H
#define TEST2_H

extern int b;

void display2();

#endif
```

File **test2.c**
```cpp
#include <stdio.h>
#include "test2.h"

int b = 10;

void display2()
{
    printf("This is test2.c\n");
}
```

File **main.c**
```cpp
#include <stdio.h>
#include "File1.h"
#include "File2.h"

int main(int argc, char const *argv[])
{
    a = 20;
    printf("a = %d\n",a);

    b = 50;
    printf("b = %d\n",b);

    display1();
    display2();
    return 0;
}
```

<br>

- Chia sẻ biến và hàm giữa các file nguồn hoặc giữa các module và thư viện mà không cần định nghĩa lại chúng.

💻 **Ví dụ**
```cpp
// hardware_config.c
unsigned int systemClock = 16000000; // Định nghĩa

// main.c
extern unsigned int systemClock;     // Khai báo
void setupSystem()
{
    printf("System clock: %u Hz\n", systemClock);
}
```

<br>

- Quản lý Thanh ghi Phần cứng: khai báo các thanh ghi phần cứng trong các file khác nhau, giúp tách biệt phần cấu hình phần cứng và logic điều khiển.

💻 **Ví dụ**
```cpp
/* registers.h */
extern uint32_t *const GPIO_PORTA; // Khai báo thanh ghi GPIO

/* registers.c */
// Định nghĩa
uint32_t *const GPIO_PORTA = (uint32_t*)0x40020000;

// Cấu hình GPIO

// main.c
#include "registers.h"
void togglePin()
{
    *GPIO_PORTA ^= (1 << 2); // Đảo bit thứ 2
    *GPIO_PORTA ^= (1 << 5); // Đảo bit thứ 5
}

```

</p>
</details>

<details><summary><b>📚 Static</b></summary>
<p>

**Cú pháp**:

```cpp
static <data_type> <name_variable>;
static <data_type> <name_function>;
```

<details><summary><b>📚📚 Static local</b></summary>
<p>
	
Khi 1 biến cục bộ được khai báo với từ khóa static:

- Biến chỉ được khởi tạo một lần, nghĩa là địa chỉ của nó sẽ tồn tại xuyên suốt chương trình.
- Giữ phạm vi của biến chỉ trong hàm đó.
- Giữ giá trị của biến qua các lần gọi hàm.

💻 **Ví dụ 1:**
```cpp
#include <stdio.h>

void count()
{
    static int a = 5;
    a++;
    printf("a = %d\n",a);
}

int main(int argc, char const *argv[])
{
    count();
    count();
    count();
    return 0;
}
```

Kết quả in ra:
```cpp
a = 6
a = 7
a = 8
```

📝 Nếu không có từ khóa static, kết quả 3 lần gọi hàm đều giống nhau vì biến ``` a ``` biến cục bộ, sẽ được lưu trong Stack và địa chỉ sẽ bị thu hồi sau khi hàm thực thi xong. 

📝 Khi thêm ``` static ```, ở lần gọi hàm đầu tiên, biến ``` a ``` sẽ được cấp phát địa chỉ, giả sử 0x01 và địa chỉ tồn tại cho đến hết chương trình.

📝 Khi gọi hàm từ lần 2 trở đi, nó sẽ không thực thi câu lệnh ``` static int a = 5 ``` vì địa chỉ biến a đã được cấp phát trước đó mà sẽ bắt đầu thực thi từ câu lệnh tiếp theo (``` a++ ```).

**Có thể thay đổi giá trị của biến cục bộ từ bên ngoài thông qua một con trỏ.** 

<br>

💻 **Ví dụ 2:**
```cpp
#include <stdio.h>

int *ptr = NULL;

void count()
{
    static int a = 5;
    ptr = &a;
    a++;
    printf("a = %d\n",a);
}

int main(int argc, char const *argv[])
{
    count();     // in ra "a = 6"
    count();     // in ra "a = 7"
    count();     // in ra "a = 8"

    *ptr = 99;  // truy cập địa chỉ 0x01 và thay đổi giá trị biến a thành 99
    count();     // in ra "a = 100"
    ptr = NULL;
    return 0;
}
```

<br>

💻 **Ví dụ 3:**
```cpp
#include <stdio.h>

void absController(int wheelSpeed)
{
    static int absEngaged = 0; // Trạng thái ABS (0: không hoạt động, 1: hoạt động)

    if (wheelSpeed < 5 && absEngaged == 0)
    {
        absEngaged = 1; // Kích hoạt ABS
        printf("ABS engaged\n");
    }
    else if (wheelSpeed >= 5 && absEngaged == 1)
    {
        absEngaged = 0; // Tắt ABS
        printf("ABS disengaged\n");
    }
}

int main()
{
    int speeds[] = {10, 3, 2, 8, 4}; // Tốc độ giả lập
    for (int i = 0; i < 5; i++)
    {
        absController(speeds[i]);
    }
    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>📚📚 Static global</b></summary>
<p>

Khi **'static'** được sử dụng với các biến toàn cục, nó sẽ hạn chế phạm vi của biến chỉ có thể gọi trong file nguồn hiện tại. Điều này giúp ngăn chặn truy cập ngoài ý muốn từ các file khác, đảm bảo tính **encapsulation (đóng gói)**.

💻 **Ví dụ 1:**

File **file1.h**
```cpp
#ifndef FILE1_H
#define FILE1_H

static int a;

static void display();

void test();

#endif
```

File **file1.c**
```cpp
#include <stdio.h>
#include "file1.h"

static int a = 10;

static void display()
{
    printf("This is file1.c\n");
}

void test()
{
    printf("Hello world\n");
}
```

File **main.c**
```cpp
#include <stdio.h>

extern int a;
extern void display();
extern void test();

int main(int argc, char const *argv[])
{
    printf("a = %d\n",a);
    display();
    test();
    return 0;
}

```

📝 gcc main.c file1.c -o main

📝 Kết quả sau khi chạy: 
```cpp
undefined reference to `display'
undefined reference to `a'
```

📝 Dễ thấy file main.c khi chạy sẽ gặp lỗi do cố gắng sử dụng extern để gọi 1 biến toàn cục hoặc hàm đã được khai báo với static trong 1 file nguồn khác.

<br>

💻 **Ví dụ 2:**

File **calculation.h:**
```cpp
#ifndef CALCULATION_H
#define CALCULATION_H

typedef struct 
{
    double x1;
    double x2;
} Result;

static double calculate_Delta(int a, int b, int c);

Result solve_E2(int a, int b, int c);

#endif
```

File **calculation.c:**
```cpp
#include <stdio.h>
#include <math.h>
#include "calculation.h"

static double calculate_Delta(int a, int b, int c)
{
    return b*b - 4*a*c;
}

Result solve_E2(int a, int b, int c)
{
    Result nghiem;

    double delta = calculateDelta(a,b,c);

    if (delta > 0) 
    {
        nghiem.x1 = (-b + sqrt(delta)) / (2 * a);
        nghiem.x2 = (-b - sqrt(delta)) / (2 * a);
    } 
    else if (delta == 0)
    {
        nghiem.x1 = nghiem.x2 = (double)(-b) / (2 * a);
    } 
    else
    {
        nghiem.x1 = nghiem.x2 = NAN;
    }
    return nghiem;
}
```

File **main.c:**
```cpp
#include <stdio.h>
#include "calculation.h"

// extern double calculateDelta(int a, int b, int c);

int main(int argc, char const *argv[])
{
    Result nghiem = {0.0, 0.0};

    nghiem = solve_E2(1, 3, -3);

    printf("x1 = %0.3f, x2 = %0.3f\n", nghiem.x1, nghiem.x2);

    // printf("delta = %f\n", calculateDelta(1,2,-3));
    return 0;
}
```

</p>
</details>

**Ứng dụng**

- Thiết kế thư viện.
- Quản lý tài nguyên bộ nhớ tốt hơn và tránh xung đột tên biến giữa các module khác nhau.
- Khi khai báo biến toàn cục với static trong một file C, biến chỉ có thể truy cập trong file đó, ngăn ngừa các vấn đề chia sẻ biến không mong muốn giữa các file.
- Dùng cho biến cục bộ trong một hàm để giữ lại giá trị của biến giữa các lần gọi hàm (persistence).

<br>

</p>
</details>

<details><summary><b>📚 Volatile</b></summary>
<p>

- **volatile** báo cho compiler biết rằng biến này **có thể sẽ được thay đổi ở bởi yếu tố bên ngoài chương trình** như hardward (ngắt, nhấn button,…) hoặc một luồng khác.
- **volatile** ngăn chặn compiler tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó, giữ cho các thao tác trên biến được thực hiện như đã được định nghĩa.
- Cú pháp: ``` volatile <data_type> <name_variable>; ```
- Biến Volatile rất cần thiết trong lập trình nhúng, vì khi đó có các tác vụ như ngắt ảnh hưởng tới giá trị của biến. Trong lập trình C cơ bản thì rất ít gặp.

💻
```cpp
#include "stm32f4xx.h"                  // Device header

uint8_t *addr = (uint8_t*)0x20000000;
volatile uint8_t var = 0;

int main()
{
	while (1)
        {
		var = *addr;
		if (var != 0) break;
	}
}
```
📝 Khi khai báo biến ``` var ``` mà không có từ khóa ``` volatile ```, nếu giá trị của biến không thay đổi hoặc thay đổi ngay lần đầu chạy debug (thông qua thay đổi giá trị tại địa chỉ 0x20000000) thì compiler sẽ tối ưu hóa biến này khi nhận thấy biến này không có sự thay đổi giá trị ở những lần chạy kế tiếp.

📝 Khi khai báo biến ``` var ``` có từ khóa ``` volatile ```, trong quá trình chạy, nếu giá trị biến thay đổi đột ngột thì chương trình vẫn cập nhật vì compiler chưa tối ưu hóa biến này.

<br>

</p>
</details>

<details><summary><b>📚 Register</b></summary>
<p>

📝 Trong kiến trúc của vi xử lý thì ALU (Arithmetic Logic Unit) đóng vai trò xử lý các tính toán số học và nó chỉ làm việc với các dự liệu được lưu trữ trong thanh ghi (Register).

📝 Khi khai báo các biến trong chương trình thì những biến này được lưu ở RAM. Nếu có thêm phép tính (``` ++ ``` hoặc ``` -- ```) thì nó chỉ lưu thông tin của phép tính này chứ chưa thực hiện.

![image](https://github.com/user-attachments/assets/a57d1e72-86f1-405d-853c-660e459a37f0)

📝 Giai đoạn 1: Nạp giá trị từ RAM vào Register

📝 Giai đoạn 2: Đưa dữ liệu từ Register sang ALU để bắt đầu xử lý.

📝 Giai đoạn 3: Khi ALU xử lý xong thì trả ngược dữ liệu về Register.

📝 Giai đoạn 4: Trả giá trị vừa xử lý từ Register về lại vùng nhớ RAM.

- ``` register ``` được sử dụng để yêu cầu trình biên dịch cố gắng lưu trữ giá trị của biến trong thanh ghi CPU thay vì bộ nhớ RAM, nhằm tăng hiệu suất truy cập (thao tác trên thanh ghi nhanh hơn rất nhiều so với RAM).
- Biến khai báo ``` register ``` không thể lấy địa chỉ bằng toán tử ``` & ``` vì thanh ghi CPU không có địa chỉ trong bộ nhớ.
- Cú pháp: ``` register <data_type> <name_variable>; ```

💻
```cpp
#include <stdio.h>
#include <time.h>

int main()
{
    // Lưu thời điểm bắt đầu
    clock_t start_time = clock();
    int i;
    //register int i;

    // Đoạn mã của chương trình
    for (i = 0; i < 2000000; ++i) {
        // Thực hiện một số công việc bất kỳ
    }

    // Lưu thời điểm kết thúc
    clock_t end_time = clock();

    // Tính thời gian chạy bằng miligiây
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Thoi gian chay cua chuong trinh: %f giay\n", time_taken);
    return 0;
}
```

📝 Khi chưa register ```Thoi gian chay cua chuong trinh: 0.005 giay```

📝 Khi có register ```Thoi gian chay cua chuong trinh: 0.001 giay```

📝 ``` register ``` chỉ sử dụng cho các biến khai báo cục bộ:

- Biến toàn cục thường tồn tại trong suốt vòng đời của chương trình, yêu cầu lưu trữ lâu dài trong RAM hoặc ROM. Thanh ghi chỉ lưu giá trị tạm thời trong thời gian xử lý (thường bị ghi đè khi thực hiện các tác vụ khác). Điều này không phù hợp với đặc điểm của biến toàn cục.
- Số lượng thanh ghi của CPU thường ít (vài chục trên hầu hết kiến trúc) nên nếu một thanh ghi bị chiếm dụng cho một biến toàn cục thì sẽ ảnh hưởng tới hiệu suất chương trình.
- Biến khai báo ``` register ``` không thể lấy địa chỉ nên việc thao tác khó khăn hơn.

</p>
</details>

</p>
</details>

<br>

<details><summary><b>7. goto - thư viện setjmp</b></summary>
<p>

<details><summary><b>7.1. goto</b></summary>
<p>

<details><summary><b>📚 Khái niệm</b></summary>
<p>

Trong ngôn ngữ C/C++, từ khóa goto được sử dụng để nhảy đến một nhãn (label) được định nghĩa trong cùng một phạm vi (scope) của hàm. Mặc dù goto cung cấp khả năng kiểm soát luồng hoạt động của mã nguồn, nhưng việc sử dụng goto thường được xem là không tốt vì nó có thể làm cho mã nguồn trở nên khó đọc và khó bảo trì.

💻 **Ví dụ 1:**
```cpp
int main()
{
    int i=0;
    
    // đặt label start
    start:
        if (i >= 5) goto end;       // chuyển control đến lable "end"
        printf("%d\n",i);
        i++;
        goto start;

    // đặt label end
    end:
        printf("The end\n");// chuyển control đến label "start"
    return 0;
}
```
📝 Trong ví dụ này, goto được sử dụng để tạo một vòng lặp đơn giản. Khi i đạt đến giá trị 5, control sẽ chuyển đến nhãn "end" và kết thúc chương trình.

<br>

💻 **Ví dụ 2: quét LED trên ma trận LED 8x8**

- Nguyên lý:

	+ Mỗi lần chỉ kích hoạt một hàng (hoặc cột) và điều khiển trạng thái của các cột (hoặc hàng) tương ứng.
 	+ Lặp lại việc quét các hàng/cột với tốc độ cao để tạo hiệu ứng tất cả LED sáng đồng thời.

- Source Code: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/goto


<br>

</p>
</details>

<details><summary><b>📚 Ứng dụng</b></summary>
<p>

**Thoát khỏi vòng lặp nhiều cấp độ**

Trong một số trường hợp, việc thoát khỏi nhiều cấp độ vòng lặp có thể trở nên phức tạp nếu sử dụng cấu trúc kiểm soát vòng lặp thông thường. Trong tình huống như vậy, goto có thể được sử dụng để dễ dàng thoát khỏi nhiều cấp độ vòng lặp.

💻
```cpp
#include <stdio.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        for (int i=0; i<5; i++)
        {
            for (int j=0; j<5; j++)
            {
                if (i == 3 && j == 3)
                {
                    goto exit_program;
                }
                else 
                {
                    printf("i=%d  j=%d\n", i, j);
                }
            }
        }
    }

    exit_program:
        printf("Stop program\n");

    return 0;
}
```

**Xử lý lỗi và giải phóng bộ nhớ**

Trong trường hợp xử lý lỗi, có thể sử dụng goto để dễ dàng giải phóng bộ nhớ đã được cấp phát trước khi thoát khỏi hàm.

💻
```cpp
void process_data()
{
    int *data = malloc(sizeof(int) * 100);

    if (data == NULL)
    {
        goto cleanup;
    }

    // Xử lý dữ liệu ở đây

cleanup:
    free(data);
}
```

**Điều hướng Menu - Thực hiện State Machine**
Trong một số trường hợp, đặc biệt là khi triển khai Menu và State Machines, goto có thể được sử dụng để chuyển đến các trạng thái khác nhau một cách dễ dàng.

💻
```cpp
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int choice = 0;
    int condition = 1;

    main_menu:
    do
    {
        printf("---Main Menu---\n");
        printf("1. Task 1\n");
        printf("2. Task 2\n");
        printf("3. Sub Menu\n");
        printf("0. Exit\n");

        
        printf("Enter your choice: ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > 3);

    printf("\n");

    switch (choice)
    {
        case 1:
            if (condition == 1) goto STATE_2;

        case 2:
            STATE_2:
            printf("This is task 2\n\n");
            break;
        
        case 3:
            goto sub_menu;

        case 0:
            goto exit_program;

        default:
            break;
    }

    sub_menu:
    do
    {
        printf("---Sub Menu---\n");
        printf("1. task A\n");
        printf("2. task B\n");
        printf("0. Back to Main Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > 2);
        
        printf("\n");

        switch (choice)
        {
            case 1:
                printf("Task A is done\n");
                break;

            case 2:
                printf("Task B is done\n");
                break;

            case 0:
                goto main_menu;

            default:
                break;
        }

    exit_program:
        printf("Exiting program.\n");

    return 0;
}
```

<br>

</p>
</details>

</p>
</details>

<details><summary><b>7.2. Thư viện setjmp</b></summary>
<p>

<details><summary><b>📚 Kiểu dữ liệu jmp_buf </b></summary>
<p>

- ``` jmp_buf ``` là một kiểu dữ liệu đặc biệt được định nghĩa trong thư viện chuẩn ``` setjmp.h ```, được sử dụng để lư trữ các dữ liệu liên quan đến trạng thái thực thi của chương trình tại thời điểm gọi hàm ``` setjmp ```, bao gồm:

	+ Program Counter (PC): một thanh ghi đặc biệt trong bộ xử lý chứa địa chỉ bộ nhớ (vị trí) của lệnh chương trình tiếp theo cần thực thi.
 	+ Thanh ghi ngăn xếp (Main Stack Pointer).
  	+ Các thanh ghi khác của CPU.
  	+ Một số trạng thái khác của hệ thống phụ thuộc vào kiến trúc bộ xử lý và hệ điều hành.

- Cách định nghĩa jmp_buf phụ thuộc vào hệ thống và trình biên dịch.

```cpp
typedef struct
{
    unsigned long regs[5]; // Lưu các thanh ghi cần thiết
    void *stack_ptr;       // Con trỏ stack
    void *program_counter; // Con trỏ chương trình
} jmp_buf;

```

</p>
</details>

<details><summary><b>📚 Hàm setjmp</b></summary>
<p>

- ``` setjmp ``` lưu trạng thái hiện tại của chương trình (bao gồm Program Counter - PC, Main Stack Pointer - thanh ghi ngăn xếp và một số thanh ghi khác của CPU) vào một biến kiểu ``` jmp_buf ```.
- ``` setjmp ``` thường được sử dụng để thiết lập một điểm quay lui (checkpoint) trong chương trình.
- ``` setjmp ``` trả về giá trị 0 khi được gọi lần đầu tiên và giá trị khác 0 khi quay lại từ longjmp.
- Cú pháp: ``` int setjmp(jmp_buf env) ```

	+ ``` env ```: biến kiểu ``` jmp_buf ``` dùng để lưu trạng thái.

	+ **Giá trị trả về:**

		+ Trả về ``` 0 ``` ở lần gọi hàm ``` setjmp ``` đầu tiên.
 
  		+ Trả về giá trị ``` khác 0 ``` nếu trạng thái được phục hồi thông qua ``` longjmp ```.

</p>
</details>

<details><summary><b>📚 Hàm longjmp</b></summary>
<p>

- ``` longjmp ``` là hàm dùng để nhảy trở lại vị trí đã lưu bởi setjmp và tiếp tục thực thi chương trình từ đó.
- Khi nhảy trở lại, hàm ``` setjmp ``` sẽ trả về một giá trị khác 0 để báo rằng trạng thái đã được khôi phục.
- Cú pháp: ``` void longjmp(jmp_buf env, int value) ```

	+ ``` env ```: biến kiểu ``` jmp_buf ``` chứa trạng thái trước đó.

 	+ ``` value ```: giá trị trả về từ ``` setjmp ```. Nếu ``` value = 0 ``` thì ``` setjmp ``` trả về 1.

💻 **Ví dụ 1:**
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

double thuong(int a, int b)
{
	if (!b)
	{
		longjmp(buf,1);
	}
	return a/(double)b;
}

int checkArray(int *arr, int size)
{
    	if (size <= 0)
	{
        	longjmp(buf,2);
	}
    	return 1;
}

int main(int argc, char const *argv[]){
	// khi bắt đầu thì setjmp(buf) luôn bằng 0

	if ((exception_code = setjmp(buf)) == 0)
	{
		int array[0];
		double ketqua = thuong(8,0);
		printf("Ket qua: %0.3f\n", ketqua);
		checkArray(array,0);
	}
	else if (exception_code == 1)
	{
		printf("ERROR! Mau bang 0\n");
	}
	else if (exception_code == 2)
	{
		printf("ERROR! Array bang 0\n");
	}
	return 0;
}
```
<br>

💻 **Ví dụ 2:**
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int exception_code;

double divide(int a, int b)
{
    if (a == 0 && b == 0)
    {
        longjmp(buf, 1);
    } 
    else if (b == 0)
    {
        longjmp(buf, 2);
    }

    return (double)a/b;
}

int main(int argc, char const *argv[])
{
    if ((exception_code = setjmp(buf)) == 0)
    {
		printf("Ket qua: %0.3f\n", divide(0,0));
    }
	else if (exception_code == 1)
    {
		printf("ERROR! Không tồn tại\n");
    }
	else if (exception_code == 2)
    {
		printf("ERROR! Chia cho 0\n");
    }

    // thêm code ở đây
    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>📚 Xử lý ngoại lệ</b></summary>
<p>

Cả hai hàm setjmp và longjmp thường được sử dụng để thực hiện xử lý ngoại lệ trong C thông qua 3 keywords chính là: **try, catch, throw**.

```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == x)
#define THROW(x) longjmp(buf,x)
```

💻**Ví dụ**
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int exception_code;

typedef enum
{   
    NO_ERROR,
    NO_EXIT,
    DIVIDE_BY_0
} ErrorCodes;

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == x)
#define THROW(x) longjmp(buf, x)

double divide(int a, int b)
{
    if (a == 0 && b == 0)
    {
        THROW(NO_EXIT);
    } 
    else if (b == 0)
    {
        THROW(DIVIDE_BY_0);
    }

    return (double)a/b;
}

int main(int argc, char const *argv[])
{
    int a,b;

    do
    {
        printf("Nhập a: "); scanf("%d", &a);
        printf("Nhập b: "); scanf("%d", &b);

        exception_code = NO_ERROR;

        TRY
        {
            printf("Kết quả: %0.3f\n", divide(a,b));
        }
        CATCH(NO_EXIT)
        {
            printf("ERROR! Không tồn tại\n");
        }
        CATCH(DIVIDE_BY_0)
        {
            printf("ERROR! Chia cho 0\n");
        }
    } while (1);
    

    // thêm code ở đây

    /*
     * Sự khác biệt giữa setjmp và assert?
     *      assert: dừng hẳn chương trình khi phát hiện lỗi
     *      setjmp: đưa ra lỗi rồi tiếp tục thực thi
     */
    return 0;
}
```

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>8. Bitmask</b></summary>
<p>

<details><summary><b>8.1. Khái niệm</b></summary>
<p>

- Bitmask, hay còn gọi là mặt nạ bit, là một kỹ thuật phổ biến trong lập trình được sử dụng để thao tác trên các bit riêng lẻ trong một giá trị nhị phân.
- Bitmask cho phép bạn kiểm tra, đặt, hoặc xóa các bit cụ thể trong một số mà không ảnh hưởng đến các bit khác. Bitmask được dùng nhiều trong các ứng dụng yêu cầu xử lý dữ liệu cấp thấp hoặc tối ưu hóa bộ nhớ..
- Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.

<br>

</p>
</details>

<details><summary><b>8.2. Các toán tử bitwise</b></summary>
<p>

Bitmask là một số nhị phân được sử dụng kết hợp với các phép toán bit như **AND (&), OR (|), XOR (^), NOT (~), dịch phải (>>) và dịch trái (<<)** để thực hiện các thao tác trên bit.

![image](https://github.com/user-attachments/assets/e9b5fc2e-0d94-4708-bbe1-740f7a21d417)

![image](https://github.com/user-attachments/assets/c8549e26-9a0b-4835-a886-d11a6bed9fb1)

<br>

```cpp
#include <stdio.h>
#include <stdint.h>

/*
 * int8_t, uint8_t       : 1 byte = 8 bit
 * int16_t, uint16_t     : 2 byte = 16 bit
 * int, int32_t, uint32_t: 4 byte = 32 bit
 */

int main(int argc, char const *argv[])
{
    uint8_t user1 = 0b00001110;
    uint8_t user2 = 0b10101001;

    printf("not user1: %d\n", (uint8_t)~user1);              // ~0b00001110 = 0b11110001 --> 241

    printf("not user2: %d\n", (uint8_t)~user2);              // ~0b10101001 = 0b01010110 --> 86

    printf("user1 | user2: %d\n", user1 | user2);   	     // 0b00001110 | 0b10101001 = 0b10101111 --> 175

    printf("user1 & user2: %d\n", user1 & user2);   	     // 0b00001110 & 0b10101001 = 0b00001000 --> 8

    printf("user1 ^ user2: %d\n", user1 ^ user2);            // 0b00001110 ^ 0b10101001 = 0b10100111 --> 167

    printf("user1 << 6: %d\n", (uint8_t)(user1 << 6));       // 0b00001110 << 6 = 0b10000000 --> 128

    printf("user2 >> 3: %d\n", (uint8_t)(user2 >> 3));       // 0b10101001 >> 3 = 0b00010101 --> 21
    
    return 0;
}
```

📝 Khi thực hiện các phép tính với các toán tử bitwise, nếu thực hiện trực tiếp (kết quả không lưu trong biến trung gian) thì compiler sẽ tự động chuyển thành dạng 32-bit

📝 ~user1 = ~(0b 00000000 00000000 00000000 00001110) = 0b 11111111 11111111 11111111 11110001 = 0xFFFFFFF1 (32-bit có dấu) nên nếu không ép kiểu về uint8_t thì kết quả sẽ là -15.

📝 user1 << 6 = (0b 00000000 00000000 00000000 00001110) << 6 = 0b 00000000 00000000 00000011 10000000 (896). Khi ép kiểu về uint8_t thì chỉ đọc 8-bit thấp nhất nên kết quả sẽ là 128.

</p>
</details>

<details><summary><b>8.3. Các phép toán phổ biến với bitwise</b></summary>
<p>

<details><summary><b>📚 Kiểm tra bit (bit checking)</b></summary>
<p>

- Sử dụng phép AND để kiểm tra xem một bit cụ thể có đang được bật hay không.

💻 Ví dụ 1:
```cpp
int num  = 0b1010; // Số nhị phân: 1010
int mask = 0b0010; // Mặt nạ để kiểm tra bit thứ 2

if (num & mask){
    printf("Bit thứ 2 đang bật\n");
} else {
    printf("Bit thứ 2 đang tắt\n");
}
```

💻 Ví dụ 2:
```cpp
uint8_t num  = 0b11011010;
uint8_t mask = 0b00001100; // Mặt nạ để kiểm tra bit thứ 2 và 3

if (num & mask){
    printf("Ít nhất một trong hai bit thứ 2 và 3 được bật\n");
} else {
    printf("Cả hai bit thứ 2 và 3 đều tắt\n");
}
```

<br>

</p>
</details>

<details><summary><b>📚 Bật một bit (bit setting)</b></summary>
<p>

- Sử dụng phép OR để bật một bit cụ thể.

💻 Ví dụ:
```cpp
int num  = 0b1001; // Số nhị phân: 1001
int mask = 0b0100; // Mặt nạ để bật bit thứ 3

num = num | mask;  // num bây giờ là 1101
```

<br>

</p>
</details>

<details><summary><b>📚 Tắt một bit (bit clearing)</b></summary>
<p>

- Sử dụng phép AND với phép NOT để tắt một bit cụ thể.

💻 Ví dụ:
```cpp
int num  = 0b1011; // Số nhị phân: 1011
int mask = 0b1101; // Mặt nạ để tắt bit thứ 2 (NOT(0010) = 1101)

num = num & mask;  // num bây giờ là 1001
```

<br>

</p>
</details>

<details><summary><b>📚 Đảo một bit (bit toggling)</b></summary>
<p>

- Sử dụng phép XOR để đảo một bit cụ thể.

💻 Ví dụ:
```cpp
int num = 0b1010; // Số nhị phân: 1010
int mask = 0b0010; // Mặt nạ để đảo bit thứ 2

num = num ^ mask; // num bây giờ là 1000
```

<br>

</p>
</details>

<details><summary><b>📚 Một số ví dụ</b></summary>
<p>

💻 **Ví dụ 1**:
```cpp
#include <stdio.h>
#include <stdint.h>
                                          //    0    1
#define GENDER    1 << 0  // bit 0: giới tính  nữ   nam     0b00000001
#define SHIRT     1 << 1  // bit 1: áo thun   không  có     0b00000010
#define HAT       1 << 2  // bit 2: nón       không  có     0b00000100
#define SHOES     1 << 3  // bit 3: giày      không  có     0b00001000
#define FEATURE1  1 << 4  // bit 4: tính năng 1             0b00010000
#define FEATURE2  1 << 5  // bit 5: tính năng 2             0b00100000
#define FEATURE3  1 << 6  // bit 6: tính năng 3             0b01000000
#define FEATURE4  1 << 7  // bit 7: tính năng 4             0b10000000

// enable bit
void enableFeature(uint8_t *options, uint8_t feature)
{
    *options = *options | feature;
}

// disable bit
void disableFeature(uint8_t *options, uint8_t feature)
{
    *options = *options & ~feature;
}

// check bit
int8_t isFeatureEnabled(uint8_t options, uint8_t feature)
{
    return ((options & feature) != 0);
}

// liệt kê các tính năng đang bật
void listSelectedFeatures(uint8_t options)
{
    printf("Selected Features: \n");

    const char* featureName[] =
    {
        "Gender",
        "Shirt",
        "Hat",
        "Shoes",
        "Feature 1",
        "Feature 2",
        "Feature 3",
        "Feature 4"
    };

    for (int i=0; i<8; i++)
    {
        if ((options >> i) & 1)
        {
            printf("%s\n", featureName[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
    uint8_t options = 0; // 0xb6: 0b00000000

    // Thêm tính năng
    enableFeature(&options, GENDER | HAT | SHOES);

    // Loại bỏ tính năng
    disableFeature(&options, HAT);

    // Liệt kệ các tính năng đã chọn
    listSelectedFeatures(options);
    
    return 0;
}
```

<br>

💻 **Ví dụ 2**:
```cpp
/***************************************************************************
 * @file    car_configuration.c
 * @brief   Cấu hình các tùy chọn của xe hơi.
 * @details Chương trình cung cấp các cấu trúc và hàm để cấu hình màu sắc, 
 *          công suất, loại động cơ và các tùy chọn bổ sung của xe hơi.
 * @version 1.0
 * @date    2024-10-12
 * @author  Anh Nguyen
 ***************************************************************************/

#include <stdio.h>
#include <stdint.h>

/**
 * @brief   Định nghĩa mã màu xe.
 */
#define COLOR_RED     0  /**< Màu đỏ    */
#define COLOR_BLUE    1  /**< Màu xanh  */
#define COLOR_BLACK   2  /**< Màu đen   */
#define COLOR_WHITE   3  /**< Màu trắng */

/**
 * @brief   Định nghĩa mã công suất động cơ xe.
 */
#define POWER_100HP   0  /**< Công suất 100HP */
#define POWER_150HP   1  /**< Công suất 150HP */
#define POWER_200HP   2  /**< Công suất 200HP */

/**
 * @brief   Định nghĩa mã loại động cơ xe.
 */
#define ENGINE_1_5L   0  /**< Động cơ 1.5L */
#define ENGINE_2_0L   1  /**< Động cơ 2.0L */

/**
 * @brief   Định nghĩa kiểu dữ liệu cho các thuộc tính xe.
 */
typedef uint8_t CarColor;   /**< Kiểu dữ liệu cho màu xe          */
typedef uint8_t CarPower;   /**< Kiểu dữ liệu cho công suất xe    */
typedef uint8_t CarEngine;  /**< Kiểu dữ liệu cho loại động cơ xe */

/**
 * @brief   Định nghĩa các bit mask cho các tùy chọn bổ sung của xe.
 */
#define SUNROOF_MASK         (1 << 0)  /**< Tùy chọn cửa sổ trời               */
#define PREMIUM_AUDIO_MASK   (1 << 1)  /**< Tùy chọn hệ thống âm thanh cao cấp */
#define SPORTS_PACKAGE_MASK  (1 << 2)  /**< Tùy chọn gói thể thao              */

/**
 * @brief   Cấu trúc dữ liệu chứa các tùy chọn xe.
 * @details Sử dụng bit-field để tối ưu hóa bộ nhớ.
 */
typedef struct
{
    CarColor  color  : 2;           /**< 2-bit cho màu sắc              */
    CarPower  power  : 2;           /**< 2-bit cho công suất            */
    CarEngine engine : 1;           /**< 1-bit cho loại động cơ         */
    uint8_t additionalOptions : 3;  /**< 3-bit cho các tùy chọn bổ sung */
} CarOptions;

/**
 * @brief   Cấu hình các thông số cơ bản của xe.
 * @details Gán màu sắc, công suất, loại động cơ và tùy chọn bổ sung cho xe.
 * @param   car     Con trỏ đến cấu trúc `CarOptions`.
 * @param   color   Màu xe.
 * @param   power   Công suất xe.
 * @param   engine  Loại động cơ.
 * @param   options Tùy chọn bổ sung (dưới dạng bit mask).
 * @return  void
 */
void configureCar(CarOptions *car, CarColor color, CarPower power, CarEngine engine, uint8_t options)
{
    car->color  = color;
    car->power  = power;
    car->engine = engine;
    car->additionalOptions = options;
}

/**
 * @brief   Bật một tùy chọn bổ sung trên xe.
 * @details Thiết lập bit mask tương ứng để bật tùy chọn.
 * @param   car         Con trỏ đến cấu trúc `CarOptions`.
 * @param   optionMask  Tùy chọn cần bật (bit mask).
 * @return  void
 */
void setOption(CarOptions *car, uint8_t optionMask)
{
    car->additionalOptions |= optionMask;
}

/**
 * @brief   Tắt một tùy chọn bổ sung trên xe.
 * @details Xóa bit mask tương ứng để tắt tùy chọn.
 * @param   car         Con trỏ đến cấu trúc `CarOptions`.
 * @param   optionMask  Tùy chọn cần tắt (bit mask).
 * @return  void
 */
void resetOption(CarOptions *car, uint8_t optionMask)
{
    car->additionalOptions &= ~optionMask;
}

/**
 * @brief   Hiển thị cấu hình của xe.
 * @details In ra thông tin về màu sắc, công suất, động cơ, và các tùy chọn bổ sung.
 * @param   car   Cấu trúc `CarOptions` chứa thông tin xe.
 * @return  void
 */
void displayCarOptions(const CarOptions car)
{
    const char *colors[]  = {"Red", "Blue", "Black", "White"};
    const char *powers[]  = {"100HP", "150HP", "200HP"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("Car Configuration: \n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUNROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
    printf("\n");
}

/**
 * @brief   Chương trình chính.
 * @details Tạo một cấu hình xe, thiết lập tùy chọn, hiển thị thông tin,
 *          sau đó tắt một tùy chọn và hiển thị lại.
 * @return  int     Trả về 0 nếu chương trình chạy thành công.
 */
int main()
{
    CarOptions myCar;

    /**
     * @brief   Cấu hình các thông số của xe.
     * @details Màu: Đen, Công suất: 150HP, Động cơ: 2.0L, Không có tùy chọn bổ sung.
     */
    configureCar(&myCar, COLOR_BLACK, POWER_150HP, ENGINE_2_0L, 0); 

    /**
     * @brief   Thêm các tùy chọn bổ sung cho xe.
     * @details Bật cửa sổ trời và hệ thống âm thanh cao cấp.
     */
    setOption(&myCar, SUNROOF_MASK);
    setOption(&myCar, PREMIUM_AUDIO_MASK);

    /**
     * @brief   Hiển thị thông tin cấu hình xe.
     */
    displayCarOptions(myCar);

    /**
     * @brief   Xóa một tùy chọn bổ sung.
     * @details Tắt hệ thống âm thanh cao cấp.
     */
    resetOption(&myCar, PREMIUM_AUDIO_MASK); 

    /**
     * @brief   Hiển thị thông tin cấu hình xe sau khi cập nhật.
     */
    displayCarOptions(myCar);

    return 0;
}
```

<br>

</p>
</details>

</p>
</details>

<details><summary><b>8.4. Ứng dụng</b></summary>
<p>

📚 **Quản lý cờ trạng thái (Status Flags)**: 

- Trong các hệ thống nhúng, việc theo dõi trạng thái của các thiết bị hoặc các module khác nhau là rất phổ biến. Bitmask cho phép lưu trữ nhiều cờ trạng thái trong một biến duy nhất, giúp tiết kiệm bộ nhớ và dễ dàng kiểm tra hoặc cập nhật trạng thái đó.

💻 Ví dụ:
```cpp
uint8_t status_flags = 0x00; // Biến lưu trữ cờ trạng thái

// Đặt bit thứ 2 để báo hiệu thiết bị đang hoạt động
status_flags |= (1 << 2);

// Kiểm tra xem bit thứ 2 có được đặt không
if (status_flags & (1 << 2))
{
    // Thiết bị đang hoạt động
}

// Xóa bit thứ 2 để báo hiệu thiết bị ngừng hoạt động
status_flags &= ~(1 << 2);
```

<br>

📚 **Quản lý I/O (Input/Output) Ports**: 

- Trong các hệ thống nhúng, bitmask được sử dụng để thiết lập hoặc đọc các chân I/O của vi điều khiển một cách hiệu quả.

💻 Ví dụ: Đặt một chân I/O thành mức cao mà không ảnh hưởng đến các chân khác:
``` PORTA |= (1 << 3); // Đặt chân PA3 lên mức cao ```

💻 Ví dụ: Xóa (đưa về mức thấp) một chân I/O:
``` PORTA &= ~(1 << 3); // Đưa chân PA3 về mức thấp ```

<br>

📚 **Đọc và Ghi các Thanh ghi (Registers)**: 

- Bitmask giúp thao tác trực tiếp với các thanh ghi của vi điều khiển một cách dễ dàng, cho phép cấu hình và điều khiển các phần cứng ngoại vi như bộ định thời (timers), UART, ADC, v.v.

💻 Ví dụ: Cấu hình bit điều khiển trong một thanh ghi:
``` TCCR0 |= (1 << CS01); // Đặt bit CS01 để chọn bộ chia tần số cho bộ định thời ```

</p>
</details>

</p>
</details>

<br>

<details><summary><b>9. Struct - Union</b></summary>
<p>

<details><summary><b>9.1. Struct</b></summary>
<p>

<details><summary><b>📚 Cơ bản về Struct</b></summary>
<p>
	
- struct là một cấu trúc dữ liệu cho phép tự định nghĩa một kiểu dữ liệu mới bằng cách nhóm các biến có các kiểu dữ liệu khác nhau lại với nhau.
- struct cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên (members) của nó.
- Cú pháp:

**Cách 1: Khai báo tường minh**
```cpp
struct structureName{       struct student_t{       struct student_t sv1;
    dataType1 member1;          char ten[30];       struct student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           hoặc
};                          };                      struct student_t sv[50];
```

**Cách 2: Khai báo không tường minh**
```cpp
typedef struct{             typedef struct{         student_t sv1;
    dataType1 member1;          char ten[30];       student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           student_t sv[20];
}structureName;             }student_t;
```

- Địa chỉ của struct chính là địa chỉ của member đầu tiên.

- Truy xuất dữ liệu:

	+ Sử dụng "." để truy xuất tới thành viên khi khai báo biến bình thường (int, char,…).

	+ Sử dụng "->" để truy xuất tới thành viên khi khai báo biến là con trỏ.

<br>

</p>
</details>

<details><summary><b>📚 Data Structure Alignment</b></summary>
<p>

Data alignment là quá trình sắp xếp các member của một struct sao cho mỗi member nằm ở địa chỉ phù hợp với yêu cầu căn chỉnh của nó. Điều này giúp CPU truy xuất dữ liệu nhanh hơn và tránh các lỗi tiềm ẩn khi truy cập bộ nhớ.

Bộ xử lý thường yêu cầu các thành phần dữ liệu nằm trên địa chỉ được căn chỉnh theo bội số của kích thước phần tử đó. Ví dụ:

- double (8 byte): thường yêu cầu được căn chỉnh trên địa chỉ chia hết cho 8 (0x00, 0x08, 0x10,...)
- int, int32_t, uint32_t (4 byte): thường yêu cầu được căn chỉnh trên địa chỉ chia hết cho 4 (0x00, 0x04, 0x08,...).
- float, uint16_t (2 byte): thường yêu cầu được căn chỉnh trên địa chỉ chia hết cho 2 (0x00, 0x02, 0x04,...).
- char, uint8_t (1 byte): không yêu cầu căn chỉnh đặc biệt

<br>

</p>
</details>

<details><summary><b>📚 Data Padding</b></summary>
<p>

Padding là các byte trống, không chứa dữ liệu và được thêm vào giữa các thành viên của cấu trúc để đảm bảo sự căn chỉnh bộ nhớ (alignment) phù hợp với kiến trúc phần cứng. Việc này giúp CPU truy cập dữ liệu nhanh hơn, nhưng cũng làm tăng kích thước tổng thể của cấu trúc.

<br>

</p>
</details>

<details><summary><b>📚 Kích thước của struct</b></summary>
<p>

**Kích thước Struct bằng tổng các kích thước của các member và padding (nếu có).**

💻 Ví dụ 1:
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint32_t var1;  // 4 byte
    uint8_t  var2;  // 1 byte
    uint16_t var3;  // 2 byte
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame));

    frame frame;
    printf("Address of var1: %p\n", &frame.var1);
    printf("Address of var2: %p\n", &frame.var2);
    printf("Address of var3: %p\n", &frame.var3);
    return 0;
}
```

**Kết quả:**
```cpp
Size of frame: 8
Address of var1: 00000048F3DFF6D8
Address of var2: 00000048F3DFF6DC
Address of var3: 00000048F3DFF6DE
```

**Giải thích:**

![image](https://github.com/user-attachments/assets/0f6e0cdf-c716-41f1-a3db-fa700344513b)

📝 Compiler sẽ cấp phát địa chỉ , mỗi lần cấp phát bao nhiêu byte sẽ tùy thuộc vào kiểu dữ liệu nào có kích thước lớn nhất.

📝 Lần 1: compiler cấp phát 4 bytes địa chỉ và ``` var1 ``` sử dụng.

📝 Lần 2: compiler cấp phát 4 bytes, ``` var2 ``` chỉ sử dụng 1 byte, thừa 3 bytes.	

📝 ``` var3 ``` sử dụng 2 bytes (dựa vào căn chỉnh) trong 3 bytes trên và còn thừa 1 byte và byte này sẽ trở thành padding.

📝 Tổng kích thước struct frame trên là 8 bytes nhưng thực tế chỉ sử dụng 7 bytes.

<br>

💻 Ví dụ 2:
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t  var1;  // 1 byte
    uint32_t var2;  // 4 byte
    uint16_t var3;  // 2 byte
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame));

    frame frame;
    printf("Address of var1: %p\n", &frame.var1);
    printf("Address of var2: %p\n", &frame.var2);
    printf("Address of var3: %p\n", &frame.var3);
    return 0;
}
```

**Kết quả:**
```cpp
Size of frame: 8
Address of var1: 00000048F3DFF6D8
Address of var2: 00000048F3DFF6DC
Address of var3: 00000048F3DFF6DE
```

**Giải thích:**

![image](https://github.com/user-attachments/assets/0b61bf95-9f0a-406c-8ad5-0263c7f55ad8)

📝 Lần 1: compiler cấp phát 4 bytes và var1 sử dụng 1 byte trong 4 byte, thừa 3 byte và 3 bytes này không đủ để lưu trữ ``` var2 ``` nên compiler sẽ tiếp tục cấp phát 4 bytes và 3 bytes còn thừa sẽ trở thành 3 byte padding.

📝 Lần 2: compiler cấp phát 4 bytes, var2 sử dụng hết.

📝 Lần 3: compiler cấp phát 4 bytes, var3 sử dụng 2 trong 4 bytes và thừa 2 byte.

📝 Tổng kích thước struct frame trên là 12 bytes nhưng thực tế chỉ sử dụng 7 bytes.

<br>

💻 Ví dụ 3:
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t  var1[9];   // 1 byte
    uint32_t var2[2];   // 4 byte
    uint16_t var3[10];  // 2 byte
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame)); 
    return 0;
}
```

**Kết quả:**
```cpp
Size of frame: 40
```

**Giải thích:**

![image](https://github.com/user-attachments/assets/af1f44b2-c870-4fd1-a125-7b76f0ffcbb7)

<br>

💻 Ví dụ 4:
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t  var1[9];   // 1 byte   8 + 1 + 7 padding	  				 = 16 byte
    uint64_t var2[3];   // 8 byte   8*3			  				 = 24 byte
    uint16_t var3[10];  // 2 byte   0123 + 4567 + 89 + 4 padding = 8 + 8 + 4 + 4 padding = 24 byte
    uint32_t var4[2];   // 4 byte   8							 = 8  byte
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame));   
    return 0;
}
```

**Kết quả:** ```72 byte```

<br>

</p>
</details>

</p>
</details>

<details><summary><b>9.2. Union</b></summary>
<p>

<details><summary><b>📚 Cơ bản về Union</b></summary>
<p>

- Union là một cấu trúc dữ liệu giúp kết hợp nhiều kiểu dữ liệu khác nhau vào một cùng một vùng nhớ.
- Mục đích chính của union là tiết kiệm bộ nhớ bằng cách chia sẻ cùng một vùng nhớ cho các thành viên của nó. Điều này có nghĩa là, trong một thời điểm, chỉ một thành viên của union có thể được sử dụng.
- Cú pháp:

**Cách 1**
```cpp
union unionName{       	    union student_t{       union student_t sv1;
    dataType1 member1;          char ten[30];       union student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           hoặc
};                           };                     union student_t sv[50];
```

**Cách 2**
```cpp
typedef union{             typedef union{           student_t sv1;
    dataType1 member1;          char ten[30];       student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           student_t sv[20];
}unionName;                }student_t;
```

<br>

</p>
</details>

<details><summary><b>📚 Kích thước Union</b></summary>
<p>

Kích thước của Union chính là tổng của kích thước của member có kích thước lớn nhất và padding (nếu có).

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union
{	           //  Scope
    uint8_t  var1; //  0 - 255
    uint32_t var2; //  0 - 4294967295
    uint16_t var3; //  0 - 65535
} frame;

int main(int argc, char const *argv[])
{
    frame data;
    printf("Size = %d\n",sizeof(frame));
    return 0;
}
```
Kết quả: ```4 byte```

<br>

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union
{        
    uint8_t  var1[3]; //  3 byte + 1 padding
    uint32_t var2[6]; //  4 byte * 6
    uint16_t var3[9]; //  4 byte (01) + 4 byte (23) + 4 byte (45) + 4 byte (67) + 2 byte (8) + 2 padding
} frame;

int main(int argc, char const *argv[])
{
    frame data;
    printf("Size = %d\n",sizeof(frame));
    return 0;
}
```
**Kết quả:** ```24 byte```

<br>

</p>
</details>

<details><summary><b>📚 Sử dụng vùng nhớ trong Union</b></summary>
<p>

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union{     //  Scope
    uint8_t  var1; //  0 - 255
    uint32_t var2; //  0 - 4294967295
    uint16_t var3; //  0 - 65535
} frame;

int main(int argc, char const *argv[]){
    frame data;
    data.var1 = 5;
    data.var2 = 6;
    data.var3 = 7;

// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//      5
//      6
//      7

    printf("Data.var1 = %d\n", data.var1);
    printf("Data.var2 = %u\n", data.var2);
    printf("Data.var3 = %d\n", data.var3);
    return 0;
}
```
**Kết quả**
```cpp
Data.var1 = 7
Data.var2 = 7
Data.var3 = 7
```

**Giải thích**

📝 Khi gán 5 cho member var1 thì tại địa chỉ 0x5FFE9C sẽ có giá trị 5.

📝 Khi gán 6 cho member var2, do các member sử dụng chung vùng nhớ nên tại địa chỉ 0x5FFE9C thì giá trị 6 sẽ ghi đè lên 5.

📝 Tương tự với member var3, giá trị cuối cùng tại địa chỉ 0x5FFE9C là 7 nên giá trị của các member đều sẽ là 7.

<br>

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union{     //  Scope
    uint8_t  var1; //  0 - 255
    uint32_t var2; //  0 - 4294967295
    uint16_t var3; //  0 - 65535
} frame;

int main(int argc, char const *argv[])
{
    frame data;
    data.var2 = 4294967290;

    printf("Data.var1 = %d\n", data.var1);
    printf("Data.var2 = %u\n", data.var2);
    printf("Data.var3 = %d\n", data.var3);
    return 0;
}
```
**Kết quả:**
```cpp
Data.var1 = 250
Data.var2 = 4294967290
Data.var3 = 65530
```

**Giải thích**

📝 4294967290 = 0b11111111 111111111 11111111 1111010

📝 Do các member dùng chung vùng nhớ nên giá trị các member bằng nhau và kích thước của union frame là 4 byte nên dữ liệu sẽ được như sau:

```cpp
// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//  11111010    11111111    11111111    11111111
```

📝 member var1 có kiểu dữ liệu là uint8_t nên chỉ lấy 8 bit ở địa chỉ 0x005FFE9C -> var1 = 0b11111010 = 250

📝 member var2 có kiểu dữ liệu là uint32_t nên giữ nguyên giá trị

📝 member var3 có kiểu dữ liệu là uint16_t nên chỉ lấy 16 bit ở địa chỉ 0x005FFE9C và 0x005FFE9D -> var3 = 0b11111111 11111010 = 65530

<br>

</p>
</details>

</p>
</details>

<details><summary><b>9.3. So sánh Struct và Union</b></summary>
<p>

<details><summary><b>📚 Giống nhau</b></summary>
<p>
	
- Đều do lập trình viên tự định nghĩa (user defined type).
- Đều sử dụng dấu "." hoặc "->" để truy cập các phần tử (hoặc có thể gọi là thuộc tính).

</p>
</details>

<details><summary><b>📚 Khác nhau</b></summary>
<p>

|           |   Struct  |   Union   |
|-----------|-----------|-----------|
| keyword   | Dùng keyword 'struct' để định nghĩa   | Dùng keyword 'union' để định nghĩa    |
| size      | Tổng các kích thước của các member và padding (nếu có)    | Tổng của kích thước của member có kích thước lớn nhất và padding (nếu có)  |
| Memory    | Mỗi member có vùng nhớ riêng biệt    | Các member dùng chung 1 vùng nhớ    |
| Modify    | Thay đổi giá trị 1 member không ảnh hưởng các member khác   | Thay đổi giá trị bất kỳ member nào cũng ảnh hưởng các member khác    |
| Truy cập  | Truy cập bất kỳ member ở thời điểm nào cũng được    | Trong một lúc chỉ truy cập được một member     |


</p>
</details>

</p>
</details>

<details><summary><b>9.4. Ứng dụng</b></summary>
<p>

<details><summary><b>📚 Ứng dụng Struct</b></summary>
<p>

Các giao thức trong nhúng như UART, I2C, SPI khi sử dụng đều phải cấu hình các thông số; mỗi giao thức sẽ có các thông số cấu hình khác nhau.

💻 UART
```cpp
typedef struct
{
  uint32_t USART_BaudRate;            /* USART communication baud rate */

  uint16_t USART_WordLength;          /* the number of data bits transmitted or received in a frame */

  uint16_t USART_StopBits;            /* Specifies the number of stop bits transmitted */

  uint16_t USART_Parity;              /* Specifies the parity mode */
 
  uint16_t USART_Mode;                /* pecifies wether the Receive or Transmit mode is enabled or disabled */

  uint16_t USART_HardwareFlowControl; /* Specifies wether the hardware flow control mode is enabled or disabled */
} USART_InitTypeDef;
```
	
<br>

</p>
</details>

<details><summary><b>📚 Ứng dụng Union</b></summary>
<p>

- Một chân GPIO_pin tại một thời điểm có thể là input hoặc output.
- Input có thể là đọc giá trị cảm biến từ bên ngoài.
- Output có thể là xuất điện áp ra để điều khiển LED hoặc relay.
- Để cấu hình thì dùng Union

💻 
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union
{
    struct
    {
        uint32_t mode  : 2;  // 00: input, 01: output
        uint32_t pull  : 2;  // 00: no pull, 01: pull-up, 10: pull-down
        uint32_t speed : 2;  // 00: 2MHz, 01: 10MHz, 10: 50MHz
        uint32_t reserved : 26; // các bit khác
    } config;

    uint32_t reg;
} GPIO_Config;

void configure_gpio(GPIO_Config *gpio, uint32_t mode, uint32_t pull, uint32_t speed)
{
    gpio->config.mode  = mode;  // Cấu hình chế độ
    gpio->config.pull  = pull;  // Cấu hình pull-up/pull-down
    gpio->config.speed = speed; // Cấu hình tốc độ
}

int main(int argc, char const *argv[])
{
    GPIO_Config GPIOA;

    // Cấu hình PA0 là output
    configure_gpio(&GPIOA, 1, 0, 2);

    // Sử dụng GPIOA.reg để viết vào thanh ghi GPIO thực tế
    write_gpio_register(GPIOA.reg);
    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>📚 Ứng dụng kết hợp Struct và Union</b></summary>
<p>

- Truyền dữ liệu từ MCUA sang MCUB

```cpp
MCUA							   MCUB

Data:
{
   id;	 	// 2 byte	   Data_Frame
   data; 	// 4 byte	--------------->	   Data
   check_sum; 	// 2 byte				Data_Frame
}

Data_Frame
```

📝 Cách làm thủ công: đưa từng byte vào mảng rồi truyền đi

📝 Ví dụ: id=10, data=1234, checksum=70 thì chuyển thành chuỗi "10", "1234", "70" rồi đưa vào mảng.

```cpp
    id            data      checksum
0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08
 1    0    1    2    3    4    7    0
              mảng frame[8]
```

🤔 Có cách nào tự động convert vào mảng khi có dữ liệu không❓

➡️ Sử dụng Struct + Union

💻
```cpp
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef union
{
    struct
    {
        uint8_t id[2];
        uint8_t data[4];
        uint8_t check_sum[2];
    } data;

    uint8_t frame[8];
} Data_Frame;


int main(int argc, char const *argv[])
{
    Data_Frame transmit_data, receive_data;
    strcpy((char*)transmit_data.data.id, "10");
    strcpy((char*)transmit_data.data.data, "1234");
    strcpy((char*)transmit_data.data.check_sum, "70");
    strcpy((char*)receive_data.frame, (char*)transmit_data.frame);
    return 0;
}
```

📝 Sủ dụng kiểu ``` uint8_t ``` cho các member để không có padding, tránh việc tốn bộ nhớ.

📝 Kích thước của mỗi member trong union đều là 8 byte nên kích thước của union cũng là 8 byte.

📝 Khi có dữ liệu, ví dụ copy các chuỗi "10", "1234", "70" vào ``` id, data, check_sum ``` thì mảng ``` frame ``` cũng tự động cập nhật dư liệu theo.

📝 Khi cần truyền dữ liệu đi, ta chỉ cần sử dụng mảng ``` frame ``` để truyền đi.

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>10. Memory layout (Phân vùng nhớ)</b></summary>
<p>

<details><summary><b>10.1. Text (Code Segment)</b></summary>
<p>

- **Vùng nhớ của địa chỉ thấp nhất**.
- **Chứa mã máy (mã lệnh thực thi chương trình).**
- **Quyền truy cập là chỉ đọc (Read-only).**
- Đối với compiler ``` Clang ``` (compiler trên MacOS) thì phân vùng Text còn lưu trữ hằng số, chuỗi hằng (string literal) và con trỏ kiểu char (khai báo toàn cục).
- Đối với compiler ``` MinGW ``` (gcc/g++ trên Windows) thì hằng số, chuỗi hằng và con trỏ kiểu char sẽ lưu trữ ở phân vùng Data nhưng với quyền truy cập là Read-only.

💻
File **main.c**
```cpp
#include <stdio.h>

char *ptr = "Hello World";

const int a = 10;

int main(int argc, char const *argv[])
{
    printf("a = %d\n", a);

    // a = 20;  / wrong

    ptr[1] = 'a';
    printf("chuoi: %s\n", *ptr);

    *ptr = "Hello";
    printf("chuoi: %s\n", *ptr);

    return 0;
}
```

📝 Compiler gcc

📝 Biến ``` a ``` khi khai báo toàn cục thì được lưu ở phân vùng Read-only Data (rdata) nên khi cố tình thay đổi giá trị của nó sẽ gặp lỗi ``` assignment of read-only variable 'a' ``` (gán biến chỉ đọc 'a'). Ngược lại, biến ``` a ``` khi khai báo cục bộ thì nó sẽ được lưu ở phân vùng Stack và có thể bị thay đổi giá trị thông qua một con trỏ.

📝 con trỏ ptr và chuỗi ``` Hello World ``` được lưu ở phân vùng Data nhưng quyền truy cập của chuỗi là read-only nên khi cố tính thay đổi (``` ptr[1] = 'a' ``` hoặc ``` *ptr = "hello" ```), mặc dù không hiện lỗi cụ thể (do compiler) nhưng khi cố thay đổi giá trị của hằng số thì chương trình tự set một cơ chế bảo vệ và khiến cho chương trình dừng lại ngay sau khi chạy dòng lệnh ``` printf("a = %d\n", a); ```.

<br>

</p>
</details>

<details><summary><b>10.2. Data (Initialized Data)</b></summary>
<p>

- Lưu trữ biến toàn cục và biến static (bao gồm toàn cục và cục bộ) với giá trị khởi tạo khác 0.
- Quyền truy cập: đọc - ghi, nghĩa là có thể đọc giá trị và có thể thay đổi giá trị của biến.
- Tất cả các biến sẽ được thu hồi sau khi kết thúc chương trình.

💻
File **main.c**:
```cpp
#include <stdio.h>

int a = 5;

static int b = 6;

void *ptr = &b;

void test()
{
    static int c = 7;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
```

📝 Biến a là toàn cục nên lưu ở phân vùng Data (.data)

📝 Biến static bao gồm toàn cục (b) và cục bộ (c) cũng sẽ được lưu trữ ở Data

📝 Con trỏ ``` ptr ``` cũng được lưu trữ ở Data và địa chỉ của biến mà nó trỏ tới (biến b) cũng nằm ở Data.

📝 Tất cả các biến a, b, c đều sẽ được cấp phát địa chỉ (giả sử 0x01, 0xb2, 0xf5) và các địa chỉ trên sẽ bị thu hồi khi chương trình kết thúc

📝 Biến a, b, c ptr đều có thể thay đổi trong quá trình thực thi (đọc – ghi).

<br>

</p>
</details>

<details><summary><b>10.3. BSS (Uninitialized Data)</b></summary>
<p>

- Lưu trữ biến toàn cục và biến static (bao gồm toàn cục và cục bộ) mà không khởi tạo giá trị ban đầu hoặc khởi tạo với giá trị khác 0.
- Quyền truy cập: đọc-ghi, nghĩa là có thể đọc giá trị và có thể thay đổi giá trị của biến.
- Tất cả các biến sẽ được thu hồi sau khi kết thúc chương trình.

💻
File **main.c**:
```cpp
#include <stdio.h>

typedef struct
{
    int x;
    int y;
} Point_Data;

Point_Data p1 = {5,7};

Point_Data p2;

int a = 0;
int b = 5;

static int m = 0;
static int n;

void test()
{
    static int c = 0;
    static int d;
}

int main()
{
    printf("a: %d\n", a);
    printf("m: %d\n", m);
    return 0;
}
```

📝 Khi dùng Struct (Union) để định nghĩa một kiểu dữ liệu mới thì những member bên trong sẽ chưa được lưu trên RAM.

📝 Khi khai báo biến thuộc kiểu struct thì khi đó những member thuộc phân vùng nhớ nào sẽ tùy thuộc vào cách khai báo biến.

📝 Ví dụ: biến ``` p1 ``` được khởi tạo với giá trị khác 0 (``` {5,7} ```) nên các member ```x,y ``` và ``` p1 ``` sẽ được lưu trữ ở Data.

📝 Ví dụ: biến ``` p2 ``` không được khởi tạo nên các member ```x,y ``` và ``` p2 ``` sẽ được lưu trữ ở BSS.

📝 Các biến static như m, n, c, d được lưu ở BSS.

📝 Biến toàn cục b lưu ở Data

<br>

</p>
</details>

<details><summary><b>10.4. Stack</b></summary>
<p>

- Lưu trữ biến cục bộ (bao gồm cả biến ``` const ``` nhưng ngoại trừ static cục bộ) và tham số truyền vào của hàm.
- Quyền truy cập: đọc - ghi
- Stack là vùng nhớ được cấp phát tự động và có cấu trúc LIFO (Last In Fisrt Out).
- Vùng nhớ sẽ bị thu hồi khi ra hỏi block code/hàm.

📝 Biến static cục bộ chỉ được khởi tạo một lần duy nhất và giữ nguyên giá trị giữa các lần gọi hàm. Vì vậy, chúng không thể lưu trữ trên ngăn xếp (stack), vì bộ nhớ stack chỉ tồn tại trong thời gian hàm đang thực thi và sẽ được giải phóng khi hàm kết thúc.

<br>

💻
```cpp
#include <stdio.h>

int total(int a, int b)
{
    int c;
    c = a + b;
    return c;
}

int main(int argc, char const *argv[])
{
    printf("a+b=%d\n",total(5,6));
    /*
        0x01: 5
        0x12: 6
        0x06: 11
    */
    printf("a+b=%d\n",total(9,7));
    /*
        0x01: 9
        0x02: 7
        0x08: 16
    */
    return 0;
}
```
📝 Biến a, b là input parameter của hàm nên lưu trữ trong Stack.

📝 Biến c là biến cục bộ nên cũng lưu trữ trong Stack.

📝 Khi chạy lệnh printf() đầu tiên, các biến a, b, c đều được cấp phát địa chỉ (giả sử 0x01 (a=5), 0x12 (b=6) và 0x06 (c)). Những địa chỉ này sẽ được lưu ở phần vùng Stack. Sau khi return kết quả thì địa chỉ của các biến a, b, c sẽ bị thu hồi.

📝 Khi chạy lệnh printf() thứ hai, a=9 và tiếp tục được cấp phát địa chỉ (có thể là 0x01 hoặc khác), tương tự b, c và sau khi return kết quả thì các địa chỉ cũng bi thu hồi.

<br>

</p>
</details>

<details><summary><b>10.5. Heap</b></summary>
<p>

<details><summary><b>📚 Cấp phát động với malloc - calloc - realloc</b></summary>
<p>

💻 Ví dụ 1: malloc
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    uint16_t *ptr = NULL;
    int num_element = 5;
    ptr = (uint16_t*)malloc(sizeof(uint16_t)*num_element);

    ptr[0] = 256; // 0b00000001 00000000

    for (int i=1; i<num_element; i++){
        ptr[i] = 2*i;
    }

    for (int i=0; i<num_element*2; i++){
        printf("dia chi: %p, gia tri: %d\n", (uint8_t*)ptr+i, *((uint8_t*)ptr+i));
    }
    return 0;
}
```

**Kết quả**:
```cpp
dia chi: 0000023164232C90, gia tri: 0
dia chi: 0000023164232C91, gia tri: 1
dia chi: 0000023164232C92, gia tri: 2
dia chi: 0000023164232C93, gia tri: 0
dia chi: 0000023164232C94, gia tri: 4
dia chi: 0000023164232C95, gia tri: 0
dia chi: 0000023164232C96, gia tri: 6
dia chi: 0000023164232C97, gia tri: 0
dia chi: 0000023164232C98, gia tri: 8
dia chi: 0000023164232C99, gia tri: 0
```

📝 ``` malloc(sizeof(uint16_t)*num_element) ```: cấp phát vùng nhớ 2*5=10 byte gồm 10 địa chỉ liền kề nhau (0x01, 0x02, 0x03, 0x04, ..., 0x0A) và mỗi phần tử sẽ chiếm 2 ô địa chỉ (2 byte).

📝 Do giá trị trả về là con trỏ void nên để xác định được giá trị chính xác ở từng địa chỉ thì phải ép kiểu.

📝 ``` (uint8_t*)ptr+i ```: ép kiểu để xem giá trị từng byte địa chỉ

<br>

💻 Ví dụ 2: malloc và realloc
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    uint16_t *ptr = NULL;
    ptr = (uint16_t*)malloc(sizeof(uint16_t)*4);

    for (int i=0; i<4; i++) ptr[i] = 2*i;

    ptr = (uint16_t*)realloc(ptr, sizeof(uint16_t)*8);

    for (int i=0; i<8; i++) ptr[i] = 2*i;

    for (int i=0; i<16; i++)
    {
        printf("dia chi: %p, gia tri: %d\n", (uint8_t*)ptr+i, *((uint8_t*)ptr+i));
    }
    return 0;
}
```

📝 ``` realloc() ```: thay đổi kích thước vùng nhớ đã được cấp phát bởi malloc() từ 8 byte lên 16 byte

<br>

💻 Ví dụ 3: calloc
```cpp
#include <stdio.h>
#include <stdlib.h>

int main()
{   
    int size = 5;
    int *ptr = (int*)calloc(size, sizeof(int));

    // Kiểm tra nếu việc cấp phát thất bại
    if (ptr == NULL)
    {
        printf("Cấp phát bộ nhớ thất bại!\n");
        return 1; // Thoát chương trình
    }

    for (int i=0; i<size; i++)
    {
        printf("arr[%d]: %d\n",i, *(ptr+i));
    }
}
```

**Kết quả:**
```cpp
arr[0]: 0
arr[1]: 0
arr[2]: 0
arr[3]: 0
arr[4]: 0
```

<br>

💻 Ví dụ 4:
```cpp
#include <stdio.h>
#include <stdlib.h>

void test1()
{
    int array[3];
    for (int i = 0; i < 3; i++)
    {
        printf("address of array[%d]: %p\n", i, (array+i));
    }
    printf("----------------------\n");
}

void test2()
{
    int *array = (int*)malloc(3*sizeof(int)); 
    for (int i = 0; i < 3; i++)
    {
        printf("address of array[%d]: %p\n", i, (array+i));
    }
    printf("----------------------\n");
    free(array);
}

int main(int argc, char const *argv[])
{  
    test1();
    test1();
    test2();
    test2();
    return 0;
}
```
**Kết quả:**
```cpp
address of array[0]: 00000000005FFE60
address of array[1]: 00000000005FFE64
address of array[2]: 00000000005FFE68
----------------------
address of array[0]: 00000000005FFE60
address of array[1]: 00000000005FFE64
address of array[2]: 00000000005FFE68
----------------------
address of array[0]: 0000000000656EC0
address of array[1]: 0000000000656EC4
address of array[2]: 0000000000656EC8
----------------------
address of array[0]: 0000000000656EC0
address of array[1]: 0000000000656EC4
address of array[2]: 0000000000656EC8
```

📝 Ở hàm ``` test1() ```, các phần tử trong mảng đều được lưu ở Stack nên khi kết thúc gọi hàm thì địa chỉ tự động thu hồi nên ở lần gọi hàm thứ 2 thì địa chỉ các phần tử vẫn giống ở lần 1.

📝 Ở hàm ``` test2() ```, con trỏ ``` array ``` lưu ở Stack nhưng các địa chỉ mà nó trỏ đến lại lưu ở phân vùng Heap và khi gọi hàm ``` free() ``` thì các địa chỉ đó bị thu hồi nên ở lần gọi hàm thứ 2 thì địa chỉ các phần tử vẫn giống ở lần 1. Tuy nhiên, nếu không thu hồi địa chỉ thì ở lần gọi hàm thứ 2, các địa chỉ chắc chắn sẽ khác so với lần 1.

<table>
  <tr>
    <th></th>
    <th><b>malloc</b></th>
    <th><b>calloc</b></th>
    <th><b>realloc</b></th>
  </tr>
  <tr>
    <td><b>Chức năng</b></td>
    <td>Cấp phát bộ nhớ liên tục với kích thước được chỉ định.</td>
    <td>Cấp phát một khối bộ nhớ liên tục có kích thước bằng số lượng phần tử.</td>
    <td>Thay đổi kích thước vùng nhớ đã được cấp phát bởi malloc () hoặc calloc ().</td>
  </tr>
  <tr>
    <td><b>Khởi tạo giá trị</b></td>
    <td>Không khởi tạo (giá trị rác).</td>
    <td>Khởi tạo toàn bộ vùng nhớ về 0.</td>
    <td>Giữ lại dữ liệu cũ, phần mở rộng không khởi tạo.</td>
  </tr>
  <tr>
    <td><b>Cú pháp</b></td>
    <td>void *malloc(size_t size)</td>
    <td>void *calloc(int n, size_t size)</td>
    <td>void *realloc(void *ptr, size_t new_size)</td>
  </tr>
  <tr>
    <td><b>Tham số truyền vào</b></td>
    <td>Kích thước mong muốn (byte).</td>
    <td>Số lượng phần tử và Kích thước mỗi phần tử (byte).</td>
    <td>Số lượng phần tử và Kích thước mỗi phần tử (byte).</td>
  </tr>
  <tr>
    <td><b>Kết quả trả về</b></td>
    <td>Con trỏ tới bộ nhớ đã cấp phát, hoặc trả về NULL nếu yêu cầu thất bại, khi dùng phải ép kiểu sang kiểu dữ liệu cần dùng.</td>
    <td>Con trỏ tới bộ nhớ đã cấp phát, hoặc trả về NULL nếu yêu cầu thất bại.</td>
    <td>
	    - Nếu con trỏ ptr là NULL, thì một khối mới được cấp phát và một con trỏ tới nó được trả về bởi hàm này.
	    - Nếu kích thước là 0 và con trỏ ptr trỏ tới một khối nhớ đang tồn tại, khối nhớ được trỏ tới bởi ptr được giải phóng và một con trỏ NULL được trả về.
    </td>
  </tr>
  <tr>
    <td><b>Giải phóng bộ nhớ</b></td>
    <td>Dùng hàm free()</td>
    <td>Dùng hàm free()</td>
    <td>Dùng hàm free()</td>
  </tr>
  <tr>
    <td><b>Hiệu suất</b></td>
    <td>Nhanh hơn so với calloc vì không thực hiện khởi tạo</td>
    <td>Chậm hơn malloc do có bước khởi tạo giá trị 0.</td>
    <td>Tùy thuộc vào việc cấp phát mới hoặc mở rộng trực tiếp.</td>
  </tr>
  <tr>
    <td><b>Sử dụng khi nào?</b></td>
    <td>Khi cần hiệu suất cao hơn và có thể tự khởi tạo dữ liệu theo cách riêng.</td>
    <td>Khi cần khởi tạo bộ nhớ với giá trị mặc định là 0 để tránh các lỗi liên quan đến giá trị rác.</td>
    <td>Khi cần thay đổi kích thước vùng nhớ đã cấp phát.</td>
  </tr>
</table>

<br>

</p>
</details>

<details><summary><b>📚 Phân vùng Heap</b></summary>
<p>

- Quyền truy cập là đọc và ghi, nghĩa là có thể thay đổi được giá trị của biến.
- Heap được sử dụng để cấp phát bộ nhớ động (thông qua các lệnh: malloc, calloc, relloc, free, new, delete, …). Điều này cho phép chương trình tạo ra và giải phóng bộ nhớ theo nhu cầu, thích ứng với sự biến đổi của dữ liệu trong quá trình chạy.
- Sẽ được giải phóng khi gọi hàm free.

💻
```cpp
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int *ptr = (int*)malloc(sizeof(int) * 6);
    return 0;
}
```

📝 Con trỏ ptr được lưu trữ ở phân vùng Stack.

📝 Những địa chỉ mà con trỏ ptr trỏ tới (địa chỉ được cấp phát thông qua malloc) được lưu trữ ở phân vùng Heap.

📝 Để thu hồi vùng nhớ thì ngoài việc sử dụng ``` free() ``` thì ta còn có thể sử dụng ``` realloc() ``` và cấp phát giá trị cho các địa chỉ đó bằng 0.

<br>

**Khi nào sử dụng Heap? Khi nào sử dụng Stack?**

**Sử dụng Stack**: Khi bạn biết trước kích thước của dữ liệu và dữ liệu này có vòng đời ngắn, được sử dụng trong phạm vi hàm.

```cpp
void function() {
    int a = 10; // Biến cục bộ "a" được lưu trên stack
    int b[20];  // Mảng tĩnh "b" có kích thước cố định được lưu trên stack
}
```

**Sử dụng Heap**: Khi bạn cần quản lý bộ nhớ với kích thước động và vòng đời của dữ liệu dài, tồn tại ngoài phạm vi của một hàm.

```cpp
void function() {
    int* ptr = (int*)malloc(sizeof(int) * 10); // Cấp phát mảng động trên heap
    // Sử dụng mảng "ptr"
    free(ptr); // Giải phóng bộ nhớ
}
```

<br>

</p>
</details>

</p>
</details>

<details><summary><b>Vì sao cần nắm rõ Memory Layout của một chương trình C/C++?</b></summary>
<p>

Khi bạn nắm được memory layout (bố cục bộ nhớ) của một chương trình C/C++, bạn có thể hiểu rõ cách mà chương trình sử dụng bộ nhớ, điều này mang lại nhiều lợi ích và ứng dụng trong việc tối ưu hóa hiệu suất, bảo mật, và kiểm tra lỗi. Dưới đây là một số điều bạn có thể làm khi hiểu được memory layout của chương trình C/C++:

# 1. Tối ưu hóa bộ nhớ

- **Quản lý bộ nhớ hiệu quả**: Khi biết cách bộ nhớ được phân bổ, bạn có thể tối ưu hóa cách sử dụng bộ nhớ, ví dụ như giảm thiểu lãng phí bộ nhớ trên stack hoặc heap.
- **Điều chỉnh stack và heap**: Nếu bạn nắm được cách stack và heap hoạt động, bạn có thể điều chỉnh kích thước của chúng sao cho phù hợp với nhu cầu của chương trình, tránh việc stack overflow hay heap fragmentation.

# 2. Giảm thiểu lỗi bộ nhớ

- **Tránh lỗi tràn bộ nhớ**: Hiểu rõ cách thức phân bổ bộ nhớ giúp bạn tránh những lỗi phổ biến như buffer overflow hoặc use-after-free (sử dụng bộ nhớ đã giải phóng).
- **Phát hiện và sửa lỗi bộ nhớ**: Ví dụ như lỗi dangling pointers (con trỏ treo), hay memory leaks (rò rỉ bộ nhớ) khi không giải phóng bộ nhớ đã cấp phát.

# 3. Cải thiện hiệu suất

- **Tối ưu hóa truy xuất bộ nhớ**: Việc biết cách dữ liệu được lưu trữ và truy xuất trong bộ nhớ giúp bạn tối ưu hóa cách chương trình tiếp cận dữ liệu, giảm thiểu chi phí liên quan đến cache misses hoặc các truy xuất bộ nhớ không hiệu quả.
- Dự đoán tính toán bộ nhớ: Việc nắm rõ vị trí dữ liệu có thể giúp bạn ước tính hiệu suất bộ nhớ của chương trình khi thực hiện các phép toán tính toán.

# 4. Nâng cao bảo mật

- **Tấn công và phòng thủ chống buffer overflow**: Hiểu rõ layout bộ nhớ giúp bạn phát hiện và ngăn chặn các cuộc tấn công buffer overflow, một lỗ hổng bảo mật phổ biến trong C/C++.
- **Điều khiển Execution Flow**: Biết cách mà bộ nhớ được phân bổ giúp bạn phòng chống các kỹ thuật tấn công như return-oriented programming (ROP), nơi kẻ tấn công thay đổi luồng điều khiển của chương trình thông qua các giá trị trên stack.

# 5. Hiểu cơ chế hoạt động của con trỏ và tham chiếu

- **Xử lý con trỏ hiệu quả**: Bạn sẽ dễ dàng làm việc với các con trỏ, tham chiếu, và các phép toán trên bộ nhớ. Điều này giúp giảm thiểu lỗi khi thao tác với con trỏ.
- **Hiểu về stack và heap**: Nắm vững các vùng bộ nhớ này giúp bạn phân biệt được khi nào cần sử dụng dynamic memory allocation và khi nào chỉ cần sử dụng static allocation.

# 6. Debugging

- **Kiểm tra lỗi bộ nhớ**: Kiến thức về bố cục bộ nhớ giúp bạn dễ dàng nhận diện các lỗi liên quan đến bộ nhớ như segmentation faults, hoặc kiểm tra địa chỉ bộ nhớ khi có sự cố.
- **Chạy debugger hiệu quả hơn**: Khi bạn hiểu cách dữ liệu được phân bổ, bạn có thể dễ dàng sử dụng debugger để theo dõi, phân tích và sửa lỗi trong chương trình.

# 7. Hiểu cách hoạt động của hệ thống

- **Hệ điều hành và hệ thống**: Biết được cách mà bộ nhớ được phân bổ cho chương trình sẽ giúp bạn hiểu cách hệ điều hành quản lý bộ nhớ, từ đó có thể viết các chương trình tương thích hơn với hệ điều hành và phần cứng.
- **Tương tác giữa phần cứng và phần mềm**: Khi hiểu rõ memory layout, bạn có thể tối ưu hóa cách chương trình tương tác với bộ nhớ vật lý và bộ vi xử lý, ví dụ như khi làm việc với các hệ thống nhúng hoặc lập trình hệ thống.

# 8. Phát triển các công cụ và thư viện

- **Phát triển các công cụ kiểm tra bộ nhớ**: Với sự hiểu biết về layout bộ nhớ, bạn có thể phát triển các công cụ như valgrind để phát hiện rò rỉ bộ nhớ hoặc lỗi truy cập bộ nhớ.
- **Tối ưu hóa thư viện**: Nếu bạn đang phát triển các thư viện C/C++, bạn có thể tối ưu hóa cách các thư viện sử dụng bộ nhớ, giúp các ứng dụng sử dụng thư viện của bạn chạy nhanh và ít lỗi bộ nhớ hơn.

<br>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>11. JSON</b></summary>
<p>

<details><summary><b>11.1. Khái niệm</b></summary>
<p>

- JSON (JavaScript Object Notation) là một **định dạng dữ liệu** phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống khác nhau.
- JSON được thiết kế để dễ đọc và dễ viết cho con người, cũng như dễ dàng để phân tích và tạo ra cho máy tính. Nó sử dụng một cú pháp nhẹ dựa trên cặp **key - value**, tương tự như các đối tượng và mảng trong JavaScript. Mỗi đối tượng JSON bao gồm một tập hợp các cặp "key" và "value", trong khi mỗi mảng JSON là một tập hợp các giá trị.

</p>
</details>

<details><summary><b>11.2. Cấu trúc JSON</b></summary>
<p>

JSON bao gồm hai thành phần chính:

1. **Cặp key-value**

- Dữ liệu được tổ chức dưới dạng dạng cặp ``` key: value ```.
- ``` key - value ``` được phân tách bằng dấu hai chấm (:)
- ``` key ``` luôn là chuỗi (string).
- ``` value ``` có thể là **bất kỳ kiểu dữ liệu**:

	+ Chuỗi (string)

 	+ Số (integer, double)
    
	+ Boolean (True/False)

	+ Null (null)

	+ Object (đối tượng)

	+ Array (mảng)

2. **Các phần tử cơ bản**

**Object**:

- Một tập hợp các cặp key – value, được đặt trong dấu ngoặc nhọn ``` { } ```.
- Các cặp key - value trong object được phân tách bằng dấu phẩy (,).

```cpp
{ 
  "name": "Anh",
  "age": 22,
  "city": "HCM",
  "is_student": false,
  "gpa": [9, 9.5, 10]
}
```

```cpp
{
    "person":
    {
        "name": "Anh",
        "age": 25,
        "address":
        {
            "city": "Hanoi",
            "postal_code": "100000"
        }
    }
}
```

<br>

**Array**:

- Là một danh sách các giá trị, được bao quanh bởi dấu ngoặc vuông ``` [] ```, các giá trị được phân tách bằng dấu phẩy.
- Các giá trị trong mảng có thể thuộc bất kỳ kiểu dữ liệu JSON nào, kể cả object hoặc mảng khác.

```cpp
[
  {
    "name": "John Doe",
    "age": 30,
    "city": "New York",
    "occupation": "Software Engineer",
    "isStudent": false
  },
  {
    "name": "Jane Smith",
    "age": null,
    "city": "Los Angeles",
    "contact": {
      "email": "jane.smith@example.com",
      "phone": "555-1234"
    }
  },
  {
    "name": "Bob Johnson",
    "age": 35,
    "city": "Chicago"
  }
]
```

<br>

**Các bước xử lý dữ liệu JSON trong C**

**1. Đưa dữ liệu JSON vào chuỗi**

- Chuỗi JSON được lưu trong một biến kiểu const char*.

**2. Duyệt qua từng ký tự và bỏ qua khoảng trắng**

**3. Xác định kiểu dữ liệu JSON**

- Kiểm tra ký tự đầu tiên:

	+ "n" → null
	+ "t" hoặc "f" → boolean
	+ "0-9" hoặc "-" → number
	+ "\"" → string
	+ "[" → array
	+ "{" → object

**4. Phân tích từng loại dữ liệu JSON**

- **Null**: Kiểm tra "null", di chuyển con trỏ.
- **Boolean**: Kiểm tra "true" hoặc "false", di chuyển con trỏ.
- **Number**: Chuyển đổi chuỗi thành số.
- **String**: Duyệt đến ký tự " đóng, trích xuất chuỗi.
- **Array**: Bắt đầu từ "[", duyệt qua từng phần tử cho đến khi gặp "]".
- **Object**: Bắt đầu từ "{", duyệt qua từng cặp "key": value.

**5. Lưu trữ dữ liệu vào cấu trúc JSONValue**

- Dùng malloc() để cấp phát bộ nhớ động.
- Dùng realloc() để mở rộng danh sách mảng hoặc object.

<br>

**Source Code**: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/JSON

<br>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>12. Linked List</b></summary>
<p>

<details><summary><b>12.1. Khái niệm</b></summary>
<p>

Danh sách liên kết (Linked List) là một cấu trúc dữ liệu trong lập trình máy tính, được sử dụng để tổ chức và lưu trữ dữ liệu. Một Linked list bao gồm một chuỗi các nút (nodes) được phân bổ động, được sắp xếp theo cách mà mỗi node sẽ chứa một giá trị và một con trỏ (pointer) trỏ đến node tiếp theo nó. Nếu con trỏ là NULL thì nó là node cuối cùng trong danh sách.

Có hai loại linked list chính:

- Singly Linked List (Danh sách liên kết đơn): Mỗi nút chỉ chứa một con trỏ đến nút tiếp theo trong chuỗi.

![image](https://github.com/user-attachments/assets/c2669fde-dacb-4f2b-9cd8-cb861c7e9e3e)

- Doubly Linked List (Danh sách liên kết đôi): Mỗi nút chứa hai con trỏ, một trỏ đến nút tiếp theo và một trỏ đến nút trước đó.

![Image](https://github.com/user-attachments/assets/727a32bb-dc9f-47c8-95b6-6fd9900b4574)

Một linked list cung cấp một cách linh hoạt để thêm, xóa và chèn các phần tử mà không cần phải di chuyển toàn bộ dãy số như mảng. Tuy nhiên, nó cũng có một số nhược điểm, như việc cần thêm một con trỏ cho mỗi nút, tăng độ phức tạp của bộ nhớ và có thể dẫn đến hiệu suất kém hơn trong một số trường hợp so với mảng.



</p>
</details>

<details><summary><b>12.2. Các thao tác chính trong danh sách liên kết đơn</b></summary>
<p>

- Khởi tạo 1 Node bất kỳ.
- Thêm Node vào đầu danh sách.
- Thêm Node vào cuối danh sách.
- Thêm Node vào vị trí bất kỳ.
- Xóa Node đầu danh sách.
- Xóa Node cuối danh sách.
- Xóa Node vị trí bất kỳ.
- Kiểm tra rỗng.
- Tính số lượng Node có trong danh sách

<br>

**Soure Code triển khai**:

- **Single Linked List**: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/Linked_List/Single

- **Double Linked List**: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/Linked_List/Doubly

<br>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>13. Stack (Ngăn xếp)</b></summary>
<p>

<details><summary><b>13.1. Khái niệm</b></summary>
<p>

Ngăn xếp (Stack) là một cấu trúc dữ liệu hoạt động theo nguyên tắc **"Last In, First Out"** (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra.

![Image](https://github.com/user-attachments/assets/60622e9e-b3a5-4a6c-bd77-fb5a011c1f65)

<br>

</p>
</details>

<details><summary><b>13.2. Các thao tác trên Stack</b></summary>
<p>

- Khởi tạo một Stack.
- Thêm phần tử vào đỉnh Stack.
- Xóa phần tử ở đỉnh Stack.
- Đọc giá trị ở đỉnh Stack.
- Kiểm tra Stack rỗng/đầy.

<br>

- **Source Code triển khai**: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/Stack

<br>
 
</p>
</details>

</p>
</details>

<br>

<details><summary><b>14. Queue (Hàng đợi)</b></summary>
<p>

<details><summary><b>14.1. Khái niệm</b></summary>
<p>

- Queue là một cấu trúc dữ liệu tuân theo nguyên tắc "First In, First Out" (FIFO), nghĩa là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra.
- Queue được chia làm 3 loại chính:

	+ Linear Queue
 	+ Circular Queue
  	+ Priority Queue 

![queue](https://drive.google.com/uc?id=1h6uwf3TiU4wA8eOgTSxVohd13ibq8szi)

</p>
</details>

<details><summary><b>14.2. Linear Queue (Hàng đợi tuyến tính)</b></summary>
<p>

- Trong Linear Queue, nếu ‘rear’ đã đạt tới max, thì queue sẽ được coi là đầy và không thể thêm phần tử mới, ngay cả khi phía trước còn khoảng trống do các phần tử đã bị xóa.
- Chỉ có thể thêm phần tử mới khi đã dequeue toàn bộ các phần tử hiện có (tức là queue rỗng hoàn toàn và front được reset về vị trí ban đầu).

<br>

- **Source Code triển khai**: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/Queue/Linear

<br>

</p>
</details>

<details><summary><b>14.3. Circular Queue (Hàng đợi vòng tròn)</b></summary>
<p>

- Khác với **Linear Queue**, trong **Circular Queue** khi chỉ số ``` rear ``` đạt max, nếu vẫn còn chỗ trống (đã xóa phần tử) thì ``` rear ``` sẽ "quay vòng" về vị trí 0 để tận dụng khoảng trống.

<br>

- **Source Code triển khai**: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/Queue/Circular

<br>
 
</p>
</details>

</p>
</details>

<br>

<details><summary><b>15. Cây (Tree)</b></summary>
<p>

<details><summary><b>15.1. Khái niệm</b></summary>
<p>

**Cấu trúc dữ liệu phân cấp (Tree)** là một cấu trúc dữ liệu phi tuyến tính, trong đó các phần tử (được gọi là nút, hay node) được tổ chức theo một thứ bậc phân cấp. Cây là một trong những cấu trúc dữ liệu quan trọng, được sử dụng rộng rãi trong khoa học máy tính để biểu diễn các quan hệ phân cấp, tìm kiếm, sắp xếp, và lưu trữ.

<br>

</p>
</details>

<details><summary><b>15.2. Cây nhị phân (Binary Tree)</b></summary>
<p>

Là một cấu trúc cây mà mỗi nút (node) có tối đa hai nút con, được gọi là nút con trái và nút con phải.

Tính chất:

- Không có quy tắc cụ thể về cách sắp xếp các phần tử.
- Được dùng làm nền tảng để xây dựng các loại cây phức tạp hơn (ví dụ: BST, Heap).

Quy tắc xây dựng cây nhị phân:

- Mỗi phần tử trong array/list sẽ được ánh xạ đến một nút trong cây nhị phân.
- Cách ánh xạ đến cây:

	+ Phần tử tại chỉ số ``` i ``` trong mảng sẽ là gốc của cây con.

  	+ Chỉ số của con trái: ``` 2 * i + 1 ```.

  	+ Chỉ số của con phải: ``` 2 * i + 2 ```.

**Ví dụ**:

```cpp
Mảng:   {1, 3, 5, 13, 2, 2, 20, 9, 4}
Chỉ số:  0  1  2   3  4  5   6  7  8

          1
       /     \
      3       5
     / \     / \
   13   2   2  20
   / \
  9   4

```

Ứng dụng:

- Biểu diễn các quan hệ phân cấp.
- Biểu diễn các biểu thức toán học (cây biểu thức).

<br>

</p>
</details>

<details><summary><b>15.3. Cây tìm kiếm nhị phân (Binary Search Tree - BST)</b></summary>
<p>

Là một loại cây nhị phân với đặc điểm đặc biệt:

- Mỗi nút trong cây:

	+ Nút trái chứa các giá trị nhỏ hơn giá trị tại nút hiện tại.

	+ Nút phải chứa các giá trị lớn hơn hoặc bằng giá trị tại nút hiện tại.

Tính chất:

- Thứ tự sắp xếp: Các phần tử được sắp xếp, cho phép tìm kiếm nhị phân hiệu quả.
- Duyệt cây in-order sẽ trả về danh sách giá trị theo thứ tự tăng dần.

**Ví dụ**:

```cpp
Mảng:    {1, 3, 5, 13, 2, 2, 20, 9, 4}
Sắp xếp: {1, 2, 2, 3, 4, 5, 9, 13, 20}
Chỉ số:   0  1  2  3  4  5  6   7   8

          4
       /     \
      2       9
     / \     / \
    1   2   5  13
         \       \
          3      20   

```

<br>

- **Source Code triển khai Binary Search Tree**: https://github.com/NHAnh2082/C_Programming_Language/blob/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/Binary_Search_Tree/Binary_Search_Tree.c

<br>

Ứng dụng:

- Tìm kiếm nhanh (lookup).
- Chèn, xóa và tìm kiếm với độ phức tạp 𝑂(log𝑛) (trong trường hợp cây cân bằng).

</p>
</details>

<details><summary><b>15.4. Heap Tree</b></summary>
<p>

Là một loại cây nhị phân với đặc điểm đặc biệt:

- **Heap Max**: Nút cha luôn có giá trị lớn hơn hoặc bằng các nút con.
- **Heap Min**: Nút cha luôn có giá trị nhỏ hơn hoặc bằng các nút con.
- Thường là cây nhị phân đầy đủ (complete binary tree), nghĩa là tất cả các mức đều đầy đủ, trừ mức cuối cùng.

Tính chất:

- Không quan tâm đến thứ tự giữa các anh chị em (siblings).
- Duy trì ưu tiên của các giá trị.

Ứng dụng:

- Triển khai hàng đợi ưu tiên (Priority Queue).
- Sắp xếp (Heap Sort).

**Ví dụ**:

- **Heap Max**:

```cpp
     25
    /  \
  20    15
 / \   / 
10  5 8  
```

- **Heap Min**

```cpp
     5
    / \
   10  8
  / \  /
 20 15 25
```

<br>

![image](https://github.com/user-attachments/assets/9297a312-423d-4e16-b94f-dcf9e25e5cca)

<br>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>16. Thuật toán sắp xếp</b></summary>
<p>

<details><summary><b>16.1. Bubble Sort</b></summary>
<p>

<details><summary><b>📚 Nguyên lý</b></summary>
<p>

- Bubble Sort lặp qua mảng nhiều lần, so sánh từng cặp phần tử và hoán đổi nếu chúng không theo thứ tự mong muốn.
- Mỗi lần lặp, phần tử lớn nhất (hoặc nhỏ nhất) sẽ được đẩy về cuối mảng qua mỗi vòng lặp.

<br>

</p>
</details>

<details><summary><b>📚Cách hoạt động</b></summary>
<p>

Giả sử có một mảng: ``` array[] = {5, 3, 8, 6, 2} ```

- Duyệt qua mảng từ đầu đến cuối.
- Nếu ``` array[n] > array[n-1] ``` thì hoán đổi vị trí.

**Lượt lặp đầu tiên (i=0)**

- Chạy từ phần tử ``` 0 -> n-1 ```

```cpp
[5, 3, 8, 6, 2] → so sánh 5 và 3 → đổi chỗ       → [3, 5, 8, 6, 2]
[3, 5, 8, 6, 2] → so sánh 5 và 8 → không đổi chỗ → [3, 5, 8, 6, 2]
[3, 5, 8, 6, 2] → so sánh 8 và 6 → đổi chỗ       → [3, 5, 6, 8, 2]
[3, 5, 6, 8, 2] → so sánh 8 và 2 → đổi chỗ       → [3, 5, 6, 2, 8]
```

**Lượt lặp đầu tiên (i=1)**

- Chạy từ phần tử ``` 0 -> n-2 ```

```cpp
[3, 5, 6, 2, 8] → so sánh 3 và 5 → không đổi chỗ → [3, 5, 6, 2, 8]
[3, 5, 6, 2, 8] → so sánh 5 và 6 → không đổi chỗ → [3, 5, 6, 2, 8]
[3, 5, 6, 2, 8] → so sánh 6 và 2 → đổi chỗ       → [3, 5, 2, 6, 8]
```

**Lượt lặp đầu tiên (i=2)**

- Chạy từ phần tử ``` 0 -> n-3 ```

```cpp
[3, 5, 2, 6, 8] → so sánh 3 và 5 → không đổi chỗ → [3, 5, 2, 6, 8]
[3, 5, 2, 6, 8] → so sánh 5 và 2 → đổi chỗ       → [3, 2, 5, 6, 8]
```

**Lượt lặp đầu tiên (i=3)**

- Chỉ còn một lần so sánh.

```cpp
[3, 2, 5, 6, 8] → so sánh 3 và 2 → đổi chỗ → [2, 3, 5, 6, 8]
```

<br>

- **Source Code triển khai**: 

<br>

</p>
</details>

</p>
</details>

<details><summary><b>16.2. Quick Sort</b></summary>
<p>

<details><summary><b>📚 Nguyên lý</b></summary>
<p>

- Quick Sort là thuật toán chia để trị (Divide & Conquer).
- Chọn một phần tử gọi là **pivot** - phần tử được chọn trong mỗi lần chia mảng, đóng vai trò quyết định trong việc phân chia mảng thành hai phần::

    + Nhỏ hơn pivot (bên trái).
    + Lớn hơn pivot (bên phải).

- Áp dụng Quick Sort đệ quy cho hai nửa còn lại.

<br>

</p>
</details>


<details><summary><b>📚 Pivot</b></summary>
<p>

Pivot trong thuật toán Quick Sort là phần tử được chọn để chia mảng thành hai phần:

- Các phần tử nhỏ hơn hoặc bằng pivot sẽ nằm bên trái.
- Các phần tử lớn hơn pivot sẽ nằm bên phải.

Pivot có nhiều cách để lựa chọn:

- Phần tử đầu tiên (First element).
- Phần tử cuối cùng (Last element).
- Phần tử giữa (Middle element).
- Trung vị của ba phần tử (Median of Three) – giá trị trung gian của 3 phần tử: đầu, giữa và cuối.
- Chọn ngẫu nhiên (Random pivot) – chọn một chỉ số bất kỳ

Phụ thuộc vào thuật toán cụ thể, cách chọn phần tử pivot có thể ảnh hưởng đến hiệu suất của thuật toán và đôi khi quyết định này có thể tạo ra kết quả tốt hơn.

<br>

</p>
</details>

<details><summary><b>📚 Cách hoạt động</b></summary>
<p>

- **B1:** Chọn pivot
- **B2:** Hoán đổi pivot với phần tử cuối cùng
- **B3:** Bắt đầu từ phần tử ngoài cùng bên trái và theo dõi chỉ số của các phần tử nhỏ hơn (hoặc bằng) là **i** . Trong khi duyệt, nếu chúng ta tìm thấy một phần tử nhỏ hơn, chúng ta hoán đổi phần tử hiện tại với **arr[i]** . Nếu không, chúng ta bỏ qua phần tử hiện tại.

<br>

Giả sử có một mảng: ``` array[] = {10, 80, 30, 90, 40, 50, 70} ```

**B1: Chọn pivot**

- Chọn **pivot = 70** (tất cả trường hợp chọn pivot đều quy về phần tử cuối cùng).

**B2: Partition**

- **Lượt lặp đầu tiên**:

```cpp 
10 < 70 → Hoán đổi 10 và 10   → [10, 80, 30, 90, 40, 50, 70]
```
  
- **Lượt lặp thứ hai**:

```cpp
80 > 70 → Không đổi           → [10, 80, 30, 90, 40, 50, 70]
```
  
- **Lượt lặp thứ ba**:

```cpp
30 > 70 → Hoán đổi 80 và 30   → [10, 30, 80, 90, 40, 50, 70]
```
  
- **Lượt lặp thứ tư**:

```cpp
90 > 70 → Không đổi           → [10, 30, 80, 90, 40, 50, 70]
```
  
- **Lượt lặp thứ năm**:

```cpp
40 > 70 → Hoán đổi 80 và 40   → [10, 30, 40, 90, 80, 50, 70]
```
  
- **Lượt lặp thứ sáu**:

```cpp
50 > 70 → Hoán đổi 90 và 50   → [10, 30, 40, 50, 80, 90, 70]
```
  
- Đưa pivot vào đúng vị trí:

```cpp
Hoán đổi 80 và 70 → [10, 30, 40, 50, 70, 90, 80]
```

<br>

❓ **Vậy việc chọn pivot khác nhau có thực sự quan trọng?**

Dù cuối cùng pivot được chuyển về cuối mảng, sự khác biệt nằm ở cách chọn pivot ban đầu. Điều này ảnh hưởng trực tiếp đến:

- Cách mảng được chia nhỏ.
- Độ cân bằng giữa hai nửa mảng sau khi phân hoạch.

Ngoài ra, chuyển pivot về cuối giúp thuật toán đơn giản hóa quá trình phân hoạch:

- Duyệt từ trái sang phải, đặt các phần tử nhỏ hơn pivot sang bên trái.
- Sau khi duyệt xong, chỉ cần đưa pivot về đúng vị trí phân chia.

Việc chọn pivot ban đầu quyết định sự cân bằng khi chia mảng. Một pivot tốt giúp mảng được chia đều → tăng tốc độ sắp xếp.

<br>

- **Source Code triển khai**: 
<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>17. Thuật toán tìm kiếm nhị phân</b></summary>
<p>

Thuật toán tìm kiếm nhị phân (binary search) là một thuật toán tìm kiếm hiệu quả trên danh sách đã được sắp xếp. Thuật toán này hoạt động bằng cách chia nhỏ phạm vi tìm kiếm thành hai phần, sau đó loại bỏ một nửa số phần tử trong mỗi bước.

<br>

Nguyên lý hoạt động:

- Bước 1: Chọn phần tử giữa của danh sách.
- Bước 2: So sánh giá trị cần tìm với phần tử giữa:

	+ Nếu bằng nhau → Trả về vị trí.
 	+ Nếu nhỏ hơn → Tìm kiếm trong nửa trái.
  	+ Nếu lớn hơn → Tìm kiếm trong nửa phải.
  
- Bước 3: Lặp lại quá trình trên cho đến khi tìm thấy phần tử hoặc phạm vi tìm kiếm thu nhỏ về 0 (không tìm thấy).

<br>

<img width="282" alt="Image" src="https://github.com/user-attachments/assets/8e78cc6c-feef-459a-b498-03e67d50b895" />

<br>

- **Source Code triển khai Binary Search**: https://github.com/NHAnh2082/C_Programming_Language/tree/85bf7f09bc7e35ce08a945981b60992579fdde83/Source%20Code/SearchAlgorithm

<br>

</p>
</details>
