#include "..\\Header\\JSONParser2.h"

int main()
{
    /* Đọc file JSON */
    const char *json = read_json_file("data.json");
    if (!json) return 1;

    /* Phân tích cú pháp chuỗi JSON */ 
    JSONValue* json_value = parse_json(&json);

    /* Kiểm tra kết quả phân tích cú pháp */ 
    test(json_value);

    /* Khởi tạo cấu trúc lưu dữ liệu JSON */ 
    DeviceConfig config = {0};

    /* Trích xuất dữ liệu JSON vào cấu trúc */
    extract_device_config(json_value, &config);

    /* Hiển thị thông tin */
    print_device_config(config);

    /* Giải phóng bộ nhớ được cấp phát */
    free_json_value(json_value);

    return 0;
}