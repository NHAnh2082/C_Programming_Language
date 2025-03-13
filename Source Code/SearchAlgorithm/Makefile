# # Tên của chương trình
# TARGET = main		# main.exe

# # Thư mục chứa header và source files
# HEADER_DIR = Header
# SOURCE_DIR = Source

# # Các tệp nguồn và tệp object tương ứng
# SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
# OBJECTS = $(SOURCES:.c=.o)

# # Trình biên dịch và các cờ
# CC = gcc
# CFLAGS = -I$(HEADER_DIR) -Wall -Wextra

# # Quy tắc đầu tiên là quy tắc mặc định sẽ được thực thi
# all: $(TARGET)	# make

# # Quy tắc để tạo ra tệp thực thi
# $(TARGET): $(OBJECTS)
# 	$(CC) -o $@ $^

# # Quy tắc để biên dịch các tệp .c thành .o
# $(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
# 	$(CC) $(CFLAGS) -c -o $@ $<

# # Quy tắc để làm sạch thư mục build
# clean:
# 	rm -f $(SOURCE_DIR)/*.o $(TARGET)

# run: $(TARGET)
# 	./$(TARGET)

# # Quy tắc giả (phony target)
# .PHONY: all


# Tên file thực thi
TARGET = main

# Thư mục chứa header và source files
HEADER_DIR = Header
SOURCE_DIR = Source
BINARY_DIR = Build

# Các tệp nguồn và tệp object tương ứng
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.c=$(BINARY_DIR)/%.o)

# Trình biên dịch và các cờ
CC = gcc
CFLAGS = -I$(HEADER_DIR) -Wall -Wextra

# Quy tắc đầu tiên là quy tắc mặc định sẽ được thực thi
all: $(BINARY_DIR)/$(TARGET)	# make

# Tạo thư mục bin nếu chưa tồn tại
$(BINARY_DIR):
	mkdir -p $(BINARY_DIR)

# Quy tắc để tạo ra tệp thực thi
$(BINARY_DIR)/$(TARGET): $(OBJECTS) | $(BINARY_DIR)
	$(CC) -o $@ $^

# Quy tắc để biên dịch các tệp .c thành .o
$(BINARY_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BINARY_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Quy tắc để làm sạch thư mục build
clean:
	rm -f $(BINARY_DIR)/*.o $(BINARY_DIR)/$(TARGET)

run: $(BINARY_DIR)/$(TARGET)
	./$(BINARY_DIR)/$(TARGET)

# Quy tắc giả (phony target)
.PHONY: all