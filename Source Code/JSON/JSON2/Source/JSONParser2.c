/***************************************************************************
 * @file    JsonParser2.c
 * @brief   Thư viện xử lý và phân tích dữ liệu JSON trong ngôn ngữ C
 * @details File này chứa các hàm để đọc, phân tích và trích xuất dữ liệu từ JSON.
 *          Dữ liệu JSON được đọc từ file và ánh xạ vào cấu trúc dữ liệu.
 * @version 1.0
 * @date    2025-02-19
 * @author  Nguyen Anh
 ***************************************************************************/
#include "..\\Header\\JSONParser2.h"


/**
 * @brief   Đọc dữ liệu từ file JSON vào bộ nhớ
 * @details Hàm này đọc toàn bộ nội dung file JSON và cấp phát bộ nhớ động
 *          để lưu trữ dữ liệu JSON dưới dạng chuỗi ký tự.
 * @param   filename [in]  Tên file JSON cần đọc
 * @return  char*    Trả về con trỏ đến buffer chứa nội dung JSON
 *                   NULL nếu không thể mở file hoặc lỗi cấp phát bộ nhớ
 */
char* read_json_file(const char *filename) 
{
    /* Mở file để bắt đầu đọc dữ liệu */
    FILE *file = fopen(filename, "r");

    /* Kiểm tra xem đọc file thành công hay chưa */
    if (!file) 
    {
        printf("Không thể mở file: %s\n", filename);
        return 0;
    }

    /* Lấy kích thước file */
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    /* Lấy kích thước file */
    if (file_size > MAX_FILE_SIZE) 
    {
        printf("Kích thước file quá lớn!\n");
        fclose(file);
        return NULL;
    }

    /* Cấp phát bộ nhớ động */
    char *buffer = (char*)malloc(file_size + 1);
    if (!buffer) 
    {
        printf("Lỗi cấp phát bộ nhớ!\n");
        fclose(file);
        return NULL;
    }

    /* Đọc dữ liệu từ file */
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Kết thúc chuỗi
    fclose(file);
    return buffer;
}


JSONValue *parse_json(const char **json);
void free_json_value(JSONValue *json_value);


/**
 * @brief   Bỏ qua các ký tự khoảng trắng trong JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  void
 */
static void skip_whitespace(const char **json)
{
    while (isspace(**json)){ (*json)++; }
}

/**
 * @brief   Phân tích giá trị null từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_NULL hoặc NULL nếu lỗi
 */
JSONValue *parse_null(const char **json)
{
    skip_whitespace(json);
    JSONValue *value = (JSONValue*)malloc(sizeof(JSONValue));

    if (strncmp(*json, "null", 4) == 0) // strncmp # strcmp
    {
        value->type = JSON_NULL;
        *json += 4;
        return value;
    }

    free(value);
    return NULL;
}

/**
 * @brief   Phân tích giá trị boolean (true/false) từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_BOOLEAN hoặc NULL nếu lỗi
 */
JSONValue *parse_boolean(const char **json)
{
    skip_whitespace(json);

    JSONValue *value = (JSONValue*)malloc(sizeof(JSONValue));

    if (strncmp(*json, "true", 4) == 0)
    {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } 
    else if (strncmp(*json, "false", 5) == 0)
    {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    } 
    else 
    {
        free(value);
        return NULL;
    }
    return value;
}

/**
 * @brief   Phân tích giá trị boolean (true/false) từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_BOOLEAN hoặc NULL nếu lỗi
 */
