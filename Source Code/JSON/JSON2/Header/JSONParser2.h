/***********************************************************************************
 * @file    JSONParser2.h
 * @brief   Thư viện phân tích cú pháp JSON đơn giản.
 * @details Cung cấp các chức năng để phân tích và quản lý dữ liệu JSON đọc từ file,
 *          bao gồm các kiểu dữ liệu cơ bản như null, boolean, số, chuỗi,
 *          mảng và object.
 * @version 1.0
 * @date    2025-03-12
 * @author  Nguyễn Văn Thưởng
 **********************************************************************************/
#ifndef JSONPARSER2_H
#define JSONPARSER2_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>


/* Định nghĩa kích thước tối đa của file JSON */
#define MAX_FILE_SIZE 4096


/**
 * @struct  DeviceConfig
 * @brief   Cấu trúc lưu thông tin thiết bị được trích xuất từ JSON
 * @details Cấu trúc này lưu trữ các thông số về thiết bị như tên, phiên bản
 *          firmware, tốc độ baud, độ phân giải ADC, tần số PWM và chế độ debug.
 */
typedef struct 
{
    char device_name[64];       /**< Tên thiết bị                               */
    char firmware_version[16];  /**< Phiên bản firmware                         */
    int baud_rate;              /**< Tốc độ baud của UART                       */
    int adc_resolution;         /**< Độ phân giải ADC (bit)                     */
    int pwm_frequency;          /**< Tần số PWM (Hz)                            */
    int debug_mode;             /**< Chế độ debug (1 = Enabled, 0 = Disabled)   */
} DeviceConfig;


/**
 * @enum    JSONType
 * @brief   Định nghĩa các kiểu dữ liệu JSON được hỗ trợ
 */
typedef enum 
{
    JSON_NULL,    /**< Giá trị null                 */
    JSON_BOOLEAN, /**< Kiểu boolean (true/false)    */
    JSON_NUMBER,  /**< Kiểu số (int/double)         */
    JSON_STRING,  /**< Kiểu chuỗi                   */
    JSON_ARRAY,   /**< Kiểu mảng                    */
    JSON_OBJECT   /**< Kiểu object                  */
} JSONType;


/**
 * @struct  JSONValue
 * @brief   Cấu trúc lưu trữ một giá trị JSON
 * @details JSONValue có thể chứa một giá trị số, chuỗi, boolean, hoặc là
 *          một object/mảng JSON lồng nhau.
 */
typedef struct JSONValue
{
    JSONType type;                      /**< Kiểu dữ liệu của giá trị JSON  */

    union
    {
        int     boolean;                /**< Giá trị boolean                */
        double  number;                 /**< Giá trị số                     */
        char    *string;                /**< Chuỗi ký tự                    */

        struct
        {
            struct JSONValue *values;   /**< Danh sách phần tử trong mảng   */
            size_t count;               /**< Số lượng phần tử trong mảng    */
        } array;

        struct
        {
            char **keys;                /**< Danh sách key trong object: ["key1", "key2", v.v]     */
            struct JSONValue *values;   /**< Danh sách giá trị tương ứng    */
            size_t count;               /**< Số lượng cặp key-value trong object  */
        } object;

    } value;
} JSONValue;


/**
 * @brief   Đọc dữ liệu từ file JSON vào bộ nhớ
 * @details Hàm này đọc toàn bộ nội dung file JSON và cấp phát bộ nhớ động
 *          để lưu trữ dữ liệu JSON dưới dạng chuỗi ký tự.
 * @param   filename [in]  Tên file JSON cần đọc
 * @return  char*    Trả về con trỏ đến buffer chứa nội dung JSON
 *                   NULL nếu không thể mở file hoặc lỗi cấp phát bộ nhớ
 */
char* read_json_file(const char *filename) ;


/**
 * @brief   Giải phóng bộ nhớ của cấu trúc JSONValue
 * @details Hàm này giải phóng tất cả các bộ nhớ đã được cấp phát động trong
 *          JSONValue, bao gồm các chuỗi, mảng và object JSON.
 * @param   json_value [in] Con trỏ đến cấu trúc JSONValue cần giải phóng
 * @return  void
 */
void free_json_value(JSONValue *json_value);


/**
 * @brief   Bỏ qua các ký tự khoảng trắng trong JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  void
 */
static void skip_whitespace(const char **json);


/**
 * @brief   Phân tích giá trị null từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_NULL hoặc NULL nếu lỗi
 */
JSONValue *parse_null(const char **json);


/**
 * @brief   Phân tích giá trị boolean (true/false) từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_BOOLEAN hoặc NULL nếu lỗi
 */
JSONValue *parse_boolean(const char **json);


/**
 * @brief   Phân tích giá trị boolean (true/false) từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_BOOLEAN hoặc NULL nếu lỗi
 */
JSONValue *parse_number(const char **json);


/**
 * @brief   Phân tích giá trị chuỗi từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_STRING hoặc NULL nếu lỗi
 */
JSONValue *parse_string(const char **json);


/**
 * @brief   Phân tích giá trị mảng JSON
 * @details Hàm này phân tích cú pháp một mảng JSON bằng cách duyệt qua các
 *          phần tử và gọi `parse_json()` để xử lý từng phần tử.
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_ARRAY hoặc NULL nếu lỗi
 */
JSONValue *parse_array(const char **json);


/**
 * @brief   Phân tích một object JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_OBJECT hoặc NULL nếu lỗi
 */
JSONValue *parse_object(const char **json);


/**
 * @brief   Phân tích tổng quát một giá trị JSON
 * @details Hàm này gọi các hàm parse tương ứng với từng loại JSON như
 *          'parse_object()', 'parse_array()', 'parse_number()', v.v.
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON đã phân tích hoặc NULL nếu lỗi
 */
JSONValue *parse_json(const char **json);


/**
 * @brief   In nội dung của JSONValue ra màn hình (debug)
 * @details Hàm này duyệt qua JSONValue và in các phần tử ra màn hình theo
 *          định dạng cây, phù hợp để kiểm tra dữ liệu JSON sau khi parse.
 * @param   json_value [in] Con trỏ đến cấu trúc JSONValue cần hiển thị
 * @return  void
 */
void test(JSONValue *json_value);


/**
 * @brief   Trích xuất dữ liệu từ JSON vào cấu trúc DeviceConfig
 * @details Hàm này duyệt qua các phần tử trong JSON và ánh xạ giá trị vào
 *          cấu trúc DeviceConfig tương ứng.
 * @param   json_value [in]  Con trỏ đến dữ liệu JSON đã được phân tích
 * @param   config     [out] Cấu trúc DeviceConfig cần điền dữ liệu
 * @return  void
 */
void extract_device_config(JSONValue *json_value, DeviceConfig *config);


/**
 * @brief   Hiển thị thông tin của DeviceConfig
 * @details Hàm này in ra các thông tin đã được trích xuất từ JSON
 * @param   config [in] Cấu trúc chứa thông tin thiết bị
 * @return  void
 */
void print_device_config(const DeviceConfig config);

#endif  // JSONPARSER2_H