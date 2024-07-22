# gbadev-containers makefile
# 
# For available targets run ``make help``

# Name of the output rom file
ROMTITLE?=out.gba
export ROMTITLE

# Input source code
IN?=$(shell pwd)/in
export IN

# Output ROM build result
OUT?=$(shell pwd)/out
export OUT

# Immutable package and environment controls
BASE_IMG?=$(shell grep BASE_IMG env | cut  -f2 -d'=')
export BASE_IMG
DEVKITPRO_IMG?=$(shell grep DEVKITPRO_IMG env | cut  -f2 -d'=')
export DEVKITPRO_IMG
BUILDER?=$(shell grep BUILDER env | cut  -f2 -d'=')
export BUILDER
BUTANO?=$(shell grep BUTANO env | cut  -f2 -d'=')
export BUTANO
MGBA?=$(shell grep MGBA env | cut  -f2 -d'=')
export MGBA
SLATE?=$(shell grep SLATE env | cut  -f2 -d'=')
export SLATE
PILLOW?=$(shell grep PILLOW env | cut  -f2 -d'=')
export PILLOW
NIM?=$(shell grep NIM env | cut  -f2 -d'=')
export NIM
NATU?=$(shell grep NATU env | cut  -f2 -d'=')
export NATU

all: # Build game and container environment
	@echo "To run game: 'make run'"
all: $(OUT)/$(ROMTITLE)

.PHONY: clean
clean: # Delete ROM build result
	find "$(OUT)" -maxdepth 1 -mindepth 1 ! -name .gitkeep ! -name out -exec rm -rf {} +

.PHONY: clean-containers
clean-containers: # Delete created containers
	$(BUILDER) image rm -f gbadev-base gbadev gbadev-examples 2>/dev/null || exit 0

lint: # Lint suggestions
	$(BUILDER) run -it -v ./in:/in:ro gbadev-base bash -c 'cd /in ; cpplint --filter=-build/include_subdir,-legal/copyright,-build/header_guard ./src/* ./include/*'
lint: base-lazy

autolint: # Auto lint
	$(BUILDER) run -it -v ./in:/in gbadev-base bash -c 'cd /in ; find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i'
	$(BUILDER) run -it -v ./in:/in gbadev-base bash -c 'cd /in ; find . -name '*.cpp' | xargs -I% clang-tidy % --fix-errors -- -I/in/include'
autolint: base-lazy

doc: # Build ROM source code documentation
	mkdir -p ./out/docs
	$(BUILDER) run -it -v ./out/docs:/out/docs -v ./in:/in:ro gbadev-base bash -c 'cd /in/ ; cp Doxyfile /tmp/Doxyfile ; sed -i /tmp/Doxyfile -e "s/= docs/= \/out\/docs/" ; doxygen /tmp/Doxyfile >/dev/null'
doc: base-lazy
docs: doc

base: # Build GBA development environment
	./scripts/build.sh

base-lazy: # Build GBA development environment, only if it doesn't already exist
	$(BUILDER) image ls | grep gbadev-base || ./scripts/build.sh

examples: # Build example games
	$(BUILDER) image ls | grep gbadev-examples || ./scripts/examples.sh
	@echo "To run examples: 'make run-examples'"

run-examples: examples
run-examples: # Run example games
	./scripts/run-examples.sh

$(OUT)/$(ROMTITLE): base-lazy clean
	./scripts/gbadev.sh

run: # Run project ROM build result in mgba
	./scripts/run.sh

slate: ## Launch pixel editor
	./scripts/slate.sh
slate: base-lazy

gimp: ## Launch gimp editor
	./scripts/gimp.sh
gimp: base-lazy

help: # Show available targets
	@echo "gbadev-containers makefile\n"
	@echo "Usage: make [target]\n"
	@echo "\nBuild the gbadev environment, build the example ROM, and play it in mgba:"
	@echo "make && make run\n"
	@echo "Available targets:"
	@grep -E '^[a-zA-Z0-9_-]+: #' < Makefile
	@echo ""
usage: help
.PHONY: help

.PHONY: test
test: # Test build generates expected result
	./scripts/test.sh

