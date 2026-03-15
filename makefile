# Nom de l'exécutable
EXEC = run

# Compilateur
CXX = g++

# Dossiers
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Flags compilation
CXXFLAGS = -std=c++17 -I$(INC_DIR) $(shell pkg-config --cflags pinocchio eigen3)

# Flags linkage
LDFLAGS = $(shell pkg-config --libs pinocchio eigen3)

# Sources
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Objets
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Dépendances auto
DEPS = $(OBJS:.o=.d)

# Exécutable final
TARGET = $(BIN_DIR)/$(EXEC)

# Règle principale
all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compilation objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Création dossiers
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

# Inclusion des dépendances
-include $(DEPS)

.PHONY: all clean fclean re