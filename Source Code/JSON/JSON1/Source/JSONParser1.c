/*******************************************************************************
 * @file    JSONParser1.h
 * @brief   Thư viện phân tích cú pháp JSON đơn giản.
 * @details Triển khai các chức năng để phân tích và quản lý dữ liệu JSON cho sẵn,
 *          bao gồm các kiểu dữ liệu cơ bản như null, boolean, số, chuỗi,
 *          mảng và object.
 * @version 1.0
 * @date    2025-03-12
 * @author  Nguyễn Văn Thưởng
 ******************************************************************************/
#include "..\\Header\\JSONParser1.h"

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

    if (strncmp(*json, "null", 4) == 0) // strncmp # strcmp // nula
    {
        value->type = JSON_NULL;    // 0x01 0x02 0x03 0x04
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
    char *end;  // "123abc"

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

    switch(**json)  // ! @ # $ 
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
void display(JSONValue *json_value)
{
    if (json_value != NULL && json_value->type == JSON_OBJECT){
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        // size_t num_fields2 = json_value->value.object.values->value.object.count;
        
        for (size_t i = 0; i < num_fields; ++i)
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
                printf("%s: %f\n", key, value->value.number);
            }
            else if (type == JSON_BOOLEAN)
            {
                printf("%s: %s\n", key, value->value.boolean ? "True" : "False");
            }
            else if (type == JSON_OBJECT)
            {
                printf("%s: \n", key);
                display(value);
            }
            else if (type == JSON_ARRAY)
            {
                printf("%s: ", key);
                for (int i = 0; i < value->value.array.count; i++) display(value->value.array.values + i);
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
            printf("%f ", json_value->value.number);
        }
        else if (json_value->type == JSON_BOOLEAN)
        {
            printf("%s ", json_value->value.boolean ? "True":"False");
        }
        else if (json_value->type == JSON_OBJECT)
        {
            printf("%s: \n", json_value->value.object.keys);
            display(json_value->value.object.values);              
        }
    }
}