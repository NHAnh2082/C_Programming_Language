/***************************************************************************
 * @file    LEDMatrix_Simulation.c
 * @brief   Mô phỏng hiển thị ký tự trên ma trận LED 8x8.
 * @details Chương trình hiển thị lần lượt ba câu chữ trên ma trận LED 8x8,
 *          sử dụng vòng lặp để hiển thị từng ký tự một. Cho phép dừng hiển thị 
 *          khi nhấn phím 'M'.
 * @version 1.0
 * @date    2024-10-12
 * @author  Anh Nguyen
 ***************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>	

/**
 * @brief   Định nghĩa ba câu cần hiển thị trên ma trận LED.
 */
char first_sentence[]  = "HI";	
char second_sentence[] = "FASHION";
char third_sentence[]  = "SUITABLE";

/**
 * @brief   Ma trận LED 8x8 mô phỏng ký tự 'H'.
 */
uint8_t letter_H[8][8] = 
{  
    {1,0,0,0,0,0,0,1},		// 0b10000001
    {1,0,0,0,0,0,0,1},		// 0b10000001
    {1,0,0,0,0,0,0,1},		// 0b10000001
    {1,1,1,1,1,1,1,1},		// 0b11111111
    {1,0,0,0,0,0,0,1},		// 0b10000001
    {1,0,0,0,0,0,0,1},		// 0b10000001
    {1,0,0,0,0,0,0,1},		// 0b10000001
    {1,0,0,0,0,0,0,1},  	// 0b10000001
};

/**
 * @brief   Ma trận LED 8x8 mô phỏng ký tự 'I'.
 */
uint8_t letter_I[8][8] = 
{  
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {1,1,1,1,1,1,1,1},  
};

/**
 * @brief   Ma trận LED 8x8 mô phỏng ký tự 'F'.
 */
uint8_t letter_F[8][8] = 
{  
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},  
};

/**
 * @brief   Ma trận LED 8x8 mô phỏng ký tự 'S'.
 */
uint8_t letter_S[8][8] = 
{  
    {0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0},  
};

/**
 * @brief   Biến button dùng để kiểm tra trạng thái nút nhấn dừng.
 */
uint8_t button = 0;

/**
 * @brief   Kiểu liệt kê đại diện cho các câu cần hiển thị.
 */
typedef enum
{
	FIRST,   /**< Câu thứ nhất */
	SECOND,  /**< Câu thứ hai */
	THIRD    /**< Câu thứ ba */
} Sentence;


/**
 * @brief   Hiển thị một ký tự trên ma trận LED 8x8.
 * @details In ra ký tự dưới dạng dấu '*' và khoảng trắng.
 * @param   matrix   Ma trận LED 8x8 chứa thông tin về ký tự cần in.
 * @return  void
 */
void print_char(const uint8_t matrix[8][8])
{
	for (size_t i=0; i<8; i++)
	{
		for (size_t j=0; j<8; j++)
		{
			printf(matrix[i][j] ? "*" : " ");
		}
		printf("\n");
	}
}

/**
 * @brief   Kiểm tra phím nhấn dừng chương trình.
 * @details Nếu phím 'M' hoặc 'm' được nhấn, chương trình sẽ dừng lại.
 * @return  uint8_t   Trả về 1 nếu phím được nhấn, ngược lại trả về 0.
 */
uint8_t is_pressed_stop_key()
{
	if (kbhit())  			/**< Kiểm tra xem có phím nào được nhấn không */
	{ 
		char key = getch();	/**< Đọc phím từ bàn phím */
		if (key == 'M' || key == 'm') return 1; /**< Nếu phím 'M' được nhấn */
	}
	return 0;
}

/**
 * @brief   Hàm delay theo giây.
 * @param   time  Số giây cần delay.
 * @return  void
 */
void delay(unsigned int time)
{
	sleep(time);
}

int main(int argc, char const *argv[])
{
	// Biến 'sentence' được khởi tạo với giá trị 'FIRST', đại diện cho câu đầu tiên cần hiển thị.
	Sentence sentence = FIRST;

	while(1)
	{	
		switch(sentence)
		{
			case FIRST:
				for (int index=0; index<sizeof(first_sentence); index++)
				{
					if (first_sentence[index] == 'H'){
						print_char(letter_H);
					} else if (first_sentence[index] == 'I'){
						print_char(letter_I);
					}
					
					if ((button = is_pressed_stop_key()) == 1) goto exit_loops;
				}
				printf("First sentence is done\n");
				printf("\n");
				delay(2);
				goto logic;


			case SECOND:
				for (int index=0; index<sizeof(second_sentence); index++)
				{
					if (second_sentence[index] == 'F'){
						print_char(letter_F);
					} else if (second_sentence[index] == 'A'){
						// in ra ký tự 'A'
					}

					if ((button = is_pressed_stop_key()) == 1) goto exit_loops;
				}
				printf("Second sentence is done\n");
				printf("\n");
				delay(2);
				goto logic;


			case THIRD:
				for (int index=0; index<sizeof(third_sentence); index++)
				{
					if (third_sentence[index] == 'S'){
						print_char(letter_S);
					} else if (third_sentence[index] == 'U'){
						// in ra ký tự 'U'
					}
					
					if ((button = is_pressed_stop_key()) == 1) goto exit_loops;
				}
				printf("Third sentence is done\n");
				printf("\n");
				delay(2);
				goto logic;
		}

		/**
		 * @brief   Chuyển đổi giữa các câu cần hiển thị.
		 */
		logic:
			if (sentence == FIRST) 		 sentence = SECOND;
			else if (sentence == SECOND) sentence = THIRD;
			else if (sentence == THIRD)  sentence = FIRST;
	}

	/**
	 * @brief   Xử lý khi nhấn nút dừng.
	 */
	exit_loops:
		printf("Stop\n");

	return 0;
}