CXX := g++

CXXFLAGS := -std=c++20 -g
LDFLAGS :=
LDLIBS := -lraylib -lopengl32 -lgdi32 -lwinmm

SRC_DIR := src
OBJ_DIR := bin
TARGET := app.exe

SOURCES := $(shell powershell -NoProfile -Command "Get-ChildItem -Path '$(SRC_DIR)' -Recurse -Filter '*.cpp' | ForEach-Object { $$_.FullName.Replace((Get-Location).Path + '\', '').Replace('\','/') }")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))


all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"


clean:
	if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	if exist "$(TARGET)" del /q "$(TARGET)"


re: clean all


.PHONY: all clean re