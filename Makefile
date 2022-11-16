DOCKERRUN := docker-compose run
BUILD_DIR := --workdir /home/cs144/build
CONTAINER := cs144

.PHONY: docker-build
docker-build:
	docker-compose build

.PHONY: setup-build-directory
setup-build-directory:
	$(DOCKERRUN) $(CONTAINER) mkdir -p ./build
	$(DOCKERRUN) $(BUILD_DIR) $(CONTAINER) cmake ..
	$(DOCKERRUN) $(BUILD_DIR) $(CONTAINER) make -j10


