include Make.defaults
include Make.rules


SRC := $(shell find src -name *.sign)


STAGE1_LEX := $(BUILD_DIR)/stage1.lex
STAGE2_LEX := $(BUILD_DIR)/stage2.lex
STAGE3_LEX := $(BUILD_DIR)/stage3.lex

STAGE1_PARSE := $(BUILD_DIR)/stage1.parse
STAGE2_PARSE := $(BUILD_DIR)/stage2.parse
STAGE3_PARSE := $(BUILD_DIR)/stage3.parse

STAGE1_GEN := $(BUILD_DIR)/stage1.c
STAGE2_GEN := $(BUILD_DIR)/stage2.c
STAGE3_GEN := $(BUILD_DIR)/stage3.c


STAGE_1 := $(BUILD_DIR)/stage1
STAGE_2 := $(BUILD_DIR)/stage2
STAGE_3 := $(BUILD_DIR)/stage3
SIGNC := $(BIN_DIR)/signc


.PHONY: all
all: $(STAGE_3)
	@

.PHONY: install
install: .$(SIGNC)
	@

# Only delete $(BIN_DIR) if we know it is safe (not set by user)
ifeq ($(origin SIGN_INSTALL_PATH),file)
.PHONY: clean-bin
clean-bin: clean
	@$(RM) -r $(BIN_DIR)
endif

.PHONY: clean
clean::
	@$(RM) -r $(BUILD_DIR)


.PHONY: signc
signc: .$(SIGNC)
	@

.PHONY: stage1
stage1: $(STAGE_1)
	@

.PHONY: stage2
stage2: $(STAGE_2)
	@

.PHONY: stage3
stage3: $(STAGE_3)
	@


$(STAGE1_LEX): $(SRC) | $(BUILD_DIR)
	@$(SIGNC) -l $(SRC) > $@

$(STAGE1_PARSE): $(SRC) | $(BUILD_DIR)
	@$(SIGNC) -p $(SRC) > $@

$(STAGE1_GEN): $(SRC) | $(BUILD_DIR)
	@$(SIGNC) -g $(SRC) > $@

$(STAGE_1): $(STAGE1_LEX) $(STAGE1_PARSE) $(STAGE1_GEN)
	@$(CC) $(CCFLAGS) -o $@ $(STAGE1_GEN)


$(STAGE2_LEX): $(STAGE_1) $(SRC)
	@$< -l $(SRC) > $@

$(STAGE2_PARSE): $(STAGE_1) $(SRC)
	@$< -p $(SRC) > $@

$(STAGE2_GEN): $(STAGE_1) $(SRC)
	@$< -g $(SRC) > $@

$(STAGE_2): $(STAGE2_LEX) $(STAGE2_PARSE) $(STAGE2_GEN)
	@$(CC) $(CCFLAGS) -o $@ $(STAGE2_GEN)


$(STAGE3_LEX): $(STAGE_2) $(SRC)
	@$< -l $(SRC) > $@

$(STAGE3_PARSE): $(STAGE_2) $(SRC)
	@$< -p $(SRC) > $@

$(STAGE3_GEN): $(STAGE_2) $(SRC)
	@$< -g $(SRC) > $@

$(STAGE_3): $(STAGE3_LEX) $(STAGE3_PARSE) $(STAGE3_GEN)
	@$(CC) $(CCFLAGS) -o $@ $(STAGE3_GEN)


.$(SIGNC): $(STAGE_3) | .$(BIN_DIR)
	@diff -q $(STAGE2_LEX) $(STAGE3_LEX) >/dev/null || (echo "Stage 3 lexer failed" && exit 1)
	@diff -q $(STAGE2_PARSE) $(STAGE3_PARSE) >/dev/null || (echo "Stage 3 parser failed" && exit 1)
	@diff -q $(STAGE2_GEN) $(STAGE3_GEN) >/dev/null || (echo "Stage 3 c codegen failed" && exit 1)
	@cp $< $(SIGNC)


include Make.docker
