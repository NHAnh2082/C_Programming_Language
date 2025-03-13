#include "..\\Header\\JSONParser1.h"

int main()
{
    const char *json_str = "{"
                                "\"1001\":{"
                                "\"SoPhong\": 3,"
                                "\"NguoiThue\":{"
                                    "\"Ten\":\"Nguyen Van A\","
                                    "\"CCCD\":\"1920517781\","
                                    "\"Tuoi\":26,"
                                    "\"ThuongTru\":{"
                                    "\"Duong\":\"73 Ba Huyen Thanh Quan\","
                                    "\"Phuong_Xa\":\"Phuong 6\","
                                    "\"Tinh_TP\":\"Ho Chi Minh\""
                                    "}"
                                "},"
                                "\"SoNguoiO\":{"
                                    "\"1\":\"Nguyen Van A\","
                                    "\"2\":\"Nguyen Van B\","
                                    "\"3\":\"Nguyen Van C\""
                                "},"
                                "\"TienDien\": [24, 65, 98],"
                                "\"TienNuoc\":30.000"
                                "},"
                                "\"1002\":{"
                                "\"SoPhong\":5,"
                                "\"NguoiThue\":{"
                                    "\"Ten\":\"Phan Hoang Trung\","
                                    "\"CCCD\":\"012345678912\","
                                    "\"Tuoi\":24,"
                                    "\"ThuongTru\":{"
                                    "\"Duong\":\"53 Le Dai Hanh\","
                                    "\"Phuong_Xa\":\"Phuong 11\","
                                    "\"Tinh_TP\":\"Ho Chi Minh\""
                                    "}"
                                "},"
                                "\"SoNguoiO\":{"
                                    "\"1\":\"Phan Van Nhat\","
                                    "\"2\":\"Phan Van Nhi\","
                                    "\"2\":\"Phan Van Tam\","
                                    "\"3\":\"Phan Van Tu\""
                                "},"
                                "\"TienDien\":23.000,"
                                "\"TienNuoc\":40.000"
                                "}"
                            "}";

    // Phân tích cú pháp chuỗi JSON
    JSONValue* json_value = parse_json(&json_str);

    // Kiểm tra kết quả phân tích cú pháp
    display(json_value);

    // Giải phóng bộ nhớ được cấp phát cho JSONValue
    free_json_value(json_value);

    return 0;
}