JSONValue *parse_number(const char **json)
{
    skip_whitespace(json);
    char *end;

    double num = strtod(*json, &end); // double strtod(const char *str, char **endptr);

    if (end != *json)
    {
        JSONValue *value = (JSONValue*)malloc(sizeof(JSONValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}

/**
 * @brief   Phân tích giá trị chuỗi từ JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_STRING hoặc NULL nếu lỗi
 */
JSONValue *parse_string(const char **json)
{
    skip_whitespace(json);

    if (**json == '\"')
    {
        (*json)++;
        const char *start = *json;

        while (**json != '\"' && **json != '\0') (*json)++;

        if (**json == '\"')
        {
            size_t length = *json - start;  // 4
            char *str = (char*)malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);    // strncopy # strcopy
            str[length] = '\0';

            JSONValue *value = (JSONValue*)malloc(sizeof(JSONValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}

/**
 * @brief   Phân tích giá trị mảng JSON
 * @details Hàm này phân tích cú pháp một mảng JSON bằng cách duyệt qua các
 *          phần tử và gọi `parse_json()` để xử lý từng phần tử.
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_ARRAY hoặc NULL nếu lỗi
 */
JSONValue *parse_array(const char **json)
{
    skip_whitespace(json);
    if (**json == '[')
    {
        (*json)++;
        skip_whitespace(json);
        JSONValue *array_value = (JSONValue*)malloc(sizeof(JSONValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        while (**json != ']' && **json != '\0')
        {
            JSONValue *element = parse_json(json); // 70
            if (element)
            {
                array_value->value.array.count++;
                array_value->value.array.values = (JSONValue*)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JSONValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } 
            else break;

            skip_whitespace(json);
            
            if (**json == ',') (*json)++;
        }

        if (**json == ']')
        {
            (*json)++;
            return array_value;
        } 
        else 
        {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}

/**
 * @brief   Phân tích một object JSON
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON_OBJECT hoặc NULL nếu lỗi
 */
JSONValue *parse_object(const char **json)
{
    skip_whitespace(json);
    if (**json == '{')
    {
        (*json)++;
        skip_whitespace(json);
        JSONValue *object_value = (JSONValue*)malloc(sizeof(JSONValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;

        while (**json != '}' && **json != '\0')
        {
            JSONValue *key = parse_string(json);
            if (key)
            {
                skip_whitespace(json);
                if (**json == ':')
                {
                    (*json)++;
                    JSONValue *value = parse_json(json);
                    if (value)
                    {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JSONValue*)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JSONValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value); 
                    } 
                    else 
                    {
                        free_json_value(key);
                        break;
                    }
                } 
                else 
                {
                    free_json_value(key);
                    break;
                }
            } 
            else break;

            skip_whitespace(json);
            if (**json == ',') (*json)++;
        }

        if (**json == '}')
        {
            (*json)++;
            return object_value;
        } 
        else 
        {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}

/**
 * @brief   Phân tích tổng quát một giá trị JSON
 * @details Hàm này gọi các hàm parse tương ứng với từng loại JSON như
 *          'parse_object()', 'parse_array()', 'parse_number()', v.v.
 * @param   json [in, out] Con trỏ đến chuỗi JSON
 * @return  JSONValue*  Con trỏ đến giá trị JSON đã phân tích hoặc NULL nếu lỗi
 */
JSONValue *parse_json(const char **json)
{
    skip_whitespace(json);

    switch(**json)
    {
        case 'n':
            return parse_null(json);

        case 't':
        case 'f':
            return parse_boolean(json);

        case '\"':
            return parse_string(json);

        case '[':
            return parse_array(json);

        case '{':
            return parse_object(json);

        default:
            if (isdigit(**json) || (**json == '-'))     // isdigit: '0', '1', '2' ... '9', '0' -0x30 => 0
            { 
                return parse_number(json);
            } 
            else 
            {
                // lỗi phân tích cú pháp
                return NULL;
            }
    }
}

/**
 * @brief   Giải phóng bộ nhớ của cấu trúc JSONValue
 * @details Hàm này giải phóng tất cả các bộ nhớ đã được cấp phát động trong
 *          JSONValue, bao gồm các chuỗi, mảng và object JSON.
 * @param   json_value [in] Con trỏ đến cấu trúc JSONValue cần giải phóng
 * @return  void
 */
void free_json_value(JSONValue *json_value)
{
    if (json_value == NULL) return;

    switch (json_value->type)
    {
        case JSON_STRING:
            free(json_value->value.string);
            break;

        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++)
            {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;

        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++)
            {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;

        default:
            break;
    }
}

/**
 * @brief   In nội dung của JSONValue ra màn hình (debug)
 * @details Hàm này duyệt qua JSONValue và in các phần tử ra màn hình theo
 *          định dạng cây, phù hợp để kiểm tra dữ liệu JSON sau khi parse.
 * @param   json_value [in] Con trỏ đến cấu trúc JSONValue cần hiển thị
 * @return  void
 */
void test(JSONValue *json_value)
{
    if (json_value != NULL && json_value->type == JSON_OBJECT)
    {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        
        for (size_t i=0; i<num_fields; ++i)
        {
            char* key = json_value->value.object.keys[i];
            JSONValue* value = &json_value->value.object.values[i];
            JSONType type = json_value->value.object.values[i].type;

            if (type == JSON_STRING)
            {
                printf("%s: %s\n", key, value->value.string);
            }
            else if (type == JSON_NUMBER)
            {
                printf("%s: %0.2f\n", key, value->value.number);
            }
            else if (type == JSON_BOOLEAN)
            {
                printf("%s: %s\n", key, value->value.boolean ? "True" : "False");
            }
            else if (type == JSON_OBJECT)
            {
                printf("%s: \n", key);
                test(value);
            }
            else if (type == JSON_ARRAY)
            {
                printf("%s: ", key);
                for (int i = 0; i < value->value.array.count; i++) test(value->value.array.values + i);
                printf("\n");
            }  
        }  
    } 
    else 
    {
        if (json_value->type == JSON_STRING)
        {
            printf("%s ", json_value->value.string);
        }
        else if (json_value->type == JSON_NUMBER)
        {
            printf("%0.2f ", json_value->value.number);
        }
        else if (json_value->type == JSON_BOOLEAN)
        {
            printf("%s ", json_value->value.boolean ? "True" : "False");
        }
        else if (json_value->type == JSON_OBJECT)
        {
            printf("%s: \n", json_value->value.object.keys);
            test(json_value->value.object.values);              
        }
    }
}

/**
 * @brief   Trích xuất dữ liệu từ JSON vào cấu trúc DeviceConfig
 * @details Hàm này duyệt qua các phần tử trong JSON và ánh xạ giá trị vào
 *          cấu trúc DeviceConfig tương ứng.
 * @param   json_value [in]  Con trỏ đến dữ liệu JSON đã được phân tích
 * @param   config     [out] Cấu trúc DeviceConfig cần điền dữ liệu
 * @return  void
 */
void extract_device_config(JSONValue *json_value, DeviceConfig *config) 
{
    if (json_value != NULL && json_value->type == JSON_OBJECT)
    {
        size_t num_fields = json_value->value.object.count;

        for (size_t i=0; i<num_fields; ++i)
        {
            char *key = json_value->value.object.keys[i];
            JSONValue *value = &json_value->value.object.values[i];
            JSONType type = json_value->value.object.values[i].type;

            if (type == JSON_STRING)
            {
                if (strcmp(key, "device_name") == 0)
                {
                    strncpy(config->device_name, value->value.string, sizeof(config->device_name) - 1);    
                }
                else if (strcmp(key, "firmware_version") == 0)
                {
                    strncpy(config->firmware_version, value->value.string, sizeof(config->firmware_version) - 1);
                }
            }
            else if (type == JSON_NUMBER) 
            {
                if (strcmp(key, "baud_rate") == 0) 
                {
                    config->baud_rate = (int)value->value.number;
                }
                else if (strcmp(key, "adc_resolution") == 0)
                {
                    config->adc_resolution = (int)value->value.number;
                }
                else if (strcmp(key, "pwm_frequency") == 0)
                {
                    config->pwm_frequency = (int)value->value.number;
                }
            } 
            else if (type == JSON_BOOLEAN) 
            {
                if (strcmp(key, "debug_mode") == 0)
                {
                    config->debug_mode = (int)value->value.boolean;
                }
            } 
            else if (type == JSON_OBJECT) 
            {
                extract_device_config(value, config);
            } 
            else if (type == JSON_ARRAY) 
            {
                printf("%s: ", key);
                for (size_t i=0; i<value->value.array.count; i++) extract_device_config(value->value.array.values + i, config);
                printf("\n");
            }
        }
    }
    else
    {
        if (json_value->type == JSON_STRING)
        {
            printf("%s ", json_value->value.string);
        }
        else if (json_value->type == JSON_NUMBER)
        {
            printf("%0.2f ", json_value->value.number);
        }
        else if (json_value->type == JSON_BOOLEAN)
        {
            printf("%s ", json_value->value.boolean ? "True" : "False");
        }
        else if (json_value->type == JSON_OBJECT)
        {
            printf("%s: \n", json_value->value.object.keys);
            extract_device_config(json_value->value.object.values, config);              
        }
    }
}

/**
 * @brief   Hiển thị thông tin của DeviceConfig
 * @details Hàm này in ra các thông tin đã được trích xuất từ JSON
 * @param   config [in] Cấu trúc chứa thông tin thiết bị
 * @return  void
 */
void print_device_config(const DeviceConfig config) 
{
    printf("Device Name: %s\n", config.device_name);
    printf("Firmware Version: %s\n", config.firmware_version);
    printf("Parameters:\n");
    printf("    - Baud Rate: %d\n", config.baud_rate);
    printf("    - ADC Resolution: %d-bit\n", config.adc_resolution);
    printf("    - PWM Frequency: %d Hz\n", config.pwm_frequency);
    printf("    - Debug Mode: %s\n", config.debug_mode ? "Enabled" : "Disabled");
}