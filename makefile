# Nom des exécutables
EXEC = run
TEST_EXEC = test_joints

# Compilateur
CXX = g++

# Dossiers
SRC_DIR = src
TEST_DIR = tests
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Flags compilation
CXXFLAGS = -std=c++17 -I$(INC_DIR) $(shell pkg-config --cflags pinocchio eigen3)

# Flags linkage
LDFLAGS = $(shell pkg-config --libs pinocchio eigen3)
TEST_LDFLAGS = $(LDFLAGS) -lgtest -lgtest_main -lpthread

# Sources
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

# Exclure main.cpp pour les tests
SRCS_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))

# Objets
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
OBJS_NO_MAIN = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS_NO_MAIN))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.test.o,$(TEST_SRCS))

# Dépendances auto
DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# Exécutables
TARGET = $(BIN_DIR)/$(EXEC)
TEST_TARGET = $(BIN_DIR)/$(TEST_EXEC)

# =========================
# Règles principales
# =========================
all: $(TARGET)

tests: $(TEST_TARGET)

# =========================
# Link programme principal
# =========================
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# =========================
# Link tests (sans main.cpp)
# =========================
$(TEST_TARGET): $(OBJS_NO_MAIN) $(TEST_OBJS) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(TEST_LDFLAGS)

# =========================
# Compilation src
# =========================
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# =========================
# Compilation tests
# =========================
$(BUILD_DIR)/%.test.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# =========================
# Création dossiers
# =========================
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# =========================
# Nettoyage
# =========================
clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

# =========================
# Dépendances
# =========================
-include $(DEPS)

.PHONY: all clean fclean re tests