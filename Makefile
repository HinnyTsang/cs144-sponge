DOCKERRUN := docker-compose run
BUILD_DIR := --workdir /home/cs144/build
CONTAINER := cs144

.PHONY: docker-build
docker-build:
	docker-compose build

.PHONY: setup
setup:
	$(DOCKERRUN) $(CONTAINER) mkdir -p ./build
	$(DOCKERRUN) $(BUILD_DIR) $(CONTAINER) ../scripts/setup.sh

.PHONY: build
build:
	$(DOCKERRUN) $(BUILD_DIR) $(CONTAINER) make

# Usage: make chaek lab=n
.PHONY: check
check:
	$(DOCKERRUN) $(BUILD_DIR) $(CONTAINER) make check_lab$(lab)

.PHONT: format
format:
	$(DOCKERRUN) $(BUILD_DIR) $(CONTAINER) make format

.PHONY: lab0
lab0:
	$(DOCKERRUN) $(BUILD_DIR) $(CONTAINER) ../scripts/lab0.sh