#include <stdio.h>
#include <string.h>


/**************************************************************************
 * @struct  SinhVien
 * @brief   Cấu trúc dữ liệu lưu trữ thông tin sinh viên
 * @details Cấu trúc này bao gồm tên, điểm trung bình và ID của sinh viên.
 **************************************************************************/
typedef struct 
{
    char ten[50];
    float diemTrungBinh;
    int id;  
} SinhVien;


/**************************************************************************
 * @brief   So sánh hai chuỗi ký tự
 * @details Hàm so sánh hai chuỗi ký tự từng ký tự một.
 *          Nếu chuỗi đầu lớn hơn chuỗi thứ hai thì trả về giá trị dương,
 *          ngược lại trả về giá trị âm, và trả về 0 nếu hai chuỗi bằng nhau
 * @param   str1   Con trỏ tới chuỗi ký tự đầu
 * @param   str2   Con trỏ tới chuỗi ký tự thứ hai
 * @return  int    Kết quả so sánh giữa hai chuỗi
 **************************************************************************/
int stringCompare(const char *str1, const char *str2) 
{
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}


/**************************************************************************
 * @brief   Hàm so sánh tên của hai sinh viên
 * @details Sử dụng hàm `stringCompare` để so sánh trường `ten` của hai sinh viên.
 * @param   a   Con trỏ tới đối tượng sinh viên đầu tiên
 * @param   b   Con trỏ tới đối tượng sinh viên thứ hai
 * @return  int Kết quả so sánh tên của hai sinh viên
 **************************************************************************/
int compareByName(const void *a, const void *b) 
{
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;
    return stringCompare(sv1->ten, sv2->ten);
}


/**************************************************************************
 * @brief   Hàm so sánh điểm trung bình của hai sinh viên
 * @details Hàm so sánh trường `diemTrungBinh` của hai sinh viên.
 *          Trả về 1 nếu `sv1` có điểm trung bình lớn hơn `sv2`, nhỏ hơn thì
 *          trả về -1, ngược lại thì trả về 0.
 * @param   a   Con trỏ tới đối tượng sinh viên đầu tiên
 * @param   b   Con trỏ tới đối tượng sinh viên thứ hai
 * @return  int Kết quả so sánh điểm trung bình
 **************************************************************************/
int compareByDiemTrungBinh(const void *a, const void *b) 
{
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;
    if (sv1->diemTrungBinh > sv2->diemTrungBinh)
        return  1;
    else if (sv1->diemTrungBinh < sv2->diemTrungBinh)
        return -1;
    else
        return  0;
}


/**************************************************************************
 * @brief   Hàm so sánh ID của hai sinh viên
 * @details So sánh giá trị của trường `id` giữa hai sinh viên.
 * @param   a   Con trỏ tới đối tượng sinh viên đầu tiên
 * @param   b   Con trỏ tới đối tượng sinh viên thứ hai
 * @return  int Kết quả so sánh ID của hai sinh viên
 **************************************************************************/
int compareByID(const void *a, const void *b) 
{
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;
   return sv1->id - sv2->id;
}

/**************************************************************************
 * @brief   Hoán đổi hai sinh viên
 * @details Hàm này thực hiện hoán đổi dữ liệu giữa hai đối tượng sinh viên.
 *          Sử dụng biến tạm thời `temp` để lưu trữ tạm thời thông tin của
 *          sinh viên thứ nhất trong quá trình hoán đổi.
 * @param   a  Con trỏ đến đối tượng sinh viên thứ nhất
 * @param   b  Con trỏ đến đối tượng sinh viên thứ hai
 * @return  void
 **************************************************************************/
void swapSV(SinhVien *a, SinhVien *b)
{
    SinhVien temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


/**************************************************************************
 * @brief   Hàm sắp xếp danh sách sinh viên
 * @details Hàm thực hiện sắp xếp danh sách sinh viên theo tiêu chí được chỉ định
 *          bởi hàm so sánh `compareFunc` (theo tên, điểm trung bình hoặc ID).
 * @param   array        Mảng chứa danh sách sinh viên
 * @param   size         Kích thước của mảng
 * @param   compareFunc  Con trỏ tới hàm so sánh
 * @return  void
 **************************************************************************/
void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *)) 
{
    int i, j;
    SinhVien temp;
    for (i = 0; i < size-1; i++)    
        for (j = i+1; j < size; j++)
            if (compareFunc(array+i, array+j)>0) {
                swapSV(array+i,array+j);
            }
}


/**************************************************************************
 * @brief   Hiển thị danh sách sinh viên
 * @details Hàm in ra thông tin của từng sinh viên trong mảng.
 * @param   array  Con trỏ tới mảng chứa danh sách sinh viên
 * @param   size   Kích thước của mảng
 * @return  void
 **************************************************************************/
void display(SinhVien *array, size_t size) 
    {
    for (size_t i = 0; i < size; i++) {
        printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
    }
    printf("\n");
}


int main() 
{
    SinhVien danhSachSV[] = {
        {  
            .ten = "Hoang",
            .diemTrungBinh = 7.5,
            .id = 100
        },
        {
            .ten = "Tuan",
            .diemTrungBinh = 4.5,
            .id = 101
        },
        {
            .ten = "Vy",
            .diemTrungBinh = 6.8,
            .id = 102},
        {  
            .ten = "Ngan",
            .diemTrungBinh = 5.6,
            .id = 10
        },
    };
    size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);

    // Sắp xếp theo tên
    sort(danhSachSV, size, compareByName);
    display(danhSachSV, size);

    // Sắp xếp theo điểm trung bình
    sort(danhSachSV, size, compareByDiemTrungBinh);
    display(danhSachSV, size);

    // Sắp xếp theo ID
    sort(danhSachSV, size, compareByID);
    display(danhSachSV, size);

    return 0;
}