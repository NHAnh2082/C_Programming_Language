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